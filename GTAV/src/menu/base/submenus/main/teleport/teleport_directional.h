#pragma once
#include "menu/base/submenu.h"

class teleport_directional_menu : public menu::submenu::submenu {
public:
	static teleport_directional_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	teleport_directional_menu()
		: menu::submenu::submenu() {}
};

namespace teleport::directional::vars {
	struct variables {
		float m_directions[6] = { 5.f, 5.f, 5.f, 5.f, 5.f, 5.f };
	};

	extern variables m_vars;
}