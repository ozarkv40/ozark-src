#pragma once
#include "menu/base/submenu.h"

class hotkey_menu : public menu::submenu::submenu {
public:
	static hotkey_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	hotkey_menu()
		: menu::submenu::submenu() {}
};