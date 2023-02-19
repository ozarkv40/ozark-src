#include "misc_camera.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"
#include "menu/base/util/camera.h"
#include "menu/base/util/timers.h"
#include "camera/aerial_camera.h"

using namespace misc::camera::vars;

namespace misc::camera::vars {
	variables m_vars;
}

void camera_menu::load() {
	set_name("Camera");
	set_parent<misc_menu>();

	add_option(submenu_option("Aerial Camera")
		.add_translate().add_hotkey()
		.add_submenu<aerial_camera_menu>());

	add_option(toggle_option("Freecam")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_freecam)
		.add_click([] {
			if (!m_vars.m_freecam) {
				if (native::does_cam_exist(m_vars.m_freecam_handle)) {
					native::set_cam_active(m_vars.m_freecam_handle, false);
					native::render_script_cams(false, true, 1000, true, false, 1);
					native::destroy_cam(m_vars.m_freecam_handle, false);
					native::set_focus_entity(menu::player::get_local_player().m_ped);
				}
			}
		}));

	add_option(number_option<float>(TOGGLE, "Camera Zoom")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_camera_zoom)
		.add_number(m_vars.m_camera_zoom_val, "%.0f", 1.f).add_min(0).add_max(1000.f).set_scroll_speed(10)
		.add_savable(get_submenu_name_stack()));
}

void camera_menu::update() {}

void camera_menu::update_once() {}

void camera_menu::feature_update() {
	if (m_vars.m_camera_zoom) {
		native::animate_gameplay_cam_zoom(1.f, m_vars.m_camera_zoom_val);
	}

	if (m_vars.m_freecam) {
		if (!native::does_cam_exist(m_vars.m_freecam_handle)) {
			math::vector3<float> coords = menu::player::get_local_player().m_coords;
			m_vars.m_freecam_handle = native::create_cam("DEFAULT_SCRIPTED_CAMERA", 0);
			native::set_cam_active(m_vars.m_freecam_handle, true);
			native::render_script_cams(true, true, 1000, true, false, 1);
			native::set_cam_coord(m_vars.m_freecam_handle, coords.x, coords.y, coords.z + 7.0f);
		} else {
			math::vector3<float> cam_coords = native::get_cam_coord(m_vars.m_freecam_handle);
			math::vector3<float> gameplay_cam_rot = native::get_gameplay_cam_rot(0);
			native::set_cam_rot(m_vars.m_freecam_handle, gameplay_cam_rot.x, gameplay_cam_rot.y, gameplay_cam_rot.z, 2);

			if (menu::player::get_local_player().m_in_vehicle) {
				native::set_vehicle_forward_speed(menu::player::get_local_player().m_vehicle, 0.0f);
			} else {
				native::task_stand_still(menu::player::get_local_player().m_ped, 10);
			}

			math::vector3<float> infront = menu::camera::get_direction();

			int left_right = native::get_control_value(2, 188);
			int up_down = native::get_control_value(2, 189);

			auto w_down = GetKeyState('W') & 0x8000 || up_down == 0;
			auto s_down = GetKeyState('S') & 0x8000 || up_down == 254;
			auto d_down = GetKeyState('D') & 0x8000 || left_right == 254;
			auto a_down = GetKeyState('A') & 0x8000 || left_right == 0;

			if (w_down) {
				native::set_cam_coord(m_vars.m_freecam_handle, cam_coords.x + infront.x * 2.f, cam_coords.y + infront.y * 2.f, cam_coords.z + infront.z * 2.f);
			} else if (s_down) {
				native::set_cam_coord(m_vars.m_freecam_handle, cam_coords.x - infront.x * 2.f, cam_coords.y - infront.y * 2.f, cam_coords.z - infront.z * 2.f);
			}

			if (a_down) {
				math::vector3<float> gameplay_cam_rot_new = gameplay_cam_rot;

				gameplay_cam_rot_new.x = 0.f;
				gameplay_cam_rot_new.y = 0.f;
				gameplay_cam_rot_new.z += 90.f;

				math::vector3<float> new_coords = cam_coords + (menu::camera::get_direction(gameplay_cam_rot_new) * 2.f);
				native::set_cam_coord(m_vars.m_freecam_handle, new_coords.x, new_coords.y, new_coords.z);
			}

			if (d_down) {
				math::vector3<float> gameplay_cam_rot_new = gameplay_cam_rot;

				gameplay_cam_rot_new.x = 0.f;
				gameplay_cam_rot_new.y = 0.f;
				gameplay_cam_rot_new.z -= 90.f;

				math::vector3<float> new_coords = cam_coords + (menu::camera::get_direction(gameplay_cam_rot_new) * 2.f);
				native::set_cam_coord(m_vars.m_freecam_handle, new_coords.x, new_coords.y, new_coords.z);
			}

			cam_coords = native::get_cam_coord(m_vars.m_freecam_handle);

			static int timer = 0;
			menu::timers::run_timed(&timer, 1000, [&] {
				native::set_focus_area(cam_coords.x, cam_coords.y, cam_coords.z, 0, 0, 0);
			});
		}
	}
}

camera_menu* g_instance;
camera_menu* camera_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new camera_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
