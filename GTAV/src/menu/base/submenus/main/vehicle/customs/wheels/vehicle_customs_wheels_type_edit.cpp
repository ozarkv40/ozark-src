#include "vehicle_customs_wheels_type_edit.h"
#include "menu/base/submenu_handler.h"
#include "vehicle_customs_wheels_type.h"
#include "../../vehicle_customs.h"

using namespace vehicle::customs::wheels::type::edit::vars;

namespace vehicle::customs::wheels::type::edit::vars {
	variables m_vars;
}

void vehicle_customs_wheels_type_edit_menu::load() {
	set_name("Wheel Type");
	set_parent<vehicle_customs_wheels_type_menu>();

	add_string("Stock Wheels");

	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_bike) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_high_end) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_lowrider) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_muscle) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_offroad) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_sport) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_suv) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_tuner) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_bennys) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_bespoke) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_open) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_street) add_string(native::get_label_text(wheel.first));
	for (auto& wheel : vehicle::customs::vars::m_vars.m_wheel_track) add_string(native::get_label_text(wheel.first));
}

void vehicle_customs_wheels_type_edit_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
	if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() && menu::base::get_current_option() - menu::base::get_scroll_offset() >= menu::base::get_max_options()) menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);
}

void vehicle_customs_wheels_type_edit_menu::update_once() {
	clear_options(0);

	vehicle::customs::wheels::type::vars::m_vars.m_update_cache = true;
	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	/* Bike Wheels */
	if (m_vars.m_wheel_type == 1 || m_vars.m_wheel_type == 2) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 6;
			})
			.add_hover([] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 6);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, m_vars.m_wheel_type == 1 ? MOD_FRONTWHEELS : MOD_BACKWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, m_vars.m_wheel_type == 1 ? MOD_FRONTWHEELS : MOD_BACKWHEELS));
			})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, m_vars.m_wheel_type == 1 ? MOD_FRONTWHEELS : MOD_BACKWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_bike) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
					vehicle::customs::vars::update_caches();
					vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
					vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 6;
				})
				.add_hover([=] {
					native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 6);
					native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
					native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, m_vars.m_wheel_type == 1 ? MOD_FRONTWHEELS : MOD_BACKWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, m_vars.m_wheel_type == 1 ? MOD_FRONTWHEELS : MOD_BACKWHEELS));
				})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 6) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Highend */
	if (m_vars.m_wheel_type == 3) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 7;
			})
			.add_hover([] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 7);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_high_end) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 7;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 7);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 7) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Lowrider */
	if (m_vars.m_wheel_type == 4) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 2;
		})
			.add_hover([] {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 2);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_lowrider) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 2;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 2);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 2) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Muscle */
	if (m_vars.m_wheel_type == 5) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 1;
		})
			.add_hover([] {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 1);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_muscle) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 1;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 1);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 1) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Offroad */
	if (m_vars.m_wheel_type == 6) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 4;
		})
			.add_hover([] {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 4);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_offroad) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 4;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 4);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 4) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Sport */
	if (m_vars.m_wheel_type == 7) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 0;
		})
			.add_hover([] {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_sport) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 0;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 0) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* SUV */
	if (m_vars.m_wheel_type == 8) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 3;
		})
			.add_hover([] {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 3);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_suv) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 3;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 3);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 3) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Tuner */
	if (m_vars.m_wheel_type == 9) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 5;
		})
			.add_hover([] {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 5);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_tuner) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 5;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 5);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 5) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Benny's */
	if (m_vars.m_wheel_type == 10) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 8;
			})
			.add_hover([] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 8);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_bennys) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 8;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 8);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 8) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Bespoke */
	if (m_vars.m_wheel_type == 11) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 9;
		})
			.add_hover([] {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 9);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_bespoke) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 9;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 9);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 9) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Open Wheel */
	if (m_vars.m_wheel_type == 12) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 10;
		})
			.add_hover([] {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 10);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_open) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 10;
			})
				.add_hover([=] {
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 10);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 10) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Street */
	if (m_vars.m_wheel_type == 13) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 11;
			})
			.add_hover([] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 11);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_street) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
					vehicle::customs::vars::update_caches();
					vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
					vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 11;
				})
				.add_hover([=] {
					native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
					native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 11);
					native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
				})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 11) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	/* Track */
	if (m_vars.m_wheel_type == 14) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Wheels"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = -1;
			vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 12;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 12);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, -1, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
		})));

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

		for (auto& Wheel : vehicle::customs::vars::m_vars.m_wheel_street) {
			temp_options.push_back(add_option(radio_option(get_string(native::get_label_text(Wheel.first)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_index = Wheel.second;
				vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type = 12;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 12);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, Wheel.second, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS));
			})));

			if (Wheel.second == current_mod) {
				selected_index = Wheel.second;
			}
		}

		if (current_mod != -1 && vehicle::customs::wheels::type::vars::m_vars.m_cached_wheel_type == 12) {
			if (selected_index != 99) {
				temp_options[selected_index + 1]->update_selected();
				menu::base::set_current_option(selected_index + 1);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}
}

void vehicle_customs_wheels_type_edit_menu::feature_update() {}

vehicle_customs_wheels_type_edit_menu* g_instance;
vehicle_customs_wheels_type_edit_menu* vehicle_customs_wheels_type_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_wheels_type_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}