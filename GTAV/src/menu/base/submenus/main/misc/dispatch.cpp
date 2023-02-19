#include "dispatch.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"

using namespace misc::dispatch::vars;

namespace misc::dispatch::vars {
	variables m_vars;

	bool is_toggled(eDispatchType service) {
		if (global::vars::g_dispatch_service_table) {
			auto Table = *(uint64_t*)(global::vars::g_dispatch_service_table + (service * 8));
			if (Table) {
				return *(bool*)(Table + 0x20);
			}
		}

		return false;
	}

	void set_toggle(eDispatchType service, bool toggle) {
		if (global::vars::g_dispatch_service_table) {
			uint64_t table = *(uint64_t*)(global::vars::g_dispatch_service_table + (service * 8));
			if (table) {
				*(bool*)(table + 0x20) = !toggle;
			}
		}
	}
}

void dispatch_menu::load() {
	set_name("Dispatch");
	set_parent<misc_menu>();

	add_option(toggle_option("Disable Police Automobile")
		.add_translate()
		.add_toggle(m_vars.m_disable_police_automobile)
		.add_click([] { set_toggle(DT_PoliceAutomobile, m_vars.m_disable_police_automobile); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Police Helicopter")
		.add_translate()
		.add_toggle(m_vars.m_disable_police_helicopter)
		.add_click([] { set_toggle(DT_PoliceHelicopter, m_vars.m_disable_police_helicopter); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Police Riders")
		.add_translate()
		.add_toggle(m_vars.m_disable_police_riders)
		.add_click([] { set_toggle(DT_PoliceRiders, m_vars.m_disable_police_riders); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Police Vehicle Request")
		.add_translate()
		.add_toggle(m_vars.m_disable_police_vehicle_request)
		.add_click([] { set_toggle(DT_PoliceVehicleRequest, m_vars.m_disable_police_vehicle_request); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Police Road Block")
		.add_translate()
		.add_toggle(m_vars.m_disable_police_roadblock)
		.add_click([] { set_toggle(DT_PoliceRoadBlock, m_vars.m_disable_police_roadblock); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Police Boat")
		.add_translate()
		.add_toggle(m_vars.m_disable_police_boat)
		.add_click([] { set_toggle(DT_PoliceBoat, m_vars.m_disable_police_boat); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Swat Automobile")
		.add_translate()
		.add_toggle(m_vars.m_disable_swat_automobile)
		.add_click([] { set_toggle(DT_SwatAutomobile, m_vars.m_disable_swat_automobile); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Swat Helicopter")
		.add_translate()
		.add_toggle(m_vars.m_disable_swat_helicopter)
		.add_click([] { set_toggle(DT_SwatHelicopter, m_vars.m_disable_swat_helicopter); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Fire Department")
		.add_translate()
		.add_toggle(m_vars.m_disable_fire_department)
		.add_click([] { set_toggle(DT_FireDepartment, m_vars.m_disable_fire_department); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Ambulance Department")
		.add_translate()
		.add_toggle(m_vars.m_disable_ambulance_department)
		.add_click([] { set_toggle(DT_AmbulanceDepartment, m_vars.m_disable_ambulance_department); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Gangs")
		.add_translate()
		.add_toggle(m_vars.m_disable_gangs)
		.add_click([] { set_toggle(DT_Gangs, m_vars.m_disable_gangs); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Army Vehicle")
		.add_translate()
		.add_toggle(m_vars.m_disable_army_vehicle)
		.add_click([] { set_toggle(DT_ArmyVehicle, m_vars.m_disable_army_vehicle); })
		.add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Bikers")
		.add_translate()
		.add_toggle(m_vars.m_disable_bikers)
		.add_click([] { set_toggle(DT_BikerBackup, m_vars.m_disable_bikers); })
		.add_savable(get_submenu_name_stack()));
}

void dispatch_menu::update() {}

void dispatch_menu::update_once() {
	m_vars.m_disable_police_automobile = !is_toggled(DT_PoliceAutomobile);
	m_vars.m_disable_police_helicopter = !is_toggled(DT_PoliceHelicopter);
	m_vars.m_disable_police_riders = !is_toggled(DT_PoliceRiders);
	m_vars.m_disable_police_vehicle_request = !is_toggled(DT_PoliceVehicleRequest);
	m_vars.m_disable_police_roadblock = !is_toggled(DT_PoliceRoadBlock);
	m_vars.m_disable_police_boat = !is_toggled(DT_PoliceBoat);
	m_vars.m_disable_swat_automobile = !is_toggled(DT_SwatAutomobile);
	m_vars.m_disable_swat_helicopter = !is_toggled(DT_SwatHelicopter);
	m_vars.m_disable_fire_department = !is_toggled(DT_FireDepartment);
	m_vars.m_disable_ambulance_department = !is_toggled(DT_AmbulanceDepartment);
	m_vars.m_disable_gangs = !is_toggled(DT_Gangs);
	m_vars.m_disable_army_vehicle = !is_toggled(DT_ArmyVehicle);
	m_vars.m_disable_bikers = !is_toggled(DT_BikerBackup);
}

void dispatch_menu::feature_update() {}

dispatch_menu* g_instance;
dispatch_menu* dispatch_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new dispatch_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
