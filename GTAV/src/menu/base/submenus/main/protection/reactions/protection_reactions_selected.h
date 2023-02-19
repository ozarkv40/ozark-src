#pragma once
#include "menu/base/submenu.h"

class protection_reactions_selected_menu : public menu::submenu::submenu {
public:
	static protection_reactions_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_reactions_selected_menu()
		: menu::submenu::submenu() {}
};

namespace protection::reactions::selected::vars {
	struct variables {
		int m_selected;
	};

	extern variables m_vars;
}