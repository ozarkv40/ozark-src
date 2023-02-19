#include "spawner_vehicle_manage.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"
#include "edit/spawner_vehicle_manage_edit.h"

using namespace spawner::vehicle::manage::vars;

namespace spawner::vehicle::manage::vars {
	variables m_vars;
}

void spawner_vehicle_manage_menu::load() {
	set_name("Manage Spawned Vehicles");
	set_parent<spawner_menu>();

	add_option(submenu_option("All Vehicles")
		.add_translate().add_hotkey()
		.add_click([] {
			spawner::vehicle::manage::edit::vars::m_vars.m_editing_all = true;
			spawner::vehicle::manage::edit::vars::m_vars.m_esp = &m_vars.m_esp;
		})
		.add_submenu<spawner_vehicle_manage_edit_menu>());

	add_option(button_option("Clear Manager")
		.add_translate().add_hotkey()
		.add_click([this] { m_vars.m_vehicles.clear(); update_once(); })
		.add_tooltip("Does NOT delete the vehicles from the world, only from the manager"));

	add_option(break_option("Vehicles")
		.add_translate());

	add_string("~m~None");
}

void spawner_vehicle_manage_menu::update() {}

void spawner_vehicle_manage_menu::update_once() {
	clear_options(3);

	for (std::size_t i = 0; i < m_vars.m_vehicles.size(); i++) {
		if (!native::does_entity_exist(m_vars.m_vehicles[i].m_handle)) {
			m_vars.m_vehicles.erase(m_vars.m_vehicles.begin() + i);
		}
	}

	if (!m_vars.m_vehicles.empty()) {
		for (std::size_t i = 0; i < m_vars.m_vehicles.size(); i++) {
			add_option(submenu_option(util::va::va("[%i] %s", i + 1, native::get_label_text(native::get_display_name_from_vehicle_model(m_vars.m_vehicles[i].m_model_hash))))
				.add_click([=] {
					spawner::vehicle::manage::edit::vars::m_vars.m_editing_all = false;
					spawner::vehicle::manage::edit::vars::m_vars.m_esp = &m_vars.m_vehicles[i].m_esp;
					spawner::vehicle::manage::edit::vars::m_vars.m_selected = i;
				})
				.add_submenu<spawner_vehicle_manage_edit_menu>());
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void spawner_vehicle_manage_menu::feature_update() {
	for (spawned_vehicle& vehicle : m_vars.m_vehicles) {
		if (vehicle.m_esp.m_name || m_vars.m_esp.m_name) {
			helper::esp::vars::name_esp(vehicle.m_esp.m_name ? vehicle.m_esp : m_vars.m_esp, vehicle.m_handle, native::get_label_text(native::get_display_name_from_vehicle_model(vehicle.m_model_hash)));
		}

		if (vehicle.m_esp.m_snapline || m_vars.m_esp.m_snapline) {
			helper::esp::vars::snapline_esp(vehicle.m_esp.m_snapline ? vehicle.m_esp : m_vars.m_esp, vehicle.m_handle);
		}

		if (vehicle.m_esp.m_2d_box || m_vars.m_esp.m_2d_box) {
			helper::esp::vars::_2d_esp(vehicle.m_esp.m_2d_box ? vehicle.m_esp : m_vars.m_esp, vehicle.m_handle, 0);
		}

		if (vehicle.m_esp.m_2d_corners || m_vars.m_esp.m_2d_corners) {
			helper::esp::vars::_2d_esp(vehicle.m_esp.m_2d_corners ? vehicle.m_esp : m_vars.m_esp, vehicle.m_handle, 1);
		}

		if (vehicle.m_esp.m_3d_box || m_vars.m_esp.m_3d_box) {
			helper::esp::vars::_3d_esp(vehicle.m_esp.m_3d_box ? vehicle.m_esp : m_vars.m_esp, vehicle.m_handle, 0);
		}

		if (vehicle.m_esp.m_3d_axis || m_vars.m_esp.m_3d_axis) {
			helper::esp::vars::_3d_esp(vehicle.m_esp.m_3d_axis ? vehicle.m_esp : m_vars.m_esp, vehicle.m_handle, 1);
		}

		if (!m_vars.m_esp.m_2d_box_rainbow.m_rainbow_toggle && vehicle.m_esp.m_2d_box_rainbow.m_rainbow_toggle) vehicle.m_esp.m_2d_box_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_2d_corners_rainbow.m_rainbow_toggle && vehicle.m_esp.m_2d_corners_rainbow.m_rainbow_toggle) vehicle.m_esp.m_2d_corners_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_3d_box_rainbow.m_rainbow_toggle && vehicle.m_esp.m_3d_box_rainbow.m_rainbow_toggle) vehicle.m_esp.m_3d_box_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_name_bg_rainbow.m_rainbow_toggle && vehicle.m_esp.m_name_bg_rainbow.m_rainbow_toggle) vehicle.m_esp.m_name_bg_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_name_text_rainbow.m_rainbow_toggle && vehicle.m_esp.m_name_text_rainbow.m_rainbow_toggle) vehicle.m_esp.m_name_text_rainbow.m_rainbow.run();
	}

	if (m_vars.m_esp.m_2d_box_rainbow.m_rainbow_toggle) m_vars.m_esp.m_2d_box_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_2d_corners_rainbow.m_rainbow_toggle) m_vars.m_esp.m_2d_corners_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_3d_box_rainbow.m_rainbow_toggle) m_vars.m_esp.m_3d_box_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_name_bg_rainbow.m_rainbow_toggle) m_vars.m_esp.m_name_bg_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_name_text_rainbow.m_rainbow_toggle) m_vars.m_esp.m_name_text_rainbow.m_rainbow.run();
}

spawner_vehicle_manage_menu* g_instance;
spawner_vehicle_manage_menu* spawner_vehicle_manage_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_vehicle_manage_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}