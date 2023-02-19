#pragma once
#include "menu/base/submenu.h"

class protection_presence_events_menu : public menu::submenu::submenu {
public:
	static protection_presence_events_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_presence_events_menu()
		: menu::submenu::submenu() {}
};

namespace protection::events::presence::vars {
	struct variables {
		protection_context m_text_message = { 3, localization("") };
		protection_context m_crew_message = { 3, localization("") };
		protection_context m_game_invite = { 3, localization("") };
		protection_context m_game_server_awards = { 3, localization("") };
		protection_context m_admin_invite = { 3, localization("") };
		protection_context m_stat_update = { 3, localization("") };
	};

	extern variables m_vars;
}