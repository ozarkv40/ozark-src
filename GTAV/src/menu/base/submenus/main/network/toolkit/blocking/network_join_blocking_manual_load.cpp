#include "network_join_blocking_manual_load.h"
#include "menu/base/submenu_handler.h"
#include "network_join_blocking_manual.h"
#include "network_join_blocking_manual_save.h"
#include "util/dirs.h"
#include "util/log.h"
#include <fstream>

using namespace network::htoolkit::blocking::load::vars;

namespace network::htoolkit::blocking::load::vars {
	variables m_vars;

	void load_blocks(std::string file) {
		const char* location = util::va::va("%s%s.json", util::dirs::get_path(join_blocking), file.c_str());

		try {
			std::ifstream input(location);
			if (input.good()) {
				nlohmann::json json = nlohmann::json::parse(input);
				input.close();

				if (!json.empty()) {
					for (auto& it = json["blocks"].begin(); it != json["blocks"].end(); ++it) {
						nlohmann::json& elements = *it;

						network::htoolkit::blocking::vars::user_block user;
						user.m_type = elements[0];
						user.m_enabled = elements[1];
						user.m_response = elements[2];

						bool add = true;

						switch (user.m_type) {
							case 1: { // rid
								user.m_rockstar_id = elements[3];

								auto vit = std::find_if(begin(network::htoolkit::blocking::vars::m_vars.m_blocked_users),
									end(network::htoolkit::blocking::vars::m_vars.m_blocked_users),
									[=](network::htoolkit::blocking::vars::user_block& e) { return e.m_type == 1 && e.m_rockstar_id == user.m_rockstar_id; });

								if (vit != end(network::htoolkit::blocking::vars::m_vars.m_blocked_users)) {
									vit->m_enabled = user.m_enabled;
									vit->m_response = user.m_response;
									add = false;
								}

								break;
							}

							case 2: { // name
								strcpy_s(user.m_name, elements[3].get<std::string>().c_str());

								auto vit = std::find_if(begin(network::htoolkit::blocking::vars::m_vars.m_blocked_users),
									end(network::htoolkit::blocking::vars::m_vars.m_blocked_users),
									[=](network::htoolkit::blocking::vars::user_block& e) { return e.m_type == 2 && !strcmp(e.m_name, elements[3].get<std::string>().c_str()); });

								if (vit != end(network::htoolkit::blocking::vars::m_vars.m_blocked_users)) {
									vit->m_enabled = user.m_enabled;
									vit->m_response = user.m_response;
									add = false;
								}

								break;
							}

							case 3: { // IP
								user.m_ip = elements[3];

								auto vit = std::find_if(begin(network::htoolkit::blocking::vars::m_vars.m_blocked_users),
									end(network::htoolkit::blocking::vars::m_vars.m_blocked_users),
									[=](network::htoolkit::blocking::vars::user_block& e) { return e.m_type == 3 && e.m_ip == user.m_ip; });

								if (vit != end(network::htoolkit::blocking::vars::m_vars.m_blocked_users)) {
									vit->m_enabled = user.m_enabled;
									vit->m_response = user.m_response;
									add = false;
								}

								break;
							}
						}

						if (add) {
							network::htoolkit::blocking::vars::m_vars.m_blocked_users.push_back(user);
						}
					}
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void save_blocks(std::string file, std::vector<network::htoolkit::blocking::vars::user_block> users) {
		const char* location = util::va::va("%s%s.json", util::dirs::get_path(join_blocking), file.c_str());

		try {
			nlohmann::json json;

			std::ifstream input(location);
			if (input.good()) {
				json = nlohmann::json::parse(input);
				input.close();
			}

			std::ofstream output(location);
			if (output.good()) {
				if (json["blocks"].empty()) {
					json["blocks"] = nlohmann::json::array();
				}

				for (network::htoolkit::blocking::vars::user_block& user : users) {
					nlohmann::json arr = nlohmann::json::array();
					arr[0] = user.m_type;
					arr[1] = user.m_enabled;
					arr[2] = user.m_response;

					switch (user.m_type) {
						case 1: // rid
							arr[3] = user.m_rockstar_id;
							break;

						case 2: // name
							arr[3] = user.m_name;
							break;

						case 3: // IP
							arr[3] = user.m_ip;
							break;
					}

					json["blocks"].push_back(arr);
				}

				output << json.dump(4);
				output.close();
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void network_join_blocking_manual_load_menu::load() {
	set_name("Save and Load");
	set_parent<network_join_blocking_manual_menu>();

	add_option(submenu_option("Save User Blocks")
		.add_translate()
		.add_submenu<network_join_blocking_manual_save_menu>());
	
	add_option(break_option("Blocks")
		.add_translate());
}

void network_join_blocking_manual_load_menu::update() {}

void network_join_blocking_manual_load_menu::update_once() {
	clear_options(2);

	std::vector<std::string> files = util::dirs::get_files_in_directory(util::dirs::get_path(join_blocking), ".json");
	if (files.size()) {
		for (std::string file : files) {
			add_option(button_option(file)
				.add_click([=] { load_blocks(file.c_str()); }));
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void network_join_blocking_manual_load_menu::feature_update() {}

network_join_blocking_manual_load_menu* g_instance;
network_join_blocking_manual_load_menu* network_join_blocking_manual_load_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_join_blocking_manual_load_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}