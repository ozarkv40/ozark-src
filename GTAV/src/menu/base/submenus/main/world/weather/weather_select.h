#pragma once
#include "menu/base/submenu.h"

class weather_select_menu : public menu::submenu::submenu {
public:
	static weather_select_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	weather_select_menu()
		: menu::submenu::submenu() {}
};

namespace world::weather::select::vars {
	struct variables {
		int m_target;
		bool m_epilepsy;
	};

	void set_weather(const char* weather);
	extern scroll_struct<std::pair<const char*, const char*>> weathers[15];
	extern variables m_vars;
}