#include "settings.h"
#include "menu/base/submenu_handler.h"
#include "../main.h"
#include "settings/settings_textures.h"
#include "settings/settings_fonts.h"
#include "settings/settings_hotkey.h"
#include "settings/settings_color.h"
#include "settings/translation.h"
#include "settings/position_scale.h"
#include "settings/themes.h"
#include "settings/themes/themes_selected.h"
#include "settings/hide_info.h"

namespace settings::vars {
	std::shared_ptr<button_option> bitch;
}

void settings_menu::load() {
	set_name("Settings");
	set_parent<main_menu>();

	add_option(submenu_option("Translations")
		.add_translate().add_hotkey()
		.add_submenu<translation_menu>());

	add_option(submenu_option("Themes")
		.add_translate().add_hotkey()
		.add_submenu<themes_menu>());

	add_option(submenu_option("Hotkeys")
		.add_translate().add_hotkey()
		.add_submenu<hotkey_menu>());

	add_option(submenu_option("Fonts")
		.add_translate().add_hotkey()
		.add_submenu<fonts_menu>());

	add_option(submenu_option("Textures")
		.add_translate().add_hotkey()
		.add_submenu<textures_menu>());

	add_option(submenu_option("Position and Scale")
		.add_translate().add_hotkey()
		.add_submenu<position_scale_menu>());

	add_option(submenu_option("Colors")
		.add_translate().add_hotkey()
		.add_submenu<color_menu>());

	add_option(submenu_option("Streamer Mode")
		.add_translate().add_hotkey()
		.add_submenu<hide_info_menu>());

	add_option(toggle_option("Open Tooltip")
		.add_translate().add_hotkey()
		.add_toggle(global::ui::g_render_tooltip).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Globe")
		.add_translate().add_hotkey()
		.add_toggle(global::ui::g_render_globe).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Title")
		.add_translate().add_hotkey()
		.add_toggle(global::ui::g_disable_title).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Smooth Scrolling")
		.add_translate().add_hotkey()
		.add_toggle(global::ui::g_scroll_lerp)
		.add_number(global::ui::g_scroll_lerp_speed, "%.0f", 1.f).add_savable(get_submenu_name_stack()));

	add_option(button_option("Unload")
		.add_translate().add_hotkey()
		.add_click([] { global::vars::g_unloading_queue = true; }));

	settings::vars::bitch = add_option(button_option("Edit Open Key")
		.add_translate().add_hotkey()
		.add_click([this] {
			menu::input::push([this] {
				menu::base::set_open_key(menu::input::get_key(settings::vars::bitch.get()->get_name().get(), menu::base::get_open_key()));
				util::config::write_int(get_submenu_name_stack(), "Open key", menu::base::get_open_key());
			});
		})
		.add_update([] (button_option* option) { option->add_side_text(menu::input::g_key_names[menu::base::get_open_key()]); }));

	themes_selected_menu::get();

	menu::base::set_open_key(util::config::read_int(get_submenu_name_stack(), "Open key", menu::base::get_open_key()));
}

void settings_menu::update() {}

void settings_menu::update_once() {}

void settings_menu::feature_update() {}

settings_menu* g_instance;
settings_menu* settings_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new settings_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}