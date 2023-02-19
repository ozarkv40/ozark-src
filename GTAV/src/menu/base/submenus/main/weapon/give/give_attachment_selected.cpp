#include "give_attachment_selected.h"
#include "menu/base/submenu_handler.h"
#include "give_attachment.h"
#include "rage/engine.h"
#include "../purchase/purchase_weapon.h"

using namespace weapon::give::attachment::selected::vars;

namespace weapon::give::attachment::selected::vars {
	variables m_vars;
}

void give_attachment_selected_menu::load() {
	set_name("Give Attachment");
	set_parent<give_attachment_menu>();
}

void give_attachment_selected_menu::update() {}

void give_attachment_selected_menu::update_once() {
	clear_options(0);

	std::vector<uint32_t> hashes = rage::engine::get_hash_list_from_hash_table(*(uint32_t*)(global::vars::g_weapon_components.m_count) - 1, global::vars::g_weapon_components.m_list);
	for (std::size_t i = 0; i < hashes.size(); i++) {
		uint32_t component = hashes[i];
		if (native::does_weapon_take_weapon_component(m_vars.m_selected_weapon, component)) {
			const char* label = weapon::purchase::weapon::vars::scripts::func_181(component, m_vars.m_selected_weapon);
			if (label) {
				if (strcmp(native::get_label_text(label), "NULL")) {
					std::shared_ptr<button_option> option = add_option(button_option(native::get_label_text(label))
						.add_click_this([=] (button_option* option) {
							if (native::has_ped_got_weapon_component(menu::player::get_local_player().m_ped, m_vars.m_selected_weapon, component)) {
								native::remove_weapon_component_from_ped(menu::player::get_local_player().m_ped, m_vars.m_selected_weapon, component);
							} else {
								native::give_weapon_component_to_ped(menu::player::get_local_player().m_ped, m_vars.m_selected_weapon, component);
							}

							update_once();
						}));

					if (native::has_ped_got_weapon_component(menu::player::get_local_player().m_ped, m_vars.m_selected_weapon, component)) {
						option->add_sprite({ "commonmenu", "shop_gunclub_icon" });
						option->add_sprite_scale({ 0.02112f, 0.03744f });
					}
				}
			}
		}
	}
}

void give_attachment_selected_menu::feature_update() {}

give_attachment_selected_menu* g_instance;
give_attachment_selected_menu* give_attachment_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new give_attachment_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}