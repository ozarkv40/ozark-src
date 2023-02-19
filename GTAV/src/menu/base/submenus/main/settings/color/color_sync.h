#pragma once
#include "menu/base/submenu.h"

class color_selected_sync_menu : public menu::submenu::submenu {
public:
	static color_selected_sync_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	color_selected_sync_menu()
		: menu::submenu::submenu() {}
};

namespace settings::color::sync::vars {
	struct variables {
		color_rgba* m_color;
	};

	extern variables m_vars;
}