#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"
#include "fx_ui_color.h"

class fx_color_menu : public menu::submenu::submenu {
public:
	static fx_color_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_color_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::color::vars {
	struct custom_color {
		math::vector3_<float> m_default_color;
		math::vector3_<float>* m_color;
		color_rgba m_internal_color;
		bool m_rainbow_toggle;
		menu::rainbow m_rainbow;
	};

	struct variables {
		custom_color* m_color;
		world::fx::ui::color::vars::custom_color* m_color2;
		math::vector3_<float>* m_selected_color;
	};

	extern variables m_vars;
}