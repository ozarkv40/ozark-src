#pragma once
#include "menu/base/submenu.h"

class network_session_finder_menu : public menu::submenu::submenu {
public:
	static network_session_finder_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_session_finder_menu()
		: menu::submenu::submenu() {}
};

namespace network::sfinder::vars {
	struct variables {
		bool m_populate;
		int m_minimum_slots = 1;

		std::vector<uint64_t> m_image_queue;
		std::vector<session_browser> m_sessions;
	};

	extern variables m_vars;
}