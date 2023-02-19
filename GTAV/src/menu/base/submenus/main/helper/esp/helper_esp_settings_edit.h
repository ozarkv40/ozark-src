#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"

class helper_esp_settings_edit_menu : public menu::submenu::submenu {
public:
	static helper_esp_settings_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	helper_esp_settings_edit_menu()
		: menu::submenu::submenu() {}
};

namespace helper::esp::settings::edit::vars {
	struct variables {
		color_rgba* m_color;
		bool* m_rainbow_toggle;
		menu::rainbow* m_rainbow;
	};

	extern variables m_vars;
}