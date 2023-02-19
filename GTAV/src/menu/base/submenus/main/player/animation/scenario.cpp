#include "scenario.h"
#include "menu/base/submenu_handler.h"
#include "../animation.h"

using namespace player::scenario::vars;

namespace player::scenario::vars {
	variables m_vars;

	scroll_struct<const char*> ambient[] = {
		{ localization("Coffee", true), "WORLD_HUMAN_AA_COFFEE" },
		{ localization("Smoking", true), "WORLD_HUMAN_AA_SMOKE" },
		{ localization("Freeway Bum", true), "WORLD_HUMAN_BUM_FREEWAY" },
		{ localization("Sleeping Bum", true), "WORLD_HUMAN_BUM_SLUMPED" },
		{ localization("Cheer", true), "WORLD_HUMAN_CHEERING" },
		{ localization("Partying", true), "WORLD_HUMAN_PARTYING" },
		{ localization("Shine Flashlight", true), "WORLD_HUMAN_SECURITY_SHINE_TORCH" },
		{ localization("Tourist Map", true), "WORLD_HUMAN_TOURIST_MAP" }
	};

	scroll_struct<const char*> activities[] = {
		{ localization("Binoculars", true), "WORLD_HUMAN_BINOCULARS" },
		{ localization("Drunk", true), "WORLD_HUMAN_DRINKING" },
		{ localization("Human Statue", true), "WORLD_HUMAN_HUMAN_STATUE" },
		{ localization("Musician", true), "WORLD_HUMAN_MUSICIAN" },
		{ localization("Fishing", true), "WORLD_HUMAN_STAND_FISHING" },
		{ localization("BBQ", true), "PROP_HUMAN_BBQ" },
		{ localization("Yoga", true), "WORLD_HUMAN_YOGA" }
	};

	scroll_struct<const char*> animals[] = {
		{ localization("Grazing Boar", true), "WORLD_BOAR_GRAZING" },
		{ localization("Grazing Cow", true), "WORLD_COW_GRAZING" },
		{ localization("Coyote Howl", true), "WORLD_COYOTE_HOWL" },
		{ localization("Coyote Rest", true), "WORLD_COYOTE_REST" },
		{ localization("Coyote Wander", true), "WORLD_COYOTE_WANDER" },
		{ localization("Rottweiler Bark", true), "WORLD_DOG_BARKING_ROTTWEILER" }
	};

	scroll_struct<const char*> fitness[] = {
		{ localization("Idle Jogger", true), "WORLD_HUMAN_JOG_STANDING" },
		{ localization("Golf", true), "WORLD_HUMAN_GOLF_PLAYER" },
		{ localization("Muscle Flex", true), "WORLD_HUMAN_MUSCLE_FLEX" },
		{ localization("Free Weights", true), "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS" },
		{ localization("Tennis", true), "WORLD_HUMAN_TENNIS_PLAYER" },
		{ localization("Bench Press", true), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS" }
	};

	scroll_struct<const char*> industrial[] = {
		{ localization("Parking Attendant", true), "WORLD_HUMAN_CAR_PARK_ATTENDANT" },
		{ localization("Drill", true), "WORLD_HUMAN_CONST_DRILL" },
		{ localization("Leaf Blower", true), "WORLD_HUMAN_GARDENER_LEAF_BLOWER" },
		{ localization("Hammering", true), "WORLD_HUMAN_HAMMERING" },
		{ localization("Janitor", true), "WORLD_HUMAN_JANITOR" },
		{ localization("Maid", true), "WORLD_HUMAN_MAID_CLEAN" },
		{ localization("Welding", true), "WORLD_HUMAN_WELDING" }
	};
}

void scenario_menu::load() {
	set_name("Scenarios");
	set_parent<animation_menu>();

	add_option(button_option("Stop Scenario")
		.add_translate().add_hotkey()
		.add_click([] { native::clear_ped_tasks_immediately(menu::player::get_local_player().m_ped); }));

	add_option(scroll_option<const char*>(SCROLLSELECT, "Ambient")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_ambient, 0, NUMOF(ambient), ambient)
		.add_click([] { native::task_start_scenario_in_place(menu::player::get_local_player().m_ped, ambient[m_vars.m_ambient].m_result, 0, true); }));

	add_option(scroll_option<const char*>(SCROLLSELECT, "Activities")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_activities, 0, NUMOF(activities), activities)
		.add_click([] { native::task_start_scenario_in_place(menu::player::get_local_player().m_ped, activities[m_vars.m_activities].m_result, 0, true); }));

	add_option(scroll_option<const char*>(SCROLLSELECT, "Animals")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_animals, 0, NUMOF(animals), animals)
		.add_click([] { native::task_start_scenario_in_place(menu::player::get_local_player().m_ped, animals[m_vars.m_animals].m_result, 0, true); }));

	add_option(scroll_option<const char*>(SCROLLSELECT, "Fitness")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_fitness, 0, NUMOF(fitness), fitness)
		.add_click([] { native::task_start_scenario_in_place(menu::player::get_local_player().m_ped, fitness[m_vars.m_fitness].m_result, 0, true); }));

	add_option(scroll_option<const char*>(SCROLLSELECT, "Industrial")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_industrial, 0, NUMOF(industrial), industrial)
		.add_click([] { native::task_start_scenario_in_place(menu::player::get_local_player().m_ped, industrial[m_vars.m_industrial].m_result, 0, true); }));
}

void scenario_menu::update() {}

void scenario_menu::update_once() {}

void scenario_menu::feature_update() {}

scenario_menu* g_instance;
scenario_menu* scenario_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new scenario_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
