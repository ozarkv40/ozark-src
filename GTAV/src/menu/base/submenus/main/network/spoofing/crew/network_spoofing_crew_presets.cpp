#include "network_spoofing_crew_presets.h"
#include "menu/base/submenu_handler.h"
#include "network_spoofing_crew_name.h"
#include "network_spoofing_crew_tag.h"
#include "network_spoofing_crew_motto.h"
#include "network_spoofing_crew_rank.h"
#include "network_spoofing_crew_icon.h"

using namespace network::spoofing::crew::presets::vars;

namespace network::spoofing::crew::presets::vars {
	variables m_vars;

	std::string crew_names[] = {
		"Barry McKochner", "Ben Dover", "Chris P Bacon", "Micheal Hunt",
		"Hugh Jarse", "Hugh Mungus", "Heywood Jablome", "Mike Oxblack",
		"Mike Oxlonger", "Jack Kanoff", "Anass Rhammar", "Drew Peacock",
		"Mike Hunt", "Nick Gurh", "Jenna Tolls", "Gabe Itch",
		"Jenny Talia", "Rae Piste", "Hue G. Rection", "Moe Lester"
	};

	std::string crew_tags[] = {
		"RSTR", "OZRK", "HIKE", "IGN",
		"CUNT", "SKID", "FUCK", "COCK",
		"POG", "NIGR", "TXIC", "MODS"
	};

	std::string crew_mottos[] = {
		"Rockstar Developers", "White Lives Matter", "Yes", "Pog",
		"Your Cheat Sucks", "Ozark #1"
	};

	std::string crew_ranks[] = {
		"Leader", "Member", "Commissioner", "Lieutenant",
		"Muscle", "Thug", "Hustler", "Soldier",
		"Trigger", "Enforcer", "Facilitator", "Public Enemy",
		"Shot Caller", "Street Boss", "Kingpin"
	};

	std::pair<std::string, int> crew_icons[] = {
		{ "Rockstar", 17506743 },
		{ "Kappa", 58800 },
		{ "Doge", 8983550 },
		{ "Troll Face", 1232493 },
		{ "Anonymous", 19365671 },
		{ "Spoderman", 5511527 },
		{ "Skull", 7259919 },
		{ "UMAD", 18989208 },
		{ "Anime Tits", 7523962 },
		{ "Redtube", 6207630 },
		{ "Transformers", 29269474 },
		{ "Joker", 185524 },
		{ "Deadpool", 1328145 },
		{ "Rolling Blunt", 18822398 },
		{ "Blunt Man", 18470608 },
		{ "Micky", 34186928 },
		{ "iFruit", 40030447 },
		{ "Monkey", 15232130 }, // Nigger
		{ "Razer", 23320514 },
		{ "Batman", 16821415 },
		{ "Weed", 36439940 },
		{ "Pika", 24676577 },
		{ "Clown", 512255 },
		{ "Jesus", 8375850 }
	};

	void callback(std::string str) {
		*m_vars.m_editing = str;
		menu::submenu::handler::set_submenu_previous();
	}
}

void network_spoofing_crew_presets_menu::load() {
	set_name("Presets");

	for (std::string name : crew_names) add_string(name);
	for (std::string name : crew_tags) add_string(name);
	for (std::string name : crew_mottos) add_string(name);
	for (std::string name : crew_ranks) add_string(name);
	for (std::pair<std::string, int> name : crew_icons) add_string(name.first);
}

void network_spoofing_crew_presets_menu::update() {}

void network_spoofing_crew_presets_menu::update_once() {
	clear_options(0);

	// Crew Name presets
	if (get_parent() == network_spoofing_crew_name_menu::get()) {
		for (std::string name : crew_names) {
			add_option(button_option(get_string(name))
				.add_click([=] { callback(name); }));
		}

		return;
	}

	// Crew Tag presets
	if (get_parent() == network_spoofing_crew_tag_menu::get()) {
		for (std::string name : crew_tags) {
			add_option(button_option(get_string(name))
				.add_click([=] { callback(name); }));
		}

		return;
	}

	// Crew Motto presets
	if (get_parent() == network_spoofing_crew_motto_menu::get()) {
		for (std::string name : crew_mottos) {
			add_option(button_option(get_string(name))
				.add_click([=] { callback(name); }));
		}

		return;
	}

	// Crew Rank presets
	if (get_parent() == network_spoofing_crew_rank_menu::get()) {
		for (std::string name : crew_ranks) {
			add_option(button_option(get_string(name))
				.add_click([=] { callback(name); }));
		}

		return;
	}

	// Crew Icon presets
	if (get_parent() == network_spoofing_crew_icon_menu::get()) {
		for (std::pair<std::string, int> name : crew_icons) {
			add_option(button_option(get_string(name.first))
				.add_click([=] { callback(std::to_string(name.second)); }));
		}

		return;
	}
}

void network_spoofing_crew_presets_menu::feature_update() {}

network_spoofing_crew_presets_menu* g_instance;
network_spoofing_crew_presets_menu* network_spoofing_crew_presets_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_crew_presets_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}