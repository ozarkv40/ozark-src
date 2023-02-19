#pragma once
#include "menu/base/submenu.h"
#include "../protection_limits.h"

class protection_message_limit_menu : public menu::submenu::submenu {
public:
	static protection_message_limit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_message_limit_menu()
		: menu::submenu::submenu() {}
};

namespace protection::limits::messages::vars {
	struct variables {
		protection::limits::vars::message_limit* m_limit;
	};

	extern variables m_vars;
}