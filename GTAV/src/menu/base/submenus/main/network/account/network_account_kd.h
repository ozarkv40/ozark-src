#pragma once
#include "menu/base/submenu.h"

class network_account_kd_menu : public menu::submenu::submenu {
public:
	static network_account_kd_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_kd_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::kd::vars {
	struct variables {
		int m_kills;
		int m_deaths;
		float m_calculated;
		std::shared_ptr<base_option> m_button;
	};

	extern variables m_vars;
}