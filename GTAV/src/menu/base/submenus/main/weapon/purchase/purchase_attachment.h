#pragma once
#include "menu/base/submenu.h"

class purchase_attachment_menu : public menu::submenu::submenu {
public:
	static purchase_attachment_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	purchase_attachment_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::purchase::attachment::vars {
	struct variables {
		std::shared_ptr<base_option> m_button;
	};

	extern variables m_vars;
}