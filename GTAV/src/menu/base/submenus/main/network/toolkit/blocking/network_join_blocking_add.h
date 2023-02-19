#pragma once
#include "menu/base/submenu.h"

class network_join_blocking_add_menu : public menu::submenu::submenu {
public:
	static network_join_blocking_add_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_join_blocking_add_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::blocking::add::vars {
	struct variables {
		int m_type;
		uint64_t m_rockstar_id;
		char m_name[32];
		uint32_t m_ip;
		int m_response;
		bool m_enabled;
	};

	extern scroll_struct<int> types[3];
	extern variables m_vars;
}