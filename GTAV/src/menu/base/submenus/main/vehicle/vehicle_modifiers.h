#pragma once
#include "menu/base/submenu.h"

class vehicle_modifiers_menu : public menu::submenu::submenu {
public:
	static vehicle_modifiers_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_modifiers_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::modifiers::vars {
	struct variables {
		float m_suspension;
		float m_tire_size;
		float m_tire_width;

		bool m_has_suspension;
		bool m_has_custom_wheels;
	};

	extern variables m_vars;
}