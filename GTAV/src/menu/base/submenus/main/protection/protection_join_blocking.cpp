#include "protection_join_blocking.h"
#include "menu/base/submenu_handler.h"
#include "../protections.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "rage/api/api.h"

using namespace protection::joining::vars;

namespace protection::joining::vars {
	variables m_vars;

	void block_resolves() {
		m_vars.m_spoof = false;

		if (m_vars.m_block) {
			rage::network::gs_session session;
			memset(&session, 0, sizeof(session));
			rage::engine::set_gsinfo(&session);
		} else {
			rage::network::network_base_config* real_config = global::vars::g_network_base_config;
			if (global::vars::g_steam) {
				real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
			}

			rage::engine::set_gsinfo(real_config->get_gs_session());
		}
	}

	void resolve_player() {
		memset(&m_vars.m_spoof_info, 0, sizeof(m_vars.m_spoof_info));

		rage::network::rockstar_identifier* identifier = new rage::network::rockstar_identifier();
		identifier->m_rockstar_id = m_vars.m_target;
		identifier->m_type = 3;

		global::vars::g_gs_info_requests.push_back({ false, 1, m_vars.m_target, GetTickCount() + 10000, [](std::string gs, uint64_t rockstar_id) {
			if (rage::engine::get_session_info_from_gs(&m_vars.m_spoof_info, gs.c_str())) {
				menu::notify::stacked(protection_join_blocking_menu::get()->get_name().get(), util::va::va("%s %i!", protection_join_blocking_menu::get()->get_string("Successfully spoofed resolve to host of target players session. The hosts Rockstar ID is").c_str(), m_vars.m_spoof_info.m_rockstar_id), global::ui::g_success);
			}
		} });

		native::clear_gamer_task_data();
		rage::engine::send_session_info_request(identifier, 1);
		delete identifier;
	}

	void input_player_rid_callback(button_option* option, const char* result) {
		if (std::find_if(begin(global::vars::g_gs_info_requests), end(global::vars::g_gs_info_requests), [](gs_info_request& elem) { return elem.m_type == 1; }) != end(global::vars::g_gs_info_requests)) {
			menu::notify::stacked(protection_join_blocking_menu::get()->get_name().get(), protection_join_blocking_menu::get()->get_string("There's already a pending query running, please wait for it to finish"), global::ui::g_error);
			return;
		}

		std::string string_name(result);
		if (std::find_if(string_name.begin(), string_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == string_name.end()) {
			if (atoll(string_name.c_str()) > 0x1000) {
				m_vars.m_target = atoll(string_name.c_str());
				resolve_player();
			}
		}
	}

	void input_player_name_callback(button_option* option, const char* result) {
		if (std::find_if(begin(global::vars::g_gs_info_requests), end(global::vars::g_gs_info_requests), [](gs_info_request& elem) { return elem.m_type == 1; }) != end(global::vars::g_gs_info_requests)) {
			menu::notify::stacked(protection_join_blocking_menu::get()->get_name().get(), protection_join_blocking_menu::get()->get_string("There's already a pending query running, please wait for it to finish"), global::ui::g_error);
			return;
		}

		rage::api::get_profiles_from_name(result, [=](bool success, std::vector<rage::api::rockstar_account> accounts, rage::api::result_info* out_info) {
			if (success && !accounts.empty()) {
				m_vars.m_target = accounts[0].m_rockstar_id;
				resolve_player();
			} else {
				menu::notify::stacked(protection_join_blocking_menu::get()->get_name().get(), protection_join_blocking_menu::get()->get_string("Failed to resolve Rockstar ID"), global::ui::g_error);
			}

			if (out_info) {
				delete out_info;
			}
		}, nullptr);
	}
}

void protection_join_blocking_menu::load() {
	set_name("Join Blocking");
	set_parent<protection_menu>();

	add_option(toggle_option("Block Resolves")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_block)
		.add_click(block_resolves).add_savable(get_submenu_name_stack())
		.add_tooltip("Block players from joining you via Social Club and Rockstar ID joiners"));

	add_option(toggle_option("Spoof Resolves")
		.add_translate()
		.add_toggle(m_vars.m_spoof)
		.add_click([] { m_vars.m_block = true; if (!m_vars.m_spoof) m_vars.m_spoof_info.m_peer_token = 0; })
		.add_tooltip("Spoof to another player so that other players attempting to join your session join someone else's instead"));

	add_option(button_option("Input Target Rockstar ID")
		.add_translate()
		.add_keyboard("Enter target players Rockstar ID", 30, input_player_rid_callback)
		.add_requirement([] { return m_vars.m_spoof; }));

	add_option(button_option("Input Target Name")
		.add_translate()
		.add_keyboard("Enter target players name", 30, input_player_name_callback)
		.add_requirement([] { return m_vars.m_spoof; }));

	m_vars.m_preview_button = add_option(button_option("")
		.add_requirement([] { return m_vars.m_spoof && m_vars.m_target > 0 && m_vars.m_spoof_info.m_peer_token > 0; }));

	add_string("Failed to find a session for that player, block has been enabled");
	add_string("Failed to find a session for that player, they may be offline");
	add_string("Failed to resolve Rockstar ID");
	add_string("There's already a pending query running, please wait for it to finish");
	add_string("Successfully spoofed resolve to host of target players session. The hosts Rockstar ID is");
	add_string("Spoofed to");
}

void protection_join_blocking_menu::update() {
	m_vars.m_preview_button->set_name(get_string("Spoofed to") + " " + std::to_string(m_vars.m_target));
}

void protection_join_blocking_menu::update_once() {}

void protection_join_blocking_menu::feature_update() {
	if (!global::vars::g_gs_info_requests.empty()) {
		for (std::size_t i = 0; i < global::vars::g_gs_info_requests.size(); i++) {
			if (global::vars::g_gs_info_requests[i].m_type == 1) {
				if (global::vars::g_gs_info_requests[i].m_finished) {
					global::vars::g_gs_info_requests.erase(global::vars::g_gs_info_requests.begin() + i);
					continue;
				}

				if (global::vars::g_gs_info_requests[i].m_expiry < GetTickCount()) {
					if (m_vars.m_spoof) {
						if (menu::base::get_current_option() >= 2) menu::base::set_current_option(1);
						m_vars.m_spoof = false;
						m_vars.m_block = true;
						block_resolves();
						menu::notify::stacked(get_name().get(), get_string("Failed to find a session for that player, block has been enabled"), global::ui::g_error);
					} else {
						menu::notify::stacked(get_name().get(), get_string("Failed to find a session for that player, they may be offline"), global::ui::g_error);
					}

					global::vars::g_gs_info_requests.erase(global::vars::g_gs_info_requests.begin() + i);
				}
			}

			if (global::vars::g_gs_info_requests[i].m_type == 69) {
				if (global::vars::g_gs_info_requests[i].m_finished) {
					global::vars::g_gs_info_requests.erase(global::vars::g_gs_info_requests.begin() + i);
					continue;
				}

				if (global::vars::g_gs_info_requests[i].m_expiry < GetTickCount()) {
					global::vars::g_gs_info_requests.erase(global::vars::g_gs_info_requests.begin() + i);
				}
			}
		}
	}
}

protection_join_blocking_menu* g_instance;
protection_join_blocking_menu* protection_join_blocking_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_join_blocking_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}