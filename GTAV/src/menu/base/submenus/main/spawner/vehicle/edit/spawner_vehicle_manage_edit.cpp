#include "spawner_vehicle_manage_edit.h"
#include "menu/base/submenu_handler.h"
#include "../spawner_vehicle_manage.h"
#include "menu/base/util/control.h"
#include "util/fiber_pool.h"
#include "global/lists.h"
#include "rage/engine.h"

using namespace spawner::vehicle::manage::edit::vars;

namespace spawner::vehicle::manage::edit::vars {
	variables m_vars;

	scroll_struct<int> driver[] = {
		{ localization("Kick", true), 0 },
		{ localization("Kill", true), 1 }
	};

	scroll_struct<float> boost[] = {
		{ localization("Forwards", true), 100.f },
		{ localization("Backwards", true), -100.f }
	};

	scroll_struct<int> teleport[] = {
		{ localization("To Me", true), 0 },
		{ localization("To Vehicle", true), 1 }
	};

	void run_entity(int index, int* var, Entity ent) {
		switch (index) {
			case 0:
				if (*var == 0) {
					Ped driver = native::get_ped_in_vehicle_seat(ent, -1, 0);
					if (driver) {
						if (native::is_ped_a_player(driver) && driver != menu::player::get_local_player().m_ped) {
							menu::control::request_control(ent, [](Entity, int) {}, true);
						} else {
							native::clear_ped_tasks_immediately(driver);
						}
					}
				} else {
					native::set_vehicle_out_of_control(ent, true, true);
				}

				break;

			case 1:
				native::set_vehicle_forward_speed(ent, boost[*var].m_result);
				break;

			case 2: {
				std::pair<math::vector3_<float>, math::vector3_<float>> n = global::lists::g_acrobatics[*var].m_result;
				native::apply_force_to_entity(ent, 1, n.first.x, n.first.y, n.first.z, n.second.x, n.second.y, n.second.z, 0, true, true, true, false, true);
				break;
			}

			case 3: {
				uint64_t address = rage::engine::get_entity_address(ent);
				if (address) {
					rage::engine::set_vehicle_gravity(address, global::lists::g_gravity[*var].m_result);
				}

				break;
			}

			case 4: {
				if (*var == 0) {
					math::vector3<float> forward = menu::player::get_local_player().m_coords + (native::get_entity_forward_vector(menu::player::get_local_player().m_entity) * 5.f);
					native::set_entity_coords(ent, forward.x, forward.y, forward.z, false, false, false, false);
				} else {
					math::vector3<float> coords = native::get_entity_coords(ent, false);
					native::set_entity_coords(menu::player::get_local_player().m_entity, coords.x, coords.y, coords.z, false, false, false, false);
				}
				
				break;
			}

			case 5:
				native::set_vehicle_fixed(ent);
				break;

			case 6:
				native::task_everyone_leave_vehicle(ent);
				for (int i = -1; i < native::get_vehicle_number_of_passengers(ent); i++) {
					Ped ped = native::get_ped_in_vehicle_seat(ent, i, 0);
					if (ped) {
						native::clear_ped_tasks_immediately(ped);
					}
				}

				break;

			case 7:
				native::set_vehicle_custom_primary_colour(ent, native::get_random_int_in_range(0, 255), native::get_random_int_in_range(0, 255), native::get_random_int_in_range(0, 255));
				native::set_vehicle_custom_secondary_colour(ent, native::get_random_int_in_range(0, 255), native::get_random_int_in_range(0, 255), native::get_random_int_in_range(0, 255));
				break;

			case 8:
				native::start_vehicle_horn(ent, 2000, 0, false);
				break;

			case 9: {
				Ped ped = native::get_ped_in_vehicle_seat(ent, -1, 0);
				if (ped) {
					native::task_vehicle_drive_to_coord(ped, ent, menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, 100, 1, native::get_entity_model(ent), 16777216, 4, -1);
				}

				break;
			}

			case 10:
				native::network_explode_vehicle(ent, true, false, false);
				break;

			case 11:
				native::set_entity_as_mission_entity(ent, true, true);
				native::delete_entity(&ent);
				break;
		}
	}

	void run(int index, bool editing_all, bool editing_pool, int* var, Entity entity) {
		if (editing_all || editing_pool) {
			std::vector<Entity> entities;
			if (editing_all) {
				for (spawner::vehicle::manage::vars::spawned_vehicle vehicle : spawner::vehicle::manage::vars::m_vars.m_vehicles) {
					entities.push_back(vehicle.m_handle);
				}
			} else {
				global::vars::g_vehicle_pool->for_each([&](Entity ent, void* veh) {
					entities.push_back(ent);
				});
			}

			util::fiber::pool::add([=] {
				for (Entity ent : entities) {
					menu::control::simple_request_control(ent);
					run_entity(index, var, ent);
				}
			});
		} else {
			menu::control::request_control(entity, [=](Entity ent) {
				run_entity(index, var, ent);
			});
		}
	}
}

void spawner_vehicle_manage_edit_menu::load() {
	set_name("Manage");
	set_parent<spawner_vehicle_manage_menu>();

	add_option(submenu_option("ESP")
		.add_translate()
		.add_submenu<helper_esp_menu>()
		.add_click([] { 
			helper_esp_menu::get()->set_parent<spawner_vehicle_manage_edit_menu>();
			helper::esp::vars::m_vars.m_current = m_vars.m_esp;
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Driver")
		.add_translate()
		.add_scroll(m_vars.m_driver, 0, NUMOF(driver), driver)
		.add_click([] { run(0, m_vars.m_editing_all, false, &m_vars.m_driver, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));
	
	add_option(scroll_option<float>(SCROLLSELECT, "Boost")
		.add_translate()
		.add_scroll(m_vars.m_boost, 0, NUMOF(boost), boost)
		.add_click([] { run(1, m_vars.m_editing_all, false, &m_vars.m_boost, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));

	add_option(scroll_option<std::pair<math::vector3_<float>, math::vector3_<float>>>(SCROLLSELECT, "Acrobatics")
		.add_translate()
		.add_scroll(m_vars.m_acrobatics, 0, NUMOF(global::lists::g_acrobatics), global::lists::g_acrobatics)
		.add_click([] { run(2, m_vars.m_editing_all, false, &m_vars.m_acrobatics, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));

	add_option(scroll_option<float>(SCROLLSELECT, "Gravity")
		.add_translate()
		.add_scroll(m_vars.m_gravity, 0, NUMOF(global::lists::g_gravity), global::lists::g_gravity)
		.add_click([] { run(3, m_vars.m_editing_all, false, &m_vars.m_gravity, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));

	add_option(scroll_option<int>(SCROLLSELECT, "Teleport")
		.add_translate()
		.add_scroll(m_vars.m_teleport, 0, NUMOF(teleport), teleport)
		.add_click([] { run(4, m_vars.m_editing_all, false, &m_vars.m_teleport, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));

	add_option(button_option("Fix")
		.add_translate()
		.add_click([] { run(5, m_vars.m_editing_all, false, nullptr, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));

	add_option(button_option("Empty Vehicle Seats")
		.add_translate()
		.add_click([] { run(6, m_vars.m_editing_all, false, nullptr, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));

	add_option(button_option("Random Paint")
		.add_translate()
		.add_click([] { run(7, m_vars.m_editing_all, false, nullptr, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));

	add_option(button_option("Honk Horn")
		.add_translate()
		.add_click([] { run(8, m_vars.m_editing_all, false, nullptr, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));
	
	add_option(button_option("Drive to Me")
		.add_translate()
		.add_click([] { run(9, m_vars.m_editing_all, false, nullptr, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));
	
	add_option(button_option("Explode")
		.add_translate()
		.add_click([] { run(10, m_vars.m_editing_all, false, nullptr, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle); }));

	add_option(button_option("Delete")
		.add_translate()
		.add_click([] {
			run(11, m_vars.m_editing_all, false, nullptr, spawner::vehicle::manage::vars::m_vars.m_vehicles[m_vars.m_selected].m_handle);
			menu::submenu::handler::set_submenu_previous(true);
		}));
}

void spawner_vehicle_manage_edit_menu::update() {}

void spawner_vehicle_manage_edit_menu::update_once() {}

void spawner_vehicle_manage_edit_menu::feature_update() {}

spawner_vehicle_manage_edit_menu* g_instance;
spawner_vehicle_manage_edit_menu* spawner_vehicle_manage_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_vehicle_manage_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}