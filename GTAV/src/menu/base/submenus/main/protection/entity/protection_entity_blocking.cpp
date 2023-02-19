#include "protection_entity_blocking.h"
#include "menu/base/submenu_handler.h"
#include "../protection_entity_events.h"

using namespace protection::entity::blocking::vars;

namespace protection::entity::blocking::vars {
	variables m_vars;
}

void protection_entity_blocking_menu::load() {
	set_name("Spawn Blocking");
	set_parent<protection_entity_events_menu>();

	add_option(toggle_option("Automobile")
		.add_translate()
		.add_toggle(m_vars.m_toggled[0]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Bike")
		.add_translate()
		.add_toggle(m_vars.m_toggled[1]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Boat")
		.add_translate()
		.add_toggle(m_vars.m_toggled[2]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Door")
		.add_translate()
		.add_toggle(m_vars.m_toggled[3]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Helicopter")
		.add_translate()
		.add_toggle(m_vars.m_toggled[4]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Object")
		.add_translate()
		.add_toggle(m_vars.m_toggled[5]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Ped")
		.add_translate()
		.add_toggle(m_vars.m_toggled[6]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Pickup")
		.add_translate()
		.add_toggle(m_vars.m_toggled[7]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Pickup Placement")
		.add_translate()
		.add_toggle(m_vars.m_toggled[8]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Plane")
		.add_translate()
		.add_toggle(m_vars.m_toggled[9]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Submarine")
		.add_translate()
		.add_toggle(m_vars.m_toggled[10]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Player")
		.add_translate()
		.add_toggle(m_vars.m_toggled[11]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Trailer")
		.add_translate()
		.add_toggle(m_vars.m_toggled[12]).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Train")
		.add_translate()
		.add_toggle(m_vars.m_toggled[13]).add_savable(get_submenu_name_stack()));
}

void protection_entity_blocking_menu::update() {}

void protection_entity_blocking_menu::update_once() {}

void protection_entity_blocking_menu::feature_update() {}

protection_entity_blocking_menu* g_instance;
protection_entity_blocking_menu* protection_entity_blocking_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_entity_blocking_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}