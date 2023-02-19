#pragma once
#include "menu/base/submenu.h"

class network_account_outfits_edit_menu : public menu::submenu::submenu {
public:
	static network_account_outfits_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_outfits_edit_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::outfits::edit::vars {
	struct variables {
		int m_slot;
		int m_clothing_cache[2][12];
		int m_accessory_cache[2][9];
	};

	extern variables m_vars;
}