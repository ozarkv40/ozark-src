#include "protection_entity_ghosting.h"
#include "menu/base/submenu_handler.h"
#include "../protection_entity_events.h"
#include "protection_entity_ghosting_edit.h"

using namespace protection::entity::ghosting::vars;

namespace protection::entity::ghosting::vars {
	variables m_vars;

	std::pair<std::string, eNetObjectTypes> types[] = {
		{ "Automobile", NetObjectAutomobile },
		{ "Bike", NetObjectBike },
		{ "Boat", NetObjectBoat },
		{ "Helicopter", NetObjectHeli },
		{ "Object", NetObjectObject },
		{ "Ped", NetObjectPed },
		{ "Pickup", NetObjectPickup },
		{ "Plane", NetObjectPlane },
		{ "Submarine", NetObjectSubmarine },
		{ "Player", NetObjectPlayer },
		{ "Trailer", NetObjectTrailer },
		{ "Train", NetObjectTrain }
	};
}

void protection_entity_ghosting_menu::load() {
	set_name("Spawn Ghosting");
	set_parent<protection_entity_events_menu>();

	for (auto& [name, type] : types) {
		m_vars.m_ghosts[type].m_type = type;
		m_vars.m_ghosts[type].m_name = name;

		m_vars.m_ghosts[type].m_enabled_for_session = util::config::read_bool(get_submenu_name_stack(), "Ghost for Session", false, { name });
	}

	add_option(submenu_option("Player")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectPlayer]; }));

	add_option(submenu_option("Automobile")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectAutomobile]; }));

	add_option(submenu_option("Bike")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectBike]; }));

	add_option(submenu_option("Boat")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectBoat]; }));

	add_option(submenu_option("Helicopter")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectHeli]; }));

	add_option(submenu_option("Object")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectObject]; }));

	add_option(submenu_option("Ped")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectPed]; }));

	add_option(submenu_option("Pickup")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectPickup]; }));

	add_option(submenu_option("Plane")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectPlane]; }));

	add_option(submenu_option("Submarine")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectSubmarine]; }));

	add_option(submenu_option("Trailer")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectTrailer]; }));

	add_option(submenu_option("Train")
		.add_translate()
		.add_submenu<protection_entity_ghosting_edit_menu>()
		.add_click([] { protection::entity::ghosting::edit::vars::m_vars.m_selected = &m_vars.m_ghosts[NetObjectTrain]; }));
}

void protection_entity_ghosting_menu::update() {}

void protection_entity_ghosting_menu::update_once() {
	protection::entity::ghosting::edit::vars::m_vars.m_ready = false;
}

void protection_entity_ghosting_menu::feature_update() {}

protection_entity_ghosting_menu* g_instance;
protection_entity_ghosting_menu* protection_entity_ghosting_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_entity_ghosting_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}