#include "network_account_level.h"
#include "menu/base/submenu_handler.h"
#include "../network_account.h"
#include "menu/base/util/stats.h"
#include "menu/base/util/global.h"
#include "rage/types/global_types.h"

using namespace network::account::level::vars;

namespace network::account::level::vars {
	variables m_vars;

	scroll_struct<int> types[] = {
		{ localization("RP", true), 0 },
		{ localization("Crew", true), 1 }
	};

	int levels[] = { 1, 25, 50, 69, 75, 100, 120, 250, 420, 500, 666, 1000, 1234, 1337, 2000, 4000, 6969, 8000 };

	int level_to_rp(int level) {
		return menu::script_global(rage::global::_155_convert_rp_to_level).at(level + 1).as<int>();
	}

	int get_rp_level() {
		return stats<int>::get("CHAR_SET_RP_GIFT_ADMIN");
	}

	int get_crew_level() {
		return stats<int>::get("MPPLY_CREW_LOCAL_XP_0");
	}

	void set_rp_level(int level) {
		if (level > 8000) level = 8000;

		stats<int>::set("CHAR_SET_RP_GIFT_ADMIN", level_to_rp(level));
		menu::notify::stacked(network_account_level_menu::get()->get_name().get(), network_account_level_menu::get()->get_string("Rank set! Change lobbies for it to take effect :)"));
	}

	void set_crew_level(int level) {
		if (level > 8000) level = 8000;
		stats<int>::set("MPPLY_CREW_LOCAL_XP_0", level_to_rp(level));
		stats<int>::set("MPPLY_CREW_LOCAL_XP_1", level_to_rp(level));
		stats<int>::set("MPPLY_CREW_LOCAL_XP_2", level_to_rp(level));
		stats<int>::set("MPPLY_CREW_LOCAL_XP_3", level_to_rp(level));
		stats<int>::set("MPPLY_CREW_LOCAL_XP_4", level_to_rp(level));
	}

	void set_level(int level) {
		if (m_vars.m_type == 0) set_rp_level(level);
		else set_crew_level(level);
	}

	int get_level() {
		if (m_vars.m_type == 0) return get_rp_level();
		else return get_crew_level();
	}
}

void network_account_level_menu::load() {
	set_name("Level");
	set_parent<network_account_menu>();

	add_option(scroll_option<int>(SCROLL, "Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(types), types));

	add_option(button_option("Input Level")
		.add_translate()
		.add_keyboard("Enter level", 4, [](button_option* option, const char* level) { set_level(std::stoi(level)); }));

	add_option(break_option("Levels")
		.add_translate());

	for (int level : levels) {
		add_option(button_option("Level " + std::to_string(level))
			.add_translate()
			.add_click([=] { set_level(level); }));
	}

	add_string("Rank set! Change lobbies for it to take effect :)");
}

void network_account_level_menu::update() {}

void network_account_level_menu::update_once() {}

void network_account_level_menu::feature_update() {}

network_account_level_menu* g_instance;
network_account_level_menu* network_account_level_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_level_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}