#pragma once
#include "menu/base/submenu.h"
#include "fx_ui_color.h"

class fx_vehicle_menu : public menu::submenu::submenu {
public:
	static fx_vehicle_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_vehicle_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::vehicle::vars {
	struct variables {
		world::fx::ui::color::vars::custom_color m_interior_light_color;
		world::fx::ui::color::vars::custom_color m_plate_light_color;
		world::fx::ui::color::vars::custom_color m_dash_light_color;
		world::fx::ui::color::vars::custom_color m_door_light_color;
	};

	extern variables m_vars;
}