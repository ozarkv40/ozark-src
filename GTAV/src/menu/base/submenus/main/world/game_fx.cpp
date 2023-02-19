#include "game_fx.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"
#include "util/memory/memory.h"
#include "fx/fx_sky.h"
#include "fx/fx_load.h"
#include "fx/fx_traffic.h"
#include "fx/fx_vehicle.h"
#include "fx/fx_vehicle_neons.h"
#include "fx/fx_puddles.h"
#include "fx/fx_cross_multiplier.h"
#include "fx/fx_liquid.h"

using namespace world::fx::vars;

namespace world::fx::vars {
	variables m_vars;
}

void game_fx_menu::load() {
	set_name("Game FX");
	set_parent<world_menu>();

	add_option(submenu_option("Save and Load")
		.add_translate().add_hotkey()
		.add_submenu<fx_load_menu>());

	add_option(submenu_option("Sky")
		.add_translate().add_hotkey()
		.add_submenu<fx_sky_menu>());

	add_option(submenu_option("Traffic Lights")
		.add_translate().add_hotkey()
		.add_submenu<fx_traffic_menu>());

	add_option(submenu_option("Vehicle")
		.add_translate().add_hotkey()
		.add_submenu<fx_vehicle_menu>());

	add_option(submenu_option("Vehicle Neons")
		.add_translate().add_hotkey()
		.add_submenu<fx_vehicle_neons_menu>());

	add_option(submenu_option("Puddles")
		.add_translate().add_hotkey()
		.add_submenu<fx_puddles_menu>());

	add_option(submenu_option("Cross Multiplier")
		.add_translate().add_hotkey()
		.add_submenu<fx_cross_multiplier_menu>());

	add_option(submenu_option("Liquid")
		.add_translate().add_hotkey()
		.add_submenu<fx_liquid_menu>());

	add_option(toggle_option("Disable Lights")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_lights)
		.add_click([] { native::set_blackout(false); }).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Enable Sky")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_sky).add_savable(get_submenu_name_stack())
		.add_click([] { *(bool*)((uint64_t)global::vars::g_ui_weather - 0x60) = m_vars.m_disable_sky; }));

	add_option(number_option<float>(TOGGLE, "Water on Map")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_water_toggle)
		.add_number(m_vars.m_water, "%.2f", 0.01f).add_min(0.f).add_max(100.f).set_scroll_speed(10).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Fog on Map")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_fog_toggle)
		.add_number(m_vars.m_fog, "%.4f", 0.0001f).add_min(0.f).add_max(10.f).set_scroll_speed(20).add_savable(get_submenu_name_stack()));
}

void game_fx_menu::update() {}

void game_fx_menu::update_once() {
	m_vars.m_fog = *(float*)global::vars::g_map_fog_intensity;
	m_vars.m_disable_sky = *(bool*)((uint64_t)global::vars::g_ui_weather - 0x60);
	m_vars.m_water = *(float*)global::vars::g_render_water_on_map_intensity;
}

void game_fx_menu::feature_update() {
	if (m_vars.m_disable_lights) {
		native::set_blackout(true);
	}

	if (m_vars.m_water_toggle) {
		*(float*)global::vars::g_render_water_on_map_intensity = m_vars.m_water;
	}
	
	if (m_vars.m_fog_toggle) {
		*(float*)global::vars::g_map_fog_intensity = m_vars.m_fog;
	}
}

game_fx_menu* g_instance;
game_fx_menu* game_fx_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new game_fx_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}