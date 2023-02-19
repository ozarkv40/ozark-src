#include "network_spoofing_profiles.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing.h"
#include "util/dirs.h"
#include "util/log.h"
#include "network_spoofing_ip.h"
#include "network_spoofing_name.h"
#include "network_spoofing_rid.h"
#include "crew/network_spoofing_crew_icon.h"
#include "crew/network_spoofing_crew_motto.h"
#include "crew/network_spoofing_crew_name.h"
#include "crew/network_spoofing_crew_rank.h"
#include "crew/network_spoofing_crew_tag.h"
#include "profiles/network_spoofing_profiles_edit.h"
#include <fstream>

using namespace network::spoofing::profiles::vars;

namespace network::spoofing::profiles::vars {
	variables m_vars;

	void disable_active_profile() {
		m_vars.m_active.m_active = false;

		if (m_vars.m_active.m_spoof_ip) {
			network::spoofing::ip::vars::spoof(true);
		}

		if (m_vars.m_active.m_spoof_rockstar_id) {
			network::spoofing::rid::vars::spoof(true);
		}

		if (m_vars.m_active.m_spoof_name) {
			network::spoofing::name::vars::spoof(true);
		}

		if (m_vars.m_active.m_spoof_crew) {
			network::spoofing::crew::icon::vars::spoof(true);
			network::spoofing::crew::motto::vars::spoof(true);
			network::spoofing::crew::name::vars::spoof(true);
			network::spoofing::crew::rank::vars::spoof(true);
			network::spoofing::crew::tag::vars::spoof(true);
		}
	}

	void save_profile(spoof_profile profile) {
		if (profile.m_file_name.empty()) {
			profile.m_file_name = profile.m_name;
		}

		profile.m_file_name += ".json";

		nlohmann::json json;
		json["rid"] = profile.m_rockstar_id;
		json["name"] = profile.m_name;
		json["ip"] = profile.m_ip;
		json["crew"]["icon"] = profile.m_crew_icon;
		json["crew"]["motto"] = profile.m_crew_motto;
		json["crew"]["name"] = profile.m_crew_name;
		json["crew"]["rank"] = profile.m_crew_rank;
		json["crew"]["tag"] = profile.m_crew_tag;

		std::ofstream output(util::dirs::get_path(spoofing_profiles) + profile.m_file_name);
		if (output.good()) {
			output << json.dump(4);
			output.close();
		}
	}
}

void network_spoofing_profiles_menu::load() {
	set_name("Profiles");
	set_parent<network_spoofing_menu>();

	add_option(button_option("Disable Active Profile")
		.add_translate()
		.add_click(disable_active_profile)
		.add_requirement([] { return m_vars.m_active.m_active; }));

	add_option(break_option("Profiles")
		.add_translate()
		.add_requirement([] { return m_vars.m_active.m_active; }));

	add_string("~m~None");
}

void network_spoofing_profiles_menu::update() {}

void network_spoofing_profiles_menu::update_once() {
	clear_options(2);

	m_vars.m_profiles.clear();

	std::vector<std::string> profiles = util::dirs::get_files_in_directory(util::dirs::get_path(spoofing_profiles), ".json");
	if (!profiles.empty()) {
		for (std::string profile : profiles) {
			std::ifstream input(util::dirs::get_path(spoofing_profiles) + profile + ".json");
			if (input.good()) {
				try {
					nlohmann::json json = nlohmann::json::parse(input);
					input.close();

					if (!json.empty()) {
						spoof_profile p;
						p.m_file_name = profile;
						p.m_rockstar_id = json["rid"].get<uint32_t>();
						p.m_ip = json["ip"];
						p.m_name = json["name"];
						p.m_crew_icon = json["crew"]["icon"].get<int>();
						p.m_crew_motto = json["crew"]["motto"];
						p.m_crew_name = json["crew"]["name"];
						p.m_crew_rank = json["crew"]["rank"];
						p.m_crew_tag = json["crew"]["tag"];

						std::size_t index = m_vars.m_profiles.size();
						if (index < 0) index = 0;
						m_vars.m_profiles.push_back(p);

						add_option(submenu_option(profile)
							.add_submenu<network_spoofing_profiles_edit_menu>()
							.add_click([=] {
								network_spoofing_profiles_edit_menu::get()->set_name(profile, false, false);
								network::spoofing::profiles::edit::vars::m_vars.m_selected = index;
						}));
					}
				} catch (std::exception& e) {
					LOG_WARN("[Json] %s", e.what());
				}
			}
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void network_spoofing_profiles_menu::feature_update() {}

network_spoofing_profiles_menu* g_instance;
network_spoofing_profiles_menu* network_spoofing_profiles_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_profiles_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}