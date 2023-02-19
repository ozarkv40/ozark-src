#include "hooks.h"
#include "menu/base/submenus/main/world/world_weather.h"

void menu::hooks::apply_weather_meta(uint64_t meta) {
	apply_weather_meta_t(meta);

	if (world::weather::vars::m_vars.m_wind_speed == 100000.f) {
		world::weather::vars::m_vars.m_wind_speed = *(float*)(meta + 0xEA8);
	}

	*(float*)(meta + 0xEB4) = world::weather::vars::m_vars.m_wind_speed * 12.f;
	*(float*)(meta + 0xEA8) = world::weather::vars::m_vars.m_wind_speed;
}