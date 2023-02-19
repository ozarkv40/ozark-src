#pragma once
#include "menu/base/submenu.h"

class teleport_settings_menu : public menu::submenu::submenu {
public:
	static teleport_settings_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	teleport_settings_menu()
		: menu::submenu::submenu() {}
};

namespace teleport::settings::vars {
	struct variables {

	};

	extern variables m_vars;
}