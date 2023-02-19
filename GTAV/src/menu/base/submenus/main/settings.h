#pragma once
#include "menu/base/submenu.h"

class settings_menu : public menu::submenu::submenu {
public:
	static settings_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	settings_menu()
		: menu::submenu::submenu() {}
};