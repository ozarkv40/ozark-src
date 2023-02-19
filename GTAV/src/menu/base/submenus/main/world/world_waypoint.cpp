#include "world_waypoint.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"
#include "global/lists.h"
#include "../helper/helper_color.h"

using namespace world::waypoint::vars;

namespace world::waypoint::vars {
	variables m_vars;
}

void world_waypoint_menu::load() {
	set_name("World Waypoint");
	set_parent<world_menu>();

	add_option(toggle_option("Toggle World Waypoint")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle));

	add_option(scroll_option<int>(SCROLL, "Marker")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_marker, 0, NUMOF(global::lists::g_markers), global::lists::g_markers));

	add_option(number_option<int>(SCROLL, "Max Markers")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_max, "%i", 1).add_min(1).add_max(50));

	add_option(number_option<float>(SCROLL, "Marker Scale")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_scale, "%.2f", 0.01f).add_min(0.f).add_max(10.f).set_scroll_speed(10));

	add_option(submenu_option("Edit Color")
		.add_translate()
		.add_submenu<helper_color_menu>()
		.add_click([this] {
			helper_color_menu::get()->set_name(get_name().get(), false, false);
			helper_color_menu::get()->set_parent<world_waypoint_menu>();
			helper::color::vars::m_vars.m_color = &m_vars.m_color;
			helper::color::vars::m_vars.m_callback = [] {};
		})
		.add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, &m_vars.m_color));
}

void world_waypoint_menu::update() {}

void world_waypoint_menu::update_once() {}

void world_waypoint_menu::feature_update() {
	if (m_vars.m_toggle) {
		if (global::vars::g_waypoint_data) {
			if (global::vars::g_waypoint_data->m_points && global::vars::g_waypoint_data->m_count) {
				for (uint32_t i = 0; i < global::vars::g_waypoint_data->m_count; i++) {
					if (i >= (uint32_t)m_vars.m_max) break;

					math::vector4<float> point = global::vars::g_waypoint_data->m_points[i];
					native::draw_marker(m_vars.m_marker, point.x, point.y, point.z + m_vars.m_scale, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, m_vars.m_scale, m_vars.m_scale, m_vars.m_scale, m_vars.m_color.r, m_vars.m_color.g, m_vars.m_color.b, m_vars.m_color.a, 0, 0, 0, 0, 0, 0, 0);
				}
			}
		}
	}
}

world_waypoint_menu* g_instance;
world_waypoint_menu* world_waypoint_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new world_waypoint_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}