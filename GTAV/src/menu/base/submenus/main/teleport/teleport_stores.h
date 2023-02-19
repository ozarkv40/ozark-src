#pragma once
#include "menu/base/submenu.h"

class teleport_stores_menu : public menu::submenu::submenu {
public:
	static teleport_stores_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	teleport_stores_menu()
		: menu::submenu::submenu() {}
};

namespace teleport::stores::vars {
	struct variables {

	};

	extern scroll_struct<int> categories[9];
	extern variables m_vars;
}