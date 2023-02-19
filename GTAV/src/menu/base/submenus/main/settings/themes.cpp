#include "themes.h"
#include "menu/base/submenu_handler.h"
#include "../settings.h"
#include "util/dirs.h"
#include "themes/themes_selected.h"
#include "settings_textures.h"
#include "util/log.h"
#include "settings_color.h"
#include "settings_fonts.h"
#include "position_scale.h"
#include "menu/base/util/fonts.h"
#include <filesystem>
#include <fstream>

using namespace settings::theme::vars;

namespace settings::theme::vars {
	variables m_vars;

	std::initializer_list<int> create_color(color_rgba color) {
		return { color.r, color.g, color.b, color.a };
	}

	void create_font(nlohmann::json& json, const char* name, int var) {
		int array_id = -1;
		for (int i = 0; i < NUMOF(settings::font::vars::fonts); i++) {
			if (settings::font::vars::fonts[i].m_result == var) {
				array_id = i;
				break;
			}
		}

		json["fonts"][name]["custom"] = array_id > 4 ? true : false;
		
		if (array_id > 4) {
			json["fonts"][name]["id"] = settings::font::vars::fonts[array_id].m_name.get_original();
		} else {
			json["fonts"][name]["id"] = array_id;
		}
	}

	void create_texture(nlohmann::json& json, menu_texture texture) {
		std::pair<std::string, std::string> text = menu::renderer::get_texture(texture);
		if (text.first == "randomha") {
			json["textures"][texture.m_submenu_name.get_original()] = "null";
		} else json["textures"][texture.m_submenu_name.get_original()] = text.second;
	}

	void save_theme(const char* name) {
		bool dupe = false;
		int new_dupe = 1;

		if (std::filesystem::exists(util::va::va("%s%s.json", util::dirs::get_path(theme), name))) {
			for (int i = 1; i < 100; i++) {
				if (std::filesystem::exists(util::va::va("%s%s (%i).json", util::dirs::get_path(theme), name, i))) {
					new_dupe = i + 1;
				} else {
					if (i != 1) {
						dupe = true;
						break;
					}
				}
			}
		}

		try {
			std::ofstream output;
			if (dupe) output = std::ofstream(util::va::va("%s%s (%i).json", util::dirs::get_path(theme), name, new_dupe));
			else output = std::ofstream(util::va::va("%s%s.json", util::dirs::get_path(theme), name));

			nlohmann::json json;

			// colors
			for (scroll_struct<color_rgba*> color : settings::color::vars::colors) {
				json["colors"][color.m_name.get_original()] = create_color(*color.m_result);
			}

			// positions/scales
			for (scroll_struct<math::vector2<float>*> scale : settings::pos::vars::scales) {
				json["pos/scale"][scale.m_name.get_original()]["x"] = scale.m_result->x;
				json["pos/scale"][scale.m_name.get_original()]["y"] = scale.m_result->y;
			}

			// fonts
			create_font(json, "Header", global::ui::g_header_font);
			create_font(json, "Footer", global::ui::g_sub_header_font);
			create_font(json, "Option", global::ui::g_option_font);
			create_font(json, "Open Tooltip", global::ui::g_open_tooltip_font);
			create_font(json, "Tooltip", global::ui::g_tooltip_font);
			create_font(json, "Stacked Display", global::ui::g_stacked_display_font);
			create_font(json, "Notify Title", global::ui::g_notify_title_font);
			create_font(json, "Notify Body", global::ui::g_notify_body_font);
			create_font(json, "Panel", global::ui::g_panel_font);

			// textures
			create_texture(json, global::ui::m_header);
			create_texture(json, global::ui::m_background);
			create_texture(json, global::ui::m_scroller);
			create_texture(json, global::ui::m_footer);
			create_texture(json, global::ui::m_tooltip_background);
			create_texture(json, global::ui::m_stacked_display_background);
			create_texture(json, global::ui::m_stacked_display_bar);
			create_texture(json, global::ui::m_panel_background);
			create_texture(json, global::ui::m_panel_bar);
			create_texture(json, global::ui::m_notify_background);
			create_texture(json, global::ui::m_notify_bar);
			create_texture(json, global::ui::m_vehicle_stats_background);
			create_texture(json, global::ui::m_vehicle_stats_bar);

			// misc
			json["globe"] = global::ui::g_render_globe;
			json["smooth"]["enabled"] = global::ui::g_scroll_lerp;
			json["smooth"]["speed"] = global::ui::g_scroll_lerp_speed;

			output << json.dump(4);
			output.close();
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}

		themes_menu::get()->update_once();
	}

	void reset() {
		global::ui::g_render_tooltip = true;
		global::ui::g_render_globe = true;
		global::ui::g_scroll_lerp = true;

		global::ui::g_wrap = 0.068f;
		global::ui::g_delta = 0.f;
		global::ui::g_scroll_lerp_speed = 25.f;

		global::ui::g_header_font = menu::fonts::get_font_id("RDR");
		global::ui::g_sub_header_font = 4;
		global::ui::g_option_font = 4;
		global::ui::g_open_tooltip_font = 4;
		global::ui::g_tooltip_font = 4;
		global::ui::g_stacked_display_font = 4;
		global::ui::g_notify_title_font = 4;
		global::ui::g_notify_body_font = 4;
		global::ui::g_panel_font = 4;

		global::ui::g_position = { 0.70f, 0.3f };
		global::ui::g_scale = { 0.22f, 0.f };
		global::ui::g_submenu_arrow_position = { 0.218f, 0.010f };
		global::ui::g_submenu_arrow_scale = { 0.007f, 0.013f };
		global::ui::g_toggle_position = { 0.221f, 0.016f };
		global::ui::g_toggle_scale = { 0.007f, 0.011f };
		global::ui::g_globe_position = { 0.4405f, 0.328f };
		global::ui::g_globe_scale = { 0.978f, 0.906f };

		global::ui::g_success = color_rgba(70, 219, 37, 255);
		global::ui::g_error = color_rgba(219, 37, 37, 255);
		global::ui::g_main_header = color_rgba(76, 37, 219, 255);
		global::ui::g_sub_header = color_rgba(0, 0, 0, 220);
		global::ui::g_sub_header_text = color_rgba(255, 255, 255, 255);
		global::ui::g_background = color_rgba(0, 0, 0, 255);
		global::ui::g_scroller = color_rgba(61, 30, 176, 255); // 255, 255, 255, 255
		global::ui::g_footer = color_rgba(76, 37, 219, 220);
		global::ui::g_title = color_rgba(255, 255, 255, 255);
		global::ui::g_open_tooltip = color_rgba(76, 37, 219, 255);
		global::ui::g_option = color_rgba(255, 255, 255, 255);
		global::ui::g_option_selected = color_rgba(255, 255, 255, 255); // 0, 0, 0, 255
		global::ui::g_toggle_on = color_rgba(130, 214, 157, 255);
		global::ui::g_toggle_off = color_rgba(200, 55, 80, 255);
		global::ui::g_break = color_rgba(255, 255, 255, 255);
		global::ui::g_submenu_bar = color_rgba(255, 255, 255, 255); // 76, 37, 219, 255
		global::ui::g_clear_area_range = color_rgba(76, 37, 219, 255);
		global::ui::g_hotkey_bar = color_rgba(76, 37, 219, 255);
		global::ui::g_notify_bar = color_rgba(76, 37, 219, 255);
		global::ui::g_notify_background = color_rgba(40, 40, 40, 255);
		global::ui::g_panel_bar = color_rgba(76, 37, 219, 255);
		global::ui::g_stacked_display_bar = color_rgba(76, 37, 219, 255);
		global::ui::g_stacked_display_background = color_rgba(0, 0, 0, 180);
		global::ui::g_panel_background = color_rgba(0, 0, 0, 180);
		global::ui::g_hotkey_background = color_rgba(0, 0, 0, 180);
		global::ui::g_hotkey_input = color_rgba(40, 40, 40, 200);
		global::ui::g_instructional_background = color_rgba(0, 0, 0, 255);
		global::ui::g_globe = color_rgba(255, 255, 255, 255);

		global::ui::m_header = menu_texture(&global::ui::g_main_header);
		global::ui::m_background = menu_texture(&global::ui::g_background);
		global::ui::m_scroller = menu_texture(&global::ui::g_scroller);
		global::ui::m_footer = menu_texture(&global::ui::g_footer);
		global::ui::m_tooltip_background = menu_texture();
		global::ui::m_stacked_display_background = menu_texture();
		global::ui::m_stacked_display_bar = menu_texture();
		global::ui::m_panel_background = menu_texture();
		global::ui::m_panel_bar = menu_texture();
		global::ui::m_notify_background = menu_texture();
		global::ui::m_notify_bar = menu_texture();

		global::ui::m_header.m_submenu_name = settings::textures::vars::m_vars.m_header_option->get_name();
		global::ui::m_notify_bar.m_submenu_name = settings::textures::vars::m_vars.m_notify_bar_option->get_name();
		global::ui::m_notify_background.m_submenu_name = settings::textures::vars::m_vars.m_notify_background_option->get_name();
		global::ui::m_panel_bar.m_submenu_name = settings::textures::vars::m_vars.m_panel_bar_option->get_name();
		global::ui::m_panel_background.m_submenu_name = settings::textures::vars::m_vars.m_panel_background_option->get_name();
		global::ui::m_stacked_display_bar.m_submenu_name = settings::textures::vars::m_vars.m_stacked_display_bar_option->get_name();
		global::ui::m_stacked_display_background.m_submenu_name = settings::textures::vars::m_vars.m_stacked_display_background_option->get_name();
		global::ui::m_tooltip_background.m_submenu_name = settings::textures::vars::m_vars.m_tooltip_background_option->get_name();
		global::ui::m_footer.m_submenu_name = settings::textures::vars::m_vars.m_footer_option->get_name();
		global::ui::m_scroller.m_submenu_name = settings::textures::vars::m_vars.m_scroller_option->get_name();
		global::ui::m_background.m_submenu_name = settings::textures::vars::m_vars.m_background_option->get_name();
	}
}

void themes_menu::load() {
	set_name("Themes");
	set_parent<settings_menu>();

	add_option(button_option("Save Theme")
		.add_translate().add_hotkey()
		.add_keyboard("Enter theme name", 50, [](button_option* option, const char* text) { save_theme(text); }));

	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click(reset));

	add_option(break_option("Themes")
		.add_translate());

	add_string("~m~None");
}

void themes_menu::update() {}

void themes_menu::update_once() {
	clear_options(3);

	m_vars.m_cached_themes.clear();

	std::vector<std::string> themes = util::dirs::get_files_in_directory(util::dirs::get_path(theme), ".json");
	if (themes.size()) {
		for (std::string theme : themes) {
			std::size_t index = m_vars.m_cached_themes.size();
			if (index < 0) index = 0;
			m_vars.m_cached_themes.push_back(theme);

			add_option(submenu_option(theme)
				.add_submenu<themes_selected_menu>()
				.add_click([=] { settings::theme::selected::vars::m_vars.m_selected = index; }));
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void themes_menu::feature_update() {}

themes_menu* g_instance;
themes_menu* themes_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new themes_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}