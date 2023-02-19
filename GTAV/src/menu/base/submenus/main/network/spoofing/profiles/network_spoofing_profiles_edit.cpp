#include "network_spoofing_profiles_edit.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing_profiles.h"
#include "../network_spoofing_ip.h"
#include "../network_spoofing_name.h"
#include "../network_spoofing_rid.h"
#include "../crew/network_spoofing_crew_icon.h"
#include "../crew/network_spoofing_crew_motto.h"
#include "../crew/network_spoofing_crew_name.h"
#include "../crew/network_spoofing_crew_rank.h"
#include "../crew/network_spoofing_crew_tag.h"

using namespace network::spoofing::profiles::edit::vars;

namespace network::spoofing::profiles::edit::vars {
	variables m_vars;

	void load_profile() {
		network::spoofing::profiles::vars::spoof_profile& profile = network::spoofing::profiles::vars::m_vars.m_profiles[m_vars.m_selected];
		network::spoofing::profiles::vars::spoof_profile& active = network::spoofing::profiles::vars::m_vars.m_active.m_profile;

		active.m_rockstar_id = profile.m_rockstar_id;
		active.m_ip = profile.m_ip;
		active.m_name = profile.m_name;
		active.m_file_name = profile.m_file_name;
		active.m_crew_icon = profile.m_crew_icon;
		active.m_crew_motto = profile.m_crew_motto;
		active.m_crew_name = profile.m_crew_name;
		active.m_crew_rank = profile.m_crew_rank;
		active.m_crew_tag = profile.m_crew_tag;

		if (network::spoofing::profiles::vars::m_vars.m_active.m_active) {
			network::spoofing::profiles::vars::disable_active_profile();
		}

		network::spoofing::profiles::vars::m_vars.m_active.m_active = true;
		network::spoofing::profiles::vars::m_vars.m_active.m_spoof_name = m_vars.m_spoof_name;
		network::spoofing::profiles::vars::m_vars.m_active.m_spoof_rockstar_id = m_vars.m_spoof_rockstar_id;
		network::spoofing::profiles::vars::m_vars.m_active.m_spoof_ip = m_vars.m_spoof_ip;
		network::spoofing::profiles::vars::m_vars.m_active.m_spoof_crew = m_vars.m_spoof_crew;

		if (m_vars.m_spoof_ip) network::spoofing::ip::vars::spoof(false, profile.m_ip);
		if (m_vars.m_spoof_name) network::spoofing::name::vars::spoof(false, profile.m_name.c_str());
		if (m_vars.m_spoof_rockstar_id) network::spoofing::rid::vars::spoof(false, profile.m_rockstar_id);

		if (m_vars.m_spoof_crew) {
			network::spoofing::crew::icon::vars::spoof(false, active.m_crew_icon);
			network::spoofing::crew::motto::vars::spoof(false, active.m_crew_motto.c_str());
			network::spoofing::crew::name::vars::spoof(false, active.m_crew_name.c_str());
			network::spoofing::crew::rank::vars::spoof(false, active.m_crew_rank.c_str());
			network::spoofing::crew::tag::vars::spoof(false, active.m_crew_tag.c_str());
		}

		menu::submenu::handler::set_submenu_previous();
	}
}

void network_spoofing_profiles_edit_menu::load() {
	set_parent<network_spoofing_profiles_menu>();

	add_option(toggle_option("Spoof Name")
		.add_translate()
		.add_toggle(m_vars.m_spoof_name));

	add_option(toggle_option("Spoof Rockstar ID")
		.add_translate()
		.add_toggle(m_vars.m_spoof_rockstar_id));

	add_option(toggle_option("Spoof IP")
		.add_translate()
		.add_toggle(m_vars.m_spoof_ip));

	add_option(toggle_option("Spoof Crew")
		.add_translate()
		.add_toggle(m_vars.m_spoof_crew));

	add_option(button_option("Load Profile")
		.add_translate()
		.add_click(load_profile));
}

void network_spoofing_profiles_edit_menu::update() {}

void network_spoofing_profiles_edit_menu::update_once() {}

void network_spoofing_profiles_edit_menu::feature_update() {}

network_spoofing_profiles_edit_menu* g_instance;
network_spoofing_profiles_edit_menu* network_spoofing_profiles_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_profiles_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}