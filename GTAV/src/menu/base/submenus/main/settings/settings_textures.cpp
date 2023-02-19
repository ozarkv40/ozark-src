#include "settings_textures.h"
#include "menu/base/submenu_handler.h"
#include "../settings.h"
#include "settings_texture.h"

using namespace settings::textures::vars;

namespace settings::textures::vars {
	variables m_vars;
}

void textures_menu::load() {
	set_name("Textures");
	set_parent<settings_menu>();

	settings::texture::vars::m_vars.m_texture = &global::ui::m_header;

	m_vars.m_header_option = add_option(submenu_option("Header")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_header;
			settings::texture::vars::m_vars.m_pixel_info = { { global::ui::g_scale.x, 0.09f } };
		}));

	m_vars.m_background_option = add_option(submenu_option("Background")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_background;
			settings::texture::vars::m_vars.m_pixel_info = { { global::ui::g_scale.x, global::ui::g_option_scale * menu::base::get_max_options() }, true, "Y" };
		}));

	m_vars.m_scroller_option = add_option(submenu_option("Scroller")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_scroller;
			settings::texture::vars::m_vars.m_pixel_info = { { global::ui::g_scale.x, global::ui::g_option_scale } };
		}));

	m_vars.m_footer_option = add_option(submenu_option("Footer")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_footer;
			settings::texture::vars::m_vars.m_pixel_info = { { global::ui::g_scale.x, global::ui::g_option_scale } };
		}));

	m_vars.m_tooltip_background_option = add_option(submenu_option("Tooltip Background")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_tooltip_background;
			settings::texture::vars::m_vars.m_pixel_info = { { global::ui::g_scale.x, global::ui::g_option_scale * menu::base::get_max_options() }, true, "Y" };
		}));

	m_vars.m_stacked_display_background_option = add_option(submenu_option("Stacked Display Background")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_stacked_display_background;
			settings::texture::vars::m_vars.m_pixel_info = { { 0.15f, 0.0815f }, true, "Y" };
		}));

	m_vars.m_stacked_display_bar_option = add_option(submenu_option("Stacked Display Bar")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_stacked_display_bar;
			settings::texture::vars::m_vars.m_pixel_info = { { 0.15f, 0.0039375f } };
		}));

	m_vars.m_panel_background_option = add_option(submenu_option("Panel Background")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_panel_background;
			settings::texture::vars::m_vars.m_pixel_info.m_pixel_size.x = 0.f;
		}));

	m_vars.m_panel_bar_option = add_option(submenu_option("Panel Bar")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_panel_bar;
			settings::texture::vars::m_vars.m_pixel_info = { { 0.f, 0.0039375f } };
		}));

	m_vars.m_notify_background_option = add_option(submenu_option("Notify Background")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_notify_background;
			settings::texture::vars::m_vars.m_pixel_info = { { 0.15f, 0.042f }, true, "X/Y" };
		}));

	m_vars.m_notify_bar_option = add_option(submenu_option("Notify Bar")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
			settings::texture::vars::m_vars.m_texture = &global::ui::m_notify_bar;
			settings::texture::vars::m_vars.m_pixel_info = { { 0.002f, 0.042f }, true, "Y" };
		}));

	m_vars.m_vehicle_stats_background_option = add_option(submenu_option("Vehicle Stats Background")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
		settings::texture::vars::m_vars.m_texture = &global::ui::m_vehicle_stats_background;
		settings::texture::vars::m_vars.m_pixel_info = { { global::ui::g_scale.x, 0.15f } };
	}));

	m_vars.m_vehicle_stats_bar_option = add_option(submenu_option("Vehicle Stats Bar")
		.add_translate().add_hotkey()
		.add_submenu<texture_menu>()
		.add_click([] {
		settings::texture::vars::m_vars.m_texture = &global::ui::m_vehicle_stats_bar;
		settings::texture::vars::m_vars.m_pixel_info = { { 0.09140625f, 0.00833328f }, true, "X" };
	}));

	global::ui::m_header.m_submenu_name = m_vars.m_header_option->get_name();
	global::ui::m_notify_bar.m_submenu_name = m_vars.m_notify_bar_option->get_name();
	global::ui::m_notify_background.m_submenu_name = m_vars.m_notify_background_option->get_name();
	global::ui::m_panel_bar.m_submenu_name = m_vars.m_panel_bar_option->get_name();
	global::ui::m_panel_background.m_submenu_name = m_vars.m_panel_background_option->get_name();
	global::ui::m_stacked_display_bar.m_submenu_name = m_vars.m_stacked_display_bar_option->get_name();
	global::ui::m_stacked_display_background.m_submenu_name = m_vars.m_stacked_display_background_option->get_name();
	global::ui::m_tooltip_background.m_submenu_name = m_vars.m_tooltip_background_option->get_name();
	global::ui::m_footer.m_submenu_name = m_vars.m_footer_option->get_name();
	global::ui::m_scroller.m_submenu_name = m_vars.m_scroller_option->get_name();
	global::ui::m_background.m_submenu_name = m_vars.m_background_option->get_name();
	global::ui::m_vehicle_stats_background.m_submenu_name = m_vars.m_vehicle_stats_background_option->get_name();
	global::ui::m_vehicle_stats_bar.m_submenu_name = m_vars.m_vehicle_stats_bar_option->get_name();
}

void textures_menu::update() {}

void textures_menu::update_once() {}

void textures_menu::feature_update() {}

textures_menu* g_instance;
textures_menu* textures_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new textures_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}