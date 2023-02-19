#include "spawner_object_manage_edit.h"
#include "menu/base/submenu_handler.h"
#include "../spawner_object_manage.h"
#include "util/fiber_pool.h"
#include "menu/base/util/control.h"

using namespace spawner::object::manage::edit::vars;

namespace spawner::object::manage::edit::vars {
	variables m_vars;

	scroll_struct<int> teleport[] = {
		{ localization("To Me", true), 0 },
		{ localization("To Object", true), 1 }
	};

	void run_entity(int index, int* var, Entity ent) {
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

			case 1: // Freeze Position
				native::freeze_entity_position(ent, true);
				break;

			case 2: // Delete
				native::set_entity_as_mission_entity(ent, true, true);
				native::delete_entity(&ent);
				break;
		}
	}

	void run(int index, bool editing_all, bool editing_pool, int* var, Entity entity) {
		if (editing_all || editing_pool) {
			std::vector<Entity> entities;
			if (editing_all) {
				for (spawner::object::manage::vars::spawned_object object : spawner::object::manage::vars::m_vars.m_objects) {
					entities.push_back(object.m_handle);
				}
			} else {
				global::vars::g_object_pool->for_each([&](Entity ent, void* ped) {
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

void spawner_object_manage_edit_menu::load() {
	set_name("Manage");
	set_parent<spawner_object_manage_menu>();

	add_option(submenu_option("ESP")
		.add_translate()
		.add_submenu<helper_esp_menu>()
		.add_click([] {
			helper_esp_menu::get()->set_parent<spawner_object_manage_edit_menu>();
			helper::esp::vars::m_vars.m_current = m_vars.m_esp;
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Teleport")
		.add_translate()
		.add_click([] { run(0, m_vars.m_editing_all, false, &m_vars.m_teleport, spawner::object::manage::vars::m_vars.m_objects[m_vars.m_selected].m_handle); })
		.add_scroll(m_vars.m_teleport, 0, NUMOF(teleport), teleport));

	add_option(button_option("Freeze Position")
		.add_translate()
		.add_click([] { run(1, m_vars.m_editing_all, false, 0, spawner::object::manage::vars::m_vars.m_objects[m_vars.m_selected].m_handle); }));

	add_option(button_option("Delete")
		.add_translate()
		.add_click([] {
			run(2, m_vars.m_editing_all, false, nullptr, spawner::object::manage::vars::m_vars.m_objects[m_vars.m_selected].m_handle);
			menu::submenu::handler::set_submenu_previous(true);
		}));
}

void spawner_object_manage_edit_menu::update() {}

void spawner_object_manage_edit_menu::update_once() {}

void spawner_object_manage_edit_menu::feature_update() {}

spawner_object_manage_edit_menu* g_instance;
spawner_object_manage_edit_menu* spawner_object_manage_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_object_manage_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}