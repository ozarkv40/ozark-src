#include "spawner_object_manage.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"
#include "edit/spawner_object_manage_edit.h"

using namespace spawner::object::manage::vars;

namespace spawner::object::manage::vars {
	variables m_vars;
}

void spawner_object_manage_menu::load() {
	set_name("Manage Spawned Objects");
	set_parent<spawner_menu>();

	add_option(submenu_option("All Objects")
		.add_translate().add_hotkey()
		.add_click([] {
			spawner::object::manage::edit::vars::m_vars.m_editing_all = true;
			spawner::object::manage::edit::vars::m_vars.m_esp = &m_vars.m_esp;
		})
		.add_submenu<spawner_object_manage_edit_menu>());

	add_option(button_option("Clear Manager")
		.add_translate().add_hotkey()
		.add_click([this] { m_vars.m_objects.clear(); update_once(); })
		.add_tooltip("Does NOT delete the objects from the world, only from the manager"));

	add_option(break_option("Objects")
		.add_translate());

	add_string("~m~None");
}

void spawner_object_manage_menu::update() {}

void spawner_object_manage_menu::update_once() {
	clear_options(3);

	for (std::size_t i = 0; i < m_vars.m_objects.size(); i++) {
		if (!native::does_entity_exist(m_vars.m_objects[i].m_handle)) {
			m_vars.m_objects.erase(m_vars.m_objects.begin() + i);
		}
	}

	if (!m_vars.m_objects.empty()) {
		for (std::size_t i = 0; i < m_vars.m_objects.size(); i++) {
			add_option(submenu_option(util::va::va("[%i] %s", i + 1, m_vars.m_objects[i].m_name.c_str()))
				.add_click([=] {
					spawner::object::manage::edit::vars::m_vars.m_editing_all = false;
					spawner::object::manage::edit::vars::m_vars.m_esp = &m_vars.m_objects[i].m_esp;
					spawner::object::manage::edit::vars::m_vars.m_selected = i;
				})
				.add_submenu<spawner_object_manage_edit_menu>());
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void spawner_object_manage_menu::feature_update() {
	for (spawned_object& object : m_vars.m_objects) {
		if (object.m_esp.m_name || m_vars.m_esp.m_name) {
			helper::esp::vars::name_esp(object.m_esp.m_name ? object.m_esp : m_vars.m_esp, object.m_handle, object.m_name);
		}

		if (object.m_esp.m_snapline || m_vars.m_esp.m_snapline) {
			helper::esp::vars::snapline_esp(object.m_esp.m_snapline ? object.m_esp : m_vars.m_esp, object.m_handle);
		}

		if (object.m_esp.m_2d_box || m_vars.m_esp.m_2d_box) {
			helper::esp::vars::_2d_esp(object.m_esp.m_2d_box ? object.m_esp : m_vars.m_esp, object.m_handle, 0);
		}

		if (object.m_esp.m_2d_corners || m_vars.m_esp.m_2d_corners) {
			helper::esp::vars::_2d_esp(object.m_esp.m_2d_corners ? object.m_esp : m_vars.m_esp, object.m_handle, 1);
		}

		if (object.m_esp.m_3d_box || m_vars.m_esp.m_3d_box) {
			helper::esp::vars::_3d_esp(object.m_esp.m_3d_box ? object.m_esp : m_vars.m_esp, object.m_handle, 0);
		}

		if (object.m_esp.m_3d_axis || m_vars.m_esp.m_3d_axis) {
			helper::esp::vars::_3d_esp(object.m_esp.m_3d_axis ? object.m_esp : m_vars.m_esp, object.m_handle, 1);
		}

		if (object.m_esp.m_skeleton_bones || m_vars.m_esp.m_skeleton_bones) {
			helper::esp::vars::skeleton_esp(object.m_esp.m_skeleton_bones ? object.m_esp : m_vars.m_esp, object.m_handle, 0);
		}

		if (object.m_esp.m_skeleton_joints || m_vars.m_esp.m_skeleton_joints) {
			helper::esp::vars::skeleton_esp(object.m_esp.m_skeleton_joints ? object.m_esp : m_vars.m_esp, object.m_handle, 1);
		}

		if (!m_vars.m_esp.m_2d_box_rainbow.m_rainbow_toggle && object.m_esp.m_2d_box_rainbow.m_rainbow_toggle) object.m_esp.m_2d_box_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_2d_corners_rainbow.m_rainbow_toggle && object.m_esp.m_2d_corners_rainbow.m_rainbow_toggle) object.m_esp.m_2d_corners_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_3d_box_rainbow.m_rainbow_toggle && object.m_esp.m_3d_box_rainbow.m_rainbow_toggle) object.m_esp.m_3d_box_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_name_bg_rainbow.m_rainbow_toggle && object.m_esp.m_name_bg_rainbow.m_rainbow_toggle) object.m_esp.m_name_bg_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_name_text_rainbow.m_rainbow_toggle && object.m_esp.m_name_text_rainbow.m_rainbow_toggle) object.m_esp.m_name_text_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_skeleton_bones_rainbow.m_rainbow_toggle && object.m_esp.m_skeleton_bones_rainbow.m_rainbow_toggle) object.m_esp.m_skeleton_bones_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_skeleton_joints_rainbow.m_rainbow_toggle && object.m_esp.m_skeleton_joints_rainbow.m_rainbow_toggle) object.m_esp.m_skeleton_joints_rainbow.m_rainbow.run();
	}

	if (m_vars.m_esp.m_2d_box_rainbow.m_rainbow_toggle) m_vars.m_esp.m_2d_box_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_2d_corners_rainbow.m_rainbow_toggle) m_vars.m_esp.m_2d_corners_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_3d_box_rainbow.m_rainbow_toggle) m_vars.m_esp.m_3d_box_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_name_bg_rainbow.m_rainbow_toggle) m_vars.m_esp.m_name_bg_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_name_text_rainbow.m_rainbow_toggle) m_vars.m_esp.m_name_text_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_skeleton_bones_rainbow.m_rainbow_toggle) m_vars.m_esp.m_skeleton_bones_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_skeleton_joints_rainbow.m_rainbow_toggle) m_vars.m_esp.m_skeleton_joints_rainbow.m_rainbow.run();
}

spawner_object_manage_menu* g_instance;
spawner_object_manage_menu* spawner_object_manage_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_object_manage_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}