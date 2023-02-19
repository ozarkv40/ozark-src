#pragma once
#include "menu/base/submenu.h"

class give_tint_selection_menu : public menu::submenu::submenu {
public:
	static give_tint_selection_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	give_tint_selection_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::give::tint::selected::vars {
	struct variables {
		radio_context m_context = { "commonmenu", "shop_tick_icon" };
		uint32_t m_selected_weapon;
	};

	extern variables m_vars;
}