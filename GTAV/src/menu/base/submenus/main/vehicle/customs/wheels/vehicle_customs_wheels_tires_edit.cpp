#include "vehicle_customs_wheels_tires_edit.h"
#include "menu/base/submenu_handler.h"
#include "vehicle_customs_wheels_tires.h"
#include "../../vehicle_customs.h"

using namespace vehicle::customs::wheels::tires::edit::vars;

namespace vehicle::customs::wheels::tires::edit::vars {
	variables m_vars;

	scroll_struct<color_rgba> tire_smoke[] = {
		{ localization("White Tire Smoke", true), { 255, 255, 255 } },
		{ localization("Black Tire Smoke", true), { 20, 20, 20 } },
		{ localization("Blue Tire Smoke", true), { 0, 174, 239 } },
		{ localization("Yellow Tire Smoke", true), { 252, 238, 0 } },
		{ localization("Purple Tire Smoke", true), { -1, -1, -1 } },
		{ localization("Orange Tire Smoke", true), { 255, 127, 0 } },
		{ localization("Green Tire Smoke", true), { -1, -1, -1 } },
		{ localization("Red Tire Smoke", true), { 226, 6, 6 } },
		{ localization("Pink Tire Smoke", true), { -1, -1, -1 } },
		{ localization("Brown Tire Smoke", true), { -1, -1, -1 } },
		{ localization("Patriot Tire Smoke", true), { 0, 0, 0 } },
	};
}

void vehicle_customs_wheels_tires_edit_menu::load() {
	set_name("Tires");
	set_parent<vehicle_customs_wheels_tires_menu>();

	add_string("Stock Tires");
	add_string("Custom Tires");
	add_string("Bulletproof Tires");
}

void vehicle_customs_wheels_tires_edit_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_wheels_tires_edit_menu::update_once() {
	clear_options(0);

	vehicle::customs::wheels::tires::vars::m_vars.m_update_cache = true;
	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	// Populate hud element colors
	if (tire_smoke[4].m_result.r == -1) {
		native::get_hud_colour(21, &tire_smoke[4].m_result.r, &tire_smoke[4].m_result.g, &tire_smoke[4].m_result.b, &tire_smoke[4].m_result.a);
		native::get_hud_colour(18, &tire_smoke[6].m_result.r, &tire_smoke[6].m_result.g, &tire_smoke[6].m_result.b, &tire_smoke[6].m_result.a);
		native::get_hud_colour(24, &tire_smoke[8].m_result.r, &tire_smoke[8].m_result.g, &tire_smoke[8].m_result.b, &tire_smoke[8].m_result.a);
		native::get_hud_colour(107, &tire_smoke[9].m_result.r, &tire_smoke[9].m_result.g, &tire_smoke[9].m_result.b, &tire_smoke[9].m_result.a);
	}

	// Tire Design
	if (m_vars.m_type == 1) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Tires"))
			.add_radio(m_vars.m_context)
			.add_click([] { vehicle::customs::wheels::tires::vars::m_vars.m_custom_tires = false; })
			.add_hover([] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS), false);
			})));

		temp_options.push_back(add_option(radio_option(get_string("Custom Tires"))
			.add_radio(m_vars.m_context)
			.add_click([] { vehicle::customs::wheels::tires::vars::m_vars.m_custom_tires = true; })
			.add_hover([] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS), true);
			})));

		if (native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS)) {
			temp_options[1]->update_selected();
			menu::base::set_current_option(1);
		}

		return;
	}

	// Tire Enhancements
	if (m_vars.m_type == 2) {
		m_vars.m_enhancements.clear();

		m_vars.m_enhancements.push_back(add_option(button_option(get_string("Standard Tires"))
			.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::tires::vars::m_vars.m_tires_low_grip = false;

				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_tyres_low_grip(menu::player::get_local_player().m_vehicle, false);

				m_vars.m_enhancements[0]->add_sprite({ "commonmenu", "shop_garage_icon" }).add_sprite_scale({ 0.02112f * 0.8f, 0.03744f * 0.8f });
				m_vars.m_enhancements[1]->remove_sprite();
			}).add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_tyres_low_grip(menu::player::get_local_player().m_vehicle, false);
			})));

		m_vars.m_enhancements.push_back(add_option(button_option(get_string("Low Grip Tires"))
			.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::wheels::tires::vars::m_vars.m_tires_low_grip = true;

				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_tyres_low_grip(menu::player::get_local_player().m_vehicle, true);

				m_vars.m_enhancements[0]->remove_sprite();
				m_vars.m_enhancements[1]->add_sprite({ "commonmenu", "shop_garage_icon" }).add_sprite_scale({ 0.02112f * 0.8f, 0.03744f * 0.8f });
			}).add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_tyres_low_grip(menu::player::get_local_player().m_vehicle, true);
			})));

		m_vars.m_enhancements.push_back(add_option(button_option(get_string("Bulletproof Tires"))
			.add_click([=] {
				vehicle::customs::vars::update_caches();
				bool state = native::get_vehicle_tyres_can_burst(menu::player::get_local_player().m_vehicle);
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_tyres_can_burst(menu::player::get_local_player().m_vehicle, !state);

				if (!state) {
					m_vars.m_enhancements[2]->remove_sprite();
				} else {
					m_vars.m_enhancements[2]->add_sprite({ "commonmenu", "shop_garage_icon" }).add_sprite_scale({ 0.02112f * 0.8f, 0.03744f * 0.8f });
				}
			}).add_hover([this] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_tyres_low_grip(menu::player::get_local_player().m_vehicle, vehicle::customs::wheels::tires::vars::m_vars.m_tires_low_grip);
			})));

		if (native::get_vehicle_tyres_are_low_grip(menu::player::get_local_player().m_vehicle)) {
			m_vars.m_enhancements[0]->remove_sprite();
			m_vars.m_enhancements[1]->add_sprite({ "commonmenu", "shop_garage_icon" }).add_sprite_scale({ 0.02112f * 0.8f, 0.03744f * 0.8f });
		} else {
			m_vars.m_enhancements[0]->add_sprite({ "commonmenu", "shop_garage_icon" }).add_sprite_scale({ 0.02112f * 0.8f, 0.03744f * 0.8f });
			m_vars.m_enhancements[1]->remove_sprite();
		}

		if (native::get_vehicle_tyres_can_burst(menu::player::get_local_player().m_vehicle)) {
			m_vars.m_enhancements[2]->remove_sprite();
		} else {
			m_vars.m_enhancements[2]->add_sprite({ "commonmenu", "shop_garage_icon" }).add_sprite_scale({ 0.02112f * 0.8f, 0.03744f * 0.8f });
		}

		return;
	}

	// Tire Smoke
	if (m_vars.m_type == 3) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		int selected_index = 99;
		bool toggled = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_TIRESMOKE);
		color_rgba current_color;
		native::get_vehicle_tyre_smoke_color(menu::player::get_local_player().m_vehicle, &current_color.r, &current_color.g, &current_color.b);

		for (int i = 0; i < NUMOF(tire_smoke); i++) {
			auto Smoke = tire_smoke[i];
			temp_options.push_back(add_option(radio_option(Smoke.m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
					vehicle::customs::wheels::tires::vars::m_vars.m_tire_smoke = true;
					vehicle::customs::wheels::tires::vars::m_vars.m_tire_smoke_color = Smoke.m_result;
				})
				.add_hover([=] {
					native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
					native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TIRESMOKE, true);
					native::set_vehicle_tyre_smoke_color(menu::player::get_local_player().m_vehicle, Smoke.m_result.r, Smoke.m_result.g, Smoke.m_result.b);
				})));

			if (toggled) {
				if (Smoke.m_result.r == current_color.r
					&& Smoke.m_result.g == current_color.g
					&& Smoke.m_result.b == current_color.b) {
					selected_index = i;
				}
			}
		}

		if (selected_index != 0) {
			if (selected_index != 99) {
				temp_options[selected_index]->update_selected();
				menu::base::set_current_option(selected_index);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}
}

void vehicle_customs_wheels_tires_edit_menu::feature_update() {}

vehicle_customs_wheels_tires_edit_menu* g_instance;
vehicle_customs_wheels_tires_edit_menu* vehicle_customs_wheels_tires_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_wheels_tires_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}