#include "misc.h"
#include "menu/base/submenu_handler.h"
#include "../main.h"
#include "misc/scripthook.h"
#include "misc/misc_camera.h"
#include "menu/base/util/panels.h"
#include "misc/misc_radio.h"
#include "misc/hud.h"
#include "misc/visions.h"
#include "misc/display.h"
#include "misc/misc_panels.h"
#include "misc/misc_disables.h"
#include "misc/misc_swaps.h"
#include "misc/dispatch.h"

using namespace misc::vars;

namespace misc::vars {
	variables m_vars;

	scroll_struct<int> metric[] = {
		{ localization("Metric", true), 0 },
		{ localization("Imperial", true), 1 }
	};
}

void misc_menu::load() {
	set_name("Miscellaneous");
	set_parent<main_menu>();

	add_option(submenu_option("ScriptHook")
		.add_translate().add_hotkey()
		.add_submenu<scripthook_menu>());

	add_option(submenu_option("Camera")
		.add_translate().add_hotkey()
		.add_submenu<camera_menu>());

	add_option(submenu_option("Radio")
		.add_translate().add_hotkey()
		.add_submenu<radio_menu>());

	add_option(submenu_option("HUD")
		.add_translate().add_hotkey()
		.add_submenu<hud_menu>());

	add_option(submenu_option("Visions")
		.add_translate().add_hotkey()
		.add_submenu<visions_menu>());

	add_option(submenu_option("Stacked Display")
		.add_translate().add_hotkey()
		.add_submenu<display_menu>());

	add_option(submenu_option("Panels")
		.add_translate().add_hotkey()
		.add_submenu<panels_menu>());

	add_option(submenu_option("Disables")
		.add_translate().add_hotkey()
		.add_submenu<misc_disables_menu>());

	add_option(submenu_option("Swaps")
		.add_translate().add_hotkey()
		.add_submenu<misc_swaps_menu>());

	add_option(submenu_option("Dispatch")
		.add_translate().add_hotkey()
		.add_submenu<dispatch_menu>());

	add_option(scroll_option<int>(SCROLL, "Speed Calculations")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_metric_system, 0, NUMOF(metric), metric)
		.add_click([] {
			global::vars::g_selected_metric_system = { m_vars.m_metric_system == 0 ? 2.236936f : 3.6f, m_vars.m_metric_system == 0 ? "MPH" : "KPH" };
		})
		.add_savable(get_submenu_name_stack())
		.add_tooltip("Metric to be used in features such as Speedometer"));

	add_option(toggle_option("Rockstar Developer Perks")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rockstar_developer_perks)
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Decreased Graphics")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_decreased_graphics)
		.add_click([] {
			if (!m_vars.m_decreased_graphics) {
				native::set_focus_entity(menu::player::get_local_player().m_ped);
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(button_option("Bail")
		.add_translate().add_hotkey()
		.add_click([] {
			if (is_valid_ptr(*(uint64_t*)(global::vars::g_network_player_manager))) {
				native::network_bail(0, 0, 0);
			}
		})
		.add_tooltip("Bail to singleplayer"));
}

void misc_menu::update() {}

void misc_menu::update_once() {
	for (menu::panels::panel_parent* panel : menu::panels::get_panel_manager()->get_panels()) {
		panel->m_render = false;
	}
}

void misc_menu::feature_update() {
	if (m_vars.m_decreased_graphics) {
		native::set_focus_area(9999.f, 9999.f, 9999.f, 0.f, 0.f, 0.f);
	}
}

misc_menu* g_instance;
misc_menu* misc_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new misc_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
