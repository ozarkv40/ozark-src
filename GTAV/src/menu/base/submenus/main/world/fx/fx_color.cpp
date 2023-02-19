#include "fx_color.h"
#include "menu/base/submenu_handler.h"
#include "menu/base/util/instructionals.h"
#include "../../helper/helper_color.h"
#include "../../helper/helper_rainbow.h"

using namespace world::fx::color::vars;

namespace world::fx::color::vars {
	variables m_vars;

	void reset() {
		if (m_vars.m_color != nullptr) {
			m_vars.m_color->m_rainbow_toggle = false;
			m_vars.m_color->m_rainbow.stop();

			m_vars.m_selected_color->x = m_vars.m_color->m_default_color.x;
			m_vars.m_selected_color->y = m_vars.m_color->m_default_color.y;
			m_vars.m_selected_color->z = m_vars.m_color->m_default_color.z;

			m_vars.m_color->m_internal_color.r = (int)(m_vars.m_color->m_default_color.x * 255.f);
			m_vars.m_color->m_internal_color.g = (int)(m_vars.m_color->m_default_color.y * 255.f);
			m_vars.m_color->m_internal_color.b = (int)(m_vars.m_color->m_default_color.z * 255.f);
		} else {
			m_vars.m_color2->m_rainbow_toggle = false;
			m_vars.m_color2->m_rainbow.stop();
			memcpy(m_vars.m_color2->m_color, &m_vars.m_color2->m_default_color, sizeof(rage::types::ui_element_color_struct));

			m_vars.m_color2->m_internal_color.r = (int)(m_vars.m_color2->m_color->m_color.x * 255.f);
			m_vars.m_color2->m_internal_color.g = (int)(m_vars.m_color2->m_color->m_color.y * 255.f);
			m_vars.m_color2->m_internal_color.b = (int)(m_vars.m_color2->m_color->m_color.z * 255.f);
		}
	}
}

void fx_color_menu::load() {
	set_name("Color");
	set_default_instructionals(false);

	add_string("Edit Color");
	add_string("Toggle Rainbow");
	add_string("Reset to Default");
}

void fx_color_menu::update() {}

void fx_color_menu::update_once() {
	clear_options(0);

	static color_rgba* internal_color = nullptr;

	if (m_vars.m_color != nullptr) {
		m_vars.m_selected_color = m_vars.m_color->m_color;
		internal_color = &m_vars.m_color->m_internal_color;
	} else {
		m_vars.m_selected_color = &m_vars.m_color2->m_color->m_color;
		internal_color = &m_vars.m_color2->m_internal_color;
	}

	internal_color->r = (int)(m_vars.m_selected_color->x * 255.f);
	internal_color->g = (int)(m_vars.m_selected_color->y * 255.f);
	internal_color->b = (int)(m_vars.m_selected_color->z * 255.f);
	internal_color->a = 255;

	add_option(submenu_option(get_string("Edit Color"))
		.add_submenu<helper_color_menu>()
		.add_click([=] {
			helper_color_menu::get()->set_name(get_name().get(), false, false);
			helper_color_menu::get()->set_parent<fx_color_menu>();
			helper::color::vars::m_vars.m_color = internal_color;

			helper::color::vars::m_vars.m_callback = [] {
				m_vars.m_selected_color->x = internal_color->r / 255.f;
				m_vars.m_selected_color->y = internal_color->g / 255.f;
				m_vars.m_selected_color->z = internal_color->b / 255.f;
			};
		})
		.add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, internal_color));

	add_option(toggle_option(get_string("Toggle Rainbow"))
		.add_toggle(m_vars.m_color != nullptr ? m_vars.m_color->m_rainbow_toggle : m_vars.m_color2->m_rainbow_toggle)
		.add_click([] {
			if (m_vars.m_color != nullptr) {
				m_vars.m_color->m_rainbow.toggle(m_vars.m_color->m_rainbow_toggle);
				if (m_vars.m_color->m_rainbow_toggle) {
					m_vars.m_color->m_rainbow.add(internal_color);
				} else {
					m_vars.m_color->m_rainbow.remove(internal_color);
				}
			} else {
				m_vars.m_color2->m_rainbow.toggle(m_vars.m_color2->m_rainbow_toggle);
				if (m_vars.m_color2->m_rainbow_toggle) {
					m_vars.m_color2->m_rainbow.add(internal_color);
				} else {
					m_vars.m_color2->m_rainbow.remove(internal_color);
				}
			}
		}));

	add_option(button_option(get_string("Reset to Default"))
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click(reset));
}

void fx_color_menu::feature_update() {}

fx_color_menu* g_instance;
fx_color_menu* fx_color_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_color_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}