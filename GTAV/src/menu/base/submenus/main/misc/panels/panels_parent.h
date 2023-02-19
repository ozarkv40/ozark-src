#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/panels.h"

class panels_parent_menu : public menu::submenu::submenu {
public:
	static panels_parent_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	panels_parent_menu()
		: menu::submenu::submenu() {}
};

namespace misc::panel::parent::vars {
	struct variables {
		menu::panels::panel_parent* m_parent;
	};

	extern variables m_vars;
}