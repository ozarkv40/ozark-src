#pragma once
#include "menu/base/submenu.h"
#include "../network_join_blocking.h"

class network_join_blocking_manual_load_menu : public menu::submenu::submenu {
public:
	static network_join_blocking_manual_load_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_join_blocking_manual_load_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::blocking::load::vars {
	struct variables {

	};

	void save_blocks(std::string file, std::vector<network::htoolkit::blocking::vars::user_block> users);
	extern variables m_vars;
}