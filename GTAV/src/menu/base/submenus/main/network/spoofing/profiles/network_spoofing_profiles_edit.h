#pragma once
#include "menu/base/submenu.h"

class network_spoofing_profiles_edit_menu : public menu::submenu::submenu {
public:
	static network_spoofing_profiles_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_profiles_edit_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::profiles::edit::vars {
	struct variables {
		std::size_t m_selected;
		bool m_spoof_name = true;
		bool m_spoof_rockstar_id = true;
		bool m_spoof_ip = false;
		bool m_spoof_crew = true;
	};

	extern variables m_vars;
}