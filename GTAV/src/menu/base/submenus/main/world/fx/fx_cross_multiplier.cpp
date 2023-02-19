#include "fx_cross_multiplier.h"
#include "menu/base/submenu_handler.h"
#include "../game_fx.h"

using namespace world::fx::cross::vars;

namespace world::fx::cross::vars {
	variables m_vars;
}

void fx_cross_multiplier_menu::load() {
	set_name("Cross Multiplier");
	set_parent<game_fx_menu>();

	memcpy(&m_vars.m_rim_light, &global::vars::g_ui_visual_settings->m_rim_light, sizeof(variables));

	add_option(number_option<float>(SCROLL, "Rim Light")
		.add_translate()
		.add_number(global::vars::g_ui_visual_settings->m_rim_light, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Global Environment Reflection")
		.add_translate()
		.add_number(global::vars::g_ui_visual_settings->m_global_environment_reflection, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Gamma")
		.add_translate()
		.add_number(global::vars::g_ui_visual_settings->m_gamma, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Mid Blur")
		.add_translate()
		.add_number(global::vars::g_ui_visual_settings->m_mid_blur, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Far Blur")
		.add_translate()
		.add_number(global::vars::g_ui_visual_settings->m_far_blur, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Sky Multiplier")
		.add_translate()
		.add_number(global::vars::g_ui_visual_settings->m_sky_multiplier, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Desaturation")
		.add_translate()
		.add_number(global::vars::g_ui_visual_settings->m_desaturation, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(button_option(get_string("Reset to Default"))
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click([] {
			memcpy(&global::vars::g_ui_visual_settings->m_rim_light, &m_vars.m_rim_light, sizeof(variables));
		}));
}

void fx_cross_multiplier_menu::update() {}

void fx_cross_multiplier_menu::update_once() {}

void fx_cross_multiplier_menu::feature_update() {}

fx_cross_multiplier_menu* g_instance;
fx_cross_multiplier_menu* fx_cross_multiplier_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_cross_multiplier_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}