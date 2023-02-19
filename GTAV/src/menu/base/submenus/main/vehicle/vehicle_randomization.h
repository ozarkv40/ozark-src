#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"

class vehicle_randomization_menu : public menu::submenu::submenu {
public:
	static vehicle_randomization_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_randomization_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::randomization::vars {
	struct variables {
		bool m_rainbow_primary;
		bool m_rainbow_secondary;
		bool m_rainbow_tire_smoke;
		bool m_rainbow_neons;
		bool m_random_upgrades;
		bool m_random_acrobatics;

		menu::rainbow m_rainbow_primary_run = { 0, 255, 255 };
		color_rgba m_rainbow_primary_color;

		menu::rainbow m_rainbow_secondary_run = { 0, 255, 255 };
		color_rgba m_rainbow_secondary_color;

		menu::rainbow m_rainbow_tire_smoke_run = { 0, 255, 255 };
		color_rgba m_rainbow_tire_smoke_color;

		menu::rainbow m_rainbow_neons_run = { 0, 255, 255 };
		color_rgba m_rainbow_neons_color;
	};

	extern variables m_vars;
}