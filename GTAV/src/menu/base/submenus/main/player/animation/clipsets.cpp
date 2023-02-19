#include "clipsets.h"
#include "menu/base/submenu_handler.h"
#include "../animation.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"

using namespace player::clipset::vars;

namespace player::clipset::vars {
	variables m_vars;

	scroll_struct<const char*> motion[] = {
		{ localization("Businessman", true), "move_m@business@a" },
		{ localization("Gangster", true), "move_m@gangster@generic" },
		{ localization("Hero", true), "move_m@brave@a" },
		{ localization("Hiker", true), "move_m@hiking" },
		{ localization("Hobo", true), "move_m@hobo@a" },
		{ localization("Injured", true), "move_m@injured" },
		{ localization("Quick", true), "move_m@quick" },
		{ localization("Wasted", true), "move_m@drunk@slightlydrunk" },
		{ localization("Very Wasted", true), "move_m@drunk@verydrunk" }
	};

	scroll_struct<const char*> weapon[] = {
		{ localization("Bag", true), "missfbi4prepp1_garbageman" },
		{ localization("Bucket", true), "move_ped_wpn_bucket" },
		{ localization("Cane", true), "move_lester_CaneUp" },
		{ localization("Jerry Can", true), "move_ped_wpn_jerrycan_generic" },
		{ localization("Mop", true), "move_ped_wpn_mop" },
		{ localization("Rifle", true), "Wpn_AssaultRifle_WeaponHoldingCrouched" },
		{ localization("Sack", true), "MOVE_P_M_ZERO_RUCKSACK" }
	};

	void start_clipset(bool weapon, const char* clipset) {
		util::fiber::pool::add([=] {
			while (!native::has_clipset_loaded(clipset)) {
				native::request_clipset(clipset);
				util::fiber::sleep(100);
			}

			if (weapon) {
				native::reset_ped_weapon_movement_clipset(menu::player::get_local_player().m_ped);
				native::set_ped_weapon_movement_clipset(menu::player::get_local_player().m_ped, clipset);
			} else {
				native::reset_ped_movement_clipset(menu::player::get_local_player().m_ped, 0.f);
				native::set_ped_movement_clipset(menu::player::get_local_player().m_ped, clipset, 1.f);
			}
		});
	}
}

void clipset_menu::load() {
	set_name("Clipset");
	set_parent<animation_menu>();

	add_option(button_option("Default Motion Clipset")
		.add_translate().add_hotkey()
		.add_click([] { native::reset_ped_movement_clipset(menu::player::get_local_player().m_ped, 0.f); }));

	add_option(scroll_option<const char*>(SCROLLSELECT, "Motion")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_motion, 0, NUMOF(motion), motion)
		.add_click([] { start_clipset(false, motion[m_vars.m_motion].m_result); }));

	add_option(button_option("Default Weapon Clipset")
		.add_translate().add_hotkey()
		.add_click([] { native::reset_ped_weapon_movement_clipset(menu::player::get_local_player().m_ped); }));

	add_option(scroll_option<const char*>(SCROLLSELECT, "Weapon")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_weapon, 0, NUMOF(weapon), weapon)
		.add_click([] { start_clipset(true, weapon[m_vars.m_weapon].m_result); }));
}

void clipset_menu::update() {}

void clipset_menu::update_once() {}

void clipset_menu::feature_update() {}

clipset_menu* g_instance;
clipset_menu* clipset_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new clipset_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
