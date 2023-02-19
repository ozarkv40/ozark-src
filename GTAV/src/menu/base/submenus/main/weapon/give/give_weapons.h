#pragma once
#include "menu/base/submenu.h"

class give_weapons_menu : public menu::submenu::submenu {
public:
	static give_weapons_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	give_weapons_menu()
		: menu::submenu::submenu() {}
};