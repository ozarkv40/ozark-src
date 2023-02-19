#include "weapon_mods.h"
#include "menu/base/submenu_handler.h"
#include "../../main.h"
#include "util/log.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/raycast.h"
#include "menu/base/submenus/main/player/movement.h"
#include "menu/base/util/camera.h"
#include "menu/base/util/control.h"
#include "explosions/explosion_editor.h"
#include "explosions/explosion_gun.h"
#include "aimbot.h"
#include "weapon_modifiers.h"
#include "entity_gun.h"
#include "particle_gun.h"
#include "gravity_gun.h"
#include "weapon_disables.h"
#include "give_weapons_ammo.h"

using namespace weapon::mods::vars;

namespace weapon::mods::vars {
	variables m_vars;

	scroll_struct<int> targeting_mode[] = {
		{ localization("Traditional", true), 0, },
		{ localization("Free Aim", true), 1, },
		{ localization("Assisted Aim", true), 2, },
		{ localization("Assisted Aim - Full", true), 3 },
		{ localization("Assisted Aim - Partial", true), 4 }
	};
}

void weapon_mods_menu::load() {
	set_name("Weapon");
	set_parent<main_menu>();

	add_option(submenu_option("Give Weapons and Ammo")
		.add_translate().add_hotkey()
		.add_submenu<give_weapons_ammo_menu>());

	add_option(submenu_option("Aim Assist")
		.add_translate().add_hotkey()
		.add_submenu<aimbot_menu>());

	add_option(submenu_option("Modifiers")
		.add_translate().add_hotkey()
		.add_submenu<weapon_modifiers_menu>());

	add_option(submenu_option("Explosion Editor")
		.add_translate().add_hotkey()
		.add_submenu<explosion_editor_menu>());

	add_option(submenu_option("Explosion Gun")
		.add_translate().add_hotkey()
		.add_submenu<explosion_gun_menu>());

	add_option(submenu_option("Entity Gun")
		.add_translate().add_hotkey()
		.add_submenu<entity_gun_menu>());

	add_option(submenu_option("Particle Gun")
		.add_translate().add_hotkey()
		.add_submenu<particle_gun_menu>());

	add_option(submenu_option("Gravity Gun")
		.add_translate().add_hotkey()
		.add_submenu<gravity_gun_menu>());

	add_option(submenu_option("Disables")
		.add_translate().add_hotkey()
		.add_submenu<weapon_disables_menu>());

	add_option(toggle_option("Infinite Ammo")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_infinite_ammo)
		.add_click([] { if (!m_vars.m_infinite_ammo) native::set_ped_infinite_ammo_clip(menu::player::get_local_player().m_ped, false); }).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Instant Kill")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_instant_kill).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Rapid Fire")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rapid_fire).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Laser Sight")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_laser_sight).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Explosive Bullets")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_explosive_ammo).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Incendiary Bullets")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_incendiary_ammo).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Delete Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_delete_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Force Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_force_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Teleport Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_teleport_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Airstrike Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_airstrike_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Defibrillator Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_defibrillator_gun)
		.add_click([] { if (m_vars.m_defibrillator_gun) native::give_weapon_to_ped(menu::player::get_local_player().m_ped, 0x3656c8c1, -1, true, true); }).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Money Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_money_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Clown Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_clown_gun)
		.add_click([] {
		if (m_vars.m_clown_gun) {
			native::request_named_ptfx_asset("scr_rcbarry2");
			native::use_particle_fx_asset_next_call("scr_rcbarry2");
			native::start_particle_fx_looped_at_coord("scr_clown_death", menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, 0, 0, 0, 0, true, true, true, true);
		} else {
			native::enable_clown_blood_vfx(false);
		}
	}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Shrink Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_shrink_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Dead Eye Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_deadeye_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Rope Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rope_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Vehicle Stealer Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_vehicle_stealer_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Valkyrie Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_valkyrie_gun).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Hash Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_hash_gun).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(SCROLL, "Targeting Mode")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_targeting_mode, 0, NUMOF(targeting_mode), targeting_mode)
		.add_click([] { native::set_player_targeting_mode(m_vars.m_targeting_mode); }).add_savable(get_submenu_name_stack()));

	add_option(button_option("Remove Weapons")
		.add_translate().add_hotkey()
		.add_click([] { native::remove_all_ped_weapons(menu::player::get_local_player().m_ped, true); }));
}

void weapon_mods_menu::update() {}

void weapon_mods_menu::update_once() {
	m_vars.m_targeting_mode = native::_0xDFFA5BE8381C3314();
}

void weapon_mods_menu::feature_update() {
	if (menu::player::get_local_player().m_has_weapon_in_hand) {
		if (m_vars.m_hash_gun) {
			static int timer = 0;
			menu::timers::run_timed(&timer, 250, [] {
				if (menu::player::get_local_player().m_is_aiming) {
					menu::raycast cast = menu::raycast_infront(999.f);
					if (cast.hit_something() && cast.hit_entity()) {
						uint32_t model = native::get_entity_model(cast.get_entity());
						LOG_CUSTOM("Hash Gun", "Hash: %X (%u)", model, model);
					}
				}
			});
		}

		if (m_vars.m_infinite_ammo) {
			native::set_ped_infinite_ammo_clip(menu::player::get_local_player().m_ped, true);
		}

		if (m_vars.m_instant_kill) {
			native::set_player_melee_weapon_damage_modifier(menu::player::get_local_player().m_id, 99999.f, 1);
			native::set_player_weapon_damage_modifier(menu::player::get_local_player().m_id, 99999.f);
		}


		if (m_vars.m_rapid_fire && !player::movement::vars::m_vars.m_no_clip_bind) {
			if (!menu::player::get_local_player().m_in_vehicle) {
				if (native::is_control_pressed(0, ControlAttack)) {
					math::vector3<float> start = native::get_gameplay_cam_coord() + (menu::camera::get_direction());
					math::vector3<float> end = native::get_gameplay_cam_coord() + (menu::camera::get_direction() * 200.f);
					native::shoot_single_bullet_between_coords_ignore_entity(start.x, start.y, start.z, end.x, end.y, end.z, native::get_weapon_damage_type(menu::player::get_local_player().m_weapon_hash), true, menu::player::get_local_player().m_weapon_hash, menu::player::get_local_player().m_ped, true, false, 500.0f, menu::player::get_local_player().m_entity, 0);
				}
			}
		}

		if (m_vars.m_laser_sight) {
			if (!menu::player::get_local_player().m_in_vehicle) {
				if (menu::player::get_local_player().m_is_aiming) {
					math::vector3<float> start_point = native::get_world_position_of_entity_bone(menu::player::get_local_player().m_ped, native::get_ped_bone_index(menu::player::get_local_player().m_ped, 0x6f06));
					math::vector3<float> updated_coords = { 0.0f, 200.0f, (native::tan(native::get_gameplay_cam_relative_pitch()) * 200.0f) };
					math::vector3<float> end_point = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_ped, updated_coords.x, updated_coords.y, updated_coords.z);
					native::draw_line(start_point.x, start_point.y, start_point.z, end_point.x, end_point.y, end_point.z, 255, 0, 0, 255);
				}
			}
		}

		if (m_vars.m_explosive_ammo) {
			if (global::vars::g_ped_factory) {
				if (global::vars::g_ped_factory->m_local_ped) {
					if (global::vars::g_ped_factory->m_local_ped->m_player_info) {
						global::vars::g_ped_factory->m_local_ped->m_player_info->m_frame_flags |= 0x800;
					}
				}
			}
		}

		if (m_vars.m_incendiary_ammo) {
			if (global::vars::g_ped_factory) {
				if (global::vars::g_ped_factory->m_local_ped) {
					if (global::vars::g_ped_factory->m_local_ped->m_player_info) {
						global::vars::g_ped_factory->m_local_ped->m_player_info->m_frame_flags |= 0x1000;
					}
				}
			}
		}

		if (m_vars.m_delete_gun) {
			Entity entity;
			if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
				if (native::get_entity_player_is_free_aiming_at(menu::player::get_local_player().m_id, &entity)) {
					if (native::is_entity_a_ped(entity)) {
						entity = native::is_ped_in_any_vehicle(entity, true) ? native::get_vehicle_ped_is_in(entity, false) : entity;
					}

					if (native::does_entity_exist(entity)) {
						menu::control::request_control(entity, [](Entity ent) {
							native::set_entity_as_mission_entity(ent, true, true);
							native::delete_entity(&ent);
						});
					}
				}
			}
		}

		if (m_vars.m_force_gun) {
			if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
				menu::raycast cast = menu::raycast_infront(99999.0f);
				if (cast.hit_entity()) {
					menu::control::request_control(cast.get_entity(), [](Entity ent) {
						math::vector3<float> velocity = ((menu::player::get_local_player().m_coords + (menu::camera::get_direction() * 9999.f)) - native::get_entity_coords(ent, false)) * 4.f;
						native::set_entity_velocity(ent, velocity.x, velocity.y, velocity.z);
					}, false);
				}
			}
		}

		if (m_vars.m_teleport_gun) {
			if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
				menu::raycast cast = menu::raycast_infront(99999.0f);
				if (!cast.get_coords().is_null() && cast.get_coords().get_distance(menu::player::get_local_player().m_coords) > 3.5f) {
					native::set_entity_coords(menu::player::get_local_player().m_entity, cast.get_coords().x, cast.get_coords().y, cast.get_coords().z, true, true, true, false);
				}
			}
		}

		if (m_vars.m_airstrike_gun) {
			if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
				menu::raycast cast = menu::raycast_infront(99999.0f);
				if (!cast.get_coords().is_null() && cast.get_coords().get_distance(menu::player::get_local_player().m_coords) > 3.5f) {
					menu::control::simple_request_weapon(0x47757124);
					menu::control::simple_request_weapon(0xf8a3939f);

					math::vector3<float> hit_coords = cast.get_coords();
					native::shoot_single_bullet_between_coords_ignore_entity(hit_coords.x, hit_coords.y, hit_coords.z, hit_coords.x, hit_coords.y, hit_coords.z, native::get_weapon_damage_type(0x47757124), true, 0x47757124, menu::player::get_local_player().m_ped, true, false, 500.0f, menu::player::get_local_player().m_entity, 0);
					native::shoot_single_bullet_between_coords_ignore_entity(hit_coords.x, hit_coords.y, hit_coords.z + 60.0f, hit_coords.x, hit_coords.y, hit_coords.z, native::get_weapon_damage_type(0xf8a3939f), true, 0xf8a3939f, menu::player::get_local_player().m_ped, true, false, 500.0f, menu::player::get_local_player().m_entity, 0);
				}
			}
		}

		if (m_vars.m_defibrillator_gun) {
			if (menu::player::get_local_player().m_weapon_hash == 0x3656c8c1) {
				Entity aimed;
				if (native::get_entity_player_is_free_aiming_at(menu::player::get_local_player().m_id, &aimed)) {
					if (native::is_entity_a_ped(aimed) && native::is_entity_dead(aimed, 0)) {
						native::resurrect_ped(aimed);
						native::revive_injured_ped(aimed);
						native::set_entity_health(aimed, 100);
					}
				}
			}
		}

		if (m_vars.m_money_gun) {
			if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
				menu::raycast cast = menu::raycast_infront(99999.0f);
				if (!cast.get_coords().is_null()) {
					menu::control::simple_request_model(0x113fd533);

					math::vector3<float> hit_coords = cast.get_coords();
					native::create_ambient_pickup(0x1e9a99f8, hit_coords.x, hit_coords.y, hit_coords.z, 1, 2500, 0x113fd533, 1, 1);
				}
			}
		}

		if (m_vars.m_clown_gun) {
			native::enable_clown_blood_vfx(true);
		}

		if (m_vars.m_shrink_gun) {
			Entity aimed;
			if (native::get_entity_player_is_free_aiming_at(menu::player::get_local_player().m_id, &aimed)) {
				if (native::is_entity_a_ped(aimed)) {
					native::set_ped_config_flag(aimed, 223, true);
				}
			}
		}

		if (m_vars.m_deadeye_gun) {
			if (!m_vars.m_deadeye_gun_internal) {
				if (m_vars.m_deadeye_gun_timeout) {
					m_vars.m_deadeye_gun_timeout_timer.start(2500);
					if (m_vars.m_deadeye_gun_timeout_timer.is_ready()) {
						m_vars.m_deadeye_gun_timeout_timer.reset();
						m_vars.m_deadeye_gun_timeout = false;
					}
				}

				if (menu::player::get_local_player().m_is_aiming) {
					if (!m_vars.m_deadeye_gun_timeout) {
						m_vars.m_deadeye_gun_internal = true;
					}
				}
			}

			if (m_vars.m_deadeye_gun_internal) {
				m_vars.m_deadeye_gun_timer.start(5000);

				if (!m_vars.m_deadeye_gun_peds.empty()) {
					for (Ped ped : m_vars.m_deadeye_gun_peds) {
						if (native::does_entity_exist(ped)) {
							native::add_entity_icon(ped, "MP_Arrow");
							native::set_entity_icon_color(ped, 255, 0, 0, 255);
						}
					}
				}

				if (!m_vars.m_deadeye_gun_timer.is_ready() && menu::player::get_local_player().m_is_aiming) {
					native::start_screen_effect("explosionjosh3", -1, true);
					native::set_time_scale(0.35f);

					Entity entity = 0;
					if (native::get_entity_player_is_free_aiming_at(menu::player::get_local_player().m_id, &entity)) {
						if (native::does_entity_exist(entity)) {
							if (native::is_entity_a_vehicle(entity)) {
								if (native::does_entity_exist(native::get_ped_in_vehicle_seat(entity, -1, 0))) {
									entity = native::get_ped_in_vehicle_seat(entity, -1, 0);
								}
							}

							if (native::is_entity_a_ped(entity)) {
								if (!native::is_ped_dead_or_dying(entity, true)) {
									if (std::find(begin(m_vars.m_deadeye_gun_peds), end(m_vars.m_deadeye_gun_peds), entity) == end(m_vars.m_deadeye_gun_peds)) {
										m_vars.m_deadeye_gun_peds.push_back(entity);
									}

									native::set_timecycle_modifier("death");
								}
							}
						}
					}
				} else {
					for (Ped ped : m_vars.m_deadeye_gun_peds) {
						if (native::does_entity_exist(ped)) {
							math::vector3<float> coords = native::get_entity_coords(ped, true);
							native::add_explosion(coords.x, coords.y, coords.z, 1, FLT_MAX, true, false, 1.f, false);
						}
					}

					native::stop_screen_effect("explosionjosh3");
					native::clear_timecycle_modifier();
					native::set_time_scale(1.f);

					m_vars.m_deadeye_gun_timeout = true;
					m_vars.m_deadeye_gun_timer.reset();
					m_vars.m_deadeye_gun_peds.clear();
					m_vars.m_deadeye_gun_internal = false;
				}
			}
		}

		if (m_vars.m_rope_gun) {
			Entity ent;
			math::vector3<float> my_coords = menu::player::get_local_player().m_coords;

			if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
				if (!native::does_entity_exist(m_vars.m_rope_gun_entities[0]) && !native::does_entity_exist(m_vars.m_rope_gun_entities[1])) {
					if (native::get_entity_player_is_free_aiming_at(menu::player::get_local_player().m_id, &ent)) {
						m_vars.m_rope_gun_entities[0] = native::is_ped_in_any_vehicle(ent, true) ? ent = native::get_vehicle_ped_is_in(ent, false) : ent;

						math::vector3<float> entity_coords = native::get_entity_coords(m_vars.m_rope_gun_entities[0], true);
						float rope_length = native::get_distance_between_coords(my_coords.x, my_coords.y, my_coords.z, entity_coords.x, entity_coords.y, entity_coords.z, true);
						
						m_vars.m_rope_gun_object = native::add_rope(my_coords.x, my_coords.y, my_coords.z, 0.f, 0.f, 0.f, rope_length, 4, rope_length, 0.5f, 0.5f, false, false, true, 1.f, false, 0);
						native::rope_load_textures();
						native::activate_physics(m_vars.m_rope_gun_object);
					}
				} else {
					if (native::does_entity_exist(m_vars.m_rope_gun_entities[0]) && !native::does_entity_exist(m_vars.m_rope_gun_entities[1])) {
						if (native::get_entity_player_is_free_aiming_at(menu::player::get_local_player().m_id, &ent)) {
							m_vars.m_rope_gun_entities[1] = native::is_ped_in_any_vehicle(ent, true) ? ent = native::get_vehicle_ped_is_in(ent, false) : ent;

							math::vector3<float> entity_coords = native::get_entity_coords(m_vars.m_rope_gun_entities[0], true);
							menu::raycast cast = menu::raycast_infront(100.f);
							if (!cast.get_coords().is_null()) {
								native::attach_entities_to_rope(m_vars.m_rope_gun_object, m_vars.m_rope_gun_entities[0], m_vars.m_rope_gun_entities[1], entity_coords.x, entity_coords.y, entity_coords.z, cast.get_coords().x, cast.get_coords().y, cast.get_coords().z, native::get_distance_between_coords(entity_coords.x, entity_coords.y, entity_coords.z, cast.get_coords().x, cast.get_coords().y, cast.get_coords().z, true), 0, 0, 0, 0);
								native::pin_rope_vertex(m_vars.m_rope_gun_object, native::get_rope_vertex_count(m_vars.m_rope_gun_object) - 1, cast.get_coords().x, cast.get_coords().y, cast.get_coords().z);
								m_vars.m_rope_gun_entities[0] = 0;
								m_vars.m_rope_gun_entities[1] = 0;
							}
						}
					}
				}
			}

			if (native::does_entity_exist(m_vars.m_rope_gun_entities[0]) && !native::does_entity_exist(m_vars.m_rope_gun_entities[1])) {
				math::vector3<float> right_hand = native::get_ped_bone_coords(menu::player::get_local_player().m_ped, 6286, 0, 0, 0);
				math::vector3<float> entity_coords = native::get_entity_coords(m_vars.m_rope_gun_entities[0], true);
				native::pin_rope_vertex(m_vars.m_rope_gun_object, 0, right_hand.x, right_hand.y, right_hand.z);
				native::pin_rope_vertex(m_vars.m_rope_gun_object, native::get_rope_vertex_count(m_vars.m_rope_gun_object) - 1, entity_coords.x, entity_coords.y, entity_coords.z);
			}
		}

		if (m_vars.m_vehicle_stealer_gun) {
			if (menu::player::get_local_player().m_in_vehicle) {
				if (native::is_this_model_a_heli(menu::player::get_local_player().m_vehicle)) {
					if (native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, -1, 0) == menu::player::get_local_player().m_ped) {
						return;
					}
				}
			}

			Entity ent;
			if (native::get_entity_player_is_free_aiming_at(menu::player::get_local_player().m_id, &ent)) {
				if (native::is_entity_a_vehicle(ent) || (native::is_entity_a_ped(ent) && native::is_ped_in_any_vehicle(ent, true))) {
					if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
						bool was_player = false;

						if (native::is_entity_a_ped(ent)) {
							Ped p = native::get_ped_in_vehicle_seat(native::get_vehicle_ped_is_in(ent, false), -1, 1);
							if (native::does_entity_exist(p)) {
								ent = native::get_vehicle_ped_is_in(ent, false);

								if (native::is_ped_a_player(p)) {
									// do the nasty
									was_player = true;
									menu::control::request_control(ent, [](Entity) {}, true);
								}
							}
						}

						if (!was_player) {
							menu::control::simple_request_control(ent);
							native::clear_ped_tasks_immediately(native::get_ped_in_vehicle_seat(ent, -1, 1));
							native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, ent, -1);
							native::set_vehicle_engine_on(ent, true, true, false);
						} else {
							util::fiber::pool::add([=] {
								util::fiber::sleep(500);
								native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, ent, -1);
								native::set_vehicle_engine_on(ent, true, true, false);
							});
						}
					}
				}
			}
		}

		if (m_vars.m_valkyrie_gun) {
			uint32_t rocket_hash = joaat("prop_ld_bomb_01_open");
			if (!native::has_model_loaded(rocket_hash)) { // temp
				native::request_model(rocket_hash);
			}

			if (native::is_ped_shooting(menu::player::get_local_player().m_ped) && !m_vars.m_valkryie_running) {
				math::vector3<float> spawn_position = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_ped, 0.f, 2.f, 0.f);
				m_vars.m_valkyrie_object = native::create_object(rocket_hash, spawn_position.x, spawn_position.y, spawn_position.z, true, true, false);
				if (native::does_entity_exist(m_vars.m_valkyrie_object)) {
					math::vector3<float> rotation = menu::player::get_local_player().m_rotation;
					native::set_entity_rotation(m_vars.m_valkyrie_object, rotation.x, rotation.y, rotation.z, 2, true);

					m_vars.m_valkyrie_cam = native::create_cam_with_params("default_scripted_camera", spawn_position.x, spawn_position.y, spawn_position.z, rotation.x, rotation.y, rotation.z, 60.f, true, 2);
					native::attach_cam_to_entity(m_vars.m_valkyrie_cam, m_vars.m_valkyrie_object, 0.f, 1.f, 0.f, true);
					native::set_cam_active(m_vars.m_valkyrie_cam, true);
					native::render_script_cams(true, false, 1000, true, false, 0);

					m_vars.m_valkyrie_timer = native::get_game_timer() + 10000;
					m_vars.m_valkryie_running = true;
				}
			}

			if (m_vars.m_valkryie_running) {
				float height = (m_vars.m_valkyrie_timer - native::get_game_timer()) / 20000.0f;
				color_rgba col;

				if (height > 0.4f) {
					col = color_rgba(0, 255, 0);
				} else if (height <= 0.4f && height > 0.3f) {
					col = color_rgba(255, 255, 0);
				} else if (height <= 0.3f && height > 0.2f) {
					col = color_rgba(255, 119, 0);
				} else if (height <= 0.2f) {
					col = color_rgba(255, 0, 0);
				}

				menu::renderer::draw_rect({ 0.18f, 0.3f }, { 0.01f, 0.5f }, color_rgba(255, 255, 255, 150));
				menu::renderer::draw_rect({ 0.18f, 0.3f + (0.5f - height) }, { 0.01f, height }, col);

				math::vector3<float> gameplay_rotation = native::get_gameplay_cam_rot(2);
				native::set_cam_rot(m_vars.m_valkyrie_cam, gameplay_rotation.x, gameplay_rotation.y, gameplay_rotation.z, 2);

				math::vector3<float> coords = native::get_offset_from_entity_in_world_coords(m_vars.m_valkyrie_object, 0.f, 0.4f, 0.f);
				native::set_entity_coords(m_vars.m_valkyrie_object, coords.x, coords.y, coords.z, false, false, false, false);

				native::set_entity_rotation(m_vars.m_valkyrie_object, gameplay_rotation.x, gameplay_rotation.y, gameplay_rotation.z, 2, true);

				menu::raycast cast = menu::raycast_infront(25.f, native::get_cam_coord(m_vars.m_valkyrie_cam));
				if (native::get_game_timer() >= m_vars.m_valkyrie_timer || (!cast.get_coords().is_null() && cast.get_coords().get_distance(native::get_cam_coord(m_vars.m_valkyrie_cam)) < 3.f)) {
					m_vars.m_valkryie_running = false;

					math::vector3<float> cam_coords = native::get_cam_coord(m_vars.m_valkyrie_cam);
					native::add_owned_explosion(menu::player::get_local_player().m_ped, cam_coords.x, cam_coords.y, cam_coords.z, 27, 2.f, true, false, 0.5f);

					native::set_entity_as_mission_entity(m_vars.m_valkyrie_object, false, true);
					native::delete_entity(&m_vars.m_valkyrie_object);
					native::render_script_cams(false, false, 1000, true, false, 0);
					native::destroy_cam(m_vars.m_valkyrie_cam, true);
				}
			}


		}
	}
}

weapon_mods_menu* g_instance;
weapon_mods_menu* weapon_mods_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new weapon_mods_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
