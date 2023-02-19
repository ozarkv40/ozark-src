#pragma once
#include "menu/base/submenu.h"

class vehicle_speedometer_menu : public menu::submenu::submenu {
public:
	static vehicle_speedometer_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_speedometer_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::speedometer::vars {
	struct variables {
		bool m_basic_speedometer;
		bool m_number_plate_speedometer;

		std::string m_previous_number_plate_text;
	};

	extern variables m_vars;
}