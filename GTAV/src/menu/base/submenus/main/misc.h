#pragma once
#include "menu/base/submenu.h"

class misc_menu : public menu::submenu::submenu {
public:
	static misc_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	misc_menu()
		: menu::submenu::submenu() {}
};

namespace misc::vars {
	struct variables {
		bool m_rockstar_developer_perks;
		bool m_decreased_graphics;

		int m_metric_system;
	};

	extern variables m_vars;
}