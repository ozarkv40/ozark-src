#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"

class helper_rainbow_config_menu : public menu::submenu::submenu {
public:
	static helper_rainbow_config_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	helper_rainbow_config_menu()
		: menu::submenu::submenu() {}
};

namespace helper::rainbow::config::vars {
	struct variables {
		menu::rainbow* m_rainbow;
	};

	extern variables m_vars;
}