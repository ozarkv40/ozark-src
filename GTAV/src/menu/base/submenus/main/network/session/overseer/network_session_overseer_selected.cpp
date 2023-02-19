#include "network_session_overseer_selected.h"
#include "menu/base/submenu_handler.h"
#include "../network_session_overseer.h"
#include "util/dirs.h"
#include "util/log.h"
#include <fstream>

using namespace network::session::overseer::selected::vars;

namespace network::session::overseer::selected::vars {
	variables m_vars;

	void save() {
		int flag = network::session::overseer::vars::m_vars.m_players[m_vars.m_selected].m_flags;

		if (m_vars.m_enabled) flag |= OVERSEER_ENABLED;
		else flag &= ~OVERSEER_ENABLED;

		if (m_vars.m_black_screen) flag |= OVERSEER_BLACK_SCREEN;
		else flag &= ~OVERSEER_BLACK_SCREEN;

		if (m_vars.m_blame) flag |= OVERSEER_BLAME;
		else flag &= ~OVERSEER_BLAME;

		if (m_vars.m_block_join) flag |= OVERSEER_BLOCK_JOIN;
		else flag &= ~OVERSEER_BLOCK_JOIN;

		if (m_vars.m_cage) flag |= OVERSEER_CAGE;
		else flag &= ~OVERSEER_CAGE;

		if (m_vars.m_crash) flag |= OVERSEER_CRASH;
		else flag &= ~OVERSEER_CRASH;

		if (m_vars.m_explode) flag |= OVERSEER_EXPLODE;
		else flag &= ~OVERSEER_EXPLODE;

		if (m_vars.m_give_wanted_level) flag |= OVERSEER_GIVE_WANTED_LEVEL;
		else flag &= ~OVERSEER_GIVE_WANTED_LEVEL;

		if (m_vars.m_glitch_physics) flag |= OVERSEER_GLITCH_PHYSICS;
		else flag &= ~OVERSEER_GLITCH_PHYSICS;

		if (m_vars.m_hostile_clone) flag |= OVERSEER_HOSTILE_CLONE;
		else flag &= ~OVERSEER_HOSTILE_CLONE;

		if (m_vars.m_kick) flag |= OVERSEER_KICK;
		else flag &= ~OVERSEER_KICK;

		if (m_vars.m_kick_from_vehicle) flag |= OVERSEER_KICK_FROM_VEHICLE;
		else flag &= ~OVERSEER_KICK_FROM_VEHICLE;

		if (m_vars.m_notify) flag |= OVERSEER_NOTIFY;
		else flag &= ~OVERSEER_NOTIFY;

		if (m_vars.m_ragdoll) flag |= OVERSEER_RAGDOLL;
		else flag &= ~OVERSEER_RAGDOLL;

		if (m_vars.m_remove_weapons) flag |= OVERSEER_REMOVE_WEAPONS;
		else flag &= ~OVERSEER_REMOVE_WEAPONS;

		if (m_vars.m_send_to_island) flag |= OVERSEER_SEND_TO_ISLAND;
		else flag &= ~OVERSEER_SEND_TO_ISLAND;

		if (m_vars.m_set_on_fire) flag |= OVERSEER_SET_ON_FIRE;
		else flag &= ~OVERSEER_SET_ON_FIRE;

		network::session::overseer::vars::m_vars.m_players[m_vars.m_selected].m_flags = flag;

		try {
			nlohmann::json json;

			std::ifstream input(util::dirs::get_path(overseer));
			if (input.good()) {
				json = nlohmann::json::parse(input);
				input.close();
			}

			json[std::to_string(network::session::overseer::vars::m_vars.m_players[m_vars.m_selected].m_rockstar_id)]["flags"] = flag;

			std::ofstream output(util::dirs::get_path(overseer));
			if (output.good()) {
				output << json.dump(4);
				output.close();
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void network_session_overseer_selected_menu::load() {
	set_name("Overseer");
	set_parent<network_session_overseer_menu>();

	add_option(toggle_option("Enabled")
		.add_translate()
		.add_toggle(m_vars.m_enabled)
		.add_click(save));

	add_option(toggle_option("Notify")
		.add_translate()
		.add_toggle(m_vars.m_notify)
		.add_click(save));

	add_option(toggle_option("Black Screen")
		.add_translate()
		.add_toggle(m_vars.m_black_screen)
		.add_click(save));

	add_option(toggle_option("Blame")
		.add_translate()
		.add_toggle(m_vars.m_blame)
		.add_click(save));

	add_option(toggle_option("Block Join (Host)")
		.add_translate()
		.add_toggle(m_vars.m_block_join)
		.add_click(save));

	add_option(toggle_option("Cage")
		.add_translate()
		.add_toggle(m_vars.m_cage)
		.add_click(save));

	add_option(toggle_option("Crash")
		.add_translate()
		.add_toggle(m_vars.m_crash)
		.add_click(save));

	add_option(toggle_option("Explode")
		.add_translate()
		.add_toggle(m_vars.m_explode)
		.add_click(save));

	add_option(toggle_option("Give Wanted Level")
		.add_translate()
		.add_toggle(m_vars.m_give_wanted_level)
		.add_click(save));

	add_option(toggle_option("Glitch Physics")
		.add_translate()
		.add_toggle(m_vars.m_glitch_physics)
		.add_click(save));

	add_option(toggle_option("Hostile Clone")
		.add_translate()
		.add_toggle(m_vars.m_hostile_clone)
		.add_click(save));

	add_option(toggle_option("Kick")
		.add_translate()
		.add_toggle(m_vars.m_kick)
		.add_click(save));

	add_option(toggle_option("Kick from Vehicle")
		.add_translate()
		.add_toggle(m_vars.m_kick_from_vehicle)
		.add_click(save));

	add_option(toggle_option("Ragdoll")
		.add_translate()
		.add_toggle(m_vars.m_ragdoll)
		.add_click(save));

	add_option(toggle_option("Remove Weapons")
		.add_translate()
		.add_toggle(m_vars.m_remove_weapons)
		.add_click(save));

	add_option(toggle_option("Send to Island")
		.add_translate()
		.add_toggle(m_vars.m_send_to_island)
		.add_click(save));

	add_option(toggle_option("Set on Fire")
		.add_translate()
		.add_toggle(m_vars.m_set_on_fire)
		.add_click(save));
}

void network_session_overseer_selected_menu::update() {}

void network_session_overseer_selected_menu::update_once() {
	int flag = network::session::overseer::vars::m_vars.m_players[m_vars.m_selected].m_flags;

	m_vars.m_black_screen = flag & OVERSEER_BLACK_SCREEN;
	m_vars.m_blame = flag & OVERSEER_BLAME;
	m_vars.m_block_join = flag & OVERSEER_BLOCK_JOIN;
	m_vars.m_cage = flag & OVERSEER_CAGE;
	m_vars.m_crash = flag & OVERSEER_CRASH;
	m_vars.m_enabled = flag & OVERSEER_ENABLED;
	m_vars.m_explode = flag & OVERSEER_EXPLODE;
	m_vars.m_give_wanted_level = flag & OVERSEER_GIVE_WANTED_LEVEL;
	m_vars.m_glitch_physics = flag & OVERSEER_GLITCH_PHYSICS;
	m_vars.m_hostile_clone = flag & OVERSEER_HOSTILE_CLONE;
	m_vars.m_kick = flag & OVERSEER_KICK;
	m_vars.m_kick_from_vehicle = flag & OVERSEER_KICK_FROM_VEHICLE;
	m_vars.m_notify = flag & OVERSEER_NOTIFY;
	m_vars.m_ragdoll = flag & OVERSEER_RAGDOLL;
	m_vars.m_remove_weapons = flag & OVERSEER_REMOVE_WEAPONS;
	m_vars.m_send_to_island = flag & OVERSEER_SEND_TO_ISLAND;
	m_vars.m_set_on_fire = flag & OVERSEER_SET_ON_FIRE;
}

void network_session_overseer_selected_menu::feature_update() {}

network_session_overseer_selected_menu* g_instance;
network_session_overseer_selected_menu* network_session_overseer_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_session_overseer_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}