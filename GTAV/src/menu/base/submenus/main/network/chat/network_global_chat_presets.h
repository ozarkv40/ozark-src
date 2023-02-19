#pragma once
#include "menu/base/submenu.h"

class network_global_chat_presets_menu : public menu::submenu::submenu {
public:
	static network_global_chat_presets_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_global_chat_presets_menu()
		: menu::submenu::submenu() {}
};

namespace network::gchat::presets::vars {
	struct variables {
		int m_count = 1;
		bool m_show_locally;
		bool m_send_tanslated;
	};

	extern variables m_vars;
}