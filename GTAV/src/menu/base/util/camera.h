#pragma once
#include "rage/invoker/natives.h"
#include "util/math.h"

namespace menu::camera {
	rage::network::player_angles* get_player_angles();
	math::vector3<float> get_direction(math::vector3<float> rotation = native::get_gameplay_cam_rot(0));
}