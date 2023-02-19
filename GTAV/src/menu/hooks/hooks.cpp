#include "hooks.h"
#include "util/memory/pattern.h"
#include "util/memory/memory.h"
#include "util/hooking/hooking.h"
#include "util/log.h"
#include "util/caller.h"
#include "global/vars.h"
#include "rage/invoker/natives.h"
#include "menu/base/util/helpers.h"
#include "util/util.h"
#include "util/threads.h"
#include "rage/types/ros_types.h"
#include "rage/ros.h"
#include "auth/crypto/crypto.h"
#include <intrin.h>
#include "menu/base/submenus/main/network/network_host_toolkit.h"
#include "menu/base/submenus/main/network/network_spoofing.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_rid.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_name.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_ip.h"
#include "menu/base/submenus/main.h"
#include "security/security.h"
#include "menu/base/util/global.h"

namespace menu::hooks {
	static uint64_t g_get_current_gta_thread;
	static uint64_t g_timeout_fix_funcs[5];

	bool(*player_peer_something_t)(uint64_t rcx, int edx);
	bool player_peer_something(uint64_t rcx, int edx) {
		if (edx >= 0) {
			uint64_t ptr = *(uint64_t*)(rcx + (edx * 8) + 0x1808);
			if (*(uint64_t*)(ptr + 0x60) == network::spoofing::vars::m_vars.m_original_peer) {
				*(uint64_t*)(ptr + 0x60) = network::spoofing::vars::m_vars.m_spoofed_peer;
			}
		}

		return player_peer_something_t(rcx, edx);
	}

	bool(*read_join_response_t)(uint64_t rcx, uint64_t rdx, int r8d, uint64_t r9);
	bool read_join_response(uint64_t rcx, uint64_t rdx, int r8d, uint64_t r9) {
		LOG_DEV("Join response called");

		bool _return = read_join_response_t(rcx, rdx, r8d, r9);
		if (_return) {
			if (*(int*)(rcx) == 40) {
				LOG(XOR("The host has told us to change our peer, let's do that..."));

				std::random_device r;
				std::seed_seq seed2 { r(), r(), r(), r(), r(), r(), r(), r() };
				std::mt19937 rng(seed2);
				std::uniform_int_distribution<int> val(5, 30);
				network::spoofing::vars::do_peer_spoof(val(rng), true);

				*(int*)(rcx) = 0;
			}

			LOG_DEV("Join response -> %i", *(int*)(rcx));
		}

		return _return;
	}

	bool(*send_join_response_t)(uint64_t rcx, uint64_t rdx, uint32_t r8d, uint64_t r9);
	bool send_join_response(uint64_t rcx, uint64_t rdx, uint32_t r8d, uint64_t r9) {
		if (global::vars::g_change_peer) {
			global::vars::g_change_peer = false;

			if (network::htoolkit::vars::m_vars.m_peer_token_correction) {
				*(int*)(rcx) = 40;
			}
		}

		return send_join_response_t(rcx, rdx, r8d, r9);
	}
	
	bool(*network_has_received_host_broadcast_data_t)();
	bool network_has_received_host_broadcast_data() {
		rage::script::gta_thread* thread = caller::call<rage::script::gta_thread*>(g_get_current_gta_thread);
		if (is_valid_ptr(thread)) {
			rage::script::game_script_handler_network_component* comp = thread->m_net_component;
			if (is_valid_ptr(comp)) {
				uint64_t unk = *(uint64_t*)((uint64_t)comp + 0x30);
				if (is_valid_ptr(unk)) {
					uint64_t unk2 = *(uint64_t*)(unk + 0x10);
					if (is_valid_ptr(unk2)) {
						uint64_t unk3 = *(uint64_t*)(unk2 + 0x10);
						if (is_valid_ptr(unk3)) {
							return network_has_received_host_broadcast_data_t();
						}
					}
				}
			}
		}
		
		return false;
	}

	bool(*join_timeout_fix_t)(uint64_t);
	bool join_timeout_fix(uint64_t config) {
		uint64_t g_game_base = global::vars::g_game_address.first;
		int offset = global::vars::g_steam ? 0x70 : 0x0;

		if (!caller::call<uint8_t>(g_timeout_fix_funcs[0], *(uint64_t*)(config + 0x20 + offset))) {
			return false;
		}

		if (!*(uint64_t*)(*(uint64_t*)(g_timeout_fix_funcs[1]) + 8)) {
			return false;
		}

		uint64_t v3 = *(uint64_t*)(g_timeout_fix_funcs[2]);

		if (*(uint32_t*)(v3 + 0x288)) {
			uint32_t current_time = timeGetTime() | 1;

			uint32_t max_timeout = caller::call<uint32_t>(g_timeout_fix_funcs[5], config);
			if (current_time - *(uint32_t*)(config + 0x869C + offset) >= max_timeout - 1) {
				LOG(XOR("Join timeout detected from a 2t1 user :weary:"));

				*(uint32_t*)(config + 0x869C + offset) = current_time;
				*(uint32_t*)(v3 + 0x288) = 0;
				*(uint8_t*)(config + 0x1A96C + offset) = 0;
				return true;
			}
		}

		return join_timeout_fix_t(config);
	}

	bool spoofing() {
		bool set = false;

		std::stack<std::string> name_stack;
		name_stack.push("Spoofing");
		name_stack.push("Network");
		name_stack.push("Ozark");

		LOG_DEV("1");
		uint64_t peer = util::config::read_uint64(name_stack, "Peer", 0);
		if (peer > 0) {
			set = true;
			network::spoofing::vars::do_peer_spoof(peer);
		}

		name_stack = std::stack<std::string>();
		name_stack.push("Rockstar ID");
		name_stack.push("Spoofing");
		name_stack.push("Network");
		name_stack.push("Ozark");

		LOG_DEV("2");
		if (util::config::read_bool(name_stack, "Save to Config", false)) {
			set = true;
			network::spoofing::rid::vars::m_vars.m_spoofing_rid
				= network::spoofing::rid::vars::m_vars.m_temp_spoofing_rid
				= util::config::read_uint64(name_stack, "Rockstar ID", network::spoofing::rid::vars::m_vars.m_spoofing_rid);

			network::spoofing::rid::vars::spoof(false, network::spoofing::rid::vars::m_vars.m_spoofing_rid);
		}

		name_stack = std::stack<std::string>();
		name_stack.push("Name");
		name_stack.push("Spoofing");
		name_stack.push("Network");
		name_stack.push("Ozark");

		LOG_DEV("3");
		if (util::config::read_bool(name_stack, "Save to Config", false)) {
			set = true;
			network::spoofing::name::vars::m_vars.m_spoofed_name = util::config::read_string(name_stack, "Name", network::spoofing::name::vars::m_vars.m_spoofed_name);

			for (int i = 1; i < NUMOF(network::spoofing::name::vars::text_settings); i++) {
				if (strstr(network::spoofing::name::vars::m_vars.m_spoofed_name.c_str(), network::spoofing::name::vars::text_settings[i].m_result)) {
					network::spoofing::name::vars::m_vars.m_style = i;
					util::replace_string(network::spoofing::name::vars::m_vars.m_spoofed_name, network::spoofing::name::vars::text_settings[i].m_result, "");
					break;
				}
			}

			for (int i = 1; i < NUMOF(network::spoofing::name::vars::text_colors); i++) {
				if (strstr(network::spoofing::name::vars::m_vars.m_spoofed_name.c_str(), network::spoofing::name::vars::text_colors[i].m_result)) {
					network::spoofing::name::vars::m_vars.m_color = i;
					util::replace_string(network::spoofing::name::vars::m_vars.m_spoofed_name, network::spoofing::name::vars::text_colors[i].m_result, "");
					break;
				}
			}

			for (int i = 1; i < NUMOF(network::spoofing::name::vars::text_icons); i++) {
				if (strstr(network::spoofing::name::vars::m_vars.m_spoofed_name.c_str(), network::spoofing::name::vars::text_icons[i].m_result)) {
					network::spoofing::name::vars::m_vars.m_icon = i;
					util::replace_string(network::spoofing::name::vars::m_vars.m_spoofed_name, network::spoofing::name::vars::text_icons[i].m_result, "");
					break;
				}
			}

			network::spoofing::name::vars::m_vars.m_temp_name = network::spoofing::name::vars::m_vars.m_spoofed_name;
			network::spoofing::name::vars::spoof(false, network::spoofing::name::vars::m_vars.m_temp_name.c_str());
		}

		name_stack = std::stack<std::string>();
		name_stack.push("IP Address");
		name_stack.push("Spoofing");
		name_stack.push("Network");
		name_stack.push("Ozark");

		LOG_DEV("4");
		if (util::config::read_bool(name_stack, "Save to Config", false)) {
			set = true;
			network::spoofing::ip::vars::m_vars.m_spoofing_ip = network::spoofing::ip::vars::m_vars.m_temp_spoofing_ip = util::config::read_string(name_stack, "IP", network::spoofing::ip::vars::m_vars.m_spoofing_ip.c_str());
			network::spoofing::ip::vars::spoof(false, network::spoofing::ip::vars::m_vars.m_spoofing_ip);
		}

		LOG_DEV("5");
		return set;
	}

	bool bypass() {
		bool successful = true;
		
		memory::scan({ XOR("E8 ? ? ? ? B0 01 8B 0F 89 0B 48 8B 5B 10 48 3B DF 75 D5 F3 0F 10 07"), 0x0, XOR("NSUB"), true }, [](uint64_t address) {
			global::vars::g_nullsub = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_nullsub);
		}, successful);

		memory::scan({ global::vars::g_steam ? XOR("48 8B 69 10 48 8B F9 49 89 43 98") : XOR("48 8B 69 10 E9"), 0, XOR("RINT"), true }, [](uint64_t address) {
			return hooking::detour(XOR("RINT"), address, &rockstar_integrity, &rockstar_integrity_t);
		}, successful);

		memory::scan({ XOR("48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 70 20 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 83"), 0, XOR("PME"), true }, [](uint64_t address) {
			return hooking::detour(XOR("PME"), address, &add_metric_to_json_array, &add_metric_to_json_array_t);
		}, successful);

		memory::scan({ XOR("48 8B 5F 08 48 8B 7F 10 49 8B D6 48 8B 03 48 8B CB FF 90 ? ? ? ? 84 C0 0F 85"), -0x3A, XOR("SNE"), true }, [](uint64_t address) {
			return hooking::detour(XOR("SNE"), address, &send_network_event, &send_network_event_t);
		}, successful);

		memory::scan({ XOR("48 89 5C 24 ? 57 48 83 EC 20 48 8B 59 20 45 32 C0 8B FA 48 85 DB 74 73 48 8B 43 10 48 8B 5B 08 3B 7B"), 0, XOR("PTID"), true }, [](uint64_t address) {
			global::vars::g_process_transaction_id = address;
			return hooking::detour(XOR("PTID"), address, &process_transaction_id, &process_transaction_id_t);
		}, successful);

		return successful;
	}

	bool globals() {
		bool successful = true;

		memory::scan(XOR("socialclub.dll"), { XOR("48 8D 05 ? ? ? ? 48 03 F8 44 8B 47 14 48 8D 57 20 E8 ? ? ? ? 85"), 0, XOR("SCGIT"), true }, [](uint64_t address) {
			global::vars::g_social_club_game_info_table = memory::read_instruction(address);
			return true;
		}, successful);

		memory::scan(XOR("socialclub.dll"), { XOR("E8 ? ? ? ? 85 C0 78 27 3B 47 14 7D 1E 48 98 48 8B D6 48 69 C8"), 0, XOR("SCGGIT"), true }, [](uint64_t address) {
			global::vars::g_social_club_get_game_info_table = memory::read_instruction(address, 1, 5);
			return true;
		}, successful);

		memory::scan({ XOR("8B 05 ? ? ? ? 85 C0 0F 84 ? ? ? ? 83 F8 06 74 08 83 C0 F8"), 0, XOR("GS"), true }, [](uint64_t address) {
			global::vars::g_game_state = (game_state*)memory::read_instruction(address, 2, 6);
			return (uint64_t)global::vars::g_game_state > 0;
		}, successful);

		memory::scan(XOR("NRT"), [](uint64_t address) {
			global::vars::g_native_registration = (rage::invoker::native_registration**)memory::read_instruction(address);
			global::vars::g_translate_native = memory::read_instruction(address + 0xB, 1, 5);
			return (uint64_t)global::vars::g_native_registration > 0;
		}, successful);

		memory::scan(XOR("GSME"), [](uint64_t address) {
			global::vars::g_get_store_module_extension = address;
			return true;
		}, successful);

		memory::scan(XOR("RSF"), [](uint64_t address) {
			global::vars::g_request_streaming_file = address;
			return true;
		}, successful);

		memory::scan(XOR("CGFXF"), [](uint64_t address) {
			global::vars::g_construct_gfx_font = address;
			return true;
		}, successful);

		memory::scan(XOR("D"), [](uint64_t address) {
			global::vars::g_destruct = address;
			return true;
		}, successful);

		memory::scan(XOR("CIDFF"), [](uint64_t address) {
			global::vars::g_create_id_for_font = address;
			return true;
		}, successful);

		memory::scan(XOR("AFL"), [](uint64_t address) {
			global::vars::g_add_font_lib = address;
			return true;
		}, successful);

		memory::scan(XOR("VERTEX"), [](uint64_t address) {
			global::vars::g_vertex_begin = memory::read_instruction(address, 1, 5);
			global::vars::g_vertex_add = memory::read_instruction(address + 0x4D, 1, 5); // good
			global::vars::g_vertex_end = memory::read_instruction(address + 0x5C, 1, 5); // good
			return true;
		}, successful);

		memory::scan(XOR("RST"), [](uint64_t address) {
			global::vars::g_render_script_texture = address;
			return true;
		}, successful);

		memory::scan(XOR("FT"), [](uint64_t address) {
			global::vars::g_font_table = memory::read_instruction(address);
			return true;
		}, successful);

		memory::scan(XOR("FMH"), [](uint64_t address) {
			global::vars::g_font_memory_helper = memory::read_instruction(address);
			return true;
		}, successful);

		memory::scan(XOR("GFIDT"), [](uint64_t address) {
			global::vars::g_get_font_id_table = address;
			return true;
		}, successful);

		memory::scan(XOR("MH"), [](uint64_t address) {
			global::vars::g_memory_heap = *(rage::types::memory_heap_pt**)(memory::read_instruction(address));
			return true;
		}, successful);

		memory::scan(XOR("SM"), [](uint64_t address) {
			global::vars::g_store_manager = (rage::types::store_manager*)(memory::read_instruction(address));
			return true;
		}, successful);

		memory::scan(XOR("D3DDEV"), [](uint64_t address) {
			global::vars::g_d3d11_device = *(uint64_t*)memory::read_instruction(address);
			return true;
		}, successful);

		memory::scan(XOR("GRCTFDX"), [](uint64_t address) {
			global::vars::g_grc_texture_factory_dx11 = *(uint64_t*)memory::read_instruction(address);
			return true;
		}, successful);

		memory::scan(XOR("TLSA"), [](uint64_t address) {
			global::vars::g_thread_alloc = memory::read_instruction(address, 1, 5);
			return true;
		}, successful);

		memory::scan(XOR("SD"), [](uint64_t address) {
			global::vars::g_setup_dictionary = address;
			return true;
		}, successful);

		memory::scan(XOR("SSI"), [](uint64_t address) {
			global::vars::g_setup_store_item = memory::read_instruction(address, 1, 5);
			return true;
		}, successful);

		memory::scan(XOR("IVPS"), [](uint64_t address) {
			global::vars::g_is_valid_pool_slot = address;
			return true;
		}, successful);

		memory::scan(XOR("ADTP"), [](uint64_t address) {
			global::vars::g_add_dictionary_to_pool = address;
			return true;
		}, successful);

		memory::scan(XOR("AGRCTD"), [](uint64_t address) {
			global::vars::g_add_grc_texture_to_dictionary = address;
			return true;
		}, successful);

		memory::scan(XOR("WEATHER"), [](uint64_t address) {
			global::vars::g_get_weather_id = memory::read_instruction(address + 7, 1, 5);
			global::vars::g_weather_table = memory::read_instruction(address);
			return true;
		}, successful);

		memory::scan(XOR("socialclub.dll"), { XOR("48 8D 05 ? ? ? ? 48 03 F8 44 8B 47 14 48 8D 57 20 E8 ? ? ? ? 85"), 0, XOR("SCGIT"), false }, [](uint64_t address) {
			global::vars::g_sc_game_info_table = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_sc_game_info_table);
		}, successful);

		memory::scan(XOR("socialclub.dll"), { XOR("E8 ? ? ? ? 85 C0 78 27 3B 47 14 7D 1E 48 98 48 8B D6 48 69 C8"), 0, XOR("SCGGIT"), false }, [](uint64_t address) {
			global::vars::g_sc_get_game_info_table = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_sc_get_game_info_table);
		}, successful);

		memory::scan(XOR("GSS"), [](uint64_t address) {
			global::vars::g_game_streamed_scripts = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_game_streamed_scripts);
		}, successful);

		memory::scan(XOR("GSS_G"), [](uint64_t address) {
			global::vars::g_get_streamed_script = address;
			return is_valid_ptr(global::vars::g_get_streamed_script);
		}, successful);

		memory::scan(XOR("CPF"), [](uint64_t address) {
			global::vars::g_ped_factory = *(rage::types::ped_factory**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_ped_factory);
		}, successful);

		memory::scan(XOR("GCP"), [](uint64_t address) {
			global::vars::g_global_cache = (uint64_t**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_global_cache);
		}, successful);

		memory::scan(XOR("WCHL"), [](uint64_t address) {
			global::vars::g_weapon_components = { memory::read_instruction(address, 2, 6), memory::read_instruction(address + 0x14) }; // good
			return is_valid_ptr(global::vars::g_weapon_components.m_count) && is_valid_ptr(global::vars::g_weapon_components.m_list);
		}, successful);

		memory::scan(XOR("WIHL"), [](uint64_t address) {
			global::vars::g_weapon_info = { memory::read_instruction(address, 4, 8), memory::read_instruction(address + 0x10) }; // good
			return is_valid_ptr(global::vars::g_weapon_info.m_count) && is_valid_ptr(global::vars::g_weapon_info.m_list);
		}, successful);

		memory::scan(XOR("GCA"), [](uint64_t address) {
			global::vars::g_game_camera_angles = (rage::network::game_camera_angles*)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_game_camera_angles);
		}, successful);

		memory::scan(XOR("GTPC"), [](uint64_t address) {
			global::vars::g_get_third_person_camera = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_get_third_person_camera);
		}, successful);

		memory::scan(XOR("TPCP"), [](uint64_t address) {
			global::vars::g_third_person_camera = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_third_person_camera);
		}, successful);

		memory::scan(XOR("GEA"), [](uint64_t address) {
			global::vars::g_get_entity_address = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_get_entity_address);
		}, successful);

		memory::scan(XOR("GEH"), [](uint64_t address) {
			global::vars::g_get_entity_handle_from_address = address;
			return is_valid_ptr(global::vars::g_get_entity_handle_from_address);
		}, successful);

		memory::scan(XOR("GCNGPFI"), [](uint64_t address) {
			global::vars::g_get_net_game_player_from_index = address;
			return is_valid_ptr(global::vars::g_get_net_game_player_from_index);
		}, successful);

		memory::scan(XOR("GMI"), [](uint64_t address) {
			global::vars::g_get_model_info = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_get_model_info);
		}, successful);

		memory::scan(XOR("SVG"), [](uint64_t address) {
			global::vars::g_set_vehicle_gravity = address;
			return is_valid_ptr(global::vars::g_set_vehicle_gravity);
		}, successful);

		memory::scan(XOR("GVPA"), [](uint64_t address) {
			global::vars::g_get_vehicle_paint_array = address;
			return is_valid_ptr(global::vars::g_get_vehicle_paint_array);
		}, successful);

		memory::scan(XOR("DOI"), [](uint64_t address) {
			global::vars::g_draw_origin_index = memory::read_instruction(address, 2, 6);
			return is_valid_ptr(global::vars::g_draw_origin_index);
		}, successful);

		memory::scan(XOR("ATCT"), [](uint64_t address) {
			global::vars::g_add_to_clock_time = address;
			return is_valid_ptr(global::vars::g_add_to_clock_time);
		}, successful);

		memory::scan(XOR("DST"), [](uint64_t address) {
			global::vars::g_dispatch_service_table = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_dispatch_service_table);
		}, successful);

		// TODO: Verify weather and time are gone
		/*memory::scan(XOR("SCT"), [](uint64_t address) {
			global::vars::g_sync_clock_time = address;
			return is_valid_ptr(global::vars::g_sync_clock_time);
		}, successful);

		memory::scan(XOR("SWU"), [](uint64_t address) {
			global::vars::g_send_weather_update = address;
			return is_valid_ptr(global::vars::g_send_weather_update);
		}, successful);*/

		memory::scan(XOR("GHNGP"), [](uint64_t address) {
			global::vars::g_get_host_net_game_player = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_get_host_net_game_player);
		}, successful);

		memory::scan(XOR("SISE"), [](uint64_t address) {
			global::vars::g_send_increment_stat_event = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_send_increment_stat_event);
		}, successful);

		memory::scan(XOR("UNOO"), [](uint64_t address) {
			global::vars::g_update_net_object_owner = address;
			return is_valid_ptr(global::vars::g_update_net_object_owner);
		}, successful);

		memory::scan(XOR("NOM"), [](uint64_t address) {
			global::vars::g_network_object_manager = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_network_object_manager);
		}, successful);

		memory::scan(XOR("NPM"), [](uint64_t address) {
			global::vars::g_network_player_manager = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_network_player_manager);
		}, successful);

		memory::scan(XOR("HROFV"), [](uint64_t address) {
			global::vars::g_handle_rotation_values_from_order = address;
			return is_valid_ptr(global::vars::g_handle_rotation_values_from_order);
		}, successful);

		memory::scan(XOR("GNGPFH"), [](uint64_t address) {
			global::vars::g_get_net_game_player_from_handle = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_get_net_game_player_from_handle);
		}, successful);

		memory::scan(XOR("GST"), [](uint64_t address) {
			global::vars::g_get_sprite_texture = address;
			return is_valid_ptr(global::vars::g_get_sprite_texture);
		}, successful);

		memory::scan(XOR("STMNM"), [](uint64_t address) {
			global::vars::g_send_text_message_net_msg = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_send_text_message_net_msg);
		}, successful);

		memory::scan(XOR("STL"), [](uint64_t address) {
			global::vars::g_set_traffic_lights = address;
			return is_valid_ptr(global::vars::g_set_traffic_lights);
		}, successful);

		memory::scan(XOR("UTL"), [](uint64_t address) {
			global::vars::g_update_traffic_lights = address;
			return is_valid_ptr(global::vars::g_update_traffic_lights);
		}, successful);

		memory::scan(XOR("STLC"), [](uint64_t address) {
			global::vars::g_set_traffic_light_colors = address;
			return is_valid_ptr(global::vars::g_set_traffic_light_colors);
		}, successful);

		memory::scan(XOR("SVLC"), [](uint64_t address) {
			global::vars::g_set_vehicle_lights = address;
			return is_valid_ptr(global::vars::g_set_vehicle_lights);
		}, successful);

		memory::scan(XOR("GSTFCT"), [](uint64_t address) {
			global::vars::g_get_sync_tree_from_clone_type = address;
			return is_valid_ptr(global::vars::g_get_sync_tree_from_clone_type);
		}, successful);

		memory::scan(XOR("GNOFNI"), [](uint64_t address) {
			global::vars::g_get_network_object_from_network_id = address;
			return is_valid_ptr(global::vars::g_get_network_object_from_network_id);
		}, successful);

		memory::scan(XOR("RBFBB"), [](uint64_t address) {
			global::vars::g_read_bool_from_bit_buffer = address;
			global::vars::g_read_uint_from_bit_buffer = memory::read_instruction(address + 0x1F, 1, 5); // good
			return true;
		}, successful);

		memory::scan(XOR("RIFBB"), [](uint64_t address) {
			global::vars::g_read_int_from_bit_buffer = memory::read_instruction(address, 1, 5);
			return true;
		}, successful);

		memory::scan(XOR("RV3FBB"), [](uint64_t address) {
			global::vars::g_read_vector3_from_bit_buffer = address;
			return true;
		}, successful);

		memory::scan(XOR("RAFBB"), [](uint64_t address) {
			global::vars::g_read_array_from_bit_buffer = address;
			return true;
		}, successful);

		memory::scan(XOR("RSFBB"), [](uint64_t address) {
			global::vars::g_read_short_from_bit_buffer = address;
			return true;
		}, successful);

		memory::scan(XOR("RULLFBB"), [](uint64_t address) {
			global::vars::g_read_ulonglong_from_bit_Buffer = address;
			return true;
		}, successful);

		memory::scan(XOR("RNMHFBB"), [](uint64_t address) {
			global::vars::g_read_msg_header_from_bit_buffer = address;
			return true;
		}, successful);

		memory::scan(XOR("WUITBB"), [](uint64_t address) {
			global::vars::g_write_uint_to_bit_buffer = address;
			return true;
		}, successful);

		memory::scan(XOR("RPFBB"), [](uint64_t address) {
			global::vars::g_read_pickup_from_bit_buffer = address;
			return true;
		}, successful);

		memory::scan(XOR("GCFP"), [](uint64_t address) {
			global::vars::g_get_network_config_from_peer = address;
			return is_valid_ptr(global::vars::g_get_network_config_from_peer);
		}, successful);

		memory::scan(XOR("NER"), [](uint64_t address) {
			global::vars::g_network_event_registration = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_network_event_registration);
		}, successful);

		memory::scan(XOR("WAYP"), [](uint64_t address) {
			global::vars::g_waypoint_data = (rage::types::waypoint_data*)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_waypoint_data);
		}, successful);

		memory::scan(XOR("NSQ"), [](uint64_t address) {
			global::vars::g_net_shop_queue = *(rage::network::net_shop_queue**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_net_shop_queue);
		}, successful);

		memory::scan(XOR("UUIV1"), [](uint64_t address) {
			global::vars::g_update_ui_values = address;
			return true;
		}, successful);

		memory::scan(XOR("UUIV2"), [](uint64_t address) {
			global::vars::g_update_ui_values_2 = address;
			return true;
		}, successful);

		memory::scan(XOR("UIVS"), [](uint64_t address) {
			global::vars::g_ui_visual_settings = (rage::types::ui_visual_settings*)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_ui_visual_settings);
		}, successful);

		memory::scan(XOR("SVNUI"), [](uint64_t address) {
			global::vars::g_set_vehicle_neon_ui = address;
			return true;
		}, successful);

		memory::scan(XOR("VFXL"), [](uint64_t address) {
			global::vars::g_vfx_liquid = (rage::types::vfx_liquid*)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_vfx_liquid);
		}, successful);

		memory::scan(XOR("HVBO"), [](uint64_t address) {
			global::vars::g_set_seethrough = address;
			return true;
		}, successful);

		memory::scan(XOR("NS_ABTQ"), [](uint64_t address) {
			global::vars::g_add_basket_to_queue = address;
			return true;
		}, successful);

		memory::scan(XOR("NS_AITB"), [](uint64_t address) {
			global::vars::g_add_item_to_basket = address;
			return true;
		}, successful);

		memory::scan(XOR("SSIR"), [](uint64_t address) {
			global::vars::g_send_session_info_request = address;
			return true;
		}, successful);

		memory::scan(XOR("RSINFO"), [](uint64_t address) {
			global::vars::g_rs_info = (rage::network::rs_info*)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_rs_info);
		}, successful);

		memory::scan(XOR("GSIFGS"), [](uint64_t address) {
			global::vars::g_get_session_info_from_gs = address;
			return true;
		}, successful);

		memory::scan(XOR("SNER"), [](uint64_t address) {
			global::vars::g_send_network_event_reply = address;
			return true;
		}, successful);

		memory::scan(XOR("SNEA"), [](uint64_t address) {
			global::vars::g_send_network_event_ack = address;
			return true;
		}, successful);

		memory::scan(XOR("SGCE"), [](uint64_t address) {
			global::vars::g_setup_give_control_event = address;
			return true;
		}, successful);

		memory::scan(XOR("SFR"), [](uint64_t address) {
			global::vars::g_send_friend_request = address;
			return true;
		}, successful);

		memory::scan({ XOR("E8 ? ? ? ? 89 03 85 C0 78 21 8B 13 48 8B 8F ? ? ? ? 4C 8D 84 24 ? ? ? ? 41 B9 ? ? ? ? 4C 89 6C 24 ? E8"), 0x0, XOR("GCPK"), true }, [](uint64_t address) {
			global::vars::g_get_client_player_key = memory::read_instruction(address, 1, 5);
			return true;
		}, successful);

		memory::scan(XOR("RWOM"), [](uint64_t address) {
			global::vars::g_render_water_on_map_intensity = memory::read_instruction(address, 4, 8);
			return is_valid_ptr(global::vars::g_render_water_on_map_intensity);
		}, successful);

		memory::scan(XOR("MFI"), [](uint64_t address) {
			global::vars::g_map_fog_intensity = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_map_fog_intensity);
		}, successful);

		memory::scan(XOR("VFXW"), [](uint64_t address) {
			global::vars::g_vfx_wheel = { (rage::types::vfx_wheel*)memory::read_instruction(address), *(uint8_t*)(address + 0xA) }; // good
			return is_valid_ptr(global::vars::g_vfx_wheel.first);
		}, successful);

		memory::scan(XOR("FL"), [](uint64_t address) {
			global::vars::g_friends = *(rage::network::friends**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_friends);
		}, successful);

		memory::scan(XOR("SPE"), [](uint64_t address) {
			global::vars::g_send_presence_event = address;
			return true;
		}, successful);

		memory::scan(XOR("MSH"), [](uint64_t address) {
			global::vars::g_migrate_script_host = address;
			return true;
		}, successful);

		memory::scan(XOR("HPBR"), [](uint64_t address) {
			global::vars::g_is_reported_for_reason = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_is_reported_for_reason);
		}, successful);

		memory::scan(XOR("GCRASH"), [](uint64_t address) {
			HANDLE thread_id = *(HANDLE*)memory::read_instruction(address);
			if (thread_id) {
				LOG_DEV("Suspending game crasher thread -> ID: %i", GetThreadId(thread_id));
				SuspendThread(thread_id);
			}

			return true;
		}, successful);

		memory::scan(XOR("CHATINF"), [](uint64_t address) {
			global::vars::g_chat_info = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_chat_info);
		}, successful);

		memory::scan(XOR("TEXS"), [](uint64_t address) {
			global::vars::g_texture_store = (rage::types::texture_store*)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_texture_store);
		}, successful);

		memory::scan(XOR("SMMR"), [](uint64_t address) {
			global::vars::g_send_matchmaking_request = address;
			return true;
		}, successful);

		memory::scan(XOR("RXMLS"), [](uint64_t address) {
			global::vars::g_read_xml_string = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_read_xml_string);
		}, successful);

		memory::scan(XOR("RXMLNS"), [](uint64_t address) {
			global::vars::g_read_xml_node_string = memory::read_instruction(address, 1, 5);
			return is_valid_ptr(global::vars::g_read_xml_node_string);
		}, successful);

		memory::scan(XOR("RYTD"), [](uint64_t address) {
			global::vars::g_register_streaming_file = address;
			return true;
		}, successful);

		memory::scan(XOR("CGIP"), [](uint64_t address) {
			global::vars::g_create_game_invite_presence = address;
			return true;
		}, successful);

		memory::scan(XOR("SGIP"), [](uint64_t address) {
			global::vars::g_send_game_invite_presence = address;
			return true;
		}, successful);

		memory::scan(XOR("SGIPT"), [](uint64_t address) {
			global::vars::g_send_game_invite_presence_table = memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_send_game_invite_presence_table);
		}, successful);

		memory::scan(XOR("SRE"), [](uint64_t address) {
			global::vars::g_send_ragdoll_event = address;
			return true;
		}, successful);

		memory::scan(XOR("NODES_1"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 11 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_2"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 2 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_3"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 10 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_4"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 32 });
			return true;
		}, successful);
		
		memory::scan(XOR("NODES_5"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 11 });
			global::vars::g_return_address_node_iterations.push_back({ address + 0xBB, 3 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_6"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 32 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_7"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 30 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_8"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 3 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_9"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 105 });
			global::vars::g_return_address_node_iterations.push_back({ address + 0x4D, 65 }); // good
			return true;
		}, successful);

		memory::scan(XOR("NODES_10"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 10 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_11"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 3 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_12"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 11 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_13"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 10 });
			return true;
		}, successful);

		memory::scan(XOR("NODES_14"), [](uint64_t address) {
			global::vars::g_return_address_node_iterations.push_back({ address, 16 });
			return true;
		}, successful);

		memory::scan(XOR("GCHP"), [](uint64_t address) {
			global::vars::g_global_chat_ptr = *(uint64_t*)memory::read_instruction(address);
			return true;
		}, successful);
		
		memory::scan(XOR("APCM"), [](uint64_t address) {
			global::vars::g_add_chat_message = address;

			global::vars::g_hack_patches["CHAT"].m_address = address + 0x211;
			global::vars::g_hack_patches["CHAT"].m_patch = { 0xBF, 0x01, 0x00, 0x00, 0x00 };
			global::vars::g_hack_patches["CHAT"].read(5);

			return true;
		}, successful);

		memory::scan(XOR("PRESFIX"), [](uint64_t address) {
			global::vars::g_hack_patches["JOINP"].m_address = address;
			global::vars::g_hack_patches["JOINP"].m_patch = { 0xB0, 0x01, 0x90, 0x90, 0x90 };
			global::vars::g_hack_patches["JOINP"].read(5);
			return true;
		}, successful);

		memory::scan(XOR("GCHATS"), [](uint64_t address) {
			global::vars::g_chat_config = memory::read_instruction(address);
			return true;
		}, successful);

		memory::scan(XOR("GPIFNM"), [] (uint64_t address) {
			global::vars::g_get_player_info_from_net_msg = address;
			return true;
		}, successful);

		memory::scan(XOR("GDROPS"), [] (uint64_t address) {
			global::vars::g_drop_shaders = memory::read_instruction(address);
			global::vars::g_drop_shader_count = memory::read_instruction(address + 0x15, 2, 6); // good
			return true;
		}, successful);

		memory::scan(XOR("GNMNP"), [] (uint64_t address) {
			global::vars::g_get_net_msg_net_player = memory::read_instruction(address, 1, 5);
			return true;
		}, successful);

		memory::scan(XOR("3DPED"), [] (uint64_t address) {
			global::vars::g_ui_3d_draw_manager = memory::read_instruction(address);
			global::vars::g_push_scene_preset_to_manager = memory::read_instruction(address + 0x5D, 1, 5);// good
			global::vars::g_add_element_to_scene = memory::read_instruction(address + 0x9F, 1, 5);// good
			global::vars::g_set_scene_element_lighting = memory::read_instruction(address + 0xE4, 1, 5);// good
			return true;
		}, successful);

		memory::scan(XOR("INVALIDS"), [] (uint64_t address) {
			global::vars::g_invalid_string_address = memory::read_instruction(address + 0x18);// good
			return true;
		}, successful);

		memory::scan(XOR("BB_RTOK"), [] (uint64_t address) {
			global::vars::g_read_token_from_bit_buffer = address;
			return true;
		}, successful);

		memory::scan(XOR("BB_RST"), [] (uint64_t address) {
			global::vars::g_read_string_from_bit_buffer = address;
			return true;
		}, successful);

		// patches
		memory::scan({ XOR("48 89 5C 24 ? 57 48 83 EC 20 8B D9 E8 ? ? ? ? 84 C0 75 6A 8B CB E8"), 0xC, XOR("SPECP"), false }, [] (uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(5);
			global::vars::g_patches.push_back(patch);

			memory::write_vector(address, { 0xB0, 0x00, 0x90, 0x90, 0x90 });
			return true;
		}, successful);

		memory::scan(XOR("PMSP"), [](uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(2);
			global::vars::g_patches.push_back(patch);

			memory::write_vector(address, { 0xEB, 0x02 });
			return true;
		}, successful);

		memory::scan(XOR("MSP"), [](uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(24);
			global::vars::g_patches.push_back(patch);

			memory::nop(address, 24);
			return true;
		}, successful);

		memory::scan(XOR("RSTRB"), [](uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(3);
			global::vars::g_patches.push_back(patch);

			memory::nop(address, 3);
			return true;
		}, successful);

		memory::scan(XOR("RSTEB"), [](uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(3);
			global::vars::g_patches.push_back(patch);

			memory::nop(address, 3);
			return true;
		}, successful);

		memory::scan(XOR("AOEB"), [](uint64_t address) {
			patches patch;
			patch.m_address = memory::read_instruction(address);
			patch.read(1);
			global::vars::g_patches.push_back(patch);

			memory::write(memory::read_instruction(address), (uint8_t)0x1);
			return true;
		}, successful);

		// added
		memory::scan(XOR("NARRCF3"), [](uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(5);
			global::vars::g_patches.push_back(patch);

			memory::write_vector(address, { 0xE9, 0x7C, 0x01, 0x00, 0x00 }); // cherax crash fix
			return true;
		}, successful);

		// added
		memory::scan(XOR("CKL"), [](uint64_t address) {
			patches patch;
			patch.m_address = memory::read_instruction(address, 1, 5);
			patch.read(3);
			global::vars::g_patches.push_back(patch);

			memory::write_vector(memory::read_instruction(address, 1, 5), { 0xB0, 0x00, 0xC3 });
			return true;
		}, successful);

		// added
		memory::scan(XOR("CKK"), [](uint64_t address) {
			patches patch;
			patch.m_address = memory::read_instruction(address, 1, 5);
			patch.read(3);
			global::vars::g_patches.push_back(patch);

			memory::write_vector(memory::read_instruction(address, 1, 5), { 0xB0, 0x00, 0xC3 });
			return true;
		}, successful);

		memory::scan(XOR("PMDN"), [](uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(1);
			global::vars::g_patches.push_back(patch);

			memory::write_vector(address, { 0xC3 });
			return true;
		}, successful);

		memory::scan(XOR("SPH"), [](uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(1);
			global::vars::g_patches.push_back(patch);

			memory::write_vector(address, { 0xC3 });
			global::vars::g_ped_orientation_writer = address;
			return true;
		}, successful);

		memory::scan(XOR("SEM"), [](uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(1);
			global::vars::g_patches.push_back(patch);

			memory::write_vector(address, { 0xC3 });
			global::vars::g_entity_orientation_writer = address;
			return true;
		}, successful);

		// added
		memory::scan({ XOR("44 38 3D ? ? ? ? 74 0E B1 01 E8 ? ? ? ? 33 C9 E8"), 0x12, XOR("TCRASH"), false }, [] (uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(5);
			global::vars::g_patches.push_back(patch);

			memory::nop(address, 5);
			return true;
		}, successful);

		memory::scan({ XOR("E8 ? ? ? ? EB 61 E8 ? ? ? ? 48 8B 0D ? ? ? ? 8B 51 20 8B 41 10 C1 E2 02 C1 FA 02 2B C2 85 C0 7E 30 E8"), 0x0, XOR("ARRC2"), false }, [] (uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(5);
			global::vars::g_patches.push_back(patch);

			memory::nop(address, 5);
			return true;
		}, successful);

		/*memory::scan(XOR("C8"), [] (uint64_t address) {
			memory::write_vector(address, { 0xB0, 0x00, 0xC3 });
			return true;
		}, successful);*/

		memory::scan({ XOR("E8 ? ? ? ? 48 8B 03 8B 97 ? ? ? ? 48 8B CB FF 90 ? ? ? ? 0F B7 83 ? ? ? ? 48 8B CB"), 0, XOR("UCRASH"), false }, [] (uint64_t address) {
			patches patch;
			patch.m_address = address;
			patch.read(5);
			global::vars::g_patches.push_back(patch);

			uint32_t jump_size = (uint32_t)((address + 0x1CF) - address - 5);
			memory::write_vector(address, { 0xE9, (uint8_t)(jump_size & 0xFF), (uint8_t)(jump_size >> 8 & 0xFF), (uint8_t)(jump_size >> 16 & 0xFF), (uint8_t)(jump_size >> 24 & 0xFF) });

			return true;
		}, successful);

		return successful;
	}

	bool globals_in_game() {
		bool successful = true;

		/*memory::scan(XOR("RI"), [](uint64_t address) {
			global::vars::g_replay_interface = *(rage::types::replay_interface**)memory::read_instruction(address, 3, 7);
			return is_valid_ptr(global::vars::g_replay_interface);
		}, successful);*/

		memory::scan({ XOR("48 8B 05 ? ? ? ? 8B 78 10 85 FF"), 0, XOR("POOL_1"), true }, [] (uint64_t address) {
			global::vars::g_object_pool = *(guid_pool**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_object_pool);
		}, successful);

		memory::scan({ XOR("48 8B 05 ? ? ? ? 41 0F BF C8 0F BF 40 10"), 0, XOR("POOL_2"), true }, [] (uint64_t address) {
			global::vars::g_ped_pool = *(guid_pool**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_ped_pool);
		}, successful);
	
		memory::scan({ XOR("48 8B 0D ? ? ? ? 45 33 C9 44 8B C5 BA ? ? ? ? E8 ? ? ? ? 48"), 0, XOR("POOL_3"), true }, [] (uint64_t address) {
			global::vars::g_vehicle_pool = *(vehicle_pool**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_vehicle_pool);
		}, successful);

		memory::scan({ XOR("48 8B 05 ? ? ? ? 0F B7 48 10 66 03 CA 66 44 03 C1 41 80 F9 04"), 0, XOR("POOL_4"), true }, [] (uint64_t address) {
			global::vars::g_pickup_pool = *(guid_pool**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_pickup_pool);
		}, successful);

		memory::scan(XOR("EXPD"), [](uint64_t address) {
			global::vars::g_explosion_data = *(rage::types::explosion_data**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_explosion_data);
		}, successful);

		memory::scan(XOR("EXPFX"), [](uint64_t address) {
			global::vars::g_explosion_fx = *(rage::types::explosion_fx**)(memory::read_instruction(address) + 0x10);
			return is_valid_ptr(global::vars::g_explosion_fx);
		}, successful);

		memory::scan(XOR("NBC"), [](uint64_t address) {
			global::vars::g_network_base_config = *(rage::network::network_base_config**)(memory::read_instruction(address));
			return is_valid_ptr(global::vars::g_network_base_config);
		}, successful);

		memory::scan(XOR("OQ"), [](uint64_t address) {
			global::vars::g_ocean_quads.m_ocean = (rage::types::ocean_quad_info*)memory::read_instruction(address);
			global::vars::g_ocean_quads.m_calming = (rage::types::ocean_quad_info*)memory::read_instruction(address + 0xC);
			global::vars::g_ocean_quads.m_wave = (rage::types::ocean_quad_info*)memory::read_instruction(address + 0x25);
			return true;
		}, successful);

		memory::scan(XOR("WT"), [](uint64_t address) {
			global::vars::g_water_tune = (rage::types::water_tune*)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_water_tune);
		}, successful);

		memory::scan(XOR("VFX-S"), [](uint64_t address) {
			global::vars::g_ui_weather = (rage::types::ui_weather*)(memory::read_instruction(address) + 0x60);
			return is_valid_ptr(global::vars::g_ui_weather);
		}, successful);

		memory::scan(XOR("VFX-P"), [](uint64_t address) {
			global::vars::g_ui_puddle = *(rage::types::ui_puddle**)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_ui_puddle);
		}, successful);

		memory::scan(XOR("RESOL"), [](uint64_t address) {
			uint64_t info = memory::read_instruction(address);
			if (info) {
				RECT desktop;
				GetWindowRect(GetDesktopWindow(), &desktop);
				global::vars::g_resolution = { *(int*)(info), *(int*)(info + 4) };
				global::vars::g_desktop_resolution = { (int)desktop.right, (int)desktop.bottom };

				LOG_WARN("Game Resolution: %ix%i, Screen Resolution: %ix%i",
					global::vars::g_resolution.x, global::vars::g_resolution.y,
					global::vars::g_desktop_resolution.x, global::vars::g_desktop_resolution.y);
			}

			return true;
		}, successful);

		memory::scan(XOR("BL"), [](uint64_t address) {
			global::vars::g_blip_list = (rage::types::blip_list*)memory::read_instruction(address);
			return is_valid_ptr(global::vars::g_blip_list);
		}, successful);

		memory::scan(XOR("SHP"), [](uint64_t address) {
			global::vars::g_script_handlers = { memory::read_instruction(address), *(uint64_t*)(memory::read_instruction(address) - 8) };
			return true;
		}, successful);

		memory::scan(XOR("INVPLY"), [] (uint64_t address) {
			global::vars::g_invite_player = address;
			return true;
		}, successful);

		return successful;
	}

	bool hooks() {
		bool successful = true;
		uint64_t host_join_request_from = 0;
		uint64_t host_join_request_to = 0;

		if (global::vars::g_steam) {
			memory::scan({ XOR("E8 ? ? ? ? 44 8B E0 85 C0 0F 84 ? ? ? ? 49 8B 8D ? ? ? ? E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 49 8B 8D"), 0x0, XOR("TIMELOLSF"), true }, [] (uint64_t address) {
				g_timeout_fix_funcs[5] = memory::read_instruction(address, 1, 5);
				return true;
			}, successful);
			
			memory::scan({ XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B D9 48 8B 89 ? ? ? ? E8 ? ? ? ? 84 C0 75 07 32 C0 E9 ? ? ? ? 48 8B 05"), 0x0, XOR("TIMELOLS"), true }, [] (uint64_t address) {
				g_timeout_fix_funcs[0] = memory::read_instruction(address + 0x1E, 1, 5);
				g_timeout_fix_funcs[1] = memory::read_instruction(address + 0x2E);
				g_timeout_fix_funcs[2] = memory::read_instruction(address + 0x3C);
				g_timeout_fix_funcs[3] = memory::read_instruction(address + 0x55, 1, 5);

				return hooking::detour(XOR("TIMELOLS"), address, &join_timeout_fix, &join_timeout_fix_t);
			}, successful);
		} else {
			memory::scan({ XOR("E8 ? ? ? ? 44 8B E0 85 C0 0F 84 ? ? ? ? 49 8B 4D 20 E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 49 8B 4D 20 E8 ? ? ? ? 84 C0"), 0x0, XOR("TIMELOLSF"), true }, [] (uint64_t address) {
				g_timeout_fix_funcs[5] = memory::read_instruction(address, 1, 5);
				return true;
			}, successful);

			memory::scan({ XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B D9 48 8B 49 20 E8 ? ? ? ? 84 C0 75 07 32 C0 E9 ? ? ? ? 48 8B 05 ? ? ? ? 48 83"), 0x0, XOR("TIMELOL"), true }, [] (uint64_t address) {
				g_timeout_fix_funcs[0] = memory::read_instruction(address + 0x1B, 1, 5);
				g_timeout_fix_funcs[1] = memory::read_instruction(address + 0x2B);
				g_timeout_fix_funcs[2] = memory::read_instruction(address + 0x39);
				g_timeout_fix_funcs[3] = memory::read_instruction(address + 0x52, 1, 5);

				return hooking::detour(XOR("TIMELOL"), address, &join_timeout_fix, &join_timeout_fix_t);
			}, successful);
		}

		memory::scan(XOR("RUTDRB"), [] (uint64_t address) {
			global::vars::g_sync_data_reader_vtable = memory::read_instruction(address);

			return hooking::vmt(XOR("BB_1"), global::vars::g_sync_data_reader_vtable, 1, &read_unsigned_int_from_buffer, &read_unsigned_int_from_buffer_t)
				&& hooking::vmt(XOR("BB_2"), global::vars::g_sync_data_reader_vtable, 2, &read_unsigned_short_from_buffer, &read_unsigned_short_from_buffer_t)
				&& hooking::vmt(XOR("BB_3"), global::vars::g_sync_data_reader_vtable, 3, &read_unsigned_char_from_buffer, &read_unsigned_char_from_buffer_t)
				&& hooking::vmt(XOR("BB_4"), global::vars::g_sync_data_reader_vtable, 4, &read_int_from_buffer, &read_int_from_buffer_t)
				&& hooking::vmt(XOR("BB_5"), global::vars::g_sync_data_reader_vtable, 5, &read_short_from_buffer, &read_short_from_buffer_t)
				&& hooking::vmt(XOR("BB_6"), global::vars::g_sync_data_reader_vtable, 6, &read_char_from_buffer, &read_char_from_buffer_t)
				&& hooking::vmt(XOR("BB_7"), global::vars::g_sync_data_reader_vtable, 7, &read_bool_from_buffer, &read_bool_from_buffer_t)
				&& hooking::vmt(XOR("BB_8"), global::vars::g_sync_data_reader_vtable, 8, &read_long_long_from_buffer, &read_long_long_from_buffer_t)
				&& hooking::vmt(XOR("BB_9"), global::vars::g_sync_data_reader_vtable, 9, &read_int_from_buffer, &read_int_from_buffer_t)
				&& hooking::vmt(XOR("BB_10"), global::vars::g_sync_data_reader_vtable, 10, &read_short_from_buffer, &read_short_from_buffer_t)
				&& hooking::vmt(XOR("BB_11"), global::vars::g_sync_data_reader_vtable, 11, &read_char_from_buffer, &read_char_from_buffer_t)
				&& hooking::vmt(XOR("BB_12"), global::vars::g_sync_data_reader_vtable, 12, &read_unsigned_long_long_from_buffer, &read_unsigned_long_long_from_buffer_t)
				&& hooking::vmt(XOR("BB_13"), global::vars::g_sync_data_reader_vtable, 13, &read_unsigned_int_from_buffer, &read_unsigned_int_from_buffer_t)
				&& hooking::vmt(XOR("BB_14"), global::vars::g_sync_data_reader_vtable, 14, &read_unsigned_short_from_buffer, &read_unsigned_short_from_buffer_t)
				&& hooking::vmt(XOR("BB_15"), global::vars::g_sync_data_reader_vtable, 15, &read_unsigned_char_from_buffer, &read_unsigned_char_from_buffer_t)
				&& hooking::vmt(XOR("BB_16"), global::vars::g_sync_data_reader_vtable, 16, &read_float_from_buffer, &read_float_from_buffer_t)
				&& hooking::vmt(XOR("BB_17"), global::vars::g_sync_data_reader_vtable, 17, &read_unsigned_float_from_buffer, &read_unsigned_float_from_buffer_t)
				&& hooking::vmt(XOR("BB_18"), global::vars::g_sync_data_reader_vtable, 18, &read_network_id_from_buffer, &read_network_id_from_buffer_t)
				&& hooking::vmt(XOR("BB_19"), global::vars::g_sync_data_reader_vtable, 23, &read_array_from_buffer, &read_array_from_buffer_t)
				&& hooking::vmt(XOR("BB_20"), global::vars::g_sync_data_reader_vtable, 24, &read_string_from_buffer, &read_string_from_buffer_t);
		}, successful);

		memory::scan({ XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 E8 ? ? ? ? 48 8B B8 ? ? ? ? 48"), 0x0, XOR("BROADVAR"), false }, [] (uint64_t address) {
			g_get_current_gta_thread = memory::read_instruction(address + 0x14, 1, 5);
			return hooking::detour(XOR("BROADVAR"), address, &network_has_received_host_broadcast_data, &network_has_received_host_broadcast_data_t);
		}, successful);

		memory::scan(XOR("PCC"), [] (uint64_t address) {
			return hooking::detour(XOR("PCC"), address, &pack_clone_create, &pack_clone_create_t);
		}, successful);

		memory::scan(XOR("PCS"), [] (uint64_t address) {
			return hooking::detour(XOR("PCS"), address, &pack_clone_sync, &pack_clone_sync_t);
		}, successful);

		memory::scan(XOR("PLPSOM"), [] (uint64_t address) {
			return hooking::detour(XOR("PLPSOM"), address, &player_peer_something, &player_peer_something_t);
		}, successful);

		memory::scan(XOR("RJRESP"), [] (uint64_t address) {
			return hooking::detour(XOR("RJRESP"), memory::read_instruction(address, 1, 5), &read_join_response, &read_join_response_t);
		}, successful);

		memory::scan(XOR("SJRESP"), [] (uint64_t address) {
			return hooking::detour(XOR("SJRESP"), memory::read_instruction(address, 1, 5), &send_join_response, &send_join_response_t);
		}, successful);

		memory::scan(XOR("GPT"), [] (uint64_t address) {
			return hooking::detour(XOR("GPT"), address, &get_peer_address, &get_peer_address_t);
		}, successful);

		memory::scan(XOR("RCS"), [](uint64_t address) {
			global::vars::g_parse_nodes = memory::read_instruction(address + 0x4C, 1, 5); 

			patches patch;
			patch.m_address = address + 0x4C;
			patch.read(5);
			global::vars::g_patches.push_back(patch);

			memory::nop(patch.m_address, 5);

			receive_clone_sync_t = (decltype(receive_clone_sync_t))address;
			return true;
		}, successful);

		memory::scan({ XOR("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 45 33 E4 4C 8B F2 4C 8B F9 4C 39 22 0F 84"), 0x0, XOR("RCSCA"), false }, [] (uint64_t address) {
			g_rcs_caller_functions[0] = memory::read_instruction(address + 0x84, 1, 5);
			g_rcs_caller_functions[1] = memory::read_instruction(address + 0x12F, 1, 5);
			g_rcs_caller_functions[2] = memory::read_instruction(address + 0x36E, 1, 5);
			g_rcs_caller_functions[3] = memory::read_instruction(address + 0x1E6, 1, 5);
			g_rcs_caller_functions[4] = memory::read_instruction(address + 0x1CA, 2, 6);
			global::vars::g_read_byte_from_bit_buffer = memory::read_instruction(address + 0x25B, 1, 5);
			
			return hooking::detour(XOR("RCSC"), address, &receive_clone_sync_caller, &receive_clone_sync_caller_t);
		}, successful);

		memory::scan(XOR("RCC"), [](uint64_t address) {
			patches patch;
			patch.m_address = address + 0x180; 
			patch.read(5);
			global::vars::g_patches.push_back(patch);

			memory::nop(patch.m_address, 5);

			return hooking::detour(XOR("RCC"), address, &receive_clone_create, &receive_clone_create_t);
		}, successful);

		memory::scan(XOR("RCR"), [](uint64_t address) {
			return hooking::detour(XOR("RCR"), address, &receive_clone_remove, &receive_clone_remove_t);
		}, successful);

		memory::scan(XOR("RBV"), [](uint64_t address) {
			return hooking::detour(XOR("RBV"), address, &receive_broadcast, &receive_broadcast_t);
		}, successful);

		memory::scan(XOR("HNE"), [](uint64_t address) {
			return hooking::detour(XOR("HNE"), address, &receive_network_event, &receive_network_event_t);
		}, successful);

		memory::scan(XOR("RCMBB"), [](uint64_t address) {
			patches patch;
			patch.m_address = address + 0x3C;
			patch.read(9);
			global::vars::g_patches.push_back(patch);

			memory::nop(address + 0x3C, 9);

			return hooking::detour(XOR("RCMBB"), memory::read_instruction(address, 1, 5), &read_chat_message, &read_chat_message_t);
		}, successful);

		memory::scan(XOR("RSIR"), [](uint64_t address) {
			return hooking::detour(XOR("RSIR"), address, &receive_session_info, &receive_session_info_t);
		}, successful);
		
		memory::scan(XOR("HHJR_1"), [&](uint64_t address) {
			host_join_request_from = address;
			return is_valid_ptr(address);
		}, successful);

		memory::scan(XOR("HHJR_2"), [&](uint64_t address) {
			host_join_request_to = address;
			return is_valid_ptr(address);
		}, successful);

		memory::scan(XOR("SJRM"), [](uint64_t address) {
			return hooking::detour(XOR("SJRM"), memory::read_instruction(address, 1, 5), &send_join_request_message, &send_join_request_message_t);
		}, successful);

		memory::scan(XOR("HHJR"), [=](uint64_t address) {
			global::vars::g_hack_patches["RSJR"].m_address = host_join_request_from;
			global::vars::g_hack_patches["RSJR"].read(11);

			uint32_t jump_size = (uint32_t)(host_join_request_to - host_join_request_from - 5 - 6);
			global::vars::g_hack_patches["RSJR"].m_patch = { 0x41, 0xBC, 0x00, 0x00, 0x00, 0x00, 0xE9, (uint8_t)(jump_size & 0xFF), (uint8_t)(jump_size >> 8 & 0xFF), (uint8_t)(jump_size >> 16 & 0xFF), (uint8_t)(jump_size >> 24 & 0xFF) };

			global::vars::g_construct_read_session_join_request_msg = memory::read_instruction(address + 0x39, 1, 5); 
			global::vars::g_read_session_join_request_msg = memory::read_instruction(address + 0x4D, 1, 5); 

			return hooking::detour(XOR("HHJR"), address, &receive_session_join_request, &receive_session_join_request_t);
		}, successful);
		
		memory::scan(XOR("HNGE"), [](uint64_t address) {
			return hooking::detour(XOR("HNGE"), address, &process_game_event, &process_game_event_t);
		}, successful);

		memory::scan(XOR("HDNM"), [](uint64_t address) {
			return hooking::detour(XOR("HDNM"), address, &handle_desync_negotiation, &handle_desync_negotiation_t);
		}, successful);

		memory::scan(XOR("HDPR"), [](uint64_t address) {
			return hooking::detour(XOR("HDPR"), address, &host_handle_desync_request, &host_handle_desync_request_t);
		}, successful);

		memory::scan(XOR("HMNSH"), [](uint64_t address) {
			global::vars::g_read_new_script_host_message = memory::read_instruction(address, 1, 5);
			return hooking::detour(XOR("HMNSH"), address - 0x6D, &read_new_script_host_message, &read_new_script_host_message_t); // good
		}, successful);

		memory::scan(XOR("UPSS"), [](uint64_t address) {
			return hooking::detour(XOR("UPSS"), address, &update_player_script_status, &update_player_script_status_t);
		}, successful);

		memory::scan(XOR("RTMBB"), [] (uint64_t address) {
			return hooking::detour(XOR("RTMBB"), memory::read_instruction(address, 1, 5), &receive_text_message, &receive_text_message_t);
		}, successful);

		memory::scan(XOR("HPE"), [] (uint64_t address) {
			return hooking::detour(XOR("HPE"), memory::read_instruction(address, 1, 5), &receive_presence_event, &receive_presence_event_t);
		}, successful);

		memory::scan(XOR("RBLM"), [] (uint64_t address) {
			return hooking::detour(XOR("RBLM"), address, &read_blacklist_message, &read_blacklist_message_t);
		}, successful);

		memory::scan(XOR("GFI"), [](uint64_t address) {
			return hooking::detour(XOR("GFI"), address, &get_font_id, &get_font_id_t);
		}, successful);

		memory::scan(XOR("RSTS"), [](uint64_t address) {
			return hooking::detour(XOR("RSTS"), address, &render_script_textures, &render_script_textures_t);
		}, successful);

		memory::scan(XOR("GNGRCT"), [](uint64_t address) {
			return hooking::detour(XOR("GNGRCT"), address, &get_next_grc_texture, &get_next_grc_texture_t);
		}, successful);

		memory::scan(XOR("RSRP"), [] (uint64_t address) {
			global::vars::g_reset_script_render_params[0] = memory::read_instruction(address, 2, 6);// good
			global::vars::g_reset_script_render_params[1] = memory::read_instruction(address + 6, 2, 6);// good
			return hooking::detour(XOR("RSRP"), address, &reset_script_render_params, &reset_script_render_params_t);
		}, successful);

		memory::scan(XOR("GNMTI"), [](uint64_t address) {
			return hooking::detour(XOR("GNMTI"), address, &get_next_marker_texture_index, &get_next_marker_texture_index_t);
		}, successful);

		memory::scan(XOR("TMTS"), [](uint64_t address) {
			return hooking::detour(XOR("TMTS"), address, &translate_marker_to_screen, &translate_marker_to_screen_t);
		}, successful);

		memory::scan(XOR("RMTS"), [](uint64_t address) {
			return hooking::detour(XOR("RMTS"), address, &render_markers_to_screen, &render_markers_to_screen_t);
		}, successful);

		memory::scan(XOR("AMTT"), [](uint64_t address) {
			return hooking::detour(XOR("AMTT"), address, &add_marker_to_table, &add_marker_to_table_t);
		}, successful);

		memory::scan(XOR("FGES"), [](uint64_t address) {
			return hooking::detour(XOR("FGES"), address, &format_engine_string, &format_engine_string_t);
		}, successful);

		memory::scan(XOR("GGESLC"), [](uint64_t address) {
			return hooking::detour(XOR("GGESLC"), address, &get_engine_string_line_count, &get_engine_string_line_count_t);
		}, successful);

		memory::scan(XOR("SBULLET"), [](uint64_t address) {
			return hooking::detour(XOR("SBULLET"), address, &shoot_bullet, &shoot_bullet_t);
		}, successful);

		memory::scan(XOR("PRU"), [](uint64_t address) {
			return hooking::detour(XOR("PRU"), address, &process_relay_usage, &process_relay_usage_t);
		}, successful);

		memory::scan(XOR("APPI"), [](uint64_t address) {
			return hooking::detour(XOR("APPI"), address, &apply_player_physical_index, &apply_player_physical_index_t);
		}, successful);

		memory::scan(XOR("WPGDN"), [](uint64_t address) {
			return hooking::detour(XOR("WPGDN"), address, &write_player_game_state_data_node, &write_player_game_state_data_node_t);
		}, successful);

		memory::scan(XOR("WPHDN"), [](uint64_t address) {
			return hooking::detour(XOR("WPHDN"), address, &write_ped_health_data_node, &write_ped_health_data_node_t);
		}, successful);

		memory::scan(XOR("SPROJ"), [](uint64_t address) {
			return hooking::detour(XOR("SPROJ"), memory::read_instruction(address, 1, 5), &shoot_projectile, &shoot_projectile_t);
		}, successful);

		memory::scan(XOR("WGSITEM"), [](uint64_t address) {
			global::vars::g_write_gs_item = address;
			return hooking::detour(XOR("WGSITEM"), address, &write_gs_item, &write_gs_item_t);
		}, successful);

		memory::scan(XOR("RMMR"), [](uint64_t address) {
			return hooking::detour(XOR("RMMR"), address, &read_matchmaking_response, &read_matchmaking_response_t);
		}, successful);

		memory::scan(XOR("WMMR"), [](uint64_t address) {
			return hooking::detour(XOR("WMMR"), address, &write_matchmaking_request, &write_matchmaking_request_t);
		}, successful);

		memory::scan(XOR("WESTR"), [](uint64_t address) {
			return hooking::detour(XOR("WESTR"), memory::read_instruction(address, 1, 5), &write_encrypted_string_to_request, &write_encrypted_string_to_request_t);
		}, successful);

		memory::scan(XOR("SGCM"), [](uint64_t address) {
			global::vars::g_send_global_chat_message = memory::read_instruction(address, 1, 5);
			return hooking::detour(XOR("SGCM"), global::vars::g_send_global_chat_message, &send_global_chat_message, &send_global_chat_message_t);
		}, successful);

		memory::scan(XOR("GGXTL"), [](uint64_t address) {
			return hooking::detour(XOR("GGXTL"), address, &get_gxt_label, &get_gxt_label_t);
		}, successful);

		// 
		memory::scan(XOR("GGXTLFH"), [](uint64_t address) {
			return hooking::detour(XOR("GGXTLFH"), address, &get_gxt_label_from_hash, &get_gxt_label_from_hash_t);
		}, successful);

		memory::scan(XOR("SCPCSC"), [](uint64_t address) {
			return hooking::detour(XOR("SCPCSC"), address, &check_chat_profanity, &check_chat_profanity_t);
		}, successful);

		memory::scan(XOR("SCPCS"), [](uint64_t address) {
			return hooking::detour(XOR("SCPCS"), address, &check_string_profanity, &check_string_profanity_t);
		}, successful);

		memory::scan(XOR("SAGTSC"), [](uint64_t address) {
			return hooking::detour(XOR("SAGTSC"), address, &send_add_gamer_to_session, &send_add_gamer_to_session_t);
		}, successful);

		memory::scan(XOR("HRP"), [](uint64_t address) {
			return hooking::detour(XOR("HRP"), address, &has_ros_privilege, &has_ros_privilege_t);
		}, successful);

		memory::scan(XOR("PDN1"), [](uint64_t address) {
			return hooking::detour(XOR("PDN1"), address, &compress_data_node, &compress_data_node_t);
		}, successful);

		memory::scan(XOR("PDN2"), [](uint64_t address) {
			return hooking::detour(XOR("PDN2"), address, &compress_data_node2, &compress_data_node2_t);
		}, successful);

		memory::scan(XOR("PGDN"), [](uint64_t address) {
			return hooking::detour(XOR("PGDN"), address, &write_player_gamer_data_node, &write_player_gamer_data_node_t);
		}, successful);
	
		memory::scan(XOR("AWM"), [](uint64_t address) {
			return hooking::detour(XOR("AWM"), address, &apply_weather_meta, &apply_weather_meta_t);
		}, successful);

		memory::scan(XOR("HMKP"), [](uint64_t address) {
			return hooking::detour(XOR("HMKP"), address, &read_kick_player_message, &read_kick_player_message_t);
		}, successful);

		memory::scan({ "48 8D 05 ? ? ? ? 48 8D 54 24 ? 48 8B CB 48 89 44 24 ? 48 89 7C 24 ? C6 44 24 ? ? E8 ? ? ? ? 48 8B", 0, XOR("WUTDRB"), true }, [] (uint64_t address) {
			global::vars::g_sync_data_writer_vtable = memory::read_instruction(address);

			return hooking::vmt(XOR("BBW_1"), global::vars::g_sync_data_writer_vtable, 1, &write_unsigned_int_from_buffer, &write_unsigned_int_from_buffer_t)
				&& hooking::vmt(XOR("BBW_19"), global::vars::g_sync_data_writer_vtable, 23, &write_array_from_buffer, &write_array_from_buffer_t);
		}, successful);

		memory::scan(XOR("BB_C"), [](uint64_t address) {
			uint64_t _class = memory::read_instruction(address + 0x7B);
			
			return hooking::detour(XOR("BB_C"), address, &construct_in_frame, &construct_in_frame_t)
				&& hooking::detour(XOR("BB_D"), *(uint64_t*)_class, &destruct_in_frame, &destruct_in_frame_t);
		}, successful);

		hooking::detour(XOR("GPADDR"), (uint64_t)&GetProcAddress, &get_proc_address, &get_proc_address_t);

		memory::scan(XOR("STT"), [](uint64_t address) {
			return hooking::detour(XOR("STT"), address, &tick_script_thread__crash, &tick_script_thread__crash_t);
		}, successful);

		memory::scan(XOR("C1"), [](uint64_t address) {
			return hooking::detour(XOR("C1"), address, &apply_vehicle_data__crash, &apply_vehicle_data__crash_t);
		}, successful);

		memory::scan(XOR("C2"), [](uint64_t address) {
			return hooking::detour(XOR("C2"), address, &attach_trailer__crash, &attach_trailer__crash_t);
		}, successful);

		memory::scan(XOR("C3"), [](uint64_t address) {
			return hooking::detour(XOR("C3"), address, &attach_trailer_audio__crash, &attach_trailer_audio__crash_t);
		}, successful);

		memory::scan(XOR("RID0"), [](uint64_t address) {
			return hooking::detour(XOR("RID0"), address, &rid0__crash, &rid0__crash_t);
		}, successful);

		memory::scan(XOR("C4"), [](uint64_t address) {
			global::vars::g_game_script_handler_manager = memory::read_instruction(address + 0x1F);
			return hooking::detour(XOR("C4"), address, &destruct_script_handler__crash, &destruct_script_handler__crash_t);
		}, successful);

		memory::scan(XOR("C5"), [](uint64_t address) {
			return hooking::detour(XOR("C5"), address, &shit_scripts__crash, &shit_scripts__crash_t);
		}, successful);

		memory::scan(XOR("C6"), [] (uint64_t address) {
			return hooking::detour(XOR("C6"), address, &shit_scripts2__crash, &shit_scripts2__crash_t);
		}, successful);

		memory::scan(XOR("C7"), [] (uint64_t address) {
			return hooking::detour(XOR("C7"), address, &sub_140AD8424__crash, &sub_140AD8424__crash_t);
		}, successful);

		memory::scan(XOR("SULL"), [](uint64_t address) {
			global::vars::g_arxan_restore_addresses[0] = address;
			memcpy(global::vars::g_arxan_restore_bytes[0][0], (void*)address, sizeof(global::vars::g_arxan_restore_bytes[0][0]));
			hooking::detour(XOR("SULL"), address, &write_net_msg_identifier, &write_net_msg_identifier_t);
			memcpy(global::vars::g_arxan_restore_bytes[0][1], (void*)address, sizeof(global::vars::g_arxan_restore_bytes[0][1]));
			return true;
		}, successful);

		memory::scan(XOR("WDD"), [](uint64_t address) {
			global::vars::g_arxan_restore_addresses[1] = address;
			memcpy(global::vars::g_arxan_restore_bytes[1][0], (void*)address, sizeof(global::vars::g_arxan_restore_bytes[1][0]));
			hooking::detour(XOR("WDD"), address, &write_ulonglong_to_bit_buffer, &write_ulonglong_to_bit_buffer_t);
			memcpy(global::vars::g_arxan_restore_bytes[1][1], (void*)address, sizeof(global::vars::g_arxan_restore_bytes[1][1]));
			return true;
		}, successful);

		if (global::vars::g_steam) {
			memory::scan({ XOR("E9 03 9C 89 FF"), 0, XOR("ARXAN1-1"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN1-1"), address, &arxan_integrity_start1, &arxan_integrity_start1_t);
			}, successful);

			memory::scan({ XOR("E9 1C 99 4F FF"), 0, XOR("ARXAN1-2"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN1-2"), address, &arxan_integrity_end1, &arxan_integrity_end1_t);
			}, successful);

			memory::scan({ XOR("E9 25 4A FA FF"), 0, XOR("ARXAN2-1"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN2-1"), address, &arxan_integrity_start2, &arxan_integrity_start2_t);
			}, successful);

			memory::scan({ XOR("E9 26 AB 6F FE"), 0, XOR("ARXAN2-2"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN2-2"), address, &arxan_integrity_end2, &arxan_integrity_end2_t);
			}, successful);

			memory::scan({ XOR("E9 AA F9 06 01"), 0, XOR("ARXAN3-1"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN3-1"), address, &arxan_integrity_start3, &arxan_integrity_start3_t);
			}, successful);

			memory::scan({ XOR("E9 5E 69 62 FD"), 0, XOR("ARXAN3-2"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN3-2"), address, &arxan_integrity_end3, &arxan_integrity_end3_t);
			}, successful);

			memory::scan({ XOR("E9 01 BC F2 02"), 0, XOR("ARXAN4-1"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN4-1"), address, &arxan_integrity_start4, &arxan_integrity_start4_t);
			}, successful);

			memory::scan({ XOR("E9 04 E2 00 00"), 0, XOR("ARXAN4-2"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN4-2"), address, &arxan_integrity_end4, &arxan_integrity_end4_t);
			}, successful);

			memory::scan({ XOR("E9 08 46 FD FF"), 0, XOR("ARXAN5-1"), true }, [] (uint64_t address) {
				return hooking::detour(XOR("ARXAN5-1"), address, &arxan_integrity_start5, &arxan_integrity_start5_t);
			}, successful);

			memory::scan({ XOR("E9 33 FF FF FF 48 89 5C 24 18"), 0, XOR("ARXAN5-2"), true }, [] (uint64_t address) {
				return hooking::detour(XOR("ARXAN5-2"), address, &arxan_integrity_end5, &arxan_integrity_end5_t);
			}, successful);
		} else {
			memory::scan({ XOR("E9 01 57 5A FF"), 0, XOR("ARXAN1-1"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN1-1"), address, &arxan_integrity_start1, &arxan_integrity_start1_t);
			}, successful);

			memory::scan({ XOR("E9 DE B2 E0 00"), 0, XOR("ARXAN1-2"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN1-2"), address, &arxan_integrity_end1, &arxan_integrity_end1_t);
			}, successful);

			memory::scan({ XOR("E9 E2 17 36 00"), 0, XOR("ARXAN2-1"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN2-1"), address, &arxan_integrity_start2, &arxan_integrity_start2_t);
			}, successful);

			memory::scan({ XOR("E9 BA 1F 08 FD"), 0, XOR("ARXAN2-2"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN2-2"), address, &arxan_integrity_end2, &arxan_integrity_end2_t);
			}, successful);

			memory::scan({ XOR("E9 2B 48 3D FF"), 0, XOR("ARXAN3-1"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN3-1"), address, &arxan_integrity_start3, &arxan_integrity_start3_t);
			}, successful);

			memory::scan({ XOR("E9 4B 1D 8E 00"), 0, XOR("ARXAN3-2"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN3-2"), address, &arxan_integrity_end3, &arxan_integrity_end3_t);
			}, successful);

			memory::scan({ XOR("E9 07 A5 25 00"), 0, XOR("ARXAN4-1"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN4-1"), address, &arxan_integrity_start4, &arxan_integrity_start4_t);
			}, successful);

			memory::scan({ XOR("E9 C2 A7 7A 00"), 0, XOR("ARXAN4-2"), true }, [](uint64_t address) {
				return hooking::detour(XOR("ARXAN4-2"), address, &arxan_integrity_end4, &arxan_integrity_end4_t);
			}, successful);
		}

		return successful;
	}
}