#include "animation.h"
#include "menu/base/submenu_handler.h"
#include "../player.h"
#include "animation/animations.h"
#include "animation/clipsets.h"
#include "animation/scenario.h"

void animation_menu::load() {
	set_name("Animation");
	set_parent<player_menu>();

	add_option(submenu_option("Animations")
		.add_translate().add_hotkey()
		.add_submenu<animations_menu>());

	add_option(submenu_option("Scenarios")
		.add_translate().add_hotkey()
		.add_submenu<scenario_menu>());

	add_option(submenu_option("Clipsets")
		.add_translate().add_hotkey()
		.add_submenu<clipset_menu>());
}

void animation_menu::update() {}

void animation_menu::update_once() {}

void animation_menu::feature_update() {}

animation_menu* g_instance;
animation_menu* animation_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new animation_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}