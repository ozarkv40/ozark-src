#pragma once
#include "menu/base/submenu.h"

class vehicle_movement_menu : public menu::submenu::submenu {
public:
	static vehicle_movement_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_movement_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::movement::vars {
	struct variables {
		bool m_flying_vehicle;
		bool m_flying_vehicle_pause;
		bool m_flying_vehicle_mouse = true;
		bool m_disable_max_speed;
		bool m_limit_max_speed;

		float m_flying_vehicle_speed = 10.f;
		float m_limit_max_speed_val;
	};

	void run_acrobatic(Vehicle veh, std::pair<math::vector3_<float>, math::vector3_<float>> data);
	extern variables m_vars;
}