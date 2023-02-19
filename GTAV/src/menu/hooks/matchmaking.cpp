#include "hooks.h"
#include "menu/base/submenus/main/network/network_session_finder.h"
#include "menu/base/submenu_handler.h"
#include "rage/engine.h"
#include "rage/ros.h"
#include "util/threads.h"
#include <random>

bool menu::hooks::read_matchmaking_response(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	if (rcx) {
		if (*(uint32_t*)(rcx + 0xE00) > 15) {
			uint64_t xml_context = rage::engine::read_xml_string(r8, "Results", 0, 1);
			if (xml_context) {
				std::vector<uint64_t> rockstar_ids;

				rage::types::xml_node* node = *(rage::types::xml_node**)(xml_context + 0x30);
				while (node) {
					if (node->m_name) {
						if (!_stricmp(node->m_name, "R")) {
							const char* attribute_string = rage::engine::read_xml_attribute_string(node, "Data", 0);
							if (attribute_string) {
								if (*attribute_string) {
									std::vector<session_browser>& sessions = network::sfinder::vars::m_vars.m_sessions;

									rage::network::gs_session session;
									if (rage::engine::get_session_info_from_gs(&session, attribute_string)) {
										if (std::find_if(begin(sessions), end(sessions), [=](session_browser& element) { return element.m_rockstar_id == session.m_rockstar_id.m_rockstar_id; }) == end(sessions)) {
											sessions.push_back({ session.m_rockstar_id.m_rockstar_id, session.m_peer_token, "", false, session.get_local_ip(), session.m_peer_token2, session.m_peer_token3 });
											rockstar_ids.push_back(session.m_rockstar_id.m_rockstar_id);
										}
									}
								}
							}
						}
					}

					node = node->m_next;
				}

				if (!rockstar_ids.empty()) {
					uint32_t* rids = new uint32_t[rockstar_ids.size()];

					for (std::size_t i = 0; i < rockstar_ids.size(); i++) {
						rids[i] = (uint32_t)rockstar_ids[i];
					}

					uint64_t* info = new uint64_t[2];
					*(uint64_t*)((uint64_t)info) = (uint64_t)rockstar_ids.size();
					*(uint64_t*)((uint64_t)info + 8) = (uint64_t)rids;
					
					util::threads::add_job([](void* lp) {
						uint64_t count = *(uint64_t*)((uint64_t)lp);
						uint32_t* ridss = (uint32_t*)*(uint64_t*)((uint64_t)lp + 8);

						rage::ros::send_stat_requests(ridss, (int)count);

						for (uint64_t i = 0; i < count; i++) {
							if (global::vars::g_unloading) return;

							if (menu::submenu::handler::get_current() != network_session_finder_menu::get()) {
								if (std::find_if(begin(network::sfinder::vars::m_vars.m_image_queue), end(network::sfinder::vars::m_vars.m_image_queue), [=](uint64_t rid) { return (uint32_t)rid == ridss[i]; }) == end(network::sfinder::vars::m_vars.m_image_queue)) network::sfinder::vars::m_vars.m_image_queue.push_back(ridss[i]);
								return;
							}

							rage::ros::download_player_image(ridss[i]);
						}

						delete[] ridss;
						delete[] lp;
					}, info);
				}
			}

			return true;
		}
	}

	return read_matchmaking_response_t(rcx, rdx, r8, r9);
}

bool menu::hooks::write_matchmaking_request(uint64_t rcx, uint32_t rs_index, uint32_t available_slots, uint64_t filter_info, uint32_t max_results, uint64_t stack_20, uint64_t stack_18) {
	if (network::sfinder::vars::m_vars.m_populate) {
		if (menu::submenu::handler::get_current() == network_session_finder_menu::get()) {
			return write_matchmaking_request_t(rcx, rs_index, network::sfinder::vars::m_vars.m_minimum_slots, filter_info, 1600, stack_20, stack_18);
		}
	}

	return write_matchmaking_request_t(rcx, rs_index, available_slots, filter_info, max_results, stack_20, stack_18);
}

bool menu::hooks::write_encrypted_string_to_request(uint64_t rcx, const char* name, char* value, bool encrypted, uint64_t stack_3C8, uint64_t stack_3C0) {
	if (name && network::sfinder::vars::m_vars.m_populate) {
		if (menu::submenu::handler::get_current() == network_session_finder_menu::get()) {
			if (!strcmp(name, "filterName")) {
				value = "Group";
			}

			if (!strcmp(name, "filterParamsJson")) {
				std::random_device r;
				std::seed_seq seed2 { r(), r(), r(), r(), r(), r(), r(), r() };
				std::mt19937 rng(seed2);
				std::uniform_int_distribution<int> val(0, 8);

				nlohmann::json json;
				json["GAME_MODE"] = 0;
				json["MMATTR_DISCRIMINATOR"] = nlohmann::json::parse(value)["MMATTR_DISCRIMINATOR"];
				json["MMATTR_MM_GROUP_2"] = 30;
				json["MMATTR_REGION"] = val(rng);
				strcpy(value, json.dump().c_str());
			}
		}
	}

	return write_encrypted_string_to_request_t(rcx, name, value, encrypted, stack_3C8, stack_3C0);
}