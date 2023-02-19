#pragma once
#include "menu/base/submenu.h"

class particle_menu : public menu::submenu::submenu {
public:
	static particle_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	particle_menu()
		: menu::submenu::submenu() {}
};