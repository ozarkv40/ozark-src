#include "protection_entity_events.h"
#include "menu/base/submenu_handler.h"
#include "../protections.h"
#include "entity/protection_entity_blocking.h"
#include "entity/protection_entity_ghosting.h"

using namespace protection::entity::vars;

namespace protection::entity::vars {
	variables m_vars;
}

void protection_entity_events_menu::load() {
	set_name("Entity");
	set_parent<protection_menu>();

	add_option(submenu_option("Spawn Blocking")
		.add_translate()
		.add_submenu<protection_entity_blocking_menu>()
		.add_tooltip("Block these entity types from being spawned for other players"));

	add_option(submenu_option("Spawn Ghosting")
		.add_translate()
		.add_submenu<protection_entity_ghosting_menu>()
		.add_tooltip("Block these entity types from specific players"));

	add_option(toggle_option("Block Modder Create")
		.add_translate()
		.add_toggle(m_vars.m_block_modder_create).add_savable(get_submenu_name_stack())
		.add_tooltip("Blocks entities being created from modders"));

	add_option(toggle_option("Block Modder Sync")
		.add_translate()
		.add_toggle(m_vars.m_block_modder_sync).add_savable(get_submenu_name_stack())
		.add_tooltip("Blocks entities being synced from modders"));
}

void protection_entity_events_menu::update() {}

void protection_entity_events_menu::update_once() {}

void protection_entity_events_menu::feature_update() {}

protection_entity_events_menu* g_instance;
protection_entity_events_menu* protection_entity_events_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_entity_events_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}