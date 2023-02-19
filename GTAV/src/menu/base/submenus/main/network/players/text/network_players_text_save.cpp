#include "network_players_text_save.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_text.h"
#include "util/log.h"
#include "util/dirs.h"
#include <fstream>

using namespace network::players::text::save::vars;

namespace network::players::text::save::vars {
	variables m_vars;

	void load_messages(network_players_text_save_menu* _this) {
		try {
			std::ifstream file(util::dirs::get_path(text_messages));
			if (file.good()) {
				nlohmann::json json = nlohmann::json::parse(file);
				file.close();

				nlohmann::json& data = json["messages"];
				if (data.size()) {
					m_vars.m_messages.clear();

					for (nlohmann::json::iterator it = data.begin(); it != data.end(); ++it) {
						m_vars.m_messages.push_back(std::make_pair(it.key(), it.value().get<std::string>()));
					}
				}
			} else {
				std::ofstream output(util::dirs::get_path(text_messages));
				if (output.good()) {
					nlohmann::json json;
					json["messages"]["Hello, Friend!"] = "Hello, Friend!";

					output << json.dump(4);
					output.close();
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}

		_this->clear_options(2);

		for (std::pair<std::string, std::string> message : m_vars.m_messages) {
			_this->add_option(button_option(message.first)
				.add_click([=] {
					menu::player::get_selected_player().m_text_message_msg = message.second;
					menu::submenu::handler::set_submenu_previous();
				}));
		}
	}

	void save(std::string name, std::string message) {
		try {
			std::ifstream file(util::dirs::get_path(text_messages));
			if (file.good()) {
				nlohmann::json json = nlohmann::json::parse(file);
				file.close();

				json["messages"][name] = message;

				std::ofstream output(util::dirs::get_path(text_messages));
				if (output.good()) {
					output << json.dump(4);
					output.close();
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void network_players_text_save_menu::load() {
	set_name("save and Load");
	set_parent<network_players_text_menu>();

	add_option(button_option("Add Message")
		.add_translate()
		.add_keyboard("Enter your message", 100, [this] (button_option* option, const char* msg) {
			std::string message = msg;
			std::string temp = message;

			if (temp.size() > 32) {
				temp.erase(temp.begin() + 32, temp.end());
				temp += std::string("...");
			}

			save(temp, message);
			load_messages(this);
		}));

	add_option(break_option("Messages")
		.add_translate());
}

void network_players_text_save_menu::update() {}

void network_players_text_save_menu::update_once() {
	load_messages(this);
}

void network_players_text_save_menu::feature_update() {}

network_players_text_save_menu* g_instance;
network_players_text_save_menu* network_players_text_save_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_text_save_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}