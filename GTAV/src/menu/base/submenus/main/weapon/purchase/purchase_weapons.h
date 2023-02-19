#pragma once
#include "menu/base/submenu.h"

class purchase_weapons_menu : public menu::submenu::submenu {
public:
	static purchase_weapons_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	purchase_weapons_menu()
		: menu::submenu::submenu() {}
};