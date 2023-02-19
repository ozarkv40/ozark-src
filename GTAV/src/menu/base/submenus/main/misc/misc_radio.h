#pragma once
#include "menu/base/submenu.h"

class radio_menu : public menu::submenu::submenu {
public:
	static radio_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	radio_menu()
		: menu::submenu::submenu() {}
};

namespace misc::radio::vars {
	struct variables {
		bool m_mobile_radio;

		radio_context m_context = { "commonmenu", "shop_garage_icon" };
	};

	extern variables m_vars;
}