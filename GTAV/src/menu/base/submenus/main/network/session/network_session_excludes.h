#pragma once
#include "menu/base/submenu.h"

class network_session_excludes_menu : public menu::submenu::submenu {
public:
	static network_session_excludes_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_session_excludes_menu()
		: menu::submenu::submenu() {}
};

namespace network::session::excludes::vars {
	struct variables {
		bool m_self = true;
		bool m_friends;
		bool m_modders;
		bool m_host;
		bool m_script_host;
		bool m_rockstar_developers;
	};

	extern variables m_vars;
}