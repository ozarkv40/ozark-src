#pragma once
#include "menu/base/submenu.h"

class vehicle_menu : public menu::submenu::submenu {
public:
	static vehicle_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::vars {
	struct variables {
		bool m_godmode;
		bool m_invisibility;
		bool m_seatbelt;
		bool m_burn_shell;

		int m_upgrades_var;
		int m_downgrades_var;
		int m_opacity = 5;
	};

	Vehicle clone_vehicle(Vehicle veh);
	void run_task(Vehicle veh, std::function<void(Vehicle)> callback);
	void max_upgrades(Vehicle veh, int type = 1);
	void low_upgrades(Vehicle vehicle, int type);

	extern scroll_struct<int> upgrades[2];
	extern variables m_vars;
}