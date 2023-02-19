#pragma once
#include "stdafx.h"
#include "rage/types/base_types.h"
#include "util/math.h"
#include "rage/invoker/natives.h"

namespace menu {
	class raycast {
	public:
		raycast(int handle);

		bool hit_entity() {
			return m_entity != 0;
		}

		bool hit_something() {
			return m_hit;
		}

		Entity get_entity() {
			return m_entity;
		}

		math::vector3<float> get_coords() {
			return m_coords;
		}
	private:
		Entity m_entity = 0;
		bool m_hit = false;
		bool m_hit_entity = false;
		math::vector3<float> m_coords;
		math::vector3<float> m_normals;
	};

	raycast raycast_infront(float length = 25.f, math::vector3<float> cam_coords = native::get_gameplay_cam_coord(), int flag = -1);
	raycast raycast_point(math::vector3<float> points[2], int flag = -1);
}