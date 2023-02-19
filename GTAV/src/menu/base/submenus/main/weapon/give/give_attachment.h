#pragma once
#include "menu/base/submenu.h"

class give_attachment_menu : public menu::submenu::submenu {
public:
	static give_attachment_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	give_attachment_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::give::attachment::vars {
	struct variables {
		int m_give_all;
		int m_remove_all;
	};

	extern variables m_vars;
}