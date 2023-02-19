#include "give_tint.h"
#include "menu/base/submenu_handler.h"
#include "give_weapons.h"
#include "give_tint_selected.h"
#include "global/lists.h"

using namespace weapon::give::tint::vars;

namespace weapon::give::tint::vars {
	namespace scripts {
		bool func_173(int iParam0) {
			switch (iParam0) {
				case joaat("WEAPON_PISTOL_MK2"):
				case joaat("WEAPON_SMG_MK2"):
				case joaat("WEAPON_ASSAULTRIFLE_MK2"):
				case joaat("WEAPON_CARBINERIFLE_MK2"):
				case joaat("WEAPON_COMBATMG_MK2"):
				case joaat("WEAPON_HEAVYSNIPER_MK2"):
				case joaat("WEAPON_PUMPSHOTGUN_MK2"):
				case joaat("WEAPON_SPECIALCARBINE_MK2"):
				case joaat("WEAPON_SNSPISTOL_MK2"):
				case joaat("WEAPON_MARKSMANRIFLE_MK2"):
				case joaat("WEAPON_REVOLVER_MK2"):
				case joaat("WEAPON_BULLPUPRIFLE_MK2"):
					return true;
			}
			return false;
		}

		int func_81(int iParam0, int* data) {
			int iVar0;
			int iVar1;

			iVar1 = native::get_num_dlc_weapons();
			iVar0 = 0;
			while (iVar0 < iVar1) {
				if (native::get_dlc_weapon_data(iVar0, data)) {
					if (data[2] == iParam0) {
						return iVar0;
					}
				}
				iVar0++;
			}
			return -1;
		}
	}

	bool does_weapon_have_tints(uint32_t weapon) {
		switch (weapon) {
			case joaat("WEAPON_KNUCKLE"):
			case joaat("WEAPON_DOUBLEACTION"):
				return false;
		}

		uint32_t group = native::get_weapontype_group(weapon);
		if (group == 0xD49321D4 || group == 0x5C4C5883 || group == 0x5F1BE07C || group == 0xFDBF656C || group == 0xA27A4F9F) return false;
		return true;
	}

	std::vector<std::pair<std::string, int>> get_tints(int weapon) {
		std::vector<std::pair<std::string, int>> items;

		switch (weapon) {
			case joaat("WEAPON_RAYPISTOL"): {
				for (int i = 0; i <= 6; i++) {
					items.push_back({ "RWT_TINT" + std::to_string(i), i });
				}
				break;
			}

			case joaat("WEAPON_RAYCARBINE"):
			case joaat("WEAPON_RAYMINIGUN"): {
				items.push_back({ "RWT_TINT7", 0 });
				items.push_back({ "RWT_TINT1", 1 });
				items.push_back({ "RWT_TINT2", 2 });
				items.push_back({ "RWT_TINT3", 3 });
				items.push_back({ "RWT_TINT4", 4 });
				items.push_back({ "RWT_TINT5", 5 });
				items.push_back({ "RWT_TINT6", 6 });
				break;
			}

			default: {
				int data[100];

				if (weapon == -61829581) {
					for (int i = 0; i <= 11; i++) {
						items.push_back({ "FW_TINT" + std::to_string(i), i });
					}
				} else if (native::network_is_game_in_progress() || scripts::func_81(weapon, data) != -1) {
					if (scripts::func_173(weapon)) {
						for (int i = 0; i <= 31; i++) {
							items.push_back({ "WCT_TINT_" + std::to_string(i), i });
						}
					} else {
						if ((((weapon == joaat("WEAPON_MUSKET") || weapon == joaat("WEAPON_FLAREGUN")) || weapon == joaat("WEAPON_FIREWORK")) || weapon == joaat("WEAPON_MARKSMANPISTOL")) || weapon == joaat("WEAPON_DBSHOTGUN")) {
							items.push_back({ "WM_TINTDF", 0 });
						} else {
							items.push_back({ "WM_TINT0", 0 });
						}

						items.push_back({ "WM_TINT4", 4 });
						items.push_back({ "WM_TINT1", 1 });
						items.push_back({ "WM_TINT6", 6 });
						items.push_back({ "WM_TINT5", 5 });
						items.push_back({ "WM_TINT3", 3 });
						items.push_back({ "WM_TINT2", 2 });
						items.push_back({ "WM_TINT7", 7 });
					}
				} else {
					items.push_back({ "WM_TINT0", 0 });
					items.push_back({ "WM_TINT4", 4 });
					items.push_back({ "WM_TINT1", 1 });
					items.push_back({ "WM_TINT6", 6 });
					items.push_back({ "WM_TINT5", 5 });
					items.push_back({ "WM_TINT3", 3 });
					items.push_back({ "WM_TINT2", 2 });
					items.push_back({ "WM_TINT7", 7 });
				}

				break;
			}
		}

		return items;
	}
}

void give_tint_menu::load() {
	set_name("Give Tint");
	set_parent<give_weapons_menu>();

	add_option(submenu_option("Current Weapon")
		.add_translate().add_hotkey()
		.add_click([] { weapon::give::tint::selected::vars::m_vars.m_selected_weapon = menu::player::get_local_player().m_weapon_hash; })
		.add_submenu<give_tint_selection_menu>()
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand && does_weapon_have_tints(menu::player::get_local_player().m_weapon_hash); }));

	add_option(break_option("Weapons")
		.add_translate());
}

void give_tint_menu::update() {}

void give_tint_menu::update_once() {
	clear_options(2);

	for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
		if (does_weapon_have_tints(weapon.m_result)) {
			std::vector<std::pair<std::string, int>> camos = get_tints((int)weapon.m_result);
			if (camos.size()) {
				add_option(submenu_option(weapon.m_name.get())
					.add_submenu<give_tint_selection_menu>()
					.add_click([=] { weapon::give::tint::selected::vars::m_vars.m_selected_weapon = weapon.m_result; }));
			}
		}
	}
}

void give_tint_menu::feature_update() {}

give_tint_menu* g_instance;
give_tint_menu* give_tint_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new give_tint_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}