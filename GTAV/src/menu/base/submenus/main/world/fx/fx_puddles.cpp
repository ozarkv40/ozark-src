#include "fx_puddles.h"
#include "menu/base/submenu_handler.h"
#include "../game_fx.h"

using namespace world::fx::puddles::vars;

namespace world::fx::puddles::vars {
	variables m_vars;
}

void fx_puddles_menu::load() {
	set_name("Puddles");
	set_parent<game_fx_menu>();

	if (!is_valid_ptr(global::vars::g_ui_puddle) || !is_valid_ptr(global::vars::g_ui_puddle->m_ripples)) {
		return;
	}

	memcpy(&m_vars.m_original, global::vars::g_ui_puddle, sizeof(rage::types::ui_puddle));
	memcpy(&m_vars.m_original_ripple, global::vars::g_ui_puddle->m_ripples, sizeof(rage::types::ui_puddle_ripple));

	add_option(number_option<float>(SCROLL, "Scale")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_scale, "%.3f", 0.005f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Range")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_range, "%.2f", 0.05f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Depth")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_depth, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Depth Test")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_depth_test, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Reflectivity")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_reflectivity, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Min Size")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_min_size, "%.3f", 0.005f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Max Size")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_max_size, "%.3f", 0.005f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Min Duration")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_min_duration, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Max Duration")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_max_duration, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Speed")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_speed, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Drop Factor")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_drop_factor, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Wind Strength")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_wind_strength, "%.2f", 0.05f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Strength")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_strength, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Player Speed")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_player_speed, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Player Map Size")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_player_map_size, "%.1f", 0.1f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, "Ripple Wind Damping")
		.add_translate()
		.add_number(global::vars::g_ui_puddle->m_ripples->m_ripple_wind_damping, "%.2f", 0.05f).add_min(-1000.f).add_max(1000.f).set_scroll_speed(0));

	add_option(button_option(get_string("Reset to Default"))
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click([] {
			memcpy(global::vars::g_ui_puddle, &m_vars.m_original, sizeof(rage::types::ui_puddle));
			memcpy(global::vars::g_ui_puddle->m_ripples, &m_vars.m_original_ripple, sizeof(rage::types::ui_puddle_ripple));
		}));
}

void fx_puddles_menu::update() {}

void fx_puddles_menu::update_once() {}

void fx_puddles_menu::feature_update() {}

fx_puddles_menu* g_instance;
fx_puddles_menu* fx_puddles_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_puddles_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}