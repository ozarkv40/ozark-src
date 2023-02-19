#include "network_players_abusive_explosions.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_abusive.h"
#include "global/lists.h"
#include "menu/base/util/control.h"

using namespace network::players::abusive::explosions::vars;

namespace network::players::abusive::explosions::vars {
	variables m_vars;

	scroll_struct<global::lists::particle> particles[21] = {
		{ localization("Default", true), { "", "", false } },
	};

	void create_explosion(menu::player::player_context& player, bool session = false) {
		int type = session ? m_vars.m_explosion_type : player.m_explosion_type;
		int visual = session ? m_vars.m_explosion_visual : player.m_explosion_visual;
		float radius = session ? m_vars.m_explosion_radius : player.m_explosion_radius;
		float camera_shake = session ? m_vars.m_explosion_camera_shake : player.m_explosion_camera_shake;
		bool sound = session ? m_vars.m_explosion_sound : player.m_explosion_sound;

		native::add_explosion(player.m_coords.x, player.m_coords.y, player.m_coords.z, global::lists::g_explosions[type].m_result, radius, sound, visual != 0, camera_shake, false);

		if (visual >= 1) {
			scroll_struct<global::lists::particle> particle = particles[visual];
			menu::control::request_particle({ particle.m_result.m_dict, particle.m_result.m_texture }, [=] (std::pair<const char*, const char*> anim) {
				native::use_particle_fx_asset_next_call(anim.first);
				native::start_particle_fx_non_looped_at_coord2(anim.second, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, 0.f, 0.f, radius, false, false, false);
			});
		}
	}
}

void network_players_abusive_explosions_menu::load() {
	set_name("Custom Explosions");
	set_parent<network_players_abusive_menu>();

	for (int i = 1; i < 21; i++) {
		particles[i] = global::lists::g_particles[i - 1];
	}

	add_option(scroll_option<ExplosionTypes>(SCROLL, "Type")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_explosion_type, 0, NUMOF(global::lists::g_explosions), global::lists::g_explosions)
		.add_update([] (scroll_option<ExplosionTypes>* option, int type) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_explosion_type, 0, NUMOF(global::lists::g_explosions), global::lists::g_explosions);
			} else {
				option->add_scroll(m_vars.m_explosion_type, 0, NUMOF(global::lists::g_explosions), global::lists::g_explosions);
			}
		}));

	add_option(scroll_option<global::lists::particle>(SCROLL, "Visual")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_explosion_visual, 0, NUMOF(particles), particles)
		.add_update([] (scroll_option<global::lists::particle>* option, int type) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_explosion_visual, 0, NUMOF(particles), particles);
			} else {
				option->add_scroll(m_vars.m_explosion_visual, 0, NUMOF(particles), particles);
			}
		}));

	add_option(number_option<float>(SCROLL, "Radius")
		.add_translate()
		.add_number(menu::player::get_selected_player().m_explosion_radius, "%.0f", 1.f).add_min(1.f).add_max(20.f).set_scroll_speed(10)
		.add_update([] (number_option<float>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_number(menu::player::get_selected_player().m_explosion_radius, "%.0f", 1.f);
			} else {
				option->add_number(m_vars.m_explosion_radius, "%.0f", 1.f);
			}
		}));

	add_option(number_option<float>(SCROLL, "Camera Shake")
		.add_translate()
		.add_number(menu::player::get_selected_player().m_explosion_camera_shake, "%.0f", 1.f).add_min(1.f).add_max(100.f).set_scroll_speed(10)
		.add_update([] (number_option<float>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_number(menu::player::get_selected_player().m_explosion_camera_shake, "%.0f", 1.f);
			} else {
				option->add_number(m_vars.m_explosion_camera_shake, "%.0f", 1.f);
			}
		}));

	add_option(toggle_option("Audible")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_explosion_sound)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_explosion_sound);
			} else {
				option->add_toggle(m_vars.m_explosion_sound);
			}
		}));

	add_option(button_option("Create Explosion")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				create_explosion(menu::player::get_selected_player(), false);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					create_explosion(player, true);
				});
			}
		}));

	add_option(toggle_option("Create Explosion Loop")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_explosion_loop)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_explosion_loop);
			} else {
				option->add_toggle(m_vars.m_explosion_loop);
			}
		}));
}

void network_players_abusive_explosions_menu::update() {}

void network_players_abusive_explosions_menu::update_once() {}

void network_players_abusive_explosions_menu::feature_update() {
	menu::player::for_each([] (menu::player::player_context& player) {
		if (player.m_explosion_loop || m_vars.m_explosion_loop) {
			if (!(menu::player::is_excluded(player.m_id) && !player.m_explosion_loop)) {
				create_explosion(player, !player.m_explosion_loop);
			}
		}
	}, true);
}

network_players_abusive_explosions_menu* g_instance;
network_players_abusive_explosions_menu* network_players_abusive_explosions_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_abusive_explosions_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}