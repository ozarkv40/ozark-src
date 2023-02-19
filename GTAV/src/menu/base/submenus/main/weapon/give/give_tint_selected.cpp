#include "give_tint_selected.h"
#include "menu/base/submenu_handler.h"
#include "give_tint.h"
#include "util/util.h"

using namespace weapon::give::tint::selected::vars;

namespace weapon::give::tint::selected::vars {
	variables m_vars;
}

void give_tint_selection_menu::load() {
	set_name("Give Tint");
	set_parent<give_tint_menu>();
}

void give_tint_selection_menu::update() {}

void give_tint_selection_menu::update_once() {
	clear_options(0);

	std::vector<std::pair<std::string, int>> camos = weapon::give::tint::vars::get_tints(m_vars.m_selected_weapon);

	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	std::vector<std::shared_ptr<radio_option>> options;
	for (std::pair<std::string, int>& camo : camos) {
		std::string label_text = native::get_label_text(camo.first.c_str());
		util::replace_string(label_text, "tint", "Tint");

		options.push_back(add_option(radio_option(label_text)
			.add_radio(m_vars.m_context)
			.add_click([=, this] {
				native::set_ped_weapon_tint_index(menu::player::get_local_player().m_ped, m_vars.m_selected_weapon, camo.second);
				update_once();
			})));
	}

	if (native::get_ped_weapon_tint_index(menu::player::get_local_player().m_ped, m_vars.m_selected_weapon) != -1) {
		options[native::get_ped_weapon_tint_index(menu::player::get_local_player().m_ped, m_vars.m_selected_weapon)]->update_selected();
	}
}

void give_tint_selection_menu::feature_update() {}

give_tint_selection_menu* g_instance;
give_tint_selection_menu* give_tint_selection_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new give_tint_selection_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}