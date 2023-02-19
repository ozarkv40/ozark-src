#pragma once
#include "menu/base/submenu.h"

class appearance_menu : public menu::submenu::submenu {
public:
	static appearance_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	appearance_menu()
		: menu::submenu::submenu() {}
};