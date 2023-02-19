#pragma once
#include "menu/base/submenu.h"

class network_account_outfits_menu : public menu::submenu::submenu {
public:
	static network_account_outfits_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_outfits_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::outfits::vars {
	struct variables {

	};

	bool does_outfit_slot_exist(int outfit_index);
	char* get_outfit_slot_name_ptr(int outfit_index);
	int get_max_slots();
	int get_free_slots();
	int get_free_slot_index();
	void delete_slot(int slot);
	void save_outfit_edit();
	extern variables m_vars;
}