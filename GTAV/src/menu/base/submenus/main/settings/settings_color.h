#pragma once
#include "menu/base/submenu.h"

class color_menu : public menu::submenu::submenu {
public:
	static color_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	color_menu()
		: menu::submenu::submenu() {}
};

namespace settings::color::vars {
	extern scroll_struct<color_rgba*> colors[30];
}