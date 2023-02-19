#pragma once
#include "menu/base/submenu.h"

class teleport_ipl_menu : public menu::submenu::submenu {
public:
	static teleport_ipl_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	teleport_ipl_menu()
		: menu::submenu::submenu() {}
};

namespace teleport::ipl::vars {
	struct variables {

	};

	extern variables m_vars;
}
