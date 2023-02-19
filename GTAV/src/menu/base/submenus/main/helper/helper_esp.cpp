#include "helper_esp.h"
#include "menu/base/submenu_handler.h"
#include "esp/helper_esp_settings.h"
#include "util/caller.h"
#include "rage/engine.h"

using namespace helper::esp::vars;

namespace helper::esp::vars {
	variables m_vars;

	scroll_struct<int> name_types[] = {
		{ localization("Without Distance", true), 0 },
		{ localization("With Distance", true), 0 },
	};

	void name_esp(esp_context context, Entity entity, std::string name_override) {
		math::vector3<float> coords = native::get_entity_coords(entity, false);
		if (!coords.is_null()) {
			math::vector2<float> screen_coords;
			if (native::get_screen_coord_from_world_coord(coords.x, coords.y, coords.z, &screen_coords.x, &screen_coords.y)) {
				native::set_draw_origin(coords.x, coords.y, coords.z, false);

				if (*(uint32_t*)(global::vars::g_draw_origin_index) != 0xFFFFFFFF) {
					screen_coords = { 0.f, 0.f };
				}

				float x_offset = 0.002f;
				float text_height = 0.2f;
				float height = (text_height / 10.f);

				std::string text = "";
				
				if (name_override.empty()) {
					text = util::va::va("%X", native::get_entity_model(entity));
				} else {
					text = name_override;
				}

				float width = menu::renderer::calculate_string_width(text, 0, text_height) + (x_offset * 2.f);
				menu::renderer::draw_rect({ screen_coords.x - (width * 0.5f), screen_coords.y }, { width, height }, context.m_name_bg_color);
				menu::renderer::draw_text(text, { screen_coords.x, screen_coords.y + 0.002f }, text_height, 0, context.m_name_text_color, JUSTIFY_CENTER);

				// distance
				if (context.m_name_type == 1) {
					text = util::va::va("%.0fm", coords.get_distance(menu::player::get_local_player().m_coords));

					width = menu::renderer::calculate_string_width(text, 0, text_height) + (x_offset * 2.f);
					float new_y = screen_coords.y + height;
					menu::renderer::draw_rect({ screen_coords.x - (width * 0.5f), new_y }, { width, height }, context.m_name_bg_color);
					menu::renderer::draw_text(text, { screen_coords.x, new_y + 0.002f }, text_height, 0, context.m_name_text_color, JUSTIFY_CENTER);
				}

				native::clear_draw_origin();
			}
		}
	}

	void snapline_esp(esp_context context, Entity entity) {
		math::vector3<float> coords = native::get_entity_coords(entity, false);
		if (!coords.is_null()) {
			menu::renderer::draw_line(menu::player::get_local_player().m_coords, coords, context.m_snapline_color);
		}
	}

	void _2d_esp(esp_context context, Entity entity, int type) {
		// 0 = box, 1 = corners
	}

	void _3d_esp(esp_context context, Entity entity, int type) {
		// 0 = box, 1= axis
		math::vector3<float> coords = native::get_entity_coords(entity, false);
		if (!coords.is_null()) {
			math::vector3<float> min_dimensions;
			math::vector3<float> max_dimensions;
			native::get_model_dimensions(native::get_entity_model(entity), &min_dimensions, &max_dimensions);

			math::vector3<float> diameter = { max_dimensions.x - min_dimensions.x, max_dimensions.y - min_dimensions.y, max_dimensions.z - min_dimensions.z };
			math::vector3<float> radius = { diameter.x / 2.f, diameter.y / 2.f, diameter.z / 2.f };

			if (type == 0) {
				math::vector3<float> FACE_UL = native::get_offset_from_entity_in_world_coords(entity, radius.x * -1, radius.y, radius.z);
				math::vector3<float> FACE_UR = native::get_offset_from_entity_in_world_coords(entity, radius.x, radius.y, radius.z);
				math::vector3<float> FACE_BL = native::get_offset_from_entity_in_world_coords(entity, radius.x * -1, radius.y, radius.z * -1);
				math::vector3<float> FACE_BR = native::get_offset_from_entity_in_world_coords(entity, radius.x, radius.y, radius.z * -1);

				math::vector3<float> BACK_UL = native::get_offset_from_entity_in_world_coords(entity, radius.x * -1, radius.y * -1, radius.z);
				math::vector3<float> BACK_UR = native::get_offset_from_entity_in_world_coords(entity, radius.x, radius.y * -1, radius.z);
				math::vector3<float> BACK_BL = native::get_offset_from_entity_in_world_coords(entity, radius.x * -1, radius.y * -1, radius.z * -1);
				math::vector3<float> BACK_BR = native::get_offset_from_entity_in_world_coords(entity, radius.x, radius.y * -1, radius.z * -1);

				// Poles
				menu::renderer::draw_line(FACE_BL, FACE_UL, context.m_3d_box_color);
				menu::renderer::draw_line(FACE_BR, FACE_UR, context.m_3d_box_color);
				menu::renderer::draw_line(BACK_BL, BACK_UL, context.m_3d_box_color);
				menu::renderer::draw_line(BACK_BR, BACK_UR, context.m_3d_box_color);
				menu::renderer::draw_line(FACE_UL, FACE_UR, context.m_3d_box_color);
				menu::renderer::draw_line(FACE_BL, FACE_BR, context.m_3d_box_color);
				menu::renderer::draw_line(BACK_UL, BACK_UR, context.m_3d_box_color);
				menu::renderer::draw_line(BACK_BL, BACK_BR, context.m_3d_box_color);

				// Bridges
				menu::renderer::draw_line(FACE_UL, BACK_UL, context.m_3d_box_color);
				menu::renderer::draw_line(FACE_UR, BACK_UR, context.m_3d_box_color);
				menu::renderer::draw_line(FACE_BL, BACK_BL, context.m_3d_box_color);
				menu::renderer::draw_line(FACE_BR, BACK_BR, context.m_3d_box_color);

				// Inner Bridges
				menu::renderer::draw_line(coords, FACE_UL, context.m_3d_box_color);
				menu::renderer::draw_line(coords, FACE_UR, context.m_3d_box_color);
				menu::renderer::draw_line(coords, FACE_BL, context.m_3d_box_color);
				menu::renderer::draw_line(coords, FACE_BR, context.m_3d_box_color);
				menu::renderer::draw_line(coords, BACK_UL, context.m_3d_box_color);
				menu::renderer::draw_line(coords, BACK_UR, context.m_3d_box_color);
				menu::renderer::draw_line(coords, BACK_BL, context.m_3d_box_color);
				menu::renderer::draw_line(coords, BACK_BR, context.m_3d_box_color);
				return;
			}

			if (type == 1) {
				math::vector3<float> X_L = native::get_offset_from_entity_in_world_coords(entity, (diameter.x * 2.f) * -1, 0, 0);
				math::vector3<float> X_R = native::get_offset_from_entity_in_world_coords(entity, (diameter.x * 2.f), 0, 0);
				math::vector3<float> Y_F = native::get_offset_from_entity_in_world_coords(entity, 0, (diameter.y * 2.f), 0);
				math::vector3<float> Y_B = native::get_offset_from_entity_in_world_coords(entity, 0, (diameter.y * 2.f) * -1, 0);
				math::vector3<float> Z_U = native::get_offset_from_entity_in_world_coords(entity, 0, 0, 500);
				math::vector3<float> Z_D = native::get_offset_from_entity_in_world_coords(entity, 0, 0, -500);

				menu::renderer::draw_line(X_L, X_R, { 255, 0, 0, 255 });
				menu::renderer::draw_line(Y_F, Y_B, { 0, 255, 0, 255 });
				menu::renderer::draw_line(Z_U, Z_D, { 0, 0, 255, 255 });
				return;
			}
		}
	}

	void draw_bone(Entity entity, int first, int second, color_rgba color) {
		math::vector3<float> first_bone = native::get_ped_bone_coords(entity, first, 0.f, 0.f, 0.f);
		math::vector3<float> second_bone = native::get_ped_bone_coords(entity, second, 0.f, 0.f, 0.f);

		if (!first_bone.is_null() && !second_bone.is_null()) {
			float fx, fy, sx, sy;
			if (native::get_screen_coord_from_world_coord(first_bone.x, first_bone.y, first_bone.z, &fx, &fy)
				&& native::get_screen_coord_from_world_coord(second_bone.x, second_bone.y, second_bone.z, &sx, &sy)) {
				menu::renderer::draw_line_2d({ fx, fy, 0.f }, { sx, sy, 0.f }, color);
			}
		}
	}

	void draw_joint(Entity entity, int bone, color_rgba color) {
		math::vector3<float> coords = native::get_ped_bone_coords(entity, bone, 0.f, 0.f, 0.f);
		if (!coords.is_null()) {
			float x, y;
			if (native::get_screen_coord_from_world_coord(coords.x, coords.y, coords.z, &x, &y)) {
				native::draw_marker(28, coords.x, coords.y, coords.z, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.03f, 0.03f, 0.03f, color.r, color.g, color.b, color.a, 0, 0, 0, 0, 0, 0, 0);
			}
		}
	}

	void draw_joint2(Entity entity, int first, int second, color_rgba color, bool skip_first = false, bool skip_second = false) {
		math::vector3<float> first_bone = native::get_ped_bone_coords(entity, first, 0.f, 0.f, 0.f);
		math::vector3<float> second_bone = native::get_ped_bone_coords(entity, second, 0.f, 0.f, 0.f);

		if (!first_bone.is_null() && !second_bone.is_null()) {
			float x, y;
			if (native::get_screen_coord_from_world_coord(first_bone.x, first_bone.y, first_bone.z, &x, &y)) {
				math::vector3<float> mid;
				mid.x = (first_bone.x + second_bone.x) / 2.f;
				mid.y = (first_bone.y + second_bone.y) / 2.f;
				mid.z = (first_bone.z + second_bone.z) / 2.f;

				if (!skip_first) native::draw_marker(28, first_bone.x, first_bone.y, first_bone.z, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.03f, 0.03f, 0.03f, color.r, color.g, color.b, color.a, 0, 0, 0, 0, 0, 0, 0);
				if (!skip_second) native::draw_marker(28, second_bone.x, second_bone.y, second_bone.z, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.03f, 0.03f, 0.03f, color.r, color.g, color.b, color.a, 0, 0, 0, 0, 0, 0, 0);
				native::draw_marker(28, mid.x, mid.y, mid.z, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.03f, 0.03f, 0.03f, color.r, color.g, color.b, color.a, 0, 0, 0, 0, 0, 0, 0);
			}
		}
	}

	void skeleton_esp(esp_context context, Entity entity, int type) {
		// 0 = bones, 1 = joints
		math::vector3<float> coords = native::get_entity_coords(entity, false);
		if (!coords.is_null()) {
			if (native::is_entity_a_ped(entity) || native::is_ped_a_player(entity)) {
				if (type == 0) {
					// bones
					draw_bone(entity, SKEL_R_Foot, MH_R_Knee, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_R_Toe0, SKEL_R_Foot, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_L_Toe0, SKEL_L_Foot, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_L_Foot, MH_L_Knee, context.m_skeleton_bones_color);
					draw_bone(entity, MH_R_Knee, SKEL_Pelvis, context.m_skeleton_bones_color);
					draw_bone(entity, MH_L_Knee, SKEL_Pelvis, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_Pelvis, SKEL_Neck_1, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_Neck_1, SKEL_R_UpperArm, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_Neck_1, SKEL_L_UpperArm, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_R_UpperArm, SKEL_R_Forearm, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_L_UpperArm, SKEL_L_Forearm, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_R_Forearm, SKEL_R_Hand, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_L_Forearm, SKEL_L_Hand, context.m_skeleton_bones_color);
					draw_bone(entity, SKEL_Neck_1, SKEL_Head, context.m_skeleton_bones_color);

					return;
				}

				if (type == 1) {
					// joints
					draw_joint2(entity, SKEL_R_Foot, MH_R_Knee, context.m_skeleton_bones_color);
					draw_joint2(entity, SKEL_R_Toe0, SKEL_R_Foot, context.m_skeleton_bones_color, false, true);
					draw_joint2(entity, SKEL_L_Toe0, SKEL_L_Foot, context.m_skeleton_bones_color);
					draw_joint2(entity, SKEL_L_Foot, MH_L_Knee, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, MH_R_Knee, SKEL_Pelvis, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, MH_L_Knee, SKEL_Pelvis, context.m_skeleton_bones_color, true, true);
					draw_joint2(entity, SKEL_Pelvis, SKEL_Neck_1, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, SKEL_Neck_1, SKEL_R_UpperArm, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, SKEL_Neck_1, SKEL_L_UpperArm, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, SKEL_R_UpperArm, SKEL_R_Forearm, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, SKEL_L_UpperArm, SKEL_L_Forearm, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, SKEL_R_Forearm, SKEL_R_Hand, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, SKEL_L_Forearm, SKEL_L_Hand, context.m_skeleton_bones_color, true, false);
					draw_joint2(entity, SKEL_Neck_1, SKEL_Head, context.m_skeleton_bones_color, true, false);

					return;
				}
			}
		}
	}
}

void helper_esp_menu::load() {
	set_name("ESP");

	add_option(submenu_option("Settings")
		.add_translate()
		.add_submenu<helper_esp_settings_menu>());

	add_string("Toggle Name");
	//add_string("Toggle 2D - Box");
	//add_string("Toggle 2D - Corners");
	add_string("Toggle 3D - Box");
	add_string("Toggle 3D - Axis");
	add_string("Toggle Skeleton - Bones");
	add_string("Toggle Skeleton - Joints");
	//add_string("Toggle Weapon");
}

void helper_esp_menu::update() {}

void helper_esp_menu::update_once() {
	clear_options(1);

	if (!m_vars.m_current) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}

	add_option(scroll_option<int>(TOGGLE, get_string("Toggle Name"))
		.add_toggle(m_vars.m_current->m_name)
		.add_scroll(m_vars.m_current->m_name_type, 0, NUMOF(name_types), name_types));

	add_option(toggle_option(get_string("Toggle Snapline"))
		.add_toggle(m_vars.m_current->m_snapline));

	/*add_option(toggle_option(get_string("Toggle 2D - Box"))
		.add_toggle(m_vars.m_current->m_2d_box));

	add_option(toggle_option(get_string("Toggle 2D - Corners"))
		.add_toggle(m_vars.m_current->m_2d_corners));*/

	add_option(toggle_option(get_string("Toggle 3D - Box"))
		.add_toggle(m_vars.m_current->m_3d_box));

	add_option(toggle_option(get_string("Toggle 3D - Axis"))
		.add_toggle(m_vars.m_current->m_3d_axis));

	add_option(toggle_option(get_string("Toggle Skeleton - Bones"))
		.add_toggle(m_vars.m_current->m_skeleton_bones)
		.add_requirement([] { return m_vars.m_current->m_ped; }));

	add_option(toggle_option(get_string("Toggle Skeleton - Joints"))
		.add_toggle(m_vars.m_current->m_skeleton_joints)
		.add_requirement([] { return m_vars.m_current->m_ped; }));

	/*add_option(toggle_option(get_string("Toggle Weapon"))
		.add_toggle(m_vars.m_current->m_weapon)
		.add_requirement([] { return m_vars.m_current->m_ped; }));*/
}

void helper_esp_menu::feature_update() {}

helper_esp_menu* g_instance;
helper_esp_menu* helper_esp_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new helper_esp_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}