#include "clear_area.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"

using namespace world::clear::vars;

namespace world::clear::vars {
	variables m_vars;
}

void clear_area_menu::load() {
	set_name("Clear Area");
	set_parent<world_menu>();

	add_option(number_option<float>(SCROLL, "Range")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_range, "%.0f", 1.f).set_scroll_speed(20).add_min(0.f));

	add_option(button_option("Clear Everything")
		.add_translate().add_hotkey()
		.add_click([] { native::clear_area(menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, m_vars.m_range, false, false, false, false); }));

	add_option(button_option("Clear Cops")
		.add_translate().add_hotkey()
		.add_click([] { native::clear_area_of_cops(menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, m_vars.m_range, 0); }));

	add_option(button_option("Clear Objects")
		.add_translate().add_hotkey()
		.add_click([] { native::clear_area_of_objects(menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, m_vars.m_range, 0); }));

	add_option(button_option("Clear Peds")
		.add_translate().add_hotkey()
		.add_click([] { native::clear_area_of_peds(menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, m_vars.m_range, 0); }));

	add_option(button_option("Clear Projectiles")
		.add_translate().add_hotkey()
		.add_click([] { native::clear_area_of_projectiles(menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, m_vars.m_range, 0); }));

	add_option(button_option("Clear Vehicles")
		.add_translate().add_hotkey()
		.add_click([] { native::clear_area_of_vehicles(menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, m_vars.m_range, false, false, false, false, false, 0); }));
}

void clear_area_menu::update() {
	native::draw_marker(28, menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, m_vars.m_range, m_vars.m_range, m_vars.m_range, global::ui::g_clear_area_range.r, global::ui::g_clear_area_range.g, global::ui::g_clear_area_range.b, global::ui::g_clear_area_range.a, 0, 0, 0, 0, 0, 0, 0);
}

void clear_area_menu::update_once() {}

void clear_area_menu::feature_update() {}

clear_area_menu* g_instance;
clear_area_menu* clear_area_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new clear_area_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}