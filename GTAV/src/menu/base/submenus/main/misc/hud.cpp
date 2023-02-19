#include "hud.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"
#include "../helper/helper_color.h"

using namespace misc::hud::vars;

namespace misc::hud::vars {
	variables m_vars;

	scroll_struct<int> hud_color_labels[] = {
		{ localization("Pure White", true), 0 },
		{ localization("White", true), 0 },
		{ localization("Black", true), 0 },
		{ localization("Grey", true), 0 },
		{ localization("Grey Light", true), 0 },
		{ localization("Grey Dark", true), 0 },
		{ localization("Red", true), 0 },
		{ localization("Red Light", true), 0 },
		{ localization("Red Dark", true), 0 },
		{ localization("Blue", true), 0 },
		{ localization("Blue Light", true), 0 },
		{ localization("Blue Dark", true), 0 },
		{ localization("Yellow", true), 0 },
		{ localization("Yellow Light", true), 0 },
		{ localization("Yellow Dark", true), 0 },
		{ localization("Orange", true), 0 },
		{ localization("Orange Light", true), 0 },
		{ localization("Orange Dark", true), 0 },
		{ localization("Green", true), 0 },
		{ localization("Green Light", true), 0 },
		{ localization("Green Dark", true), 0 },
		{ localization("Purple", true), 0 },
		{ localization("Purple Light", true), 0 },
		{ localization("Purple Dark", true), 0 },
		{ localization("Pink", true), 0 },
		{ localization("Radar Health", true), 0 },
		{ localization("Radar Armour", true), 0 },
		{ localization("Radar Damage", true), 0 },
		{ localization("Player 1", true), 0 },
		{ localization("Player 2", true), 0 },
		{ localization("Player 3", true), 0 },
		{ localization("Player 4", true), 0 },
		{ localization("Player 5", true), 0 },
		{ localization("Player 6", true), 0 },
		{ localization("Player 7", true), 0 },
		{ localization("Player 8", true), 0 },
		{ localization("Player 9", true), 0 },
		{ localization("Player 10", true), 0 },
		{ localization("Player 11", true), 0 },
		{ localization("Player 12", true), 0 },
		{ localization("Player 13", true), 0 },
		{ localization("Player 14", true), 0 },
		{ localization("Player 15", true), 0 },
		{ localization("Player 16", true), 0 },
		{ localization("Player 17", true), 0 },
		{ localization("Player 18", true), 0 },
		{ localization("Player 19", true), 0 },
		{ localization("Player 20", true), 0 },
		{ localization("Player 21", true), 0 },
		{ localization("Player 22", true), 0 },
		{ localization("Player 23", true), 0 },
		{ localization("Player 24", true), 0 },
		{ localization("Player 25", true), 0 },
		{ localization("Player 26", true), 0 },
		{ localization("Player 27", true), 0 },
		{ localization("Player 28", true), 0 },
		{ localization("Player 29", true), 0 },
		{ localization("Player 30", true), 0 },
		{ localization("Player 31", true), 0 },
		{ localization("Player 32", true), 0 },
		{ localization("Simple Blip Default", true), 0 },
		{ localization("Menu Blue", true), 0 },
		{ localization("Menu Grey Light", true), 0 },
		{ localization("Menu Blue Extra Dark", true), 0 },
		{ localization("Menu Yellow", true), 0 },
		{ localization("Menu Yellow Dark", true), 0 },
		{ localization("Menu Green", true), 0 },
		{ localization("Menu Grey", true), 0 },
		{ localization("Menu Grey Dark", true), 0 },
		{ localization("Menu Highlight", true), 0 },
		{ localization("Menu Standard", true), 0 },
		{ localization("Menu Dimmed", true), 0 },
		{ localization("Menu Extra Dimmed", true), 0 },
		{ localization("Brief Title", true), 0 },
		{ localization("Mid Grey MP", true), 0 },
		{ localization("Player 1 Dark", true), 0 },
		{ localization("Player 2 Dark", true), 0 },
		{ localization("Player 3 Dark", true), 0 },
		{ localization("Player 4 Dark", true), 0 },
		{ localization("Player 5 Dark", true), 0 },
		{ localization("Player 6 Dark", true), 0 },
		{ localization("Player 7 Dark", true), 0 },
		{ localization("Player 8 Dark", true), 0 },
		{ localization("Player 9 Dark", true), 0 },
		{ localization("Player 10 Dark", true), 0 },
		{ localization("Player 11 Dark", true), 0 },
		{ localization("Player 12 Dark", true), 0 },
		{ localization("Player 13 Dark", true), 0 },
		{ localization("Player 14 Dark", true), 0 },
		{ localization("Player 15 Dark", true), 0 },
		{ localization("Player 16 Dark", true), 0 },
		{ localization("Player 17 Dark", true), 0 },
		{ localization("Player 18 Dark", true), 0 },
		{ localization("Player 19 Dark", true), 0 },
		{ localization("Player 20 Dark", true), 0 },
		{ localization("Player 21 Dark", true), 0 },
		{ localization("Player 22 Dark", true), 0 },
		{ localization("Player 23 Dark", true), 0 },
		{ localization("Player 24 Dark", true), 0 },
		{ localization("Player 25 Dark", true), 0 },
		{ localization("Player 26 Dark", true), 0 },
		{ localization("Player 27 Dark", true), 0 },
		{ localization("Player 28 Dark", true), 0 },
		{ localization("Player 29 Dark", true), 0 },
		{ localization("Player 30 Dark", true), 0 },
		{ localization("Player 31 Dark", true), 0 },
		{ localization("Player 32 Dark", true), 0 },
		{ localization("Bronze", true), 0 },
		{ localization("Silver", true), 0 },
		{ localization("Gold", true), 0 },
		{ localization("Platinum", true), 0 },
		{ localization("Gang 1", true), 0 },
		{ localization("Gang 2", true), 0 },
		{ localization("Gang 3", true), 0 },
		{ localization("Gang 4", true), 0 },
		{ localization("Same Crew", true), 0 },
		{ localization("Freemode", true), 0 },
		{ localization("Pause BG", true), 0 },
		{ localization("Friendly", true), 0 },
		{ localization("Enemy", true), 0 },
		{ localization("Location", true), 0 },
		{ localization("Pickup", true), 0 },
		{ localization("Pause Singleplayer", true), 0 },
		{ localization("Freemode Dark", true), 0 },
		{ localization("Inactive Mission", true), 0 },
		{ localization("Damage", true), 0 },
		{ localization("Pink Light", true), 0 },
		{ localization("PM Item Highlight", true), 0 },
		{ localization("Script Variable", true), 0 },
		{ localization("Yoga", true), 0 },
		{ localization("Tennis", true), 0 },
		{ localization("Golf", true), 0 },
		{ localization("Shooting Range", true), 0 },
		{ localization("Flight School", true), 0 },
		{ localization("North Blue", true), 0 },
		{ localization("Social Club", true), 0 },
		{ localization("Platform Blue", true), 0 },
		{ localization("Platform Green", true), 0 },
		{ localization("Platform Grey", true), 0 },
		{ localization("Facebook Blue", true), 0 },
		{ localization("In-Game BG", true), 0 },
		{ localization("Darts", true), 0 },
		{ localization("Waypoint", true), 0 },
		{ localization("Michael", true), 0 },
		{ localization("Franklin", true), 0 },
		{ localization("Trevor", true), 0 },
		{ localization("Golf P1", true), 0 },
		{ localization("Golf P2", true), 0 },
		{ localization("Golf P3", true), 0 },
		{ localization("Golf P4", true), 0 },
		{ localization("Waypoint Light", true), 0 },
		{ localization("Waypoint Dark", true), 0 },
		{ localization("panel Light", true), 0 },
		{ localization("Michael Dark", true), 0 },
		{ localization("Franklin Dark", true), 0 },
		{ localization("Trevor Dark", true), 0 },
		{ localization("Objective Route", true), 0 },
		{ localization("Pause Map Tint", true), 0 },
		{ localization("Pause Deselect", true), 0 },
		{ localization("PM Weapons Purchasable", true), 0 },
		{ localization("PM Weapons Locked", true), 0 },
		{ localization("End Screen BG", true), 0 },
		{ localization("Chop", true), 0 },
		{ localization("Pausemap Tint Half", true), 0 },
		{ localization("North Blue Official", true), 0 },
		{ localization("Script Variable 2", true), 0 },
		{ localization("H", true), 0 },
		{ localization("H Dark", true), 0 },
		{ localization("T", true), 0 },
		{ localization("T Dark", true), 0 },
		{ localization("HS Hard", true), 0 },
		{ localization("Controller Michael", true), 0 },
		{ localization("Controller Franklin", true), 0 },
		{ localization("Controller Trevor", true), 0 },
		{ localization("Controller Chop", true), 0 },
		{ localization("Video Editor Video", true), 0 },
		{ localization("Video Editor Audio", true), 0 },
		{ localization("Video Editor Text", true), 0 },
		{ localization("HB Blue", true), 0 },
		{ localization("HB Yellow", true), 0 },
		{ localization("Video Editor Score", true), 0 },
		{ localization("Video Editor Audio Fadeout", true), 0 },
		{ localization("Video Editor Text Fadeout", true), 0 },
		{ localization("Video Editor Score Fadeout", true), 0 },
		{ localization("Heist Background", true), 0 },
		{ localization("Video Editor Ambient", true), 0 },
		{ localization("Video Editor Ambient Fadeout", true), 0 },
		{ localization("GB", true), 0 },
		{ localization("G", true), 0 },
		{ localization("B", true), 0 },
		{ localization("Low Flow", true), 0 },
		{ localization("Low Flow Dark", true), 0 },
		{ localization("G1", true), 0 },
		{ localization("G2", true), 0 },
		{ localization("G3", true), 0 },
		{ localization("G4", true), 0 },
		{ localization("G5", true), 0 },
		{ localization("G6", true), 0 },
		{ localization("G7", true), 0 },
		{ localization("G8", true), 0 },
		{ localization("G9", true), 0 },
		{ localization("G10", true), 0 },
		{ localization("G11", true), 0 },
		{ localization("G12", true), 0 },
		{ localization("G13", true), 0 },
		{ localization("G14", true), 0 },
		{ localization("G15", true), 0 },
		{ localization("Adversary", true), 0 },
		{ localization("Degen Red", true), 0 },
		{ localization("Degen Yellow", true), 0 },
		{ localization("Degen Green", true), 0 },
		{ localization("Degen Cyan", true), 0 },
		{ localization("Degen Blue", true), 0 },
		{ localization("Degen Magenta", true), 0 },
		{ localization("Stunt 1", true), 0 },
		{ localization("Stunt 2", true), 0 },
		{ localization("Special Race Series", true), 0 },
		{ localization("Special Race Series Dark", true), 0 },
		{ localization("CS", true), 0 },
		{ localization("CS Dark", true), 0 },
		{ localization("Tech Green", true), 0 },
		{ localization("Tech Green Dark", true), 0 },
		{ localization("Tech Red", true), 0 },
		{ localization("Tech Green Very Dark", true), 0 },
	};

	void set_color(hud_menu* _this) {
		native::set_hud_colour(m_vars.m_hud, m_vars.m_color.r, m_vars.m_color.g, m_vars.m_color.b, m_vars.m_color.a);

		// Save color
		util::config::write_color(_this->get_submenu_name_stack(), hud_color_labels[m_vars.m_hud].m_name.get_original(), m_vars.m_color);
	}
}

void hud_menu::load() {
	set_name("HUD");
	set_parent<misc_menu>();

	native::get_hud_colour(m_vars.m_hud, &m_vars.m_color.r, &m_vars.m_color.g, &m_vars.m_color.b, &m_vars.m_color.a);

	add_option(scroll_option<int>(SCROLL, "HUD")
		.add_translate()
		.add_scroll(m_vars.m_hud, 0, NUMOF(hud_color_labels), hud_color_labels)
		.add_click([] { native::get_hud_colour(m_vars.m_hud, &m_vars.m_color.r, &m_vars.m_color.g, &m_vars.m_color.b, &m_vars.m_color.a); }));

	add_option(submenu_option("Edit Color")
		.add_translate()
		.add_submenu<helper_color_menu>()
		.add_click([this] {
			helper_color_menu::get()->set_name(hud_color_labels[m_vars.m_hud].m_name.get(), false, false);
			helper_color_menu::get()->set_parent<hud_menu>();
			helper::color::vars::m_vars.m_color = &m_vars.m_color;
			helper::color::vars::m_vars.m_callback = [this] { set_color(this); };
		})
		.add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, &m_vars.m_color));

	// Load colors
	for (int i = 0; i < NUMOF(hud_color_labels); i++) {
		color_rgba color;
		if (util::config::read_color(get_submenu_name_stack(), hud_color_labels[i].m_name.get_original(), &color)) {
			native::set_hud_colour(m_vars.m_hud, color.r, color.g, color.b, color.a);
		}
	}
}

void hud_menu::update() {}

void hud_menu::update_once() {}

void hud_menu::feature_update() {}

hud_menu* g_instance;
hud_menu* hud_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new hud_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}