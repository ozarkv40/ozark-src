#include "vehicle_collision.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"

using namespace vehicle::collision::vars;

namespace vehicle::collision::vars {
	variables m_vars;
}

void vehicle_collision_menu::load() {
	set_name("Collision");
	set_parent<vehicle_menu>();

	add_option(toggle_option("Disable Full Collision")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_full_collision)
		.add_click([] { if (!m_vars.m_disable_full_collision) if (menu::player::get_local_player().m_in_vehicle) native::set_entity_collision(menu::player::get_local_player().m_vehicle, true, true);  }));

	add_option(toggle_option("Disable Vehicle Collision")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_vehicle_collision));
}

void vehicle_collision_menu::update() {}

void vehicle_collision_menu::update_once() {}

void vehicle_collision_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_disable_full_collision) {
			native::set_entity_collision(menu::player::get_local_player().m_vehicle, !m_vars.m_disable_full_collision, true);
		}

		if (m_vars.m_disable_vehicle_collision) {
			global::vars::g_vehicle_pool->for_each([](Entity veh, void*) {
				native::set_entity_no_collision_entity(veh, menu::player::get_local_player().m_vehicle, true);
			});
		}
	}
}

vehicle_collision_menu* g_instance;
vehicle_collision_menu* vehicle_collision_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_collision_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}