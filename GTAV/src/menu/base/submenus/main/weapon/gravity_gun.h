#pragma once
#include "menu/base/submenu.h"

class gravity_gun_menu : public menu::submenu::submenu {
public:
	static gravity_gun_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	gravity_gun_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::gravity::vars {
	struct variables {
		bool m_toggle;
		bool m_attraction;
		bool m_peds;
		bool m_vehicles;
		bool m_objects;

		float m_attraction_distance = 10.f;
		float m_force = 4.f;
		float m_distance = 10.f;

		Entity m_entity;
	};

	extern variables m_vars;
}