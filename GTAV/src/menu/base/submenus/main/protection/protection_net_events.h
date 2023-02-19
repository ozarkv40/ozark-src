#pragma once
#include "menu/base/submenu.h"

class protection_net_events_menu : public menu::submenu::submenu {
public:
	static protection_net_events_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_net_events_menu()
		: menu::submenu::submenu() {}
};

namespace protection::events::net::vars {
	struct variables {
		protection_context m_give_weapon = { 3, localization("Blocks players giving you weapons", true) };
		protection_context m_remove_weapon = { 3, localization("Blocks players removing a weapon", true) };
		protection_context m_remove_all_weapons = { 3, localization("Blocks players removing all weapons", true) };
		protection_context m_freeze = { 3, localization("Blocks players freezing you in place", true) };
		protection_context m_explosion = { 3, localization("Blocks players exploding you", true) };
		protection_context m_fire = { 3, localization("Blocks players starting fires on you", true) };
		protection_context m_particle_fx = { 3, localization("Blocks players using PTFX on you", true) };
		protection_context m_script_events = { 3, localization("Blocks players using malicious script events on you", true) };
		protection_context m_increment_stat = { 3, localization("Blocks players modifying your stats", true) };
		protection_context m_weather = { 3, localization("Blocks players changing the weather", true) };
		protection_context m_clock = { 3, localization("Blocks players changing the time", true) };
		protection_context m_sound = { 3, localization("Blocks players playing sounds on you", true) };
		protection_context m_vehicle_control = { 3, localization("Blocks players modifying your vehicle", true) };
		protection_context m_blame_explosion = { 1, localization("Notifies when a player is blaming another player", true) };

	};

	extern variables m_vars;
}