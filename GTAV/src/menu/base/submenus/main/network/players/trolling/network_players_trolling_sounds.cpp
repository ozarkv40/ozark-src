#include "network_players_trolling_sounds.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_trolling.h"
#include "global/lists.h"

using namespace network::players::trolling::sounds::vars;

namespace network::players::trolling::sounds::vars {
	variables m_vars;

	void start_sound(menu::player::player_context& player, std::pair<const char*, const char*> sound, bool add, int optionid) {
		int sound_id = native::get_sound_id();
		native::play_sound_from_coord(sound_id, sound.first, player.m_coords.x, player.m_coords.y, player.m_coords.z, sound.second, true, 0, true);

		if (add) {
			m_vars.m_sounds[optionid] = sound_id;
		}
	}
}

void network_players_trolling_sounds_menu::load() {
	set_name("Sounds");
	set_parent<network_players_trolling_menu>();

	add_option(button_option("Stop All")
		.add_translate()
		.add_click([] {
			for (auto& sound : m_vars.m_sounds) {
				native::stop_sound(sound.second);
			}
		}));

	add_option(break_option("Sounds")
		.add_translate());

	for (int i = 0; i < NUMOF(global::lists::g_sounds); i++) {
		scroll_struct<std::pair<const char*, const char*>>& arr = global::lists::g_sounds[i];

		m_vars.m_option_cache.push_back(add_option(button_option(arr.m_name.get())
			.add_translate()
			.add_update([=] (button_option* option) { option->set_name(global::lists::g_sounds[i].m_name.get()); })
			.add_click([=] {
				if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
					start_sound(menu::player::get_selected_player(), arr.m_result, true, i);
				} else {
					menu::player::for_each([=] (menu::player::player_context& player) {
						start_sound(player, arr.m_result, true, i);
					});
				}
			})));
	}
}

void network_players_trolling_sounds_menu::update() {
	for (auto& sound : m_vars.m_sounds) {
		if (native::has_sound_finished(sound.second)) {
			m_vars.m_option_cache[sound.first]->remove_sprite();
		} else {
			m_vars.m_option_cache[sound.first]->add_sprite({ "commonmenu", "shop_tick_icon" }).add_sprite_scale({ 0.022f, 0.039f });
		}
	}
}

void network_players_trolling_sounds_menu::update_once() {}

void network_players_trolling_sounds_menu::feature_update() {}

network_players_trolling_sounds_menu* g_instance;
network_players_trolling_sounds_menu* network_players_trolling_sounds_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_trolling_sounds_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}