#include "player.h"
#include "../main.h"
#include "menu/base/submenu_handler.h"
#include "menu/base/util/global.h"
#include "menu/base/util/input.h"
#include "player/appearance.h"
#include "player/movement.h"
#include "player/animation.h"
#include "player/particles.h"
#include "rage/types/global_types.h"

using namespace player::vars;

namespace player::vars {
	variables m_vars;

	scroll_struct<int> invisibility[] = {
		{ localization("Local", true), 0 },
		{ localization("Network", true), 0 },
		{ localization("Network + Local", true), 0 },
	};

	scroll_struct<int> request[] = {
		{ localization("Ballistic Armor and Minigun", true), 0 },
		{ localization("Airstrike", true), 0 },
		{ localization("Backup Helicopter", true), 0 },
		{ localization("Helicopter Pickup", true), 0 }
	};

	void cops_turn_blind_eye() {
		if (m_vars.m_cops_turn_blind_eye) {
			menu::script_global(rage::global::_155_customs_base).at(4622).as<int>() = 5; // 1.55 done
			menu::script_global(rage::global::_155_customs_base).at(4625).as<int>() = native::get_network_time() + 637000; // 1.55 done
		} else {
			menu::script_global(rage::global::_155_customs_base).at(4622).as<int>() = 0;// 1.55 done
			menu::script_global(rage::global::_155_customs_base).at(4625).as<int>() = native::get_network_time(); // 1.55 done
		}
	}

	void off_the_radar() {
		if (m_vars.m_off_the_radar) {
			menu::script_global(rage::global::_155_property_base2).at(menu::player::get_local_player().m_id, rage::global::_155_property_base2_size).at(209).as<int>() = 1;// 1.55 done
			menu::script_global(rage::global::_155_time_base).at(70).as<int>() = native::get_network_time() + 757000;// 1.55 done
		} else {
			menu::script_global(rage::global::_155_property_base2).at(menu::player::get_local_player().m_id, rage::global::_155_property_base2_size).at(209).as<int>() = 0;// 1.55 done
			menu::script_global(rage::global::_155_time_base).at(70).as<int>() = native::get_network_time();// 1.55 done
		}
	}

	void reveal_hidden_players() {
		if (m_vars.m_reveal_hidden_players) {
			menu::script_global(rage::global::_155_property_base2).at(menu::player::get_local_player().m_id, rage::global::_155_property_base2_size).at(212).as<int>() = 1; // 1.55 done
			menu::script_global(rage::global::_155_time_base).at(71).as<int>() = native::get_network_time() + 757000;// 1.55 done
		} else {
			menu::script_global(rage::global::_155_property_base2).at(menu::player::get_local_player().m_id, rage::global::_155_property_base2_size).at(212).as<int>() = 0;// 1.55 done
			menu::script_global(rage::global::_155_time_base).at(71).as<int>() = native::get_network_time();// 1.55 done
		}
	}

	void no_ragdoll() {
		native::set_ped_can_ragdoll(menu::player::get_local_player().m_ped, !m_vars.m_disable_ragdoll);
		native::set_ped_can_ragdoll_from_player_impact(menu::player::get_local_player().m_ped, !m_vars.m_disable_ragdoll);
		native::set_ped_can_be_knocked_off_vehicle(menu::player::get_local_player().m_ped, !m_vars.m_disable_ragdoll);
	}

	void badsport(bool toggle) {
		if (!toggle) native::stat_set_bool(0x8C1C0FAF, false, true);
		native::stat_set_float(0xBE89A9D2, toggle ? 300.f : 0.f, true);
	}
}

void player_menu::load() {
	set_name("Player");
	set_parent<main_menu>();

	add_option(submenu_option("Appearance")
		.add_translate().add_hotkey()
		.add_submenu<appearance_menu>());

	add_option(submenu_option("Movement")
		.add_translate().add_hotkey()
		.add_submenu<movement_menu>());

	add_option(submenu_option("Animation")
		.add_translate().add_hotkey()
		.add_submenu<animation_menu>());

	add_option(submenu_option("Particle FX")
		.add_translate().add_hotkey()
		.add_submenu<particle_menu>());

	add_option(toggle_option("Godmode")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_godmode).add_savable(get_submenu_name_stack())
		.add_click([] {
			if (!m_vars.m_godmode)
				native::set_entity_invincible(menu::player::get_local_player().m_ped, false);
		}));

	add_option(toggle_option("Disable Police")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_police).add_savable(get_submenu_name_stack())
		.add_click([] {
			if (!m_vars.m_disable_police) {
				native::set_max_wanted_level(5);
			}
		}));

	add_option(toggle_option("Disable Ragdoll")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_ragdoll).add_savable(get_submenu_name_stack())
		.add_click(no_ragdoll));

	add_option(toggle_option("Off the Radar")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_off_the_radar).add_savable(get_submenu_name_stack())
		.add_click(off_the_radar));

	add_option(toggle_option("Cops Turn Blind Eye")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_cops_turn_blind_eye).add_savable(get_submenu_name_stack())
		.add_click(cops_turn_blind_eye));

	add_option(toggle_option("Reveal Hidden Players")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_reveal_hidden_players).add_savable(get_submenu_name_stack())
		.add_click(reveal_hidden_players));

	add_option(toggle_option("Peds Ignore")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_peds_ingore_player).add_savable(get_submenu_name_stack())
		.add_click([] {
			if (!m_vars.m_peds_ingore_player) {
				native::set_police_ignore_player(menu::player::get_local_player().m_ped, true);
				native::set_everyone_ignore_player(menu::player::get_local_player().m_ped, true);
				native::set_player_can_be_hassled_by_gangs(menu::player::get_local_player().m_ped, false);
				native::set_ignore_low_priority_shocking_events(menu::player::get_local_player().m_ped, true);
			}
		}));

	add_option(button_option("Bullshark Testosterone")
		.add_translate().add_hotkey()
		.add_click([] { menu::script_global(rage::global::_155_time_base).at(4013).as<bool>() = true; })); // 1.55 done

	add_option(scroll_option<int>(SCROLLSELECT, "Merryweather Request")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_merryweather, 0, NUMOF(request), request)
		.add_click([] {
			switch (m_vars.m_merryweather) {
				case 0: menu::script_global(rage::global::_155_customs_base).at(884).as<bool>() = true; break;  // 1.55 done
				case 1: menu::script_global(rage::global::_155_customs_base).at(4454).as<bool>() = true; break; // 1.55 done
				case 2: menu::script_global(rage::global::_155_customs_base).at(4453).as<bool>() = true; break; // 1.55 done
				case 3: menu::script_global(rage::global::_155_customs_base).at(876).as<bool>() = true; break; // 1.55 done
			}
		}));

	add_option(button_option("Suicide")
		.add_translate().add_hotkey()
		.add_click([] { native::apply_damage_to_ped(menu::player::get_local_player().m_ped, 30000, true); }));

	add_option(button_option("Clone")
		.add_translate().add_hotkey()
		.add_click([] { native::clone_ped(menu::player::get_local_player().m_ped, menu::player::get_local_player().m_heading, true, false); }));

	add_option(button_option("Health & Armor Regeneration")
		.add_translate().add_hotkey()
		.add_click([] {
		native::set_ped_armour(menu::player::get_local_player().m_ped, 100);
		native::set_entity_health(menu::player::get_local_player().m_ped, native::get_entity_max_health(menu::player::get_local_player().m_ped));
	}));

	add_option(button_option("Sky Dive")
		.add_translate().add_hotkey()
		.add_click([] {
			if (native::get_entity_height_above_ground(menu::player::get_local_player().m_ped) < 50.f) {
				native::set_entity_coords(menu::player::get_local_player().m_ped, menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z + 1000.f, true, true, true, false);
				native::task_sky_dive(menu::player::get_local_player().m_ped, TRUE);
			}
		}));

	add_option(toggle_option("Reduced Collision")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_reduced_collision).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(TOGGLE, "Invisibility")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_invisibility)
		.add_scroll(m_vars.m_invisibility_var, 0, NUMOF(invisibility), invisibility).add_savable(get_submenu_name_stack())
		.add_click([] {
			if (!m_vars.m_invisibility) {
				native::set_entity_visible(menu::player::get_local_player().m_ped, true, true);
				native::network_set_entity_invisible_to_network(menu::player::get_local_player().m_ped, false);
				native::set_local_player_invisible_locally(false);
			}
		}));

	add_option(toggle_option("Superman")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_superman));

	add_option(toggle_option("Badsport")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_badsport)
		.add_click([] {
			badsport(m_vars.m_badsport);
		})
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Breathe Fire")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_breathe_fire)
		.add_click([] { if (!m_vars.m_breathe_fire) native::remove_particle_fx(m_vars.m_breathe_fire_handle, false); }).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Swim Anywhere")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_swim_anywhere).add_savable(get_submenu_name_stack())
		.add_tooltip("~y~Notice: ~w~Local only"));

	add_option(toggle_option("Kill Killers")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_kill_killers).add_savable(get_submenu_name_stack())
		.add_tooltip("Kill peds/players that kill you"));
}

void player_menu::update() {}

void player_menu::update_once() {}

void player_menu::feature_update() {
	if (m_vars.m_kill_killers) {
		if (!menu::player::get_local_player().m_alive) {
			Entity killer = native::get_ped_source_of_death(menu::player::get_local_player().m_ped);
			if (native::does_entity_exist(killer)) {
				if (!native::is_entity_dead(killer, 0)) {
					math::vector3<float> position = native::get_entity_coords(killer, true);
					if (!position.is_null()) {
						native::add_explosion(position.x, position.y, position.z, 0, 50.f, false, true, 0.f, false);
					}
				}
			}
		}
	}

	if (m_vars.m_peds_ingore_player) {
		native::set_police_ignore_player(menu::player::get_local_player().m_ped, false);
		native::set_everyone_ignore_player(menu::player::get_local_player().m_ped, false);
		native::set_player_can_be_hassled_by_gangs(menu::player::get_local_player().m_ped, true);
		native::set_ignore_low_priority_shocking_events(menu::player::get_local_player().m_ped, false);
	}

	if (m_vars.m_invisibility) {
		switch (m_vars.m_invisibility_var) {
			case 0:
				native::set_local_player_invisible_locally(true);
				break;

			case 1:
				native::network_set_entity_invisible_to_network(menu::player::get_local_player().m_ped, true);
				native::set_entity_locally_visible(menu::player::get_local_player().m_ped);
				break;

			case 2:
				native::network_set_entity_invisible_to_network(menu::player::get_local_player().m_ped, true);
				native::set_local_player_invisible_locally(true);
				break;
		}
	}

	if (m_vars.m_godmode) {
		native::set_entity_invincible(menu::player::get_local_player().m_ped, true);
	}

	if (m_vars.m_disable_ragdoll) {
		no_ragdoll();
	}

	if (m_vars.m_disable_police) {
		native::set_max_wanted_level(0);
		native::clear_player_wanted_level(menu::player::get_local_player().m_id);
	}

	if (m_vars.m_reduced_collision) {
		native::set_ped_capsule(menu::player::get_local_player().m_ped, 0.001f);
	}

	if (m_vars.m_invisibility) {
		native::set_entity_visible(menu::player::get_local_player().m_ped, false, false);
	}

	if (m_vars.m_superman) {
		int left_right = native::get_control_value(2, 188);
		int up_down = native::get_control_value(2, 189);

		if (native::get_entity_height_above_ground(menu::player::get_local_player().m_ped) < 3.f) {
			native::give_weapon_to_ped(menu::player::get_local_player().m_ped, 0xFBAB5776, -1, true, true);

			math::vector3<float> coords = menu::player::get_local_player().m_coords;
			coords.z += 100.f;
			native::set_entity_coords(menu::player::get_local_player().m_ped, coords.x, coords.y, coords.z, false, false, false, false);
		} else {
			if (up_down == 254 || menu::input::is_pressed(true, 'S')) {
				native::apply_force_to_entity(menu::player::get_local_player().m_ped, 1, 0.f, 3.f, 10.f, 0.f, 0.f, 0.f, false, true, true, true, false, true);
			}

			if (up_down == 0 || menu::input::is_pressed(true, 'W')) {
				native::apply_force_to_entity(menu::player::get_local_player().m_ped, 1, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, false, true, true, true, false, true);
			}

			if (menu::input::is_pressed(true, VK_SHIFT) || menu::input::is_pressed(false, ControlFrontendRt)) {
				native::apply_force_to_entity(menu::player::get_local_player().m_ped, 1, 0.f, 15.f, .3f, 0.f, 0.f, 0.f, false, true, true, true, false, true);
			}

			if (left_right == 254 || menu::input::is_pressed(true, 'D')) {
				native::apply_force_to_entity(menu::player::get_local_player().m_ped, 1, 1.20f, 0.f, 0.f, 0.f, 0.1f, 0.f, false, true, true, true, false, true);
			}

			if (left_right == 0 || menu::input::is_pressed(true, 'A')) {
				native::apply_force_to_entity(menu::player::get_local_player().m_ped, 1, -1.20f, 0.f, 0.f, 0.f, 0.1f, 0.f, false, true, true, true, false, true);
			}
		}
	}

	if (m_vars.m_off_the_radar) {
		off_the_radar();
	}

	if (m_vars.m_reveal_hidden_players) {
		reveal_hidden_players();
	}

	if (m_vars.m_cops_turn_blind_eye) {
		cops_turn_blind_eye();
	}

	if (m_vars.m_swim_anywhere) {
		if (global::vars::g_ped_factory) {
			auto Ped = global::vars::g_ped_factory->m_local_ped;
			if (Ped) {
				Ped->set_flag((1 << 1)); // IS_PED_SWIMMING
			}
		}
	}

	if (m_vars.m_breathe_fire) {
		if (native::has_named_ptfx_asset_loaded("core")) {
			native::use_particle_fx_asset_next_call("core");
			if (!native::does_particle_fx_looped_exist(m_vars.m_breathe_fire_handle)) {
				m_vars.m_breathe_fire_handle = native::start_particle_fx_looped_on_entity_bone("ent_sht_flame", menu::player::get_local_player().m_ped, -0.02f, 0.2f, 0.0f, 90.0f, 100.0f, 90.0f, native::get_ped_bone_index(menu::player::get_local_player().m_ped, 31086), 1.0f, false, false, false);
			}
		} else {
			native::request_named_ptfx_asset("core");
		}
	}
}

player_menu* g_instance;
player_menu* player_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new player_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}