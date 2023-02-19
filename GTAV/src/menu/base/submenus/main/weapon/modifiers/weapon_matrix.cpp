#include "weapon_matrix.h"
#include "menu/base/submenu_handler.h"
#include "../weapon_modifiers.h"
#include "rage/engine.h"
#include "../weapon_modifiers.h"

using namespace weapon::matrix::vars;

namespace weapon::matrix::vars {
	variables m_vars;
}

void weapon_matrix_menu::load() {
	set_name("Matrix");
	set_parent<weapon_modifiers_menu>();

	add_option(number_option<float>(TOGGLE, "Left - (X)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_left.x)
		.add_number(m_vars.m_matrix_val.m_left.x, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_left.x) {
					object->m_matrix.m_left.x = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_left.x;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Left - (Y)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_left.y)
		.add_number(m_vars.m_matrix_val.m_left.y, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_left.y) {
					object->m_matrix.m_left.y = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_left.y;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Left - (Z)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_left.z)
		.add_number(m_vars.m_matrix_val.m_left.z, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_left.z) {
					object->m_matrix.m_left.z = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_left.z;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Left - (W)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_left.w)
		.add_number(m_vars.m_matrix_val.m_left.w, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_left.w) {
					object->m_matrix.m_left.w = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_left.w;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Up - (X)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_up.x)
		.add_number(m_vars.m_matrix_val.m_up.x, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_up.x) {
					object->m_matrix.m_up.x = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_up.x;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Up - (Y)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_up.y)
		.add_number(m_vars.m_matrix_val.m_up.y, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_up.y) {
					object->m_matrix.m_up.y = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_up.y;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Up - (Z)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_up.z)
		.add_number(m_vars.m_matrix_val.m_up.z, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_up.z) {
					object->m_matrix.m_up.z = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_up.z;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Up - (W, Width)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_up.w)
		.add_number(m_vars.m_matrix_val.m_up.w, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_up.w) {
					object->m_matrix.m_up.w = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_up.w;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Forward - (X)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_forward.x)
		.add_number(m_vars.m_matrix_val.m_forward.x, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_forward.x) {
					object->m_matrix.m_forward.x = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_forward.x;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Forward - (Y)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_forward.y)
		.add_number(m_vars.m_matrix_val.m_forward.y, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_forward.y) {
					object->m_matrix.m_forward.y = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_forward.y;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Forward - (Z)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_forward.z)
		.add_number(m_vars.m_matrix_val.m_forward.z, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_forward.z) {
					object->m_matrix.m_forward.z = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_forward.z;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Forward - (W, Height)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_matrix.m_forward.w)
		.add_number(m_vars.m_matrix_val.m_forward.w, "%.2f", 0.01f).set_scroll_speed(10).add_min(0.f).add_max(100.f)
		.add_update([](number_option<float>* option, int position) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (!m_vars.m_matrix.m_forward.w) {
					object->m_matrix.m_forward.w = m_vars.m_original[weapon::modifiers::vars::get_weapon_info()].m_forward.w;
				}
			}
		})
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand; })
		.add_savable(get_submenu_name_stack()));
}

void weapon_matrix_menu::update() {}

void weapon_matrix_menu::update_once() {
	if (menu::player::get_local_player().m_has_weapon_in_hand) {
		rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
		if (object) {
			if (m_vars.m_original.find(weapon::modifiers::vars::get_weapon_info()) == m_vars.m_original.end()) {
				m_vars.m_original[weapon::modifiers::vars::get_weapon_info()] = object->m_matrix;
			}

			if (!m_vars.m_matrix.m_left.x) m_vars.m_matrix_val.m_left.x = object->m_matrix.m_left.x;
			if (!m_vars.m_matrix.m_left.y) m_vars.m_matrix_val.m_left.y = object->m_matrix.m_left.y;
			if (!m_vars.m_matrix.m_left.z) m_vars.m_matrix_val.m_left.z = object->m_matrix.m_left.z;
			if (!m_vars.m_matrix.m_left.w) m_vars.m_matrix_val.m_left.w = object->m_matrix.m_left.w;

			if (!m_vars.m_matrix.m_up.x) m_vars.m_matrix_val.m_up.x = object->m_matrix.m_up.x;
			if (!m_vars.m_matrix.m_up.y) m_vars.m_matrix_val.m_up.y = object->m_matrix.m_up.y;
			if (!m_vars.m_matrix.m_up.z) m_vars.m_matrix_val.m_up.z = object->m_matrix.m_up.z;
			if (!m_vars.m_matrix.m_up.w) m_vars.m_matrix_val.m_up.w = object->m_matrix.m_up.w;

			if (!m_vars.m_matrix.m_forward.x) m_vars.m_matrix_val.m_forward.x = object->m_matrix.m_forward.x;
			if (!m_vars.m_matrix.m_forward.y) m_vars.m_matrix_val.m_forward.y = object->m_matrix.m_forward.y;
			if (!m_vars.m_matrix.m_forward.z) m_vars.m_matrix_val.m_forward.z = object->m_matrix.m_forward.z;
			if (!m_vars.m_matrix.m_forward.w) m_vars.m_matrix_val.m_forward.w = object->m_matrix.m_forward.w;
		}
	}
}

void weapon_matrix_menu::feature_update() {
	if (menu::player::get_local_player().m_has_weapon_in_hand) {
		if (m_vars.m_original.find(weapon::modifiers::vars::get_weapon_info()) != m_vars.m_original.end()) {
			rage::types::object* object = (rage::types::object*)rage::engine::get_entity_address(menu::player::get_local_player().m_weapon_entity);
			if (object) {
				if (m_vars.m_matrix.m_left.x) object->m_matrix.m_left.x = m_vars.m_matrix_val.m_left.x;
				if (m_vars.m_matrix.m_left.y) object->m_matrix.m_left.y = m_vars.m_matrix_val.m_left.y;
				if (m_vars.m_matrix.m_left.z) object->m_matrix.m_left.z = m_vars.m_matrix_val.m_left.z;
				if (m_vars.m_matrix.m_left.w) object->m_matrix.m_left.w = m_vars.m_matrix_val.m_left.w;

				if (m_vars.m_matrix.m_up.x) object->m_matrix.m_up.x = m_vars.m_matrix_val.m_up.x;
				if (m_vars.m_matrix.m_up.y) object->m_matrix.m_up.y = m_vars.m_matrix_val.m_up.y;
				if (m_vars.m_matrix.m_up.z) object->m_matrix.m_up.z = m_vars.m_matrix_val.m_up.z;
				if (m_vars.m_matrix.m_up.w) object->m_matrix.m_up.w = m_vars.m_matrix_val.m_up.w;

				if (m_vars.m_matrix.m_forward.x) object->m_matrix.m_forward.x = m_vars.m_matrix_val.m_forward.x;
				if (m_vars.m_matrix.m_forward.y) object->m_matrix.m_forward.y = m_vars.m_matrix_val.m_forward.y;
				if (m_vars.m_matrix.m_forward.z) object->m_matrix.m_forward.z = m_vars.m_matrix_val.m_forward.z;
				if (m_vars.m_matrix.m_forward.w) object->m_matrix.m_forward.w = m_vars.m_matrix_val.m_forward.w;
			}
		}
	}
}

weapon_matrix_menu* g_instance;
weapon_matrix_menu* weapon_matrix_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new weapon_matrix_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}