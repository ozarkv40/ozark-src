#pragma once
#include "menu/base/submenu.h"

class scenario_menu : public menu::submenu::submenu {
public:
	static scenario_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	scenario_menu()
		: menu::submenu::submenu() {}
};

namespace player::scenario::vars {
	struct variables {
		int m_ambient;
		int m_activities;
		int m_animals;
		int m_fitness;
		int m_industrial;
	};

	extern variables m_vars;
}