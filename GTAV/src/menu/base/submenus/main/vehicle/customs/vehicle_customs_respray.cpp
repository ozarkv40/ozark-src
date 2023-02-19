#include "vehicle_customs_respray.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs.h"
#include "respray/vehicle_customs_respray_type.h"

using namespace vehicle::customs::respray::vars;

namespace vehicle::customs::respray::vars {
	variables m_vars;
}

void vehicle_customs_respray_menu::load() {
	set_name("Respray");
	set_parent<vehicle_customs_menu>();

	add_option(submenu_option("Primary Color")
		.add_translate()
		.add_submenu<vehicle_customs_respray_type_menu>()
		.add_click([] { vehicle::customs::respray::type::vars::m_vars.m_type = 1; }));

	add_option(submenu_option("Secondary Color")
		.add_translate()
		.add_submenu<vehicle_customs_respray_type_menu>()
		.add_click([] { vehicle::customs::respray::type::vars::m_vars.m_type = 2; }));

	add_option(submenu_option("Livery")
		.add_translate()
		.add_submenu<vehicle_customs_respray_type_menu>()
		.add_click([] { vehicle::customs::respray::type::vars::m_vars.m_type = 3; })
		.add_requirement([] { return native::get_vehicle_livery_count(menu::player::get_local_player().m_vehicle) > 0 && native::get_livery_name(menu::player::get_local_player().m_vehicle, 0); }));
}

void vehicle_customs_respray_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_respray_menu::update_once() {
	if (m_vars.m_update_cache) {
		m_vars.m_update_cache = false;
		native::set_vehicle_livery(menu::player::get_local_player().m_vehicle, m_vars.m_livery);
	}

	m_vars.m_livery = native::get_vehicle_livery(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_respray_menu::feature_update() {}

vehicle_customs_respray_menu* g_instance;
vehicle_customs_respray_menu* vehicle_customs_respray_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_respray_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}