#pragma once
#include "menu/base/submenu.h"

class vehicle_particles_menu : public menu::submenu::submenu {
public:
	static vehicle_particles_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_particles_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::particles::vars {
	struct variables {
		bool m_toggle;
		bool m_bones[10];
		int m_particle;
		float m_scale = 0.2f;
	};

	extern variables m_vars;
}