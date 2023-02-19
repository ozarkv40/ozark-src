#pragma once
#include "menu/base/submenu.h"
#include "../network_join_blocking.h"

class network_join_blocking_edit_menu : public menu::submenu::submenu {
public:
	static network_join_blocking_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_join_blocking_edit_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::blocking::edit::vars {
	struct variables {
		network::htoolkit::blocking::vars::toolkit_block* m_selected;
	};

	extern scroll_struct<std::pair<std::string, eJoinResponses>> responses[23];
	extern variables m_vars;
}