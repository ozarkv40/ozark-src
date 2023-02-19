#include "local_entities.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"
#include "util/fiber_pool.h"
#include "global/lists.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/spawner/vehicle/edit/spawner_vehicle_manage_edit.h"
#include "menu/base/submenus/main/spawner/object/edit/spawner_object_manage_edit.h"
#include "menu/base/submenus/main/spawner/ped/edit/spawner_ped_manage_edit.h"

using namespace world::local::vars;

namespace world::local::vars {
	variables m_vars;

	scroll_struct<int> type[] = {
		{ localization("Vehicle", true), 0 },
		{ localization("Object", true), 0 },
		{ localization("Ped", true), 0 },
	};

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
}

void local_entities_menu::load() {
	set_name("Local Entities");
	set_parent<world_menu>();

	add_option(scroll_option<int>(SCROLL, "Entity Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(type), type)
		.add_click([this] { update_once(); }));

	m_vars.m_object_esp.m_name_bg_color = { 87, 229, 87, 144 };
	m_vars.m_object_esp.m_snapline_color = { 87, 229, 87, 144 };
	m_vars.m_object_esp.m_2d_box_color = { 87, 229, 87, 144 };
	m_vars.m_object_esp.m_2d_corners_color = { 87, 229, 87, 144 };
	m_vars.m_object_esp.m_3d_box_color = { 87, 229, 87, 144 };

	m_vars.m_ped_esp.m_name_bg_color = { 249, 159, 24, 180 };
	m_vars.m_ped_esp.m_snapline_color = { 249, 159, 24, 180 };
	m_vars.m_ped_esp.m_2d_box_color = { 249, 159, 24, 180 };
	m_vars.m_ped_esp.m_2d_corners_color = { 249, 159, 24, 180 };
	m_vars.m_ped_esp.m_3d_box_color = { 249, 159, 24, 180 };

	m_vars.m_vehicle_esp.m_name_bg_color = { 229, 64, 64, 180 };
	m_vars.m_vehicle_esp.m_snapline_color = { 229, 64, 64, 180 };
	m_vars.m_vehicle_esp.m_2d_box_color = { 229, 64, 64, 180 };
	m_vars.m_vehicle_esp.m_2d_corners_color = { 229, 64, 64, 180 };
	m_vars.m_vehicle_esp.m_3d_box_color = { 229, 64, 64, 180 };

	add_string("ESP");
	add_string("Driver");
	add_string("Boost");
	add_string("Acrobatics");
	add_string("Gravity");
	add_string("Teleport");
	add_string("Fix");
	add_string("Empty Vehicle Seats");
	add_string("Random Paint");
	add_string("Honk Horn");
	add_string("Drive to Me");
	add_string("Explode");
	add_string("Delete");
	add_string("Freeze Position");
	add_string("Revive");
	add_string("Kill");
	add_string("Clone");
}

void local_entities_menu::update() {}

void local_entities_menu::update_once() {
	clear_options(1);

	// vehicle
	if (m_vars.m_type == 0) {
		add_option(submenu_option(get_string("ESP"))
			.add_submenu<helper_esp_menu>()
			.add_click([] {
				helper_esp_menu::get()->set_parent<local_entities_menu>();
				helper::esp::vars::m_vars.m_current = &m_vars.m_vehicle_esp;
				helper::esp::vars::m_vars.m_current->m_ped = false;
			}));

		add_option(scroll_option<int>(SCROLLSELECT, get_string("Driver"))
			.add_scroll(m_vars.m_driver, 0, NUMOF(driver), driver)
			.add_click([] { spawner::vehicle::manage::edit::vars::run(0, false, true, &m_vars.m_driver); }));

		add_option(scroll_option<float>(SCROLLSELECT, get_string("Boost"))
			.add_scroll(m_vars.m_boost, 0, NUMOF(boost), boost)
			.add_click([] { spawner::vehicle::manage::edit::vars::run(1, false, true, &m_vars.m_boost); }));

		add_option(scroll_option<std::pair<math::vector3_<float>, math::vector3_<float>>>(SCROLLSELECT, get_string("Acrobatics"))
			.add_scroll(m_vars.m_acrobatics, 0, NUMOF(global::lists::g_acrobatics), global::lists::g_acrobatics)
			.add_click([] { spawner::vehicle::manage::edit::vars::run(2, false, true, &m_vars.m_acrobatics); }));

		add_option(scroll_option<float>(SCROLLSELECT, get_string("Gravity"))
			.add_scroll(m_vars.m_gravity, 0, NUMOF(global::lists::g_gravity), global::lists::g_gravity)
			.add_click([] { spawner::vehicle::manage::edit::vars::run(3, false, true, &m_vars.m_gravity); }));

		add_option(scroll_option<int>(SCROLLSELECT, get_string("Teleport"))
			.add_scroll(m_vars.m_teleport, 0, 1, teleport)
			.add_click([] { spawner::vehicle::manage::edit::vars::run(4, false, true, &m_vars.m_teleport); }));

		add_option(button_option(get_string("Fix"))
			.add_click([] { spawner::vehicle::manage::edit::vars::run(5, false, true, nullptr); }));

		add_option(button_option(get_string("Empty Vehicle Seats"))
			.add_click([] { spawner::vehicle::manage::edit::vars::run(6, false, true, nullptr); }));

		add_option(button_option(get_string("Random Paint"))
			.add_click([] { spawner::vehicle::manage::edit::vars::run(7, false, true, nullptr); }));

		add_option(button_option(get_string("Honk Horn"))
			.add_click([] { spawner::vehicle::manage::edit::vars::run(8, false, true, nullptr); }));

		add_option(button_option(get_string("Drive to Me"))
			.add_click([] { spawner::vehicle::manage::edit::vars::run(9, false, true, nullptr); }));

		add_option(button_option(get_string("Explode"))
			.add_click([] { spawner::vehicle::manage::edit::vars::run(10, false, true, nullptr); }));

		add_option(button_option(get_string("Delete"))
			.add_click([] {
				spawner::vehicle::manage::edit::vars::run(11, false, true, nullptr);
			}));

		return;
	}

	// object
	if (m_vars.m_type == 1) {
		add_option(submenu_option(get_string("ESP"))
			.add_submenu<helper_esp_menu>()
			.add_click([] {
				helper_esp_menu::get()->set_parent<local_entities_menu>();
				helper::esp::vars::m_vars.m_current = &m_vars.m_object_esp;
				helper::esp::vars::m_vars.m_current->m_ped = false;
			}));

		add_option(scroll_option<int>(SCROLLSELECT, get_string("Teleport"))
			.add_click([] { spawner::object::manage::edit::vars::run(0, false, true, &m_vars.m_teleport); })
			.add_scroll(m_vars.m_teleport, 0, 1, teleport));

		add_option(button_option(get_string("Freeze Position"))
			.add_click([] { spawner::object::manage::edit::vars::run(1, false, true, 0); }));

		add_option(button_option(get_string("Delete"))
			.add_click([] { spawner::object::manage::edit::vars::run(2, false, true, nullptr); }));

		return;
	}

	// ped
	if (m_vars.m_type == 2) {
		add_option(submenu_option(get_string("ESP"))
			.add_submenu<helper_esp_menu>()
			.add_click([] {
				helper_esp_menu::get()->set_parent<local_entities_menu>();
				helper::esp::vars::m_vars.m_current = &m_vars.m_ped_esp;
				m_vars.m_ped_esp.m_ped = true;
			}));

		add_option(scroll_option<int>(SCROLLSELECT, get_string("Teleport"))
			.add_click([] { spawner::ped::manage::edit::vars::run(0, false, true, &m_vars.m_teleport); })
			.add_scroll(m_vars.m_teleport, 0, NUMOF(teleport), teleport));

		add_option(button_option(get_string("Revive"))
			.add_click([] { spawner::ped::manage::edit::vars::run(2, false, true, nullptr); }));

		add_option(button_option(get_string("Kill"))
			.add_click([] { spawner::ped::manage::edit::vars::run(3, false, true, nullptr); }));

		add_option(button_option(get_string("Explode"))
			.add_click([] { spawner::ped::manage::edit::vars::run(4, false, true, nullptr); }));

		add_option(button_option(get_string("Clone"))
			.add_click([] { spawner::ped::manage::edit::vars::run(5, false, true, nullptr); }));

		add_option(button_option(get_string("Delete"))
			.add_click([] { spawner::ped::manage::edit::vars::run(1, false, true, nullptr); }));
	}
}

void local_entities_menu::feature_update() {
	if (m_vars.m_vehicle_esp.m_name
		|| m_vars.m_vehicle_esp.m_snapline
		|| m_vars.m_vehicle_esp.m_2d_box
		|| m_vars.m_vehicle_esp.m_2d_corners
		|| m_vars.m_vehicle_esp.m_3d_box
		|| m_vars.m_vehicle_esp.m_3d_axis) {
		global::vars::g_vehicle_pool->for_each([] (Entity entity, void* veh) {
			if (entity == menu::player::get_local_player().m_vehicle) return;

			if (m_vars.m_vehicle_esp.m_name) {
				helper::esp::vars::name_esp(m_vars.m_vehicle_esp, entity, native::get_label_text(native::get_display_name_from_vehicle_model(native::get_entity_model(entity))));
			}

			if (m_vars.m_vehicle_esp.m_snapline) {
				helper::esp::vars::snapline_esp(m_vars.m_vehicle_esp, entity);
			}

			if (m_vars.m_vehicle_esp.m_2d_box) {
				helper::esp::vars::_2d_esp(m_vars.m_vehicle_esp, entity, 0);
			}

			if (m_vars.m_vehicle_esp.m_2d_corners) {
				helper::esp::vars::_2d_esp(m_vars.m_vehicle_esp, entity, 1);
			}

			if (m_vars.m_vehicle_esp.m_3d_box) {
				helper::esp::vars::_3d_esp(m_vars.m_vehicle_esp, entity, 0);
			}

			if (m_vars.m_vehicle_esp.m_3d_axis) {
				helper::esp::vars::_3d_esp(m_vars.m_vehicle_esp, entity, 1);
			}

			if (m_vars.m_vehicle_esp.m_2d_box_rainbow.m_rainbow_toggle) m_vars.m_vehicle_esp.m_2d_box_rainbow.m_rainbow.run();
			if (m_vars.m_vehicle_esp.m_2d_corners_rainbow.m_rainbow_toggle) m_vars.m_vehicle_esp.m_2d_corners_rainbow.m_rainbow.run();
			if (m_vars.m_vehicle_esp.m_3d_box_rainbow.m_rainbow_toggle) m_vars.m_vehicle_esp.m_3d_box_rainbow.m_rainbow.run();
			if (m_vars.m_vehicle_esp.m_name_bg_rainbow.m_rainbow_toggle) m_vars.m_vehicle_esp.m_name_bg_rainbow.m_rainbow.run();
			if (m_vars.m_vehicle_esp.m_name_text_rainbow.m_rainbow_toggle) m_vars.m_vehicle_esp.m_name_text_rainbow.m_rainbow.run();
			if (m_vars.m_vehicle_esp.m_snapline_rainbow.m_rainbow_toggle) m_vars.m_vehicle_esp.m_snapline_rainbow.m_rainbow.run();
		});
	}

	if (m_vars.m_object_esp.m_name
		|| m_vars.m_object_esp.m_snapline
		|| m_vars.m_object_esp.m_2d_box
		|| m_vars.m_object_esp.m_2d_corners
		|| m_vars.m_object_esp.m_3d_box
		|| m_vars.m_object_esp.m_3d_axis) {
		global::vars::g_object_pool->for_each([] (Entity entity, void* object) {
			if (m_vars.m_object_esp.m_name) {
				helper::esp::vars::name_esp(m_vars.m_object_esp, entity);
			}

			if (m_vars.m_object_esp.m_snapline) {
				helper::esp::vars::snapline_esp(m_vars.m_object_esp, entity);
			}

			if (m_vars.m_object_esp.m_2d_box) {
				helper::esp::vars::_2d_esp(m_vars.m_object_esp, entity, 0);
			}

			if (m_vars.m_object_esp.m_2d_corners) {
				helper::esp::vars::_2d_esp(m_vars.m_object_esp, entity, 1);
			}

			if (m_vars.m_object_esp.m_3d_box) {
				helper::esp::vars::_3d_esp(m_vars.m_object_esp, entity, 0);
			}

			if (m_vars.m_object_esp.m_3d_axis) {
				helper::esp::vars::_3d_esp(m_vars.m_object_esp, entity, 1);
			}

			if (m_vars.m_object_esp.m_2d_box_rainbow.m_rainbow_toggle) m_vars.m_object_esp.m_2d_box_rainbow.m_rainbow.run();
			if (m_vars.m_object_esp.m_2d_corners_rainbow.m_rainbow_toggle) m_vars.m_object_esp.m_2d_corners_rainbow.m_rainbow.run();
			if (m_vars.m_object_esp.m_3d_box_rainbow.m_rainbow_toggle) m_vars.m_object_esp.m_3d_box_rainbow.m_rainbow.run();
			if (m_vars.m_object_esp.m_name_bg_rainbow.m_rainbow_toggle) m_vars.m_object_esp.m_name_bg_rainbow.m_rainbow.run();
			if (m_vars.m_object_esp.m_name_text_rainbow.m_rainbow_toggle) m_vars.m_object_esp.m_name_text_rainbow.m_rainbow.run();
			if (m_vars.m_object_esp.m_snapline_rainbow.m_rainbow_toggle) m_vars.m_object_esp.m_snapline_rainbow.m_rainbow.run();
		});
	}

	if (m_vars.m_ped_esp.m_name
		|| m_vars.m_ped_esp.m_snapline
		|| m_vars.m_ped_esp.m_2d_box
		|| m_vars.m_ped_esp.m_2d_corners
		|| m_vars.m_ped_esp.m_3d_box
		|| m_vars.m_ped_esp.m_3d_axis
		|| m_vars.m_ped_esp.m_skeleton_bones
		|| m_vars.m_ped_esp.m_skeleton_joints) {
		global::vars::g_ped_pool->for_each([] (Entity entity, void* ped) {
			if (entity == menu::player::get_local_player().m_ped) return;

			if (m_vars.m_ped_esp.m_name) {
				helper::esp::vars::name_esp(m_vars.m_ped_esp, entity);
			}

			if (m_vars.m_ped_esp.m_snapline) {
				helper::esp::vars::snapline_esp(m_vars.m_ped_esp, entity);
			}

			if (m_vars.m_ped_esp.m_2d_box) {
				helper::esp::vars::_2d_esp(m_vars.m_ped_esp, entity, 0);
			}

			if (m_vars.m_ped_esp.m_2d_corners) {
				helper::esp::vars::_2d_esp(m_vars.m_ped_esp, entity, 1);
			}

			if (m_vars.m_ped_esp.m_3d_box) {
				helper::esp::vars::_3d_esp(m_vars.m_ped_esp, entity, 0);
			}

			if (m_vars.m_ped_esp.m_3d_axis) {
				helper::esp::vars::_3d_esp(m_vars.m_ped_esp, entity, 1);
			}

			if (m_vars.m_ped_esp.m_skeleton_bones) {
				helper::esp::vars::skeleton_esp(m_vars.m_ped_esp, entity, 0);
			}

			if (m_vars.m_ped_esp.m_skeleton_joints) {
				helper::esp::vars::skeleton_esp(m_vars.m_ped_esp, entity, 1);
			}

			if (m_vars.m_ped_esp.m_2d_box_rainbow.m_rainbow_toggle) m_vars.m_ped_esp.m_2d_box_rainbow.m_rainbow.run();
			if (m_vars.m_ped_esp.m_2d_corners_rainbow.m_rainbow_toggle) m_vars.m_ped_esp.m_2d_corners_rainbow.m_rainbow.run();
			if (m_vars.m_ped_esp.m_3d_box_rainbow.m_rainbow_toggle) m_vars.m_ped_esp.m_3d_box_rainbow.m_rainbow.run();
			if (m_vars.m_ped_esp.m_name_bg_rainbow.m_rainbow_toggle) m_vars.m_ped_esp.m_name_bg_rainbow.m_rainbow.run();
			if (m_vars.m_ped_esp.m_name_text_rainbow.m_rainbow_toggle) m_vars.m_ped_esp.m_name_text_rainbow.m_rainbow.run();
			if (m_vars.m_ped_esp.m_snapline_rainbow.m_rainbow_toggle) m_vars.m_ped_esp.m_snapline_rainbow.m_rainbow.run();
			if (m_vars.m_ped_esp.m_skeleton_bones_rainbow.m_rainbow_toggle) m_vars.m_ped_esp.m_skeleton_bones_rainbow.m_rainbow.run();
			if (m_vars.m_ped_esp.m_skeleton_joints_rainbow.m_rainbow_toggle) m_vars.m_ped_esp.m_skeleton_joints_rainbow.m_rainbow.run();
		});
	}
}

local_entities_menu* g_instance;
local_entities_menu* local_entities_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new local_entities_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}