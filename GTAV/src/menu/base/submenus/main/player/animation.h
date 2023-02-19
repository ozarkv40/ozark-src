#pragma once
#include "menu/base/submenu.h"

class animation_menu : public menu::submenu::submenu {
public:
	static animation_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	animation_menu()
		: menu::submenu::submenu() {}
};