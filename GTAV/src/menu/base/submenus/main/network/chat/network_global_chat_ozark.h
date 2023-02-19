#pragma once
#include "menu/base/submenu.h"

class network_global_chat_ozark_menu : public menu::submenu::submenu {
public:
	static network_global_chat_ozark_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_global_chat_ozark_menu()
		: menu::submenu::submenu() {}
};

namespace network::gchat::ozark::vars {
	struct variables {
		bool m_enabled;
		int m_color;
		std::string m_prefix = "!oz";
	};

	extern scroll_struct<int> colors[10];
	extern variables m_vars;
}