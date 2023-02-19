#include "spawner_ped_manage_edit.h"
#include "menu/base/submenu_handler.h"
#include "../spawner_ped_manage.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "menu/base/util/control.h"

using namespace spawner::ped::manage::edit::vars;

namespace spawner::ped::manage::edit::vars {
	variables m_vars;

	scroll_struct<int> teleport[] = {
		{ localization("To Me", true), 0 },
		{ localization("To Object", true), 1 }
	};

	void run_entity(int index, int* var, Entity ent) {
		if (ent == menu::player::get_local_player().m_ped || native::is_ped_a_player(ent)) return;

		switch (index) {
			case 0: { // Teleport
				if (*var == 0) {
					math::vector3<float> forward = menu::player::get_local_player().m_coords + (native::get_entity_forward_vector(menu::player::get_local_player().m_entity) * 5.f);
					native::set_entity_coords(ent, forward.x, forward.y, forward.z, false, false, false, false);
				} else {
					math::vector3<float> coords = native::get_entity_coords(ent, false);
					native::set_entity_coords(menu::player::get_local_player().m_entity, coords.x, coords.y, coords.z, false, false, false, false);
				}

				break;
			}

			case 1: // Delete
				native::set_entity_as_mission_entity(ent, true, true);
				native::delete_entity(&ent);
				break;

			case 2:
				native::resurrect_ped(ent);
				native::revive_injured_ped(ent);
				native::set_entity_health(ent, 100);
				native::clear_ped_tasks_immediately(ent);
				break;

			case 3:
				native::apply_damage_to_ped(ent, 30000, true);
				break;

			case 4: {
				math::vector3<float> coords = native::get_entity_coords(ent, true);
				native::add_explosion(coords.x, coords.y, coords.z, 0, 10.f, true, false, 0.f, false);
				break;
			}

			case 5:
				native::clone_ped(ent, 0.f, true, true);
				break;
		}
	}

	void run(int index, bool editing_all, bool editing_pool, int* var, Entity entity) {
		if (editing_all || editing_pool) {
			std::vector<Entity> entities;
			if (editing_all) {
				for (spawner::ped::manage::vars::spawned_ped ped : spawner::ped::manage::vars::m_vars.m_peds) {
					entities.push_back(ped.m_handle);
				}
			} else {
				global::vars::g_ped_pool->for_each([&](Entity ent, void* ped) {
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

void spawner_ped_manage_edit_menu::load() {
	set_name("Manage");
	set_parent<spawner_ped_manage_menu>();

	add_option(submenu_option("ESP")
		.add_translate()
		.add_submenu<helper_esp_menu>()
		.add_click([] {
			helper_esp_menu::get()->set_parent<spawner_ped_manage_edit_menu>();
			helper::esp::vars::m_vars.m_current = m_vars.m_esp;
			m_vars.m_esp->m_ped = true;
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Teleport")
		.add_translate()
		.add_click([] { run(0, m_vars.m_editing_all, false, &m_vars.m_teleport, spawner::ped::manage::vars::m_vars.m_peds[m_vars.m_selected].m_handle); })
		.add_scroll(m_vars.m_teleport, 0, NUMOF(teleport), teleport));

	add_option(button_option("Revive")
		.add_translate()
		.add_click([] { run(2, m_vars.m_editing_all, false, nullptr, spawner::ped::manage::vars::m_vars.m_peds[m_vars.m_selected].m_handle); }));

	add_option(button_option("Kill")
		.add_translate()
		.add_click([] { run(3, m_vars.m_editing_all, false, nullptr, spawner::ped::manage::vars::m_vars.m_peds[m_vars.m_selected].m_handle); }));

	add_option(button_option("Explode")
		.add_translate()
		.add_click([] { run(4, m_vars.m_editing_all, false, nullptr, spawner::ped::manage::vars::m_vars.m_peds[m_vars.m_selected].m_handle); }));

	add_option(button_option("Clone")
		.add_translate()
		.add_click([] { run(5, m_vars.m_editing_all, false, nullptr, spawner::ped::manage::vars::m_vars.m_peds[m_vars.m_selected].m_handle); }));

	add_option(button_option("Delete")
		.add_translate()
		.add_click([] {
			run(1, m_vars.m_editing_all, false, nullptr, spawner::ped::manage::vars::m_vars.m_peds[m_vars.m_selected].m_handle);
			menu::submenu::handler::set_submenu_previous(true);
		}));
}

void spawner_ped_manage_edit_menu::update() {}

void spawner_ped_manage_edit_menu::update_once() {}

void spawner_ped_manage_edit_menu::feature_update() {}

spawner_ped_manage_edit_menu* g_instance;
spawner_ped_manage_edit_menu* spawner_ped_manage_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_ped_manage_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}