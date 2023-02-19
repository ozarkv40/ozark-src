#pragma once
#include "menu/base/submenu.h"
#include "../network_join_blocking.h"

class network_join_blocking_manual_edit_menu : public menu::submenu::submenu {
public:
	static network_join_blocking_manual_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_join_blocking_manual_edit_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::blocking::manual::edit::vars {
	struct variables {
		int m_response;
		int m_type;
		network::htoolkit::blocking::vars::user_block* m_selected;
	};

	extern variables m_vars;
}