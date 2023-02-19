#include "network_spoofing_crew.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing.h"
#include "crew/network_spoofing_crew_icon.h"
#include "crew/network_spoofing_crew_rank.h"
#include "crew/network_spoofing_crew_motto.h"
#include "crew/network_spoofing_crew_tag.h"
#include "crew/network_spoofing_crew_name.h"

using namespace network::spoofing::crew::vars;

namespace network::spoofing::crew::vars {
	variables m_vars;
}

void network_spoofing_crew_menu::load() {
	set_name("Crew");
	set_parent<network_spoofing_menu>();

	add_option(submenu_option("Crew Name")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_crew_name_menu>());

	add_option(submenu_option("Crew Tag")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_crew_tag_menu>());

	add_option(submenu_option("Crew Motto")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_crew_motto_menu>());

	add_option(submenu_option("Crew Rank")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_crew_rank_menu>());

	add_option(submenu_option("Crew Icon")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_crew_icon_menu>());
}

void network_spoofing_crew_menu::update() {}

void network_spoofing_crew_menu::update_once() {}

void network_spoofing_crew_menu::feature_update() {}

network_spoofing_crew_menu* g_instance;
network_spoofing_crew_menu* network_spoofing_crew_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_crew_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}