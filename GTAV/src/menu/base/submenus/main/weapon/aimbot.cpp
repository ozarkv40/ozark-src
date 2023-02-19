#include "aimbot.h"
#include "menu/base/submenu_handler.h"
#include "weapon_mods.h"
#include "global/lists.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/camera.h"
#include "menu/base/renderer.h"
#include "menu/base/util/player_manager.h"
#include "rage/engine.h"
#include "triggerbot.h"

using namespace weapon::aimbot::vars;

namespace weapon::aimbot::vars {
	variables m_vars;

	scroll_struct<int> aim_entity[] = {
		{ localization("Players Only", true), 0, },
		{ localization("Peds Only", true), 1, },
		{ localization("Everyone", true), 2 },
	};

	scroll_struct<int> aim_filter[] = {
		{ localization("Visible", true), 0, },
		{ localization("Logical", true), 1 },
	};

	scroll_struct<int> aim_type[] = {
		{ localization("Snap", true), 0, },
		{ localization("Silent", true), 1 },
	};
}

void aimbot_menu::load() {
	set_name("Aim Assist");
	set_parent<weapon_mods_menu>();

	add_option(submenu_option("Triggerbot")
		.add_translate().add_hotkey()
		.add_submenu<triggerbot_menu>());

	add_option(toggle_option("Toggle Aimbot")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Aiming Required")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_aiming_required).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(SCROLL, "Aim Entity")
		.add_translate()
		.add_scroll(m_vars.m_aim_entity, 0, NUMOF(aim_entity), aim_entity).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(SCROLL, "Aim Filter")
		.add_translate()
		.add_scroll(m_vars.m_aim_filter, 0, NUMOF(aim_filter), aim_filter).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(SCROLL, "Aim Type")
		.add_translate()
		.add_scroll(m_vars.m_aim_type, 0, NUMOF(aim_type), aim_type).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(SCROLL, "Aim Tag")
		.add_translate()
		.add_scroll(m_vars.m_aim_tag, 0, NUMOF(global::lists::g_ped_bones), global::lists::g_ped_bones).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<float>(SCROLL, "Aim Distance")
		.add_translate()
		.add_scroll(m_vars.m_aim_distance, 0, NUMOF(global::lists::g_distances), global::lists::g_distances).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Limit to FOV")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_fov)
		.add_number(m_vars.m_fov_range, "%.2f", 0.01f).add_min(0.f).add_max(5.f).can_loop().set_scroll_speed(10).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Draw FOV Radius")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_fov_draw).add_savable(get_submenu_name_stack())
		.add_tooltip("Draws the FOV radius on-screen")
		.add_requirement([] { return m_vars.m_fov; }));

	add_option(scroll_option<uint32_t>(TOGGLE, "Auto Fire (With Delay)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_auto_fire)
		.add_scroll(m_vars.m_auto_fire_delay, 0, NUMOF(global::lists::g_timers), global::lists::g_timers).add_savable(get_submenu_name_stack()));
}

void aimbot_menu::update() {}

void aimbot_menu::update_once() {}

void aimbot_menu::feature_update() {
	if (m_vars.m_toggle) {
		if (m_vars.m_fov && m_vars.m_fov_draw) {
			menu::renderer::draw_sprite({ "ozarktextures", "circle_rev2.png" }, { 0.5f, 0.5f }, { 0.1f * m_vars.m_fov_range, 0.18f * m_vars.m_fov_range }, 0.f, { 255, 255, 255, 255 });
		}

		if (m_vars.m_aiming_required) {
			if (!menu::player::get_local_player().m_is_aiming) {
				return;
			}
		}

		float closest_distance = 9999.f;
		Ped closest_entity = 0;

		switch (m_vars.m_aim_entity) {
			case 2:
			case 0: {
				// players only
				menu::player::for_each([&](menu::player::player_context& player) {
					if (native::is_entity_dead(player.m_ped, 0)) return; // alive check
					if (player.m_id == menu::player::get_local_player().m_id) return;
					if (m_vars.m_aim_filter == 0 && !native::has_entity_clear_los_to_entity(menu::player::get_local_player().m_ped, player.m_ped, 1)) return; // visible check
					if (native::get_entity_height_above_ground(player.m_ped) < 0.f) return;

					float distance = menu::player::get_local_player().m_coords.get_distance(player.m_coords);
					if (distance > global::lists::g_distances[m_vars.m_aim_distance].m_result) return;

					if (m_vars.m_fov) {
						math::vector2<float> screen_position;
						if (native::get_screen_coord_from_world_coord(player.m_coords.x, player.m_coords.y, player.m_coords.z, &screen_position.x, &screen_position.y)) {
							float left_side = 0.5f - ((0.1f * m_vars.m_fov_range) / 2.f);
							float right_side = 0.5f + ((0.1f * m_vars.m_fov_range) / 2.f);
							float top = 0.5f - ((0.18f * m_vars.m_fov_range) / 2.f);
							float bottom = 0.5f + ((0.18f * m_vars.m_fov_range) / 2.f);

							if (!((screen_position.x >= left_side && screen_position.x <= right_side) && (screen_position.y >= top && screen_position.y <= bottom))) {
								return;
							}
						} else return;
					}

					if (distance < closest_distance) {
						closest_distance = distance;
						closest_entity = player.m_ped;
					}
				}, true);

				if (m_vars.m_aim_entity != 2) break;
			}

			case 1: {
				// peds only
				global::vars::g_ped_pool->for_each([&](Ped ped, void* ptr) {
					if (native::is_ped_a_player(ped)) return;
					if (native::is_entity_dead(ped, TRUE)) return;
					if (m_vars.m_aim_filter == 0 && !native::has_entity_clear_los_to_entity(menu::player::get_local_player().m_ped, ped, 1)) return;
					if (native::get_entity_height_above_ground(ped) < 0.f) return;

					math::vector3<float> coords = native::get_entity_coords(ped, false);
					float distance = menu::player::get_local_player().m_coords.get_distance(coords);
					if (distance > global::lists::g_distances[m_vars.m_aim_distance].m_result) return;

					if (m_vars.m_fov) {
						math::vector2<float> screen_position;
						if (native::get_screen_coord_from_world_coord(coords.x, coords.y, coords.z, &screen_position.x, &screen_position.y)) {
							float left_side = 0.5f - ((0.1f * m_vars.m_fov_range) / 2.f);
							float right_side = 0.5f + ((0.1f * m_vars.m_fov_range) / 2.f);
							float top = 0.5f - ((0.18f * m_vars.m_fov_range) / 2.f);
							float bottom = 0.5f + ((0.18f * m_vars.m_fov_range) / 2.f);

							if (!((screen_position.x >= left_side && screen_position.x <= right_side) && (screen_position.y >= top && screen_position.y <= bottom))) {
								return;
							}
						} else return;
					}

					if (distance < closest_distance) {
						closest_distance = distance;
						closest_entity = ped;
					}
				});

				if (m_vars.m_aim_entity != 2) break;
			}
		}

		if (closest_entity) {
			math::vector3<float> bone_coords = native::get_world_position_of_entity_bone(closest_entity, native::get_ped_bone_index(closest_entity, global::lists::g_ped_bones[m_vars.m_aim_tag].m_result));

			if (m_vars.m_aim_type == 0) {
				rage::network::player_angles* camera = menu::camera::get_player_angles();
				if (is_valid_ptr(camera)) {
					math::vector3_<float> crosshair = camera->m_crosshair_location;
					math::vector3<float> converted(crosshair.x, crosshair.y, crosshair.z);

					float distance = bone_coords.get_distance(converted);
					camera->m_view_angles = { (bone_coords.x - crosshair.x) / distance, (bone_coords.y - crosshair.y) / distance, (bone_coords.z - crosshair.z) / distance };

					if (m_vars.m_auto_fire) {
						menu::timers::run_timed(&m_vars.m_auto_fire_delay_timer, global::lists::g_timers[m_vars.m_auto_fire_delay].m_result, [=] {
							native::set_ped_shoots_at_coord(menu::player::get_local_player().m_ped, bone_coords.x, bone_coords.y, bone_coords.z, true);
						});
					}
				}
			} else {
				if (m_vars.m_auto_fire) {
					menu::timers::run_timed(&m_vars.m_auto_fire_delay_timer, global::lists::g_timers[m_vars.m_auto_fire_delay].m_result, [=] {
						native::set_ped_shoots_at_coord(menu::player::get_local_player().m_ped, bone_coords.x, bone_coords.y, bone_coords.z, true);
					});
				}

				if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
					native::set_ped_shoots_at_coord(menu::player::get_local_player().m_ped, bone_coords.x, bone_coords.y, bone_coords.z, true);
				}
			}
		}
	}
}

aimbot_menu* g_instance;
aimbot_menu* aimbot_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new aimbot_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
