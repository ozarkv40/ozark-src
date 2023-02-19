#include "fx_liquid.h"
#include "menu/base/submenu_handler.h"
#include "../game_fx.h"
#include "../../helper/helper_color.h"

using namespace world::fx::liquid::vars;

namespace world::fx::liquid::vars {
	variables m_vars;

	scroll_struct<eLiquid> liquid[] = {
		{ localization("Puddle", true), LIQUID_PUDDLE },
		{ localization("Blood", true), LIQUID_BLOOD },
		{ localization("Oil", true), LIQUID_OIL },
		{ localization("Petrol", true), LIQUID_PETROL },
		{ localization("Mud", true), LIQUID_MUD }
	};
}

void fx_liquid_menu::load() {
	set_name("Liquid");
	set_parent<game_fx_menu>();

	memcpy(m_vars.m_backup, global::vars::g_vfx_liquid, sizeof(m_vars.m_backup));

	add_option(scroll_option<eLiquid>(SCROLL, "Liquid Type")
		.add_scroll(m_vars.m_selected, 0, NUMOF(liquid), liquid)
		.add_click([this] { update_once(); }));

	add_string("Edit Color");
}

void fx_liquid_menu::update() {}

void fx_liquid_menu::update_once() {
	clear_options(1);

	m_vars.m_color = {
		global::vars::g_vfx_liquid[m_vars.m_selected].r,
		global::vars::g_vfx_liquid[m_vars.m_selected].g,
		global::vars::g_vfx_liquid[m_vars.m_selected].b,
		global::vars::g_vfx_liquid[m_vars.m_selected].a
	};

	add_option(submenu_option(get_string("Edit Color"))
		.add_submenu<helper_color_menu>()
		.add_click([=] {
			helper_color_menu::get()->set_name(get_name().get(), false, false);
			helper_color_menu::get()->set_parent<fx_liquid_menu>();
			helper::color::vars::m_vars.m_color = &m_vars.m_color;

			helper::color::vars::m_vars.m_callback = [] {
				global::vars::g_vfx_liquid[m_vars.m_selected].r = m_vars.m_color.r;
				global::vars::g_vfx_liquid[m_vars.m_selected].g = m_vars.m_color.g;
				global::vars::g_vfx_liquid[m_vars.m_selected].b = m_vars.m_color.b;
				global::vars::g_vfx_liquid[m_vars.m_selected].a = m_vars.m_color.a;
			};
		})
		.add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, &m_vars.m_color));

	add_option(button_option(get_string("Reset to Default"))
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click([] {
			memcpy(global::vars::g_vfx_liquid, &m_vars.m_backup, sizeof(m_vars.m_backup));
		}));
}

void fx_liquid_menu::feature_update() {}

fx_liquid_menu* g_instance;
fx_liquid_menu* fx_liquid_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_liquid_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}