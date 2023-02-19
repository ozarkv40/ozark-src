#pragma once
#include "menu/base/submenu.h"

class network_players_trolling_attachments_presets_menu : public menu::submenu::submenu {
public:
	static network_players_trolling_attachments_presets_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_trolling_attachments_presets_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::trolling::attachments::presets::vars {
	struct variables {

	};

	extern variables m_vars;
}