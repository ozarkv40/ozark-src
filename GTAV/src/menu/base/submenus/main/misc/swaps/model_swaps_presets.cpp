#include "model_swaps_presets.h"
#include "menu/base/submenu_handler.h"
#include "model_swaps.h"
#include "model_swaps.h"
#include "util/fiber_pool.h"
#include "util/fiber.h"

using namespace misc::swaps::model::presets::vars;

namespace misc::swaps::model::presets::vars {
	variables m_vars;

	std::string police_vehicles[] = {
		"PBUS",
		"PRANGER",
		"POLICE",
		"POLICE2",
		"POLICE3",
		"POLICE4",
		"POLICEB",
		"POLICEOLD1",
		"POLICEOLD2",
		"POLICET",
		"SHERIFF",
		"SHERIFF2",
		"RIOT",
		"RIOT2"
	};

	std::string police_peds[] = {
		"CSB_COP",
		"S_F_Y_COP_01",
		"S_F_Y_COP_01_P",
		"S_F_Y_HWAYCOP_01",
		"S_F_Y_HWAYCOP_01_P",
		"S_F_M_SNOWCOP_01",
		"S_F_M_SNOWCOP_01_P",
		"S_F_Y_SHERIFF_01",
		"S_F_Y_BLACKOPS_01",
		"S_F_Y_BLACKOPS_02",
		"S_F_Y_BLACKOPS_03",
		"S_M_Y_COP_01",
		"S_M_Y_COP_01_P",
		"S_M_Y_HWAYCOP_01",
		"S_M_Y_HWAYCOP_01_P",
		"S_M_M_SNOWCOP_01",
		"S_M_M_SNOWCOP_01_P",
		"S_M_Y_SHERIFF_01",
		"S_M_Y_BLACKOPS_01",
		"S_M_Y_BLACKOPS_02",
		"S_M_Y_BLACKOPS_03",
	};
}

void model_swaps_presets_menu::load() {
	set_name("Presets");
	set_parent<model_swaps_menu>();

	add_option(toggle_option("Monster Truck Police Vehicles")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_monster_truck_police)
		.add_click([] {
			util::fiber::pool::add([] {
				for (std::string str : police_vehicles) {
					if (m_vars.m_monster_truck_police) {
						misc::swaps::model::vars::add_swap(str.c_str(), "marshall");
					} else misc::swaps::model::vars::remove_swap(native::get_hash_key(str.c_str()));
				}
			});
		}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Astronaut Police Peds")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_astronaut_police_peds)
		.add_click([] {
			util::fiber::pool::add([] {
				for (std::string str : police_peds) {
					if (m_vars.m_astronaut_police_peds) {
						misc::swaps::model::vars::add_swap(str.c_str(), "S_M_M_MovSpace_01");
					} else misc::swaps::model::vars::remove_swap(native::get_hash_key(str.c_str()));
				}
			});
		}).add_savable(get_submenu_name_stack()));
}

void model_swaps_presets_menu::update() {}

void model_swaps_presets_menu::update_once() {}

void model_swaps_presets_menu::feature_update() {}

model_swaps_presets_menu* g_instance;
model_swaps_presets_menu* model_swaps_presets_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new model_swaps_presets_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}