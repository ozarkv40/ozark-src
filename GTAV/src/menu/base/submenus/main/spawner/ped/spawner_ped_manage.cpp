#include "spawner_ped_manage.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"
#include "edit/spawner_ped_manage_edit.h"

using namespace spawner::ped::manage::vars;

namespace spawner::ped::manage::vars {
	variables m_vars;
}

void spawner_ped_manage_menu::load() {
	set_name("Manage Spawned Peds");
	set_parent<spawner_menu>();

	add_option(submenu_option("All Peds")
		.add_translate().add_hotkey()
		.add_click([] {
			spawner::ped::manage::edit::vars::m_vars.m_editing_all = true;
			spawner::ped::manage::edit::vars::m_vars.m_esp = &m_vars.m_esp;
			m_vars.m_esp.m_ped = true;
		})
		.add_submenu<spawner_ped_manage_edit_menu>());

	add_option(button_option("Clear Manager")
		.add_translate().add_hotkey()
		.add_click([this] { m_vars.m_peds.clear(); update_once(); })
		.add_tooltip("Does NOT delete the peds from the world, only from the manager"));

	add_option(break_option("Peds")
		.add_translate());

	add_string("~m~None");
}

void spawner_ped_manage_menu::update() {}

void spawner_ped_manage_menu::update_once() {
	clear_options(3);

	for (std::size_t i = 0; i < m_vars.m_peds.size(); i++) {
		if (!native::does_entity_exist(m_vars.m_peds[i].m_handle)) {
			m_vars.m_peds.erase(m_vars.m_peds.begin() + i);
		}
	}

	if (!m_vars.m_peds.empty()) {
		for (std::size_t i = 0; i < m_vars.m_peds.size(); i++) {
			add_option(submenu_option(util::va::va("[%i] %s", i + 1, m_vars.m_peds[i].m_name.c_str()))
				.add_click([=] {
					spawner::ped::manage::edit::vars::m_vars.m_editing_all = false;
					spawner::ped::manage::edit::vars::m_vars.m_esp = &m_vars.m_peds[i].m_esp;
					spawner::ped::manage::edit::vars::m_vars.m_selected = i;
				})
				.add_submenu<spawner_ped_manage_edit_menu>());
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void spawner_ped_manage_menu::feature_update() {
	for (spawned_ped& ped : m_vars.m_peds) {
		if (ped.m_esp.m_name || m_vars.m_esp.m_name) {
			helper::esp::vars::name_esp(ped.m_esp.m_name ? ped.m_esp : m_vars.m_esp, ped.m_handle, ped.m_name);
		}

		if (ped.m_esp.m_snapline || m_vars.m_esp.m_snapline) {
			helper::esp::vars::snapline_esp(ped.m_esp.m_snapline ? ped.m_esp : m_vars.m_esp, ped.m_handle);
		}

		if (ped.m_esp.m_2d_box || m_vars.m_esp.m_2d_box) {
			helper::esp::vars::_2d_esp(ped.m_esp.m_2d_box ? ped.m_esp : m_vars.m_esp, ped.m_handle, 0);
		}

		if (ped.m_esp.m_2d_corners || m_vars.m_esp.m_2d_corners) {
			helper::esp::vars::_2d_esp(ped.m_esp.m_2d_corners ? ped.m_esp : m_vars.m_esp, ped.m_handle, 1);
		}

		if (ped.m_esp.m_3d_box || m_vars.m_esp.m_3d_box) {
			helper::esp::vars::_3d_esp(ped.m_esp.m_3d_box ? ped.m_esp : m_vars.m_esp, ped.m_handle, 0);
		}

		if (ped.m_esp.m_3d_axis || m_vars.m_esp.m_3d_axis) {
			helper::esp::vars::_3d_esp(ped.m_esp.m_3d_axis ? ped.m_esp : m_vars.m_esp, ped.m_handle, 1);
		}

		if (ped.m_esp.m_skeleton_bones || m_vars.m_esp.m_skeleton_bones) {
			helper::esp::vars::skeleton_esp(ped.m_esp.m_skeleton_bones ? ped.m_esp : m_vars.m_esp, ped.m_handle, 0);
		}

		if (ped.m_esp.m_skeleton_joints || m_vars.m_esp.m_skeleton_joints) {
			helper::esp::vars::skeleton_esp(ped.m_esp.m_skeleton_joints ? ped.m_esp : m_vars.m_esp, ped.m_handle, 1);
		}

		if (!m_vars.m_esp.m_2d_box_rainbow.m_rainbow_toggle && ped.m_esp.m_2d_box_rainbow.m_rainbow_toggle) ped.m_esp.m_2d_box_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_2d_corners_rainbow.m_rainbow_toggle && ped.m_esp.m_2d_corners_rainbow.m_rainbow_toggle) ped.m_esp.m_2d_corners_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_3d_box_rainbow.m_rainbow_toggle && ped.m_esp.m_3d_box_rainbow.m_rainbow_toggle) ped.m_esp.m_3d_box_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_name_bg_rainbow.m_rainbow_toggle && ped.m_esp.m_name_bg_rainbow.m_rainbow_toggle) ped.m_esp.m_name_bg_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_name_text_rainbow.m_rainbow_toggle && ped.m_esp.m_name_text_rainbow.m_rainbow_toggle) ped.m_esp.m_name_text_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_skeleton_bones_rainbow.m_rainbow_toggle && ped.m_esp.m_skeleton_bones_rainbow.m_rainbow_toggle) ped.m_esp.m_skeleton_bones_rainbow.m_rainbow.run();
		if (!m_vars.m_esp.m_skeleton_joints_rainbow.m_rainbow_toggle && ped.m_esp.m_skeleton_joints_rainbow.m_rainbow_toggle) ped.m_esp.m_skeleton_joints_rainbow.m_rainbow.run();
	}

	if (m_vars.m_esp.m_2d_box_rainbow.m_rainbow_toggle) m_vars.m_esp.m_2d_box_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_2d_corners_rainbow.m_rainbow_toggle) m_vars.m_esp.m_2d_corners_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_3d_box_rainbow.m_rainbow_toggle) m_vars.m_esp.m_3d_box_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_name_bg_rainbow.m_rainbow_toggle) m_vars.m_esp.m_name_bg_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_name_text_rainbow.m_rainbow_toggle) m_vars.m_esp.m_name_text_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_skeleton_bones_rainbow.m_rainbow_toggle) m_vars.m_esp.m_skeleton_bones_rainbow.m_rainbow.run();
	if (m_vars.m_esp.m_skeleton_joints_rainbow.m_rainbow_toggle) m_vars.m_esp.m_skeleton_joints_rainbow.m_rainbow.run();
}

spawner_ped_manage_menu* g_instance;
spawner_ped_manage_menu* spawner_ped_manage_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_ped_manage_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}