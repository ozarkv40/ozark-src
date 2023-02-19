#include "fx_traffic.h"
#include "menu/base/submenu_handler.h"
#include "../game_fx.h"
#include "util/memory/memory.h"

using namespace world::fx::traffic::vars;

namespace world::fx::traffic::vars {
	variables m_vars;
}

void fx_traffic_menu::load() {
	set_name("Traffic Lights");
	set_parent<game_fx_menu>();

	m_vars.m_far_fade_start = (float*)memory::read_instruction(global::vars::g_update_traffic_lights + 0x149, 4, 8);
	m_vars.m_far_fade_end = (float*)memory::read_instruction(global::vars::g_update_traffic_lights + 0x13D, 4, 8);
	m_vars.m_near_fade_start = (float*)memory::read_instruction(global::vars::g_update_traffic_lights + 0x187, 4, 8);
	m_vars.m_near_fade_end = (float*)memory::read_instruction(global::vars::g_update_traffic_lights + 0x17C, 4, 8);

	m_vars.m_near_color.m_color = (rage::types::ui_element_color_struct*)memory::read_instruction(global::vars::g_set_traffic_lights + 0x28, 3, 7);
	m_vars.m_red_color.m_color = (math::vector3_<float>*)memory::read_instruction(global::vars::g_set_traffic_light_colors + 0x63, 3, 7);
	m_vars.m_green_color.m_color = (math::vector3_<float>*)memory::read_instruction(global::vars::g_set_traffic_light_colors + 0xBD, 3, 7);
	m_vars.m_amber_color.m_color = (math::vector3_<float>*)memory::read_instruction(global::vars::g_set_traffic_light_colors + 0x8D, 3, 7);
	m_vars.m_walk_color.m_color = (math::vector3_<float>*)memory::read_instruction(global::vars::g_set_traffic_lights + 0x13F, 3, 7);
	m_vars.m_dont_walk_color.m_color = (math::vector3_<float>*)memory::read_instruction(global::vars::g_set_traffic_lights + 0x14E, 3, 7);

	m_vars.m_near_color.m_default_color = *m_vars.m_near_color.m_color;
	m_vars.m_red_color.m_default_color = *m_vars.m_red_color.m_color;
	m_vars.m_green_color.m_default_color = *m_vars.m_green_color.m_color;
	m_vars.m_amber_color.m_default_color = *m_vars.m_amber_color.m_color;
	m_vars.m_walk_color.m_default_color = *m_vars.m_walk_color.m_color;
	m_vars.m_dont_walk_color.m_default_color = *m_vars.m_dont_walk_color.m_color;

	add_option(submenu_option("Near Color")
		.add_translate()
		.add_submenu<fx_ui_color_menu>()
		.add_click([] {
			world::fx::ui::color::vars::m_vars.m_color = &m_vars.m_near_color;
			fx_ui_color_menu::get()->set_parent<fx_traffic_menu>();
		}));

	add_option(submenu_option("Red Color")
		.add_translate()
		.add_submenu<fx_color_menu>()
		.add_click([] {
			fx_color_menu::get()->set_parent<fx_traffic_menu>();
			world::fx::color::vars::m_vars.m_color = &m_vars.m_red_color;
		}));

	add_option(submenu_option("Amber Color")
		.add_translate()
		.add_submenu<fx_color_menu>()
		.add_click([] {
			fx_color_menu::get()->set_parent<fx_traffic_menu>();
			world::fx::color::vars::m_vars.m_color = &m_vars.m_amber_color;
		}));

	add_option(submenu_option("Green Color")
		.add_translate()
		.add_submenu<fx_color_menu>()
		.add_click([] {
			fx_color_menu::get()->set_parent<fx_traffic_menu>();
			world::fx::color::vars::m_vars.m_color = &m_vars.m_green_color;
		}));

	add_option(submenu_option("Walk Color")
		.add_translate()
		.add_submenu<fx_color_menu>()
		.add_click([] {
			fx_color_menu::get()->set_parent<fx_traffic_menu>();
			world::fx::color::vars::m_vars.m_color = &m_vars.m_walk_color;
		}));

	add_option(submenu_option("Don't Walk Color")
		.add_translate()
		.add_submenu<fx_color_menu>()
		.add_click([] {
			fx_color_menu::get()->set_parent<fx_traffic_menu>();
			world::fx::color::vars::m_vars.m_color = &m_vars.m_dont_walk_color;
		}));

	add_option(number_option<float>(SCROLL, "Far Fade Start")
		.add_translate()
		.add_number(*m_vars.m_far_fade_start, "%.0f", 1.f).add_min(-100.f).add_max(1000000.f));

	add_option(number_option<float>(SCROLL, "Far Fade End")
		.add_translate()
		.add_number(*m_vars.m_far_fade_end, "%.0f", 1.f).add_min(-100.f).add_max(1000000.f));

	add_option(number_option<float>(SCROLL, "Near Fade Start")
		.add_translate()
		.add_number(*m_vars.m_near_fade_start, "%.0f", 1.f).add_min(-100.f).add_max(1000000.f));

	add_option(number_option<float>(SCROLL, "Near Fade End")
		.add_translate()
		.add_number(*m_vars.m_near_fade_end, "%.0f", 1.f).add_min(-100.f).add_max(1000000.f));
}

void fx_traffic_menu::update() {}

void fx_traffic_menu::update_once() {}

void fx_traffic_menu::feature_update() {
	world::fx::color::vars::custom_color* list[] = {
		&m_vars.m_red_color,
		&m_vars.m_green_color,
		&m_vars.m_amber_color,
		&m_vars.m_walk_color,
		&m_vars.m_dont_walk_color
	};

	for (world::fx::color::vars::custom_color* l : list) {
		if (l->m_rainbow_toggle) {
			l->m_rainbow.run();
			l->m_color->x = l->m_internal_color.r / 255.f;
			l->m_color->y = l->m_internal_color.g / 255.f;
			l->m_color->z = l->m_internal_color.b / 255.f;
		}
	}

	if (m_vars.m_near_color.m_rainbow_toggle) {
		m_vars.m_near_color.m_rainbow.run();
		m_vars.m_near_color.m_color->m_color.x = m_vars.m_near_color.m_internal_color.r / 255.f;
		m_vars.m_near_color.m_color->m_color.y = m_vars.m_near_color.m_internal_color.g / 255.f;
		m_vars.m_near_color.m_color->m_color.z = m_vars.m_near_color.m_internal_color.b / 255.f;
	}
}

fx_traffic_menu* g_instance;
fx_traffic_menu* fx_traffic_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_traffic_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}