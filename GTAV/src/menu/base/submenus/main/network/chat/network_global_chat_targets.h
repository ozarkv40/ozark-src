#pragma once
#include "menu/base/submenu.h"

class network_global_chat_targets_menu : public menu::submenu::submenu {
public:
	static network_global_chat_targets_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_global_chat_targets_menu()
		: menu::submenu::submenu() {}
};

namespace network::gchat::targets::vars {
	struct variables {
		bool m_enabled;
	};

	extern variables m_vars;
}