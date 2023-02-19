#include "misc_swaps.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"
#include "swaps/model_swaps.h"
#include "swaps/texture_swaps.h"

using namespace misc::swaps::vars;

namespace misc::swaps::vars {
	variables m_vars;
}

void misc_swaps_menu::load() {
	set_name("Swaps");
	set_parent<misc_menu>();

	add_option(submenu_option("Model Swaps")
		.add_translate().add_hotkey()
		.add_submenu<model_swaps_menu>());

	add_option(submenu_option("Texture Swaps")
		.add_translate().add_hotkey()
		.add_submenu<texture_swaps_menu>());
}

void misc_swaps_menu::update() {}

void misc_swaps_menu::update_once() {}

void misc_swaps_menu::feature_update() {}

misc_swaps_menu* g_instance;
misc_swaps_menu* misc_swaps_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new misc_swaps_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}