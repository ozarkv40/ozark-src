#pragma once
#include "stdafx.h"
#include "rage/types/generic_types.h"

namespace menu::screen::ped {
	void draw_on_screen_ped(rage::types::ped* ped, math::vector2<float> pos, math::vector2<float> scale, math::vector3_<float> position_offset = { 0.00f, -2.00f, 0.40f });
}