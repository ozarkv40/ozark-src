#pragma once
#include "menu/base/submenu.h"

class animations_menu : public menu::submenu::submenu {
public:
	static animations_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	animations_menu()
		: menu::submenu::submenu() {}
};

namespace player::animations::vars {
	struct variables {
		bool m_controllable;
		bool m_contort;

		int m_sexual;
		int m_animals;
		int m_actions;
		int m_dance;
		int m_misc;

		float m_speed = 1.f;
	};

	extern variables m_vars;
}