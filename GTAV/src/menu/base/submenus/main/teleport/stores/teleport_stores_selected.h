#pragma once
#include "menu/base/submenu.h"

class teleport_stores_selected_menu : public menu::submenu::submenu {
public:
	static teleport_stores_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	teleport_stores_selected_menu()
		: menu::submenu::submenu() {}
};

namespace teleport::stores::selected::vars {
	struct variables {
		int m_selected;
	};

	extern variables m_vars;
}