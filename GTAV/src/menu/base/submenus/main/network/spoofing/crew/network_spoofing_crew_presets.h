#pragma once
#include "menu/base/submenu.h"

class network_spoofing_crew_presets_menu : public menu::submenu::submenu {
public:
	static network_spoofing_crew_presets_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_crew_presets_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::crew::presets::vars {
	struct variables {
		std::string* m_editing;
	};

	extern variables m_vars;
}