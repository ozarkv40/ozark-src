#include "visions.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"
#include "util/memory/memory.h"

using namespace misc::visions::vars;

namespace misc::visions::vars {
	variables m_vars;

	scroll_struct<const char*> visions[]{
		{ localization("None", true), "" },
		{ localization("Sunglasses", true), "sunglasses" },
		{ localization("Camera BW", true), "CAMERA_BW" },
		{ localization("Hint Cam", true), "Hint_cam" },
		{ localization("UFO", true), "ufo" },
		{ localization("UFO Deathray", true), "ufo_deathray" },
		{ localization("Dying", true), "dying" },
		{ localization("Underwater", true), "underwater" },
		{ localization("Spectator", true), "spectator1" },
		{ localization("Cops Splash", true), "CopsSPLASH" },
		{ localization("Crane Cam", true), "crane_cam" },
		{ localization("Secret Camera", true), "secret_camera" },
		{ localization("Graveyard Shootout", true), "graveyard_shootout" },
		{ localization("Cops", true), "cops" },
		{ localization("Damage", true), "damage" },
		{ localization("Bikers Splash", true), "BikersSPLASH" },
		{ localization("Bikers", true), "Bikers" },
		{ localization("Prologue Shootout", true), "prologue_shootout" },
		{ localization("Vagos", true), "vagos" },
		{ localization("Sniper", true), "sniper" },
	};
}

void visions_menu::load() {
	set_name("Visions");
	set_parent<misc_menu>();

	memcpy(m_vars.m_backup, (void*)(global::vars::g_set_seethrough + 0x14), 5);

	add_option(toggle_option("Thermal Vision")
		.add_translate().add_hotkey()
		.add_click([] {
			if (m_vars.m_thermal_vision) {
				memory::write_vector(global::vars::g_set_seethrough + 0x14, { 0xB3, 0x01, 0x90, 0x90, 0x90 });
				native::set_seethrough(true);
			} else {
				memory::write(global::vars::g_set_seethrough + 0x14, m_vars.m_backup, 5);
				native::set_seethrough(false);
			}
		})
		.add_toggle(m_vars.m_thermal_vision).add_savable(get_submenu_name_stack()));

	add_option(break_option("Visions")
		.add_translate());

	for (int i = 0; i < NUMOF(visions); i++) {
		add_option(radio_option(visions[i].m_name.get())
			.add_translate()
			.add_radio(m_vars.m_context)
			.add_click([=] { if (i == 0) native::clear_timecycle_modifier(); }));
	}
}

void visions_menu::update() {}

void visions_menu::update_once() {}

void visions_menu::feature_update() {
	if (m_vars.m_context.m_selected != 0) {
		native::set_timecycle_modifier(visions[m_vars.m_context.m_selected].m_result);
	}
}

visions_menu* g_instance;
visions_menu* visions_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new visions_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}