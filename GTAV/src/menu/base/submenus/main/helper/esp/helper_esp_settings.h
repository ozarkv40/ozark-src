#pragma once
#include "menu/base/submenu.h"

class helper_esp_settings_menu : public menu::submenu::submenu {
public:
	static helper_esp_settings_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	helper_esp_settings_menu()
		: menu::submenu::submenu() {}
};

namespace helper::esp::settings::vars {
	struct variables {
	};

	extern variables m_vars;
}