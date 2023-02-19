#include "particles.h"
#include "menu/base/submenu_handler.h"
#include "../player.h"
#include "ptfx/particle_manager.h"
#include "ptfx/hand_trails.h"

void particle_menu::load() {
	set_name("Particle FX");
	set_parent<player_menu>();

	add_option(submenu_option("Particle Manager")
		.add_translate().add_hotkey()
		.add_submenu<particle_manager_menu>());

	add_option(submenu_option("Hand Trails")
		.add_translate().add_hotkey()
		.add_submenu<hand_trails_menu>());
}

void particle_menu::update() {}

void particle_menu::update_once() {}

void particle_menu::feature_update() {}

particle_menu* g_instance;
particle_menu* particle_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new particle_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}