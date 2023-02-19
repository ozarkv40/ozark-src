#include "appearance.h"
#include "menu/base/submenu_handler.h"
#include "../player.h"
#include "model.h"
#include "wardrobe.h"
#include "menu/base/util/panels.h"

void appearance_menu::load() {
	set_name("Appearance");
	set_parent<player_menu>();

	add_option(submenu_option("Model")
		.add_translate().add_hotkey()
		.add_submenu<model_menu>());

	add_option(submenu_option("Wardrobe")
		.add_translate().add_hotkey()
		.add_submenu<wardrobe_menu>()
		.add_click([] { wardrobe_menu::get()->set_parent<appearance_menu>(); }));
}

void appearance_menu::update() {}

void appearance_menu::update_once() {
	menu::panels::toggle_panel_render("PANEL_OUTFIT", false);
}

void appearance_menu::feature_update() {}

appearance_menu* g_instance;
appearance_menu* appearance_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new appearance_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
