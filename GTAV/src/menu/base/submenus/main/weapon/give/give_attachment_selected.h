#pragma once
#include "menu/base/submenu.h"

class give_attachment_selected_menu : public menu::submenu::submenu {
public:
	static give_attachment_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	give_attachment_selected_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::give::attachment::selected::vars {
	struct variables {
		uint32_t m_selected_weapon;
	};

	extern variables m_vars;
}