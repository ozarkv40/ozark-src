#include "fx_ui_color.h"
#include "menu/base/submenu_handler.h"
#include "fx_color.h"

using namespace world::fx::ui::color::vars;

namespace world::fx::ui::color::vars {
	variables m_vars;
}

void fx_ui_color_menu::load() {
	set_name("Color");

	add_string("Edit Color");
	add_string("Intensity");
	add_string("Radius");
	add_string("Falloff Exponent");
	add_string("Inner Cone Angle");
	add_string("Outer Cone Angle");
	add_string("Corona HDR");
	add_string("Corona Size");
	add_string("Shadow Blur");
	add_string("Capsule Length");
	add_string("Save to Config");
	add_string("Reset to Default");
}

void fx_ui_color_menu::update() {}

void fx_ui_color_menu::update_once() {
	clear_options(0);

	add_option(submenu_option(get_string("Edit Color"))
		.add_translate()
		.add_submenu<fx_color_menu>()
		.add_click([] {
			fx_color_menu::get()->set_parent<fx_ui_color_menu>();
			world::fx::color::vars::m_vars.m_color = nullptr;
			world::fx::color::vars::m_vars.m_color2 = m_vars.m_color;
		}));

	add_option(number_option<float>(SCROLL, get_string("Intensity"))
		.add_number(m_vars.m_color->m_color->m_intensity, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, get_string("Radius"))
		.add_number(m_vars.m_color->m_color->m_radius, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, get_string("Falloff Exponent"))
		.add_number(m_vars.m_color->m_color->m_falloff_exp, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, get_string("Inner Cone Angle"))
		.add_number(m_vars.m_color->m_color->m_inner_cone_angle, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, get_string("Outer Cone Angle"))
		.add_number(m_vars.m_color->m_color->m_outer_cone_angle, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, get_string("Corona HDR"))
		.add_number(m_vars.m_color->m_color->m_corona_hdr, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, get_string("Corona Size"))
		.add_number(m_vars.m_color->m_color->m_corona_size, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, get_string("Shadow Blur"))
		.add_number(m_vars.m_color->m_color->m_shadow_blur, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(number_option<float>(SCROLL, get_string("Capsule Length"))
		.add_number(m_vars.m_color->m_color->m_capsule_length, "%.2f", 0.05f).add_min(-100.f).add_max(10000.f).set_scroll_speed(0));

	add_option(button_option(get_string("Reset to Default"))
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click([] {
			m_vars.m_color->m_rainbow_toggle = false;
			m_vars.m_color->m_rainbow.stop();

			memcpy(m_vars.m_color->m_color, &m_vars.m_color->m_default_color, sizeof(rage::types::ui_element_color_struct));
		}));
}

void fx_ui_color_menu::feature_update() {}

fx_ui_color_menu* g_instance;
fx_ui_color_menu* fx_ui_color_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_ui_color_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}