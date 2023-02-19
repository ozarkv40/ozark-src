#include "helper_color_preset.h"
#include "menu/base/submenu_handler.h"
#include "../helper_color.h"

using namespace helper::color::preset::vars;

namespace helper::color::preset::vars {
	variables m_vars;

	scroll_struct<color_rgba> presets[] = {
		{ localization("Ozark Blue", true), color_rgba(0x0095ffff) },
		{ localization("Emerald", true), color_rgba(0, 155, 119, 200) },
		{ localization("Tangerine Tango", true), color_rgba(221, 65, 36, 200) },
		{ localization("Honeysucle", true), color_rgba(214, 80, 118, 200) },
		{ localization("Turquoise", true), color_rgba(68, 184, 172, 200) },
		{ localization("Mimosa", true), color_rgba(239, 192, 80, 200) },
		{ localization("Blue Izis", true), color_rgba(91, 94, 166, 200) },
		{ localization("Chili Pepper", true), color_rgba(155, 35, 53, 200) },
		{ localization("Sand Dollar", true), color_rgba(223, 207, 190, 200) },
		{ localization("Blue Turquoise", true), color_rgba(85, 180, 176, 200) },
		{ localization("Tigerlily", true), color_rgba(225, 93, 68, 200) },
		{ localization("Aqua Sky", true), color_rgba(127, 205, 205, 200) },
		{ localization("True Red", true), color_rgba(188, 36, 60, 200) },
		{ localization("Fuchsia Rose", true), color_rgba(195, 68, 122, 200) },
		{ localization("Cerulean Blue", true), color_rgba(152, 180, 212, 200) },
		{ localization("Galaxy Blue", true), color_rgba(0x2A, 0x4B, 0x7C, 200) },
		{ localization("Dark Cheddar", true), color_rgba(0xE0, 0x81, 0x19, 200) },
		{ localization("Orange Tiger", true), color_rgba(0xF9, 0x67, 0x14, 200) },
		{ localization("Turmeric", true), color_rgba(0xFE, 0x84, 0x0E, 200) },
		{ localization("Pink Peacock", true), color_rgba(0xC6, 0x21, 0x68, 200) },
		{ localization("Aspen Gold", true), color_rgba(0xFF, 0xD6, 0x62, 200) },
		{ localization("Eclipse", true), color_rgba(0x34, 0x31, 0x48, 200) },
		{ localization("Valiant Poppy", true), color_rgba(0xBD, 0x3D, 0x3A, 200) },
		{ localization("Nebulas Blue", true), color_rgba(0x3F, 0x69, 0xAA, 200) },
		{ localization("Ceylon Yellow", true), color_rgba(0xD5, 0xAE, 0x41, 200) },
		{ localization("Russet Orange", true), color_rgba(0xE4, 0x7A, 0x2E, 200) },
		{ localization("Quetzal Green", true), color_rgba(0x00, 0x6E, 0x6D, 200) },
		{ localization("Cherry Tomato", true), color_rgba(0xE9, 0x4B, 0x3C, 200) },
		{ localization("Meadowlark", true), color_rgba(0xEC, 0xDB, 0x54, 200) },
		{ localization("Baby Blue", true), color_rgba(0x6F, 0x9F, 0xD8, 200) },
		{ localization("Arcadia", true), color_rgba(0x00, 0xA5, 0x91, 200) },
		{ localization("Ultra Violet", true), color_rgba(0x6B, 0x5B, 0x95, 200) },
		{ localization("Lime Punch", true), color_rgba(0xBF, 0xD6, 0x41, 200) },
		{ localization("Harbor Mist", true), color_rgba(0xB4, 0xB7, 0xBA, 200) },
		{ localization("Grenadine", true), color_rgba(0xDC, 0x4C, 0x46, 200) },
		{ localization("Navy Peony", true), color_rgba(0x22, 0x3A, 0x5E, 200) },
		{ localization("Marina", true), color_rgba(0x4F, 0x84, 0xC4, 200) },
		{ localization("Autumn Maple", true), color_rgba(0xD2, 0x69, 0x1E, 200) },
		{ localization("Niagara", true), color_rgba(0x57, 0x8C, 0xA9, 200) },
		{ localization("Primrose Yellow", true), color_rgba(0xF6, 0xD1, 0x55, 200) },
		{ localization("Flame", true), color_rgba(0xF2, 0x55, 0x2C, 200) },
		{ localization("Lapis Blue", true), color_rgba(0x00, 0x4B, 0x8D, 200) },
		{ localization("Island Paradise", true), color_rgba(0x95, 0xDE, 0xE3, 200) },
		{ localization("Pink Yarrow", true), color_rgba(0xCE, 0x31, 0x75, 200) },
		{ localization("Riverside", true), color_rgba(0x4C, 0x6A, 0x92, 200) },
		{ localization("Aurora Red", true), color_rgba(0xB9, 0x3A, 0x32, 200) },
		{ localization("Serenity", true), color_rgba(0x91, 0xA8, 0xD0, 200) },
		{ localization("Green Flash", true), color_rgba(0x79, 0xC7, 0x53, 200) },
		{ localization("Buttercup", true), color_rgba(0xFA, 0xE0, 0x3C, 200) },
		{ localization("Limpet Shell", true), color_rgba(0x98, 0xDD, 0xDE, 200) }
	};
}

void helper_color_preset_menu::load() {
	set_name("Presets");
	set_parent<helper_color_menu>();
}

void helper_color_preset_menu::update() {}

void helper_color_preset_menu::update_once() {
	clear_options(0);

	for (scroll_struct<color_rgba>& preset : presets) {
		add_option(button_option(preset.m_name.get())
			.add_click([=] {
				*m_vars.m_color = preset.m_result;
				helper::color::vars::m_vars.m_callback();
			})
			.add_hover([=] { menu::renderer::render_color_preview(preset.m_result); }));
	}
}

void helper_color_preset_menu::feature_update() {}

helper_color_preset_menu* g_instance;
helper_color_preset_menu* helper_color_preset_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new helper_color_preset_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}