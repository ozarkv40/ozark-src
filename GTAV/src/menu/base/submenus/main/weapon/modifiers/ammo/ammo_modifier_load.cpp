#include "ammo_modifier_load.h"
#include "menu/base/submenu_handler.h"
#include "ammo_modifier.h"
#include "util/json.h"
#include "util/log.h"
#include "util/dirs.h"
#include "ammo_modifier_swap.h"
#include "ammo_modifier_edit.h"
#include "ammo_modifier_swap.h"
#include <fstream>

using namespace weapon::ammo::load::vars;

namespace weapon::ammo::load::vars {
	variables m_vars;

	struct ModifierSave {
		std::string m_name;
		uint32_t m_model;
		uint32_t m_swap;
		float m_damage;
		float m_force;
		float m_speed;
	};

	void load_modifier(ModifierSave modifier) {
		if (modifier.m_model != modifier.m_swap) {
			swap::vars::swap(modifier.m_model, modifier.m_swap);
		}

		edit::vars::m_vars.m_current_hash = modifier.m_model;

		rage::types::weapon_info* weapon = edit::vars::get_active_weapon();
		if (weapon) {
			weapon->m_damage = modifier.m_damage;
			weapon->m_force = modifier.m_force;
			weapon->m_speed = modifier.m_speed;
		}
	}

	void save_modifier(const char* name, uint32_t model) {
		uint32_t swap_model = model;

		auto vit = std::find_if(edit::vars::m_vars.m_modifiers.begin(), edit::vars::m_vars.m_modifiers.end(), [=](edit::vars::EditContext& Context) {
			return Context.m_hash == model;
		});

		if (vit != edit::vars::m_vars.m_modifiers.end()) {
			swap_model = vit->m_swap;
		}

		edit::vars::m_vars.m_current_hash = model;

		rage::types::weapon_info* weapon = edit::vars::get_active_weapon();
		if (weapon) {
			try {
				nlohmann::json json;

				std::ifstream input(util::dirs::get_path(ammo_modifier));
				if (input.good()) {
					input >> json;
					input.close();
				}

				std::ofstream output(util::dirs::get_path(ammo_modifier));
				if (output.good()) {
					json[name] = nlohmann::json::array({
						model,
						swap_model,
						weapon->m_damage,
						weapon->m_force,
						weapon->m_speed
					});

					output << json.dump(4);
					output.close();
				}
			} catch (std::exception& e) {
				LOG_WARN("[json] %s", e.what());
			}
		}
	}
}

void ammo_modifier_load_menu::load() {
	set_name("Load modifier");
	set_parent<ammo_modifier_menu>();

	add_string("~m~None");
}

void ammo_modifier_load_menu::update() {}

void ammo_modifier_load_menu::update_once() {
	clear_options(0);

	try {
		std::ifstream input(util::dirs::get_path(ammo_modifier));
		if (input.good()) {
			nlohmann::json json;
			input >> json;
			input.close();

			if (json.size() > 0) {
				std::vector<ModifierSave> modifiers;

				for (auto& it = json.begin(); it != json.end(); ++it) {
					nlohmann::json data = *it;
					modifiers.push_back({ it.key(), data[0].get<uint32_t>(), data[1].get<uint32_t>(), data[2].get<float>(), data[3].get<float>(), data[4].get<float>() });
				}

				for (ModifierSave& modifier : modifiers) {
					add_option(button_option(modifier.m_name)
						.add_click([=] { load_modifier(modifier); }));
				}
			} else {
				add_option(button_option(get_string("~m~None")).ref());
			}
		} else {
			add_option(button_option(get_string("~m~None")).ref());
		}
	} catch (std::exception& e) {
		LOG_WARN("[Json] %s", e.what());
	}
}

void ammo_modifier_load_menu::feature_update() {}

ammo_modifier_load_menu* g_instance;
ammo_modifier_load_menu* ammo_modifier_load_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new ammo_modifier_load_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}