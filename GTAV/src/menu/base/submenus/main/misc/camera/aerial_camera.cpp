#include "aerial_camera.h"
#include "menu/base/submenu_handler.h"
#include "../misc_camera.h"

using namespace misc::camera::aerial::vars;

namespace misc::camera::aerial::vars {
	variables m_vars;
}

void aerial_camera_menu::load() {
	set_name("Aerial Camera");
	set_parent<camera_menu>();

	add_option(toggle_option("Toggle Aerial Camera")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle_camera)
		.add_click([] {
			if (!native::does_cam_exist(m_vars.m_aerial_cam)) {
				m_vars.m_aerial_cam = native::create_camera(26379945, true);
				native::set_cam_active(m_vars.m_aerial_cam, true);
				native::render_script_cams(true, true, 1000, true, false, 0);
			} else {
				native::destroy_cam(m_vars.m_aerial_cam, true);
				native::render_script_cams(false, true, 1000, true, false, 0);
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(number_option<int>(SCROLL, "Camera Distance")
		.add_translate()
		.add_number(m_vars.m_distance, "%i", 1).add_min(0).add_max(300).set_scroll_speed(10)
		.add_savable(get_submenu_name_stack()));
}

void aerial_camera_menu::update() {}

void aerial_camera_menu::update_once() {}

void aerial_camera_menu::feature_update() {
	if (m_vars.m_toggle_camera) {
		if (native::does_cam_exist(m_vars.m_aerial_cam)) {
			math::vector3<float> coords = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_entity, 0, (float)(m_vars.m_distance / 2) * -1, (float)m_vars.m_distance);
			coords.z = menu::player::get_local_player().m_coords.z + m_vars.m_distance;
			native::set_cam_coord(m_vars.m_aerial_cam, coords.x, coords.y, coords.z);
			native::point_cam_at_entity(m_vars.m_aerial_cam, menu::player::get_local_player().m_entity, 0, 0, 0, true);
		}
	}
}

aerial_camera_menu* g_instance;
aerial_camera_menu* aerial_camera_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new aerial_camera_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
