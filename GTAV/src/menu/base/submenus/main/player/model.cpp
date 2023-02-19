#include "model.h"
#include "menu/base/submenu_handler.h"
#include "appearance.h"
#include "global/lists.h"
#include "menu/base/util/control.h"
#include "util/fiber.h"

using namespace player::model::vars;

namespace player::model::vars {
	variables m_vars;

	void change_model(uint32_t hash) {
		if (native::is_model_in_cdimage(hash)) {
			if (native::is_model_valid(hash)) {
				menu::control::request_model(hash, [](uint32_t ModelHash) {
					native::set_player_model(menu::player::get_local_player().m_id, ModelHash);
					m_vars.m_last_model = ModelHash;

					util::fiber::sleep(2000);
					global::vars::g_reload_weapons = true;
				});
			}
		}
	}
}

void model_menu::load() {
	set_name("Model");
	set_parent<appearance_menu>();

	add_option(button_option("Refresh Model")
		.add_translate()
		.add_click([] {
			native::reset_ped_visible_damage(menu::player::get_local_player().m_ped);
			native::clear_ped_blood_damage(menu::player::get_local_player().m_ped);
			native::clear_ped_decorations(menu::player::get_local_player().m_ped);
		}));

	add_option(button_option("Refresh Model Cache")
		.add_translate()
		.add_click([] {
			m_vars.m_last_model = 0;
		})
		.add_tooltip("Refresh the cache that re-applies your model when you die"));

	add_option(button_option("Input Custom Model")
		.add_translate()
		.add_keyboard("Input the model! (Hint: name, hash or numeric)", 30, [](button_option*, const char* name) {
			if (name) {
				if (name[0] == '0' && (name[1] == 'x' || name[1] == 'X')) {
					// hash
					change_model((uint32_t)_strtoui64(name, 0, 0));
				} else {
					std::string str(name);
					if (std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end()) {
						// numeric
						change_model((uint32_t)atoi(name));
					} else {
						// name
						change_model(native::get_hash_key(name));
					}
				}
			}
		}));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Popular")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_popular, 0, NUMOF(global::lists::g_ped_model_popular), global::lists::g_ped_model_popular).loop()
		.add_click([] { change_model(global::lists::g_ped_model_popular[m_vars.m_popular].m_result); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Story")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_story, 0, NUMOF(global::lists::g_ped_model_story), global::lists::g_ped_model_story).loop()
		.add_click([] { change_model(global::lists::g_ped_model_story[m_vars.m_story].m_result); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Animals")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_animals, 0, NUMOF(global::lists::g_ped_model_animal), global::lists::g_ped_model_animal).loop()
		.add_click([] { change_model(global::lists::g_ped_model_animal[m_vars.m_animals].m_result); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Emergency")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_emergency, 0, NUMOF(global::lists::g_ped_model_emergency), global::lists::g_ped_model_emergency).loop()
		.add_click([] { change_model(global::lists::g_ped_model_emergency[m_vars.m_emergency].m_result); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Role")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_role, 0, NUMOF(global::lists::g_ped_model_role), global::lists::g_ped_model_role).loop()
		.add_click([] { change_model(global::lists::g_ped_model_role[m_vars.m_role].m_result); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Ambient")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_ambient, 0, NUMOF(global::lists::g_ped_model_ambient), global::lists::g_ped_model_ambient).loop()
		.add_click([] { change_model(global::lists::g_ped_model_ambient[m_vars.m_ambient].m_result); }));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Misc")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_misc, 0, NUMOF(global::lists::g_ped_model_misc), global::lists::g_ped_model_misc).loop()
		.add_click([] { change_model(global::lists::g_ped_model_misc[m_vars.m_misc].m_result); }));
}

void model_menu::update() {}

void model_menu::update_once() {}

void model_menu::feature_update() {
	if (!menu::player::get_local_player().m_alive) {
		if (m_vars.m_last_model) {
			m_vars.m_reapply = true;
		}
	} else {
		if (m_vars.m_reapply) {
			m_vars.m_reapply = false;

			if (m_vars.m_last_model) {
				change_model(m_vars.m_last_model);
			}
		}
	}
}

model_menu* g_instance;
model_menu* model_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new model_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
