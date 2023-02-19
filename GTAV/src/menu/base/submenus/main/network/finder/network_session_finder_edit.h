#pragma once
#include "menu/base/submenu.h"

class network_session_finder_edit_menu : public menu::submenu::submenu {
public:
	static network_session_finder_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_session_finder_edit_menu()
		: menu::submenu::submenu() {}
};

namespace network::sfinder::edit::vars {
	struct variables {
		std::size_t m_selected;
	};

	extern variables m_vars;
}