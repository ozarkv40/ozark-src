#pragma once
#include "menu/base/submenu.h"

class network_players_trolling_attachments_menu : public menu::submenu::submenu {
public:
	static network_players_trolling_attachments_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_trolling_attachments_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::trolling::attachments::vars {
	struct variables {
		int m_attachment_bone;
		int m_attachment_custom;
		int m_attachment_peds;
		int m_attachment_vehicles;
		int m_attachment_objects;
		int m_attachment_flags;

		bool m_attachment_randomize_bone;
		bool m_attachment_randomize_rotation;
	};

	extern variables m_vars;
}