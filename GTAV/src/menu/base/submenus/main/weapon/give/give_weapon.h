#pragma once
#include "menu/base/submenu.h"

class give_weapon_menu : public menu::submenu::submenu {
public:
	static give_weapon_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	give_weapon_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::give::vars {
	struct variables {
		bool m_give_weapons;
	};

	void upgrade_weapon_components(Ped ped, uint32_t weapon_hash);
	void remove_weapon_upgrades(Ped ped, uint32_t weapon_hash);
	void give_weapon(Ped ped, uint32_t weapon_hash, bool equip_now, bool fully_upgraded);
	extern variables m_vars;
}