#include "teleport_save_load.h"
#include "menu/base/submenu_handler.h"
#include "../teleport.h"
#include "util/dirs.h"
#include "util/log.h"
#include <filesystem>
#include <fstream>

using namespace teleport::save::vars;

namespace teleport::save::vars {
	variables m_vars;

	void save(const char* text, math::vector3<float> coords) {
		try {
			std::ifstream input(util::dirs::get_path(teleport));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				std::ofstream output(util::dirs::get_path(teleport));
				if (output.good()) {
					json["locations"][text] = { coords.x, coords.y, coords.z };

					output << json.dump(4);
					output.close();
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void load_saves(teleport_save_load_menu* _this) {
		try {
			std::ifstream input(util::dirs::get_path(teleport));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				nlohmann::json& data = json["locations"];
				if (!data.empty()) {
					m_vars.m_locations.clear();

					for (auto& it = data.begin(); it != data.end(); ++it) {
						nlohmann::json& coords = *it;
						m_vars.m_locations.push_back({ it.key(), { coords[0].get<float>(), coords[1].get<float>(), coords[2].get<float>() } });
					}
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}

		_this->clear_options(2);

		if (!m_vars.m_locations.empty()) {
			for (std::pair<std::string, math::vector3<float>>& location : m_vars.m_locations) {
				_this->add_option(button_option(location.first)
					.add_click([=] { teleport::vars::teleport(location.second); }));
			}
		} else {
			_this->add_option(break_option(_this->get_string("~m~None")));
		}
	}
}

void teleport_save_load_menu::load() {
	set_name("Save and Load");
	set_parent<teleport_menu>();

	add_string("~m~None");

	add_option(button_option("Save Current Position")
		.add_translate().add_hotkey()
		.add_keyboard("Enter save name", 30, [this](button_option* option, const char* text) {
			save(text, menu::player::get_local_player().m_coords);
			load_saves(this);
		}));

	add_option(break_option("Locations")
		.add_translate());

	if (!std::filesystem::exists(util::dirs::get_path(teleport))) {
		try {
			std::ofstream output(util::dirs::get_path(teleport));
			if (output.good()) {
				nlohmann::json json;
				json["locations"]["Beach Cove"] = { 3073.21f, 2128.90f, 2.38f };
				json["locations"]["Karaoke Bar"] = { 374.39f, -1000.61f, -99.f };
				json["locations"]["Character Creation"] = { 409.43f, -998.23f, -99.f };
				json["locations"]["Garage"] = { 398.87f, -970.25f, -99.f };
				
				output << json.dump(4);
				output.close();
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void teleport_save_load_menu::update() {}

void teleport_save_load_menu::update_once() {
	load_saves(this);
}

void teleport_save_load_menu::feature_update() {}

teleport_save_load_menu* g_instance;
teleport_save_load_menu* teleport_save_load_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new teleport_save_load_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}