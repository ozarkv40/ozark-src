#include "purchase_attachment.h"
#include "menu/base/submenu_handler.h"
#include "purchase_weapons.h"
#include "purchase_weapon.h"
#include "global/lists.h"
#include "rage/engine.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "menu/base/util/notify.h"

using namespace weapon::purchase::attachment::vars;
using namespace weapon::purchase::weapon::vars;

namespace weapon::purchase::attachment::vars {
	variables m_vars;

	// g_weapon_components
	std::vector<rage::network::transaction> create_component_transaction_list(uint32_t weapon) {
		std::vector<rage::network::transaction> list;

		std::vector<uint32_t> hashes = rage::engine::get_hash_list_from_hash_table(*(uint32_t*)(global::vars::g_weapon_components.m_count) - 1, global::vars::g_weapon_components.m_list);
		for (uint32_t component : hashes) {
			if (native::does_weapon_take_weapon_component(weapon, component)) {
				if (!native::has_ped_got_weapon_component(menu::player::get_local_player().m_ped, weapon, component)) {
					char output[0x100];
					scripts::func_116(output, scripts::func_181(component, (int)weapon), native::get_entity_model(menu::player::get_local_player().m_ped), 3, 1, scripts::func_57((int)weapon), scripts::func_117((int)weapon), -1, 0, 0);

					int transaction_hash = (int)native::get_hash_key(output);

					if (native::network_shop_get_price(transaction_hash, 1671640801, true) != -1) {
						list.push_back({ transaction_hash, -1, native::network_shop_get_price(transaction_hash, 1671640801, true), 1, 1 });
					}
				}
			}
		}

		return list;
	}

	int calculate_total_price() {
		int total = 0;

		for (scroll_struct<uint32_t> hash : global::lists::g_weapons) {
			std::vector<rage::network::transaction> list = create_component_transaction_list(hash.m_result);
			if (!list.empty()) {
				for (rage::network::transaction& transaction : list) {
					total += transaction.m_price;
				}
			}
		}

		return total;
	}

	void purchase_all_attachments() {
		util::fiber::pool::add([] {
			for (scroll_struct<uint32_t> hash : global::lists::g_weapons) {
				std::vector<rage::network::transaction> list = create_component_transaction_list(hash.m_result);
				if (!list.empty()) {
					int total = 0;
					for (rage::network::transaction& transaction : list) {
						total += transaction.m_price;
					}

					rage::engine::process_basket_transaction(1671640801, 537254313, 4, list);
					while (rage::engine::is_basket_transaction_queue_busy()) util::fiber::sleep(1);
				}
			}

			menu::notify::stacked(purchase_attachment_menu::get()->get_string("Purchase Attachments"), purchase_attachment_menu::get()->get_string("Purchase complete! Change sessions to take affect"), global::ui::g_success);
		});
	}
}

void purchase_attachment_menu::load() {
	set_name("Purchase Attachment");
	set_parent<purchase_weapons_menu>();

	add_string("Purchase Attachments");
	add_string("Total price: $");
	add_string("Purchase complete! Change sessions to take affect");

	weapon::purchase::attachment::vars::m_vars.m_button = add_option(button_option("Purchase All Attachments")
		.add_translate().add_hotkey()
		.add_click(purchase_all_attachments));
}

void purchase_attachment_menu::update() {}

void purchase_attachment_menu::update_once() {
	weapon::purchase::attachment::vars::m_vars.m_button->set_tooltip(get_string("Total price: $") + std::to_string(calculate_total_price()));
}

void purchase_attachment_menu::feature_update() {}

purchase_attachment_menu* g_instance;
purchase_attachment_menu* purchase_attachment_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new purchase_attachment_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}