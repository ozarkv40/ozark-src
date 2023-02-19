#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"

class fx_ui_color_menu : public menu::submenu::submenu {
public:
	static fx_ui_color_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_ui_color_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::ui::color::vars {
	struct custom_color {
		rage::types::ui_element_color_struct m_default_color;
		rage::types::ui_element_color_struct* m_color;
		color_rgba m_internal_color;
		bool m_rainbow_toggle;
		menu::rainbow m_rainbow;
	};

	struct variables {
		custom_color* m_color;
	};

	extern variables m_vars;
}