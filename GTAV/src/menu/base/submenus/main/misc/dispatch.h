#pragma once
#include "menu/base/submenu.h"

class dispatch_menu : public menu::submenu::submenu {
public:
	static dispatch_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	dispatch_menu()
		: menu::submenu::submenu() {}
};

namespace misc::dispatch::vars {
	struct variables {
		bool m_disable_police_automobile;
		bool m_disable_police_helicopter;
		bool m_disable_police_riders;
		bool m_disable_police_vehicle_request;
		bool m_disable_police_roadblock;
		bool m_disable_police_boat;
		bool m_disable_swat_automobile;
		bool m_disable_swat_helicopter;
		bool m_disable_fire_department;
		bool m_disable_ambulance_department;
		bool m_disable_gangs;
		bool m_disable_army_vehicle;
		bool m_disable_bikers;
	};

	extern variables m_vars;
}