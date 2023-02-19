#include "trains.h"
#include "menu/base/submenu_handler.h"
#include "../world.h"
#include "menu/base/util/control.h"

using namespace world::train::vars;

namespace world::train::vars {
	variables m_vars;

	scroll_struct<float> train_speeds[] = {
		{ localization("-500", false), -500.f },
		{ localization("-250", false), -250.f },
		{ localization("-100", false), -100.f },
		{ localization("-50", false), -50.f },
		{ localization("-25", false), -25.f },
		{ localization("-10", false), -10.f },
		{ localization("-1", false), -1.f },
		{ localization("0", false), 0.f },
		{ localization("1", false), 1.f },
		{ localization("10", false), 10.f },
		{ localization("25", false), 25.f },
		{ localization("50", false), 50.f },
		{ localization("100", false), 100.f },
		{ localization("250", false), 250.f },
		{ localization("500", false), 500.f }
	};

	scroll_struct<int> train_paints[] = {
		{ localization("Chrome", true), 120 },
		{ localization("Gold", true), 158 },
		{ localization("Pink", true), 135 },
		{ localization("Blue", true), 140 }
	};

	void enter_train() {
		if (!native::is_vehicle_seat_free(m_vars.m_train, -1, 0)) {
			Ped ped = native::get_ped_in_vehicle_seat(m_vars.m_train, -1, 0);
			native::set_entity_as_mission_entity(ped, true, true);
			native::delete_entity(&ped);
		}

		native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, m_vars.m_train, -1);
	}

	void paint_train() {
		menu::control::simple_request_control(m_vars.m_train);
		if (native::get_is_vehicle_primary_colour_custom(m_vars.m_train)) {
			native::clear_vehicle_custom_primary_colour(m_vars.m_train);
		}

		if (native::get_is_vehicle_secondary_colour_custom(m_vars.m_train)) {
			native::clear_vehicle_custom_secondary_colour(m_vars.m_train);
		}

		native::set_vehicle_colours(m_vars.m_train, train_paints[m_vars.m_paint].m_result, train_paints[m_vars.m_paint].m_result);

		for (int i = 1; i < 50; i++) {
			Vehicle carriage = native::get_train_carriage(m_vars.m_train, i);
			if (native::does_entity_exist(carriage)) {
				native::set_vehicle_colours(carriage, train_paints[m_vars.m_paint].m_result, train_paints[m_vars.m_paint].m_result);
			}
		}
	}

	void delete_carriage() {
		std::vector<Vehicle> carriages;

		for (int i = 1; i < 50; i++) {
			Vehicle carriage = native::get_train_carriage(m_vars.m_train, i);
			if (native::does_entity_exist(carriage)) {
				carriages.push_back(carriage);
			}
		}

		for (Vehicle& carriage : carriages) {
			menu::control::simple_request_control(carriage);
			native::set_entity_as_mission_entity(carriage, true, true);
			native::delete_entity(&carriage);
		}
	}

	void delete_train() {
		delete_carriage();
		menu::control::simple_request_control(m_vars.m_train);
		native::set_entity_as_mission_entity(m_vars.m_train, true, true);
		native::delete_mission_train(&m_vars.m_train);
	}

	void find_train() {
		float closest_distance = std::numeric_limits<float>::max();
		Entity closest_entity = 0;

		global::vars::g_vehicle_pool->for_each([&](Entity handle, void* veh) {
			if (native::get_entity_model(handle) == 0x3D6AAA9B) {
				float distance = menu::player::get_local_player().m_coords.get_distance(native::get_entity_coords(handle, true));
				if (distance < closest_distance) {
					closest_distance = distance;
					closest_entity = handle;
				}
			}
		});

		if (closest_entity != 0) {
			m_vars.m_train = closest_entity;
		} else {
			menu::notify::stacked(trains_menu::get()->get_string("Train"), trains_menu::get()->get_string("Couldn't find a train"), global::ui::g_error);
		}
	}

	bool requirement() {
		return m_vars.m_train && native::does_entity_exist(m_vars.m_train);
	}
}

void trains_menu::load() {
	set_name("Train");
	set_parent<world_menu>();

	add_option(toggle_option("Allow Random Trains")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_allow_random)
		.add_click([] { native::set_random_trains(m_vars.m_allow_random); }));

	add_option(button_option("Find Train")
		.add_translate().add_hotkey()
		.add_click(find_train)
		.add_tooltip("Must be near train tracks"));

	add_option(button_option("Spawn Train")
		.add_translate().add_hotkey()
		.add_click([] { m_vars.m_spawn = true; })
		.add_tooltip("Must be near train tracks"));

	add_option(break_option("Spawned Train")
		.add_translate()
		.add_requirement(requirement));

	add_option(button_option("Enter Train")
		.add_translate()
		.add_click(enter_train)
		.add_requirement(requirement));

	add_option(scroll_option<float>(TOGGLE, "Speed")
		.add_translate()
		.add_toggle(m_vars.m_speed)
		.add_scroll(m_vars.m_speed_val, 0, NUMOF(train_speeds), train_speeds)
		.add_click([] { menu::control::simple_request_control(m_vars.m_train); })
		.add_requirement(requirement));

	add_option(scroll_option<int>(SCROLLSELECT, "Paint")
		.add_translate()
		.add_scroll(m_vars.m_paint, 0, NUMOF(train_paints), train_paints)
		.add_click(paint_train)
		.add_requirement(requirement));

	add_option(toggle_option("Derail")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_derail)
		.add_click([] { native::set_render_train_as_derailed(m_vars.m_train, m_vars.m_derail); })
		.add_requirement(requirement));

	add_option(button_option("Delete carriages")
		.add_translate().add_hotkey()
		.add_click(delete_carriage)
		.add_requirement(requirement));

	add_option(button_option("Delete Train")
		.add_translate().add_hotkey()
		.add_click(delete_train)
		.add_requirement(requirement));

	add_string("Train");
	add_string("Couldn't find a train");
	add_string("Manager reset, cached train too far");
	add_string("You must delete the existing train first");
}

void trains_menu::update() {
	if (requirement()) {
		if (menu::player::get_local_player().m_coords.get_distance(native::get_entity_coords(m_vars.m_train, false)) > 100.f) {
			m_vars.m_train = 0;
			menu::notify::stacked(get_string("Train"), get_string("Manager reset, cached train too far"), global::ui::g_error);
		}
	} else {
		if (menu::base::get_current_option() > 3) menu::base::set_current_option(0);
	}
}

void trains_menu::update_once() {}

void trains_menu::feature_update() {
	if (m_vars.m_spawn) {
		m_vars.m_spawn = false;

		if (m_vars.m_train && native::does_entity_exist(m_vars.m_train)) {
			menu::notify::stacked(get_string("Train"), get_string("You must delete the existing train first"), global::ui::g_error);
			return;
		}

		menu::control::simple_request_model(0x3D6AAA9B);
		menu::control::simple_request_model(0x0AFD22A6);
		menu::control::simple_request_model(0x36DCFF98);
		menu::control::simple_request_model(0x0E512E79);
		menu::control::simple_request_model(0x264D9262);
		menu::control::simple_request_model(0xD1ABB666);

		m_vars.m_train = native::create_mission_train(15, menu::player::get_local_player().m_coords.x, menu::player::get_local_player().m_coords.y, menu::player::get_local_player().m_coords.z, true);
	}

	if (m_vars.m_speed) {
		if (m_vars.m_train) {
			if (native::does_entity_exist(m_vars.m_train)) {
				if (native::get_ped_in_vehicle_seat(m_vars.m_train, -1, 0) == menu::player::get_local_player().m_ped) {
					native::set_train_speed(m_vars.m_train, train_speeds[m_vars.m_speed_val].m_result);
					native::set_train_cruise_speed(m_vars.m_train, train_speeds[m_vars.m_speed_val].m_result);
					return;
				}
			}
		}

		m_vars.m_speed = false;
	}
}

trains_menu* g_instance;
trains_menu* trains_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new trains_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
