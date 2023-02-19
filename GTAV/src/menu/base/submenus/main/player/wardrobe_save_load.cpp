#include "wardrobe_save_load.h"
#include "menu/base/submenu_handler.h"
#include "wardrobe.h"
#include "util/va.h"
#include "util/dirs.h"
#include "util/log.h"
#include <fstream>

using namespace player::wardrobe::saveload::vars;

namespace player::wardrobe::saveload::vars {
	void save_outfit(const char* name, menu::player::player_context player) {
		const char* location = util::va::va("%s%s.json", util::dirs::get_path(outfit), name);

		try {
			std::ofstream output(location);
			if (output.good()) {
				nlohmann::json json;

				for (scroll_struct<std::pair<int, math::vector3_<float>>> component : wardrobe::vars::components) {
					json["Clothing"][component.m_name.get_original() + " Drawable"] = native::get_ped_drawable_variation(player.m_ped, component.m_result.first);
					json["Clothing"][component.m_name.get_original() + " texture_context"] = native::get_ped_texture_variation(player.m_ped, component.m_result.first);
				}

				for (scroll_struct<std::pair<int, math::vector3_<float>>> prop : wardrobe::vars::accessories) {
					json["Accessories"][prop.m_name.get_original() + " Drawable"] = native::get_ped_prop_index(player.m_ped, prop.m_result.first);
					json["Accessories"][prop.m_name.get_original() + " texture_context"] = native::get_ped_prop_texture_index(player.m_ped, prop.m_result.first);
				}

				output << json.dump(4);
				output.close();

				wardrobe_save_load_menu::get()->update_once();
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void load_outfit(const char* name) {
		const char* location = util::va::va("%s%s.json", util::dirs::get_path(outfit), name);

		try {
			std::ifstream input(location);
			if (input.good()) {
				nlohmann::json json;
				input >> json;

				native::clear_all_ped_props(menu::player::get_local_player().m_ped);

				for (scroll_struct<std::pair<int, math::vector3_<float>>> component : wardrobe::vars::components) {
					native::set_ped_component_variation(menu::player::get_local_player().m_ped, component.m_result.first, json["Clothing"][component.m_name.get_original() + " Drawable"].get<int>(), json["Clothing"][component.m_name.get_original() + " texture_context"].get<int>(), 0);
				}

				for (scroll_struct<std::pair<int, math::vector3_<float>>> prop : wardrobe::vars::accessories) {
					native::set_ped_prop_index(menu::player::get_local_player().m_ped, prop.m_result.first, json["Accessories"][prop.m_name.get_original() + " Drawable"].get<int>(), json["Accessories"][prop.m_name.get_original() + " texture_context"].get<int>(), true);
				}

				input.close();
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void wardrobe_save_load_menu::load() {
	set_name("Save and Load");
	set_parent<wardrobe_menu>();

	add_option(button_option("Save Outfit")
		.add_translate().add_hotkey()
		.add_keyboard("Enter the outfit name!", 30, [=](button_option* _this, const char* name) { save_outfit(name, menu::player::get_local_player()); }));

	add_option(break_option("Outfits")
		.add_translate());

	add_string("~m~None");
}

void wardrobe_save_load_menu::update() {}

void wardrobe_save_load_menu::update_once() {
	clear_options(2);

	std::vector<std::string> files = util::dirs::get_files_in_directory(util::dirs::get_path(outfit), ".json");
	if (files.size()) {
		for (std::string file : files) {
			add_option(button_option(file)
				.add_click([=] { load_outfit(file.c_str()); }));
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void wardrobe_save_load_menu::feature_update() {}

wardrobe_save_load_menu* g_instance;
wardrobe_save_load_menu* wardrobe_save_load_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new wardrobe_save_load_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}