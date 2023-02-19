#include "movement.h"
#include "menu/base/submenu_handler.h"
#include "../player.h"
#include "menu/base/util/input.h"
#include "menu/base/submenu_handler.h"
#include "menu/base/util/notify.h"
#include "menu/base/util/control.h"

using namespace player::movement::vars;

namespace player::movement::vars {
	variables m_vars;

	float get_analog_range(int stick) {
		return (((float)native::get_control_value(0, stick)) - 127) / 127;
	}

	void no_clip() {
		if (menu::input::is_just_pressed(true, VK_F8)) {
			m_vars.m_no_clip_bind ^= true;
			if (!m_vars.m_no_clip_bind) {
				native::set_entity_collision(menu::player::get_local_player().m_entity, true, true);
				native::freeze_entity_position(menu::player::get_local_player().m_entity, false);
				native::enable_all_control_actions(0);
			}
		}

		if (m_vars.m_no_clip && m_vars.m_no_clip_bind) {
			math::vector3<float> pos;
			pos.x = get_analog_range(ControlFrontendAxisX) * m_vars.m_no_clip_speed;
			pos.y = get_analog_range(ControlFrontendAxisY) * m_vars.m_no_clip_speed * -1.f;

			math::vector3<float> apos = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_entity, pos.x, pos.y, pos.z);
			float input = native::get_control_normal(0, ControlAttack) - native::get_control_normal(0, ControlAim);

			if (menu::input::is_pressed(false, ControlFrontendRt) || input > 0.f) {
				apos.z += m_vars.m_no_clip_speed;
			}

			if (menu::input::is_pressed(false, ControlFrontendLt) || input < 0.f) {
				apos.z -= m_vars.m_no_clip_speed;
			}

			native::set_entity_coords_no_offset(menu::player::get_local_player().m_entity, apos.x, apos.y, apos.z, false, false, false);

			math::vector3<float> rot = native::get_gameplay_cam_rot(2);
			native::set_entity_rotation(menu::player::get_local_player().m_entity, 0.f, rot.y, rot.z, 2, true);

			native::freeze_entity_position(menu::player::get_local_player().m_entity, true);
			native::set_entity_collision(menu::player::get_local_player().m_entity, false, false);

			native::disable_control_action(0, ControlFrontendLt, true);
			native::disable_control_action(0, ControlFrontendRt, true);
			native::disable_control_action(0, ControlFrontendCancel, true);
		}
	}
}

void movement_menu::load() {
	set_name("Movement");
	set_parent<player_menu>();

	add_string("No Clip");
	add_string("Press F8 to enable/disable");

	add_option(number_option<float>(TOGGLE, "No Clip")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_no_clip)
		.add_number(m_vars.m_no_clip_speed, "%.1f", 0.1f).add_min(0.0f).add_max(10.f).show_max().add_savable(get_submenu_name_stack())
		.add_click([this] {
			if (m_vars.m_no_clip) {
				if (m_vars.m_no_clip_notify) {
					m_vars.m_no_clip_notify = false;

					if (menu::submenu::handler::get_current() == this) {
						menu::notify::stacked(get_string("No Clip"), get_string("Press F8 to enable/disable"));
					}
				}
			} else {
				m_vars.m_no_clip_notify = true;
				native::set_entity_collision(menu::player::get_local_player().m_entity, true, true);
				native::freeze_entity_position(menu::player::get_local_player().m_entity, false);
				native::enable_all_control_actions(0);
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Run Multiplier")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_super_run)
		.add_number(m_vars.m_super_run_speed, "%.2f", 0.01f).add_min(0.0f).add_max(100.f).show_max().can_loop().set_scroll_speed(20)
		.add_click([] {
			if (global::vars::g_ped_factory && global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_player_info) {
					global::vars::g_ped_factory->m_local_ped->m_player_info->set_run_speed(m_vars.m_super_run ? m_vars.m_super_run_speed : 1.0f);
				}
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Swim Multiplier")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_super_swim)
		.add_number(m_vars.m_super_swim_speed, "%.2f", 0.01f).add_min(0.0f).add_max(100.f).show_max().can_loop().set_scroll_speed(20)
		.add_click([] {
			if (global::vars::g_ped_factory && global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_player_info) {
					global::vars::g_ped_factory->m_local_ped->m_player_info->m_swim_speed = 1.f;
				}
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Super Run")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_super_run_alternative)
		.add_number(m_vars.m_super_run_alternative_speed, "%.1f", 0.1f).add_min(0.0f).add_max(100.f).show_max().can_loop().set_scroll_speed(20).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Super Jump")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_super_jump).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Walk on Air")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_walk_on_air)
		.add_click([] {
			if (!m_vars.m_walk_on_air) {
				if (m_vars.m_walk_on_air_entity) {
					menu::control::request_control(m_vars.m_walk_on_air_entity, [](Entity ent) {
						native::set_entity_as_mission_entity(ent, true, true);
						native::delete_entity(&ent);
					});
				}
			}
		})
		.add_tooltip("Disable mid air and re-enable when at desired altitude to go down"));
}

void movement_menu::update() {}

void movement_menu::update_once() {}

void movement_menu::feature_update() {
	no_clip();

	if (m_vars.m_super_jump) {
		native::set_super_jump_this_frame(menu::player::get_local_player().m_id);
	}

	if (m_vars.m_super_run_alternative) {
		if (native::is_disabled_control_pressed(0, ControlSprint)) {
			native::apply_force_to_entity(menu::player::get_local_player().m_ped, 1, 0.f, m_vars.m_super_run_alternative_speed, 0.f, 0.f, 0.f, 0.f, 0, 1, 1, 1, 0, 1);
		}
	}

	if (m_vars.m_walk_on_air) {
		if (!native::does_entity_exist(m_vars.m_walk_on_air_entity)) {
			math::vector3<float> spawn_coords = menu::player::get_local_player().m_coords;
			spawn_coords.z -= 1.7f;
			m_vars.m_walk_on_air_entity = native::create_object(joaat("prop_pooltable_02"), spawn_coords.x, spawn_coords.y, spawn_coords.z, true, true, false);
		} else {
			native::set_entity_visible(m_vars.m_walk_on_air_entity, FALSE, FALSE);
			if (!menu::player::get_local_player().m_in_vehicle) {
				math::vector3<float> obj_pos = native::get_entity_coords(m_vars.m_walk_on_air_entity, FALSE);
				if (sqrtf(powf(menu::player::get_local_player().m_coords.x - obj_pos.x, 2.0f) + powf(menu::player::get_local_player().m_coords.y - obj_pos.y, 2.0f) + powf(menu::player::get_local_player().m_coords.z - obj_pos.z, 2.0f)) > 1.7f) {
					native::set_entity_heading(m_vars.m_walk_on_air_entity, menu::player::get_local_player().m_heading);
					if (native::is_ped_jumping(menu::player::get_local_player().m_ped)) {
						native::set_entity_coords_no_offset(m_vars.m_walk_on_air_entity, menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z - 1.7f, FALSE, FALSE, FALSE);
					} else {
						native::set_entity_coords_no_offset(m_vars.m_walk_on_air_entity, menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, obj_pos.z, FALSE, FALSE, FALSE);
					}
				}
			}
		}
	}
}

movement_menu* g_instance;
movement_menu* movement_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new movement_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
