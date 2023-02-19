#include "world.h"
#include "menu/base/submenu_handler.h"
#include "menu/base/util/panels.h"
#include "util/memory/memory.h"
#include "../main.h"
#include "world/world_weather.h"
#include "world/world_time.h"
#include "world/bullet_tracers.h"
#include "world/world_waypoint.h"
#include "world/clear_area.h"
#include "world/ocean.h"
#include "world/game_fx.h"
#include "world/trains.h"
#include "world/local_entities.h"

using namespace world::vars;

namespace world::vars {
	variables m_vars;
}

void world_menu::load() {
	set_name("World");
	set_parent<main_menu>();

	add_option(submenu_option("Local Entities")
		.add_translate().add_hotkey()
		.add_submenu<local_entities_menu>());

	add_option(submenu_option("Game FX")
		.add_translate().add_hotkey()
		.add_submenu<game_fx_menu>());

	add_option(submenu_option("Weather")
		.add_translate().add_hotkey()
		.add_submenu<weather_menu>());

	add_option(submenu_option("Time")
		.add_translate().add_hotkey()
		.add_submenu<time_menu>());

	add_option(submenu_option("Bullet Tracers")
		.add_translate().add_hotkey()
		.add_submenu<bullet_tracers_menu>());

	add_option(submenu_option("World Waypoint")
		.add_translate().add_hotkey()
		.add_submenu<world_waypoint_menu>());

	add_option(submenu_option("Clear Area")
		.add_translate().add_hotkey()
		.add_submenu<clear_area_menu>());

	add_option(submenu_option("Ocean")
		.add_translate().add_hotkey()
		.add_submenu<ocean_menu>());

	add_option(submenu_option("Train")
		.add_translate().add_hotkey()
		.add_submenu<trains_menu>());
	
	add_option(button_option("Interior Refresh")
		.add_translate().add_hotkey()
		.add_click([] { native::refresh_interior(native::get_interior_from_entity(menu::player::get_local_player().m_ped)); }));
}

void world_menu::update() {}

void world_menu::update_once() {
	menu::panels::toggle_panel_render("PANEL_CLOCK", false);
}

void world_menu::feature_update() {
	if (m_vars.m_disable_lights) {
		native::set_blackout(true);
	}

	if (m_vars.m_render_water_on_map) {
		memory::write(global::vars::g_render_water_on_map_intensity, 1.0f);
	}
}

world_menu* g_instance;
world_menu* world_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new world_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
