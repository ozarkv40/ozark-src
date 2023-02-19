#pragma once
#include "stdafx.h"
#include "menu/base/options/scroll.h"
#include "util/math.h"
#include "rage/types/base_types.h"

namespace global::lists {
	struct particle {
		const char* m_dict;
		const char* m_texture;
		bool m_looped;

		particle(const char* a = "", const char* b = "", bool c = false)
			: m_dict(a), m_texture(b), m_looped(c) {}
	};

	extern scroll_struct<uint32_t> g_timers[10];
	extern scroll_struct<float> g_distances[8];
	extern scroll_struct<uint32_t> g_ped_model_popular[9];
	extern scroll_struct<uint32_t> g_ped_model_story[25];
	extern scroll_struct<uint32_t> g_ped_model_animal[20];
	extern scroll_struct<uint32_t> g_ped_model_emergency[16];
	extern scroll_struct<uint32_t> g_ped_model_role[14];
	extern scroll_struct<uint32_t> g_ped_model_ambient[6];
	extern scroll_struct<uint32_t> g_ped_model_misc[5];
	extern scroll_struct<particle> g_particles[29];
	extern scroll_struct<int> g_ped_bones[13];
	extern scroll_struct<const char*> g_vehicle_bones[10];
	extern scroll_struct<uint32_t> g_weapons[98];
	extern scroll_struct<ExplosionTypes> g_explosions[36];
	extern scroll_struct<float> g_gravity[9];
	extern scroll_struct<int> g_opacity[6];
	extern scroll_struct<uint32_t> g_vehicle_weapons[9];
	extern scroll_struct<std::pair<math::vector3_<float>, math::vector3_<float>>> g_acrobatics[10];
	extern scroll_struct<math::vector3<float>> g_popular_locations[35];
	extern scroll_struct<uint32_t> g_object_model_small[39];
	extern scroll_struct<uint32_t> g_object_model_medium[27];
	extern scroll_struct<uint32_t> g_object_model_large[17];
	extern scroll_struct<uint32_t> g_object_model_flags[17];
	extern scroll_struct<float> g_precisions[10];
	extern scroll_struct<std::pair<const char*, const char*>> g_sounds[109];
	extern scroll_struct<int> g_markers[43];
}