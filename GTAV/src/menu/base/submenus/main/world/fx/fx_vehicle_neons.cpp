#include "fx_vehicle_neons.h"
#include "menu/base/submenu_handler.h"
#include "../game_fx.h"
#include "util/memory/memory.h"

using namespace world::fx::vehicle::neons::vars;

namespace world::fx::vehicle::neons::vars {
	variables m_vars;
}

void fx_vehicle_neons_menu::load() {
	set_name("Vehicle Neons");
	set_parent<game_fx_menu>();

	m_vars.m_intensity = (float*)(memory::read_instruction(global::vars::g_set_vehicle_neon_ui + 0x35, 4, 8));
	m_vars.m_radius = (float*)(memory::read_instruction(global::vars::g_set_vehicle_neon_ui + 0x57, 4, 8));
	m_vars.m_fall_off_exponent = (float*)(memory::read_instruction(global::vars::g_set_vehicle_neon_ui + 0x79, 4, 8));
	m_vars.m_capsule_extent_sides = (float*)(memory::read_instruction(global::vars::g_set_vehicle_neon_ui + 0x9B, 4, 8));
	m_vars.m_capsule_extent_front_back = (float*)(memory::read_instruction(global::vars::g_set_vehicle_neon_ui + 0xBD, 4, 8));
	m_vars.m_clip_plane_height = (float*)(memory::read_instruction(global::vars::g_set_vehicle_neon_ui + 0xDF, 4, 8));
	m_vars.m_bike_clip_plane_height = (float*)(memory::read_instruction(global::vars::g_set_vehicle_neon_ui + 0xFB, 4, 8));

	m_vars.m_backup_intensity = *m_vars.m_intensity;
	m_vars.m_backup_radius = *m_vars.m_radius;
	m_vars.m_backup_fall_off_exponent = *m_vars.m_fall_off_exponent;
	m_vars.m_backup_capsule_extent_sides = *m_vars.m_capsule_extent_sides;
	m_vars.m_backup_capsule_extent_front_back = *m_vars.m_capsule_extent_front_back;
	m_vars.m_backup_clip_plane_height = *m_vars.m_clip_plane_height;
	m_vars.m_backup_bike_clip_plane_height = *m_vars.m_bike_clip_plane_height;

	add_option(number_option<float>(SCROLL, "Intensity")
		.add_translate()
		.add_number(*m_vars.m_intensity, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Radius")
		.add_translate()
		.add_number(*m_vars.m_radius, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Falloff Exponent")
		.add_translate()
		.add_number(*m_vars.m_fall_off_exponent, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Capsule Extent Sides")
		.add_translate()
		.add_number(*m_vars.m_capsule_extent_sides, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Capsule Extent Front Back")
		.add_translate()
		.add_number(*m_vars.m_capsule_extent_front_back, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Clip Plane Height")
		.add_translate()
		.add_number(*m_vars.m_clip_plane_height, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Bike Clip Plane Height")
		.add_translate()
		.add_number(*m_vars.m_bike_clip_plane_height, "%.2f", 0.01f).set_scroll_speed(10));

	add_option(button_option(get_string("Reset to Default"))
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click([=] {
			*m_vars.m_intensity = m_vars.m_backup_intensity;
			*m_vars.m_radius = m_vars.m_backup_radius;
			*m_vars.m_fall_off_exponent = m_vars.m_backup_fall_off_exponent;
			*m_vars.m_capsule_extent_sides = m_vars.m_backup_capsule_extent_sides;
			*m_vars.m_capsule_extent_front_back = m_vars.m_backup_capsule_extent_front_back;
			*m_vars.m_clip_plane_height = m_vars.m_backup_clip_plane_height;
			*m_vars.m_bike_clip_plane_height = m_vars.m_backup_bike_clip_plane_height;
		}));
}

void fx_vehicle_neons_menu::update() {}

void fx_vehicle_neons_menu::update_once() {}

void fx_vehicle_neons_menu::feature_update() {}

fx_vehicle_neons_menu* g_instance;
fx_vehicle_neons_menu* fx_vehicle_neons_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_vehicle_neons_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}