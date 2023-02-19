#include "helper_esp_settings.h"
#include "menu/base/submenu_handler.h"
#include "../helper_esp.h"
#include "helper_esp_settings_edit.h"

using namespace helper::esp::settings::vars;

namespace helper::esp::settings::vars {
	variables m_vars;
}

void helper_esp_settings_menu::load() {
	set_name("Settings");
	set_parent<helper_esp_menu>();

	add_option(submenu_option("Name")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_name_text_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_name_text_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_name_text_rainbow.m_rainbow_toggle;
		}));

	add_option(submenu_option("Name - Background")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_name_bg_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_name_bg_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_name_bg_rainbow.m_rainbow_toggle;
		}));

	/*add_option(submenu_option("2D - Box")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_2d_box_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_2d_box_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_2d_box_rainbow.m_rainbow_toggle;
		}));

	add_option(submenu_option("2D - Corners")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_2d_corners_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_2d_corners_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_2d_corners_rainbow.m_rainbow_toggle;
		}));*/

	add_option(submenu_option("3D - Box")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_3d_box_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_3d_box_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_3d_box_rainbow.m_rainbow_toggle;
		}));

	add_option(submenu_option("Skeleton - Bones")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_skeleton_bones_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_skeleton_bones_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_skeleton_bones_rainbow.m_rainbow_toggle;
		}).add_requirement([] { return helper::esp::vars::m_vars.m_current->m_ped; }));

	add_option(submenu_option("Skeleton - Joints")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_skeleton_joints_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_skeleton_joints_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_skeleton_joints_rainbow.m_rainbow_toggle;
	}).add_requirement([] { return helper::esp::vars::m_vars.m_current->m_ped; }));

	/*add_option(submenu_option("Weapon")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_weapon_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_weapon_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_weapon_rainbow.m_rainbow_toggle;
	}).add_requirement([] { return helper::esp::vars::m_vars.m_current->m_ped; }));*/

	add_option(submenu_option("Snapline")
		.add_translate()
		.add_submenu<helper_esp_settings_edit_menu>()
		.add_click_this([] (submenu_option* option) {
			helper_esp_settings_edit_menu::get()->set_name(option->get_name().get(), false, false);
			helper::esp::settings::edit::vars::m_vars.m_color = &helper::esp::vars::m_vars.m_current->m_snapline_color;
			helper::esp::settings::edit::vars::m_vars.m_rainbow = &helper::esp::vars::m_vars.m_current->m_snapline_rainbow.m_rainbow;
			helper::esp::settings::edit::vars::m_vars.m_rainbow_toggle = &helper::esp::vars::m_vars.m_current->m_snapline_rainbow.m_rainbow_toggle;
		}));
}

void helper_esp_settings_menu::update() {}

void helper_esp_settings_menu::update_once() {}

void helper_esp_settings_menu::feature_update() {}

helper_esp_settings_menu* g_instance;
helper_esp_settings_menu* helper_esp_settings_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new helper_esp_settings_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}