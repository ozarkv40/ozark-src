#pragma once
#include "menu/base/submenu.h"

class protection_entity_blocking_menu : public menu::submenu::submenu {
public:
	static protection_entity_blocking_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_entity_blocking_menu()
		: menu::submenu::submenu() {}
};

namespace protection::entity::blocking::vars {
	struct variables {
		bool m_toggled[14];
	};

	extern variables m_vars;
}