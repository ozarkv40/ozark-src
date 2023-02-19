#pragma once
#include "menu/base/submenu.h"

class weather_menu : public menu::submenu::submenu {
public:
	static weather_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	weather_menu()
		: menu::submenu::submenu() {}
};

namespace world::weather::vars {
	struct variables {
		bool m_lightning;
		bool m_ground_snow;

		int m_rain;
		int m_wind;
		int m_clouds;

		float m_wind_speed = 100000.f;
	};

	extern scroll_struct<int> target_type[3];
	extern variables m_vars;
}