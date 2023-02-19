#include "themes_selected.h"
#include "menu/base/submenu_handler.h"
#include "../themes.h"
#include "util/config.h"
#include "util/dirs.h"
#include "util/log.h"
#include "../settings_color.h"
#include "../settings_fonts.h"
#include "../position_scale.h"
#include "menu/base/util/textures.h"
#include <fstream>

using namespace settings::theme::selected::vars;

namespace settings::theme::selected::vars {
	variables m_vars;

	void load_font(nlohmann::json json, const char* name, int* var) {
		if (!json["fonts"][name].is_null()) {
			if (json["fonts"][name]["custom"].get<bool>()) {
				for (scroll_struct<int> font : settings::font::vars::fonts) {
					if (font.m_name.get_original() == json["fonts"][name]["id"].get<std::string>()) {
						*var = font.m_result;
						break;
					}
				}
			} else {
				*var = settings::font::vars::fonts[json["fonts"][name]["id"].get<int>()].m_result;
			}
		}
	}

	void load_texture(nlohmann::json& json, menu_texture& texture) {
		if (!json["textures"][texture.m_submenu_name.get_original()].is_null()) {
			if (json["textures"][texture.m_submenu_name.get_original()].get<std::string>() != "null") {
				texture.m_texture = json["textures"][texture.m_submenu_name.get_original()].get<std::string>();

				for (std::size_t i = 0; i < menu::textures::get_list().size(); i++) {
					if (!menu::textures::get_list()[i].m_name.compare(texture.m_texture)) {
						texture.m_context.m_selected = (int)i;
						texture.m_enabled = true;
						break;
					}
				}
			} else {
				texture.m_enabled = false;
			}
		}
	}

	void load_theme(const char* name) {
		try {
			std::ifstream input(util::va::va("%s%s.json", util::dirs::get_path(theme), name));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				// colors
				for (scroll_struct<color_rgba*> color : settings::color::vars::colors) {
					if (!json["colors"][color.m_name.get_original()].is_null()) {
						color.m_result->r = json["colors"][color.m_name.get_original()][0].get<int>();
						color.m_result->g = json["colors"][color.m_name.get_original()][1].get<int>();
						color.m_result->b = json["colors"][color.m_name.get_original()][2].get<int>();
						color.m_result->a = json["colors"][color.m_name.get_original()][3].get<int>();
					}
				}

				// positions/scales
				for (scroll_struct<math::vector2<float>*> scale : settings::pos::vars::scales) {
					if (!json["pos/scale"][scale.m_name.get_original()].is_null()) {
						scale.m_result->x = json["pos/scale"][scale.m_name.get_original()]["x"].get<float>();
						scale.m_result->y = json["pos/scale"][scale.m_name.get_original()]["y"].get<float>();
					}
				}

				// fonts
				load_font(json, "Header", &global::ui::g_header_font);
				load_font(json, "Footer", &global::ui::g_sub_header_font);
				load_font(json, "Option", &global::ui::g_option_font);
				load_font(json, "Open Tooltip", &global::ui::g_open_tooltip_font);
				load_font(json, "Tooltip", &global::ui::g_tooltip_font);
				load_font(json, "Stacked Display", &global::ui::g_stacked_display_font);
				load_font(json, "Notify Title", &global::ui::g_notify_title_font);
				load_font(json, "Notify Body", &global::ui::g_notify_body_font);
				load_font(json, "Panel", &global::ui::g_panel_font);

				// textures
				load_texture(json, global::ui::m_header);
				load_texture(json, global::ui::m_background);
				load_texture(json, global::ui::m_scroller);
				load_texture(json, global::ui::m_footer);
				load_texture(json, global::ui::m_tooltip_background);
				load_texture(json, global::ui::m_stacked_display_background);
				load_texture(json, global::ui::m_stacked_display_bar);
				load_texture(json, global::ui::m_panel_background);
				load_texture(json, global::ui::m_panel_bar);
				load_texture(json, global::ui::m_notify_background);
				load_texture(json, global::ui::m_notify_bar);
				load_texture(json, global::ui::m_vehicle_stats_background);
				load_texture(json, global::ui::m_vehicle_stats_bar);

				// misc
				global::ui::g_render_globe = json["globe"].get<bool>();
				global::ui::g_scroll_lerp = json["smooth"]["enabled"].get<float>();
				global::ui::g_scroll_lerp_speed = json["smooth"]["speed"].get<float>();
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void themes_selected_menu::load() {
	set_name("Theme");
	set_parent<themes_menu>();

	add_option(button_option("Load")
		.add_translate()
		.add_click([] { load_theme(settings::theme::vars::m_vars.m_cached_themes[m_vars.m_selected].c_str()); }));

	add_option(button_option("Delete")
		.add_translate()
		.add_click([] {
			remove(util::va::va("%s%s.json", util::dirs::get_path(theme), settings::theme::vars::m_vars.m_cached_themes[m_vars.m_selected].c_str()));
			menu::submenu::handler::set_submenu_previous(true);
		}));

	add_option(button_option("Set as Load Default")
		.add_translate()
		.add_click([this] { util::config::write_string(get_submenu_name_stack(), "Launch", settings::theme::vars::m_vars.m_cached_themes[m_vars.m_selected]); }));

	std::string launch = util::config::read_string(get_submenu_name_stack(), "Launch", "-none-");
	if (launch.compare("-none-")) {
		load_theme(launch.c_str());
	}
}

void themes_selected_menu::update() {}

void themes_selected_menu::update_once() {}

void themes_selected_menu::feature_update() {}

themes_selected_menu* g_instance;
themes_selected_menu* themes_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new themes_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}