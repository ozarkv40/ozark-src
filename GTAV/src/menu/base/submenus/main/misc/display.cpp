#include "display.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"
#include "menu/base/util/stacked_display.h"
#include "menu/base/util/timers.h"
#include "util/va.h"
#include "rage/engine.h"

using namespace misc::display::vars;

namespace misc::display::vars {
	variables m_vars;

	scroll_struct<int> fps[] = {
		{ localization("FPS", true), 0, },
		{ localization("Average", true), 1, },
		{ localization("Both", true), 2 },
	};

	std::string get_next_host() {
		std::vector<std::pair<std::string, uint64_t>> players;
		
		menu::player::for_each([&](menu::player::player_context& player) {
			if (is_valid_ptr(player.m_net_player)) {
				if (is_valid_ptr(player.m_net_player->m_player_info)) {
					if (player.m_net_player == rage::engine::get_host_net_game_player()) return;
					players.push_back({ player.m_name, player.m_net_player->m_player_info->m_host_token });
				}
			}
		}, true, true);

		std::sort(begin(players), end(players), [](std::pair<std::string, uint64_t> first, std::pair<std::string, uint64_t> second) {
			return first.second < second.second;
		});

		if (players.empty()) return "N/A";
		return players[0].first;
	}
}

void display_menu::load() {
	set_name("Stacked Display");
	set_parent<misc_menu>();

	add_option(scroll_option<int>(TOGGLE, "FPS")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_fps)
		.add_scroll(m_vars.m_fps_var, 0, NUMOF(fps), fps)
		.add_click([] {
			if (!m_vars.m_fps) {
				menu::display::disable("SR_FPS");
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Position")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_position)
		.add_click([] {
			if (!m_vars.m_position) {
				menu::display::disable("SR_POS");
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Free Slots")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_free_slots)
		.add_click([] {
			if (!m_vars.m_free_slots) {
				menu::display::disable("SR_FREESLOTS");
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Modder Count")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_modder_count)
		.add_click([] {
			if (!m_vars.m_modder_count) {
				menu::display::disable("SR_MODDERS");
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Host")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_host)
		.add_click([] {
			if (!m_vars.m_host) {
				menu::display::disable("SR_HOST");
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Next Host")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_next_host)
		.add_click([] {
			if (!m_vars.m_next_host) {
				menu::display::disable("SR_NHOST");
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Pools")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_entity_pools)
		.add_click([] {
			if (!m_vars.m_entity_pools) {
				menu::display::disable("SR_AttachmentPool");
				menu::display::disable("SR_ObjectPool");
				menu::display::disable("SR_PedPool");
				menu::display::disable("SR_PickupPool");
				menu::display::disable("SR_VehiclePool");
			}
		}).add_savable(get_submenu_name_stack()));

	add_string("Modders");
	add_string("Free Slots");
	add_string("Position");
	add_string("Average FPS");
	add_string("Avg");
	add_string("FPS");
	add_string("Object Pool");
	add_string("Ped Pool");
	add_string("Pickup Pool");
	add_string("Vehicle Pool");
	add_string("Camera Pool");
	add_string("Frame Count");
	add_string("Next Host");
	add_string("Host");
}

void display_menu::update() {}

void display_menu::update_once() {}

void display_menu::feature_update() {
	static int timer = 0;
	menu::timers::run_timed(&timer, 1000, [] {
		m_vars.m_draw_fps_cache[1] = m_vars.m_draw_fps_cache[0];
		m_vars.m_draw_fps_cache[0] = native::get_frame_count();
	});

	if (m_vars.m_fps) {
		int frames = m_vars.m_draw_fps_cache[0] - m_vars.m_draw_fps_cache[1] - 1;

		if (m_vars.m_draw_fps_average_count < 900) {
			m_vars.m_draw_fps_average_total += frames;
			m_vars.m_draw_fps_average_count++;
		} else {
			m_vars.m_draw_fps_average_total = m_vars.m_draw_fps_average_count = 0;
		}

		if (m_vars.m_draw_fps_average_total != 0 && m_vars.m_draw_fps_average_count != 0) {
			m_vars.m_draw_fps_average = m_vars.m_draw_fps_average_total / m_vars.m_draw_fps_average_count;
		}

		char buffer[50];
		if (m_vars.m_fps_var == 0) {
			sprintf_s(buffer, "%s%i", frames < 60 ? "~r~" : frames > 100 ? "~g~" : "", frames);
		} else if (m_vars.m_fps_var == 1) {
			sprintf_s(buffer, "%s%i", m_vars.m_draw_fps_average < 60 ? "~r~" : m_vars.m_draw_fps_average > 100 ? "~g~" : "", m_vars.m_draw_fps_average);
			menu::display::update("SR_FPS", get_string("Average FPS"), buffer);
			return;
		} else {
			sprintf_s(buffer, "%s%i~w~ (%s. %s%i~w~)", frames < 60 ? "~r~" : frames > 100 ? "~g~" : "", frames, get_string("Avg").c_str(), m_vars.m_draw_fps_average < 60 ? "~r~" : m_vars.m_draw_fps_average > 100 ? "~g~" : "", m_vars.m_draw_fps_average);
		}

		menu::display::update("SR_FPS", get_string("FPS"), buffer);
	}

	if (m_vars.m_position) {
		math::vector3<float> coords = menu::player::get_local_player().m_coords;
		menu::display::update("SR_POS", get_string("Position"), util::va::va("[%.2f, %.2f, %.2f]", coords.x, coords.y, coords.z));
	}

	if (m_vars.m_free_slots) {
		menu::display::update("SR_FREESLOTS", get_string("Free Slots"), std::to_string(32 - native::network_get_num_connected_players()));
	}

	if (m_vars.m_modder_count) {
		int count = 0;

		menu::player::for_each([&](menu::player::player_context& player) {
			if (player.m_is_modder) count++;
		}, true);

		menu::display::update("SR_MODDERS", get_string("Modders"), std::to_string(count));
	}

	if (m_vars.m_entity_pools) {
		std::vector<std::pair<std::string, std::pair<int, int>>> pool_info;

		pool_info.push_back(std::make_pair(get_string("Object Pool"), std::make_pair(global::vars::g_object_pool->m_count, global::vars::g_object_pool->m_max)));
		pool_info.push_back(std::make_pair(get_string("Ped Pool"), std::make_pair(global::vars::g_ped_pool->m_count, global::vars::g_ped_pool->m_max)));
		pool_info.push_back(std::make_pair(get_string("Pickup Pool"), std::make_pair(global::vars::g_pickup_pool->m_count, global::vars::g_pickup_pool->m_max)));
		pool_info.push_back(std::make_pair(get_string("Vehicle Pool"), std::make_pair(global::vars::g_vehicle_pool->m_count, global::vars::g_vehicle_pool->m_max)));

		for (std::size_t i = 0; i < pool_info.size(); i++) {
			std::string name = pool_info[i].first;
			name.erase(remove(name.begin(), name.end(), ' '), name.end());
			menu::display::update(("SR_" + name), pool_info[i].first.c_str(), util::va::va("%i/%i", pool_info[i].second.first, pool_info[i].second.second));
		}
	}

	if (m_vars.m_frame_count) {
		menu::display::update("SR_FRAMECOUNT", get_string("Frame Count"), std::to_string(native::get_frame_count()));
	}

	if (m_vars.m_host) {
		if (rage::engine::get_host_net_game_player() && rage::engine::get_host_net_game_player()->m_player_info) {
			menu::display::update("SR_HOST", get_string("Host"), rage::engine::get_host_net_game_player()->m_player_info->m_name);
		} else {
			menu::display::disable("SR_HOST");
		}
	}

	if (m_vars.m_next_host) {
		if (native::network_get_num_connected_players() > 1) {
			menu::display::update("SR_NHOST", get_string("Next Host"), get_next_host());
		} else {
			menu::display::disable("SR_NHOST");
		}
	}
}

display_menu* g_instance;
display_menu* display_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new display_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
