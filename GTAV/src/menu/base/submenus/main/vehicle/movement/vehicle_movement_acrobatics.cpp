#include "vehicle_movement_acrobatics.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_movement.h"
#include "global/lists.h"

using namespace vehicle::movement::acrobatics::vars;

namespace vehicle::movement::acrobatics::vars {
	variables m_vars;
}

void vehicle_movement_acrobatics_menu::load() {
	set_name("Acrobatics");
	set_parent<vehicle_movement_menu>();
}

void vehicle_movement_acrobatics_menu::update() {}

void vehicle_movement_acrobatics_menu::update_once() {
	clear_options(0);

	for (scroll_struct<std::pair<math::vector3_<float>, math::vector3_<float>>>& acrobat : global::lists::g_acrobatics) {
		add_option(button_option(acrobat.m_name.get())
			.add_click([=] { vehicle::movement::vars::run_acrobatic(menu::player::get_local_player().m_vehicle, acrobat.m_result); }));
	}
}

void vehicle_movement_acrobatics_menu::feature_update() {}

vehicle_movement_acrobatics_menu* g_instance;
vehicle_movement_acrobatics_menu* vehicle_movement_acrobatics_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_movement_acrobatics_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}