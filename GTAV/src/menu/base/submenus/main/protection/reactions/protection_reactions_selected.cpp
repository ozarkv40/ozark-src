#include "protection_reactions_selected.h"
#include "menu/base/submenu_handler.h"
#include "../protection_reactions.h"

using namespace protection::reactions::selected::vars;

namespace protection::reactions::selected::vars {
	variables m_vars;
}

void protection_reactions_selected_menu::load() {
	set_name("Reactions");
	set_parent<protection_reactions_menu>();

	add_option(toggle_option("Explode")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_explode)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_explode); }));

	add_option(toggle_option("Crash")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_crash)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_crash); }));

	add_option(toggle_option("Kick")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_kick)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_kick); }));

	add_option(toggle_option("Add to Overseer")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_add_to_overseer)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_add_to_overseer); }));

	add_option(toggle_option("Cage")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_cage)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_cage); }));

	add_option(toggle_option("Kick from Vehicle")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_kick_from_vehicle)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_kick_from_vehicle); }));

	add_option(toggle_option("Set on Fire")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_set_on_fire)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_set_on_fire); }));

	add_option(toggle_option("Ragdoll")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_ragdoll)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_ragdoll); }));

	add_option(toggle_option("Glitch Physics")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_glitch_physics)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_glitch_physics); }));

	add_option(toggle_option("Black Screen")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_black_screen)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_black_screen); }));

	add_option(toggle_option("Blame")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_blame)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_blame); }));

	add_option(toggle_option("Give Wanted Level")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_give_wanted_level)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_give_wanted_level); }));

	add_option(toggle_option("Send to Island")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_send_to_island)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_send_to_island); }));

	add_option(toggle_option("Remove Weapons")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_remove_weapons)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_remove_weapons); }));

	add_option(toggle_option("Hostile Clone")
		.add_translate()
		.add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_hostile_clone)
		.add_update([] (toggle_option* option, int pos) { option->add_toggle(protection::reactions::vars::m_vars.m_reactions[m_vars.m_selected].m_hostile_clone); }));
}

void protection_reactions_selected_menu::update() {}

void protection_reactions_selected_menu::update_once() {}

void protection_reactions_selected_menu::feature_update() {}

protection_reactions_selected_menu* g_instance;
protection_reactions_selected_menu* protection_reactions_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_reactions_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}