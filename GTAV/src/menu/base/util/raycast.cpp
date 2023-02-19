#include "raycast.h"
#include "menu/base/util/player_manager.h"
#include "camera.h"

namespace menu {
	raycast::raycast(int handle) {
		Entity hit_entity;
		native::get_shape_test_result(handle, &m_hit, &m_coords, &m_normals, &hit_entity);

		if (m_hit) {
			if (native::does_entity_exist(hit_entity)) {
				int type = native::get_entity_type(hit_entity);
				if (hit_entity != menu::player::get_local_player().m_ped
					&& (type == 1 || type == 2 || type == 3)) {
					m_entity = hit_entity;
				} else m_entity = 0;
			}

			m_hit_entity = m_entity != 0;
		}
	}

	raycast raycast_infront(float length, math::vector3<float> cam_coords, int flag) {
		math::vector3<float> target = cam_coords + (camera::get_direction() * length);
		return raycast(native::start_shape_test_ray(cam_coords.x, cam_coords.y, cam_coords.z, target.x, target.y, target.z, flag, menu::player::get_local_player().m_ped, 0));
	}

	raycast raycast_point(math::vector3<float> points[2], int flag) {
		return raycast(native::start_shape_test_ray(points[0].x, points[0].y, points[0].z, points[1].x, points[1].y, points[1].z, flag, menu::player::get_local_player().m_ped, 0));
	}
}