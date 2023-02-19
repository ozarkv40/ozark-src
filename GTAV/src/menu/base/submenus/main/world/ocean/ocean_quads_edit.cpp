#include "ocean_quads_edit.h"
#include "menu/base/submenu_handler.h"
#include "ocean_quads.h"

using namespace world::ocean::quads::edit::vars;

namespace world::ocean::quads::edit::vars {
	variables m_vars;
}

void ocean_quads_edit_menu::load() {
	set_name("Ocean Quads");
	set_parent<ocean_quads_menu>();

	add_string("Minimum - X");
	add_string("Minimum - Y");
	add_string("Maximum - X");
	add_string("Maximum - Y");
	add_string("Height");
	add_string("Clear");
	add_string("Dampening");
	add_string("Amplitude");
	add_string("Direction - X");
	add_string("Direction - Y");
}

void ocean_quads_edit_menu::update() {
	world::ocean::quads::vars::quad_esp();
}

void ocean_quads_edit_menu::update_once() {
	clear_options(0);

	m_vars.m_calming = (rage::types::ocean_calming_quad*)world::ocean::quads::vars::m_vars.m_closest_quad;
	m_vars.m_wave = (rage::types::ocean_wave_quad*)world::ocean::quads::vars::m_vars.m_closest_quad;
	m_vars.m_ocean = (rage::types::ocean_quad*)world::ocean::quads::vars::m_vars.m_closest_quad;

	add_option(number_option<short>(SCROLL, get_string("Minimum - X"))
		.add_number(m_vars.m_ocean->m_min.x, "%i", 1)
		.add_min(std::numeric_limits<short>::min())
		.add_max(std::numeric_limits<short>::max()).set_scroll_speed(10));

	add_option(number_option<short>(SCROLL, get_string("Minimum - Y"))
		.add_number(m_vars.m_ocean->m_min.y, "%i", 1)
		.add_min(std::numeric_limits<short>::min())
		.add_max(std::numeric_limits<short>::max()).set_scroll_speed(10));

	add_option(number_option<short>(SCROLL, get_string("Maximum - X"))
		.add_number(m_vars.m_ocean->m_max.x, "%i", 1)
		.add_min(std::numeric_limits<short>::min())
		.add_max(std::numeric_limits<short>::max()).set_scroll_speed(10));

	add_option(number_option<short>(SCROLL, get_string("Maximum - Y"))
		.add_number(m_vars.m_ocean->m_max.y, "%i", 1)
		.add_min(std::numeric_limits<short>::min())
		.add_max(std::numeric_limits<short>::max()).set_scroll_speed(10));

	/* Ocean */
	if (world::ocean::quads::vars::m_vars.m_type == 0) {
		add_option(number_option<float>(SCROLL, get_string("Height"))
			.add_number(m_vars.m_ocean->m_height, "%.0f", 1.f)
			.add_min(-10000.f).add_max(10000.f).set_scroll_speed(10));

		m_vars.m_clear = m_vars.m_ocean->m_alpha != 0x1A1A1A1A;

		add_option(toggle_option(get_string("Clear"))
			.add_toggle(m_vars.m_clear)
			.add_click([] { m_vars.m_ocean->m_alpha = m_vars.m_clear ? 0x01010101 : 0x1A1A1A1A; }));
		return;
	}

	/* Calming */
	if (world::ocean::quads::vars::m_vars.m_type == 1) {
		add_option(number_option<float>(SCROLL, get_string("Dampening"))
			.add_number(m_vars.m_calming->m_dampening, "%.1f", 0.1f).add_min(0.f).add_max(10000.f).set_scroll_speed(10));
		return;
	}

	/* Wave */
	if (world::ocean::quads::vars::m_vars.m_type == 2) {
		add_option(number_option<short>(SCROLL, get_string("Amplitude"))
			.add_number(m_vars.m_wave->m_amplitude, "%i", 1).add_min(0).add_max(10000).set_scroll_speed(10));

		add_option(number_option<uint8_t>(SCROLL, get_string("Direction - X"))
			.add_number(m_vars.m_wave->m_direction.x, "%i", 1).add_min(0).add_max(255));

		add_option(number_option<uint8_t>(SCROLL, get_string("Direction - Y"))
			.add_number(m_vars.m_wave->m_direction.y, "%i", 1).add_min(0).add_max(255));
	}
}

void ocean_quads_edit_menu::feature_update() {}

ocean_quads_edit_menu* g_instance;
ocean_quads_edit_menu* ocean_quads_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new ocean_quads_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}