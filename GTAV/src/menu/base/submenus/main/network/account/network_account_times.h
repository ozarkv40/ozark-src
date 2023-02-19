#pragma once
#include "menu/base/submenu.h"

class network_account_times_menu : public menu::submenu::submenu {
public:
	static network_account_times_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_times_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::times::vars {
	struct variables {
		int m_type;
		int m_days;
		int m_hours;
		int m_minutes;
		int m_seconds;
		int m_milliseconds;
	};

	extern variables m_vars;
}