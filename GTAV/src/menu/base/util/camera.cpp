#include "camera.h"
#include "global/vars.h"
#include "util/caller.h"

namespace menu::camera {
	rage::network::player_angles* get_player_angles() {
		if (is_valid_ptr(global::vars::g_game_camera_angles)) {
			rage::network::game_camera_angles* camera_angles = global::vars::g_game_camera_angles;
			if (is_valid_ptr(camera_angles)) {
				rage::network::camera_manager_angles* camera_manager_angles = camera_angles->m_camera_manager_angles;
				if (is_valid_ptr(camera_manager_angles)) {
					rage::network::camera_angles* camera_angles = camera_manager_angles->m_camera_angles;
					if (is_valid_ptr(camera_angles)) {
						rage::network::player_angles* player_angles = caller::call<rage::network::player_angles*>(global::vars::g_get_third_person_camera, *(uint64_t*)(global::vars::g_third_person_camera), camera_angles->m_ped);
						if (is_valid_ptr(player_angles)) {
							return (rage::network::player_angles*)((uint64_t)player_angles + 0x390);
						}

						if (is_valid_ptr(camera_angles)) {
							if (is_valid_ptr(camera_angles->m_fps_player_angles)) {
								return camera_angles->m_fps_player_angles;
							}
						}
					}
				}
			}
		}

		return nullptr;
	}

	math::vector3<float> get_direction(math::vector3<float> rotation) {
		math::vector3<float> tmp;
		tmp.y = rotation.z * 0.0174532924f;
		tmp.x = rotation.x * 0.0174532924f;
		tmp.z = abs(cos(tmp.x));

		return math::vector3<float>((-sin(tmp.y)) * tmp.z, (cos(tmp.y)) * tmp.z, sin(tmp.x));
	}
}