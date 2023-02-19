#include "vehicle_boost.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "rage/engine.h"

using namespace vehicle::boost::vars;

namespace vehicle::boost::vars {
	variables m_vars;

	void boost(Vehicle ve, bool Forwards, bool disable_fx) {
		vehicle::vars::run_task(ve, [=](Vehicle veh) {
			if (m_vars.m_boost_fx && !disable_fx) {
				native::set_vehicle_boost_active(veh, true);
				native::start_screen_effect("RaceTurbo", -1, false);
			}

			if (m_vars.m_boost_sound && !disable_fx) {
				native::request_script_audio_bank("DLC_IMPORTEXPORT/STEAL_STUNT", false, -1);
				native::play_sound_from_entity(-1, "Speed_Boost", veh, "DLC_IE_Stunt_Man_Sounds", false, 0);
			}

			native::set_vehicle_forward_speed(veh, Forwards ? m_vars.m_boost_forwards + native::get_entity_speed(veh) : -m_vars.m_boost_backwards);

			if (m_vars.m_boost_fx && !disable_fx) {
				native::stop_screen_effect("RaceTurbo");
				native::set_vehicle_boost_active(veh, false);
			}
		});
	}
}

void vehicle_boost_menu::load() {
	set_name("Boost");
	set_parent<vehicle_menu>();

	add_option(toggle_option("Boost FX")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_boost_fx).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Boost Sound")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_boost_sound).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Nitrous Oxide (Horn)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_nitrous_oxide).add_savable(get_submenu_name_stack()));

	add_option(number_option<int>(SCROLLSELECT, "Boost Forwards")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_boost_forwards, "%i", 1).add_min(0).add_max(5000).set_scroll_speed(10).show_max()
		.add_click([] { boost(menu::player::get_local_player().m_vehicle, true); }));

	add_option(number_option<int>(SCROLLSELECT, "Boost Backwards")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_boost_backwards, "%i", 1).add_min(0).add_max(5000).set_scroll_speed(10).show_max()
		.add_click([] { boost(menu::player::get_local_player().m_vehicle, false); }));

	add_option(toggle_option("Unlimited Special Ability")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_unlimited_special_ability).add_savable(get_submenu_name_stack()));
}

void vehicle_boost_menu::update() {}

void vehicle_boost_menu::update_once() {}

void vehicle_boost_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_unlimited_special_ability) {
			if (native::has_vehicle_rocket_boost(menu::player::get_local_player().m_vehicle)) {
				static std::pair<uint32_t, bool> yes = { 0, false };

				if (native::is_vehicle_rocket_boost_active(menu::player::get_local_player().m_vehicle)) {
					if (!yes.second) {
						yes.second = true;
						yes.first = GetTickCount() + 3500;
					}

					native::set_vehicle_rocket_boost_refill_time(menu::player::get_local_player().m_vehicle, 0.0f);
					native::set_vehicle_rocket_boost_percentage(menu::player::get_local_player().m_vehicle, 100.f);

					if (yes.second) {
						if (GetTickCount() > yes.first) {
							yes.second = false;
							native::set_vehicle_rocket_boost_active(menu::player::get_local_player().m_vehicle, false);
						}
					}
				}
			}
		}

		static bool reset = false;
		if (m_vars.m_nitrous_oxide) {
			Vehicle veh = menu::player::get_local_player().m_vehicle;
			if (native::is_horn_active(veh)) {
				if (m_vars.m_boost_fx) {
					native::set_vehicle_boost_active(veh, true);
					native::start_screen_effect("RaceTurbo", -1, false);
				}

				native::set_vehicle_engine_power_multiplier(menu::player::get_local_player().m_vehicle, 10.f);

				uint64_t address = rage::engine::get_entity_address(veh);
				if (address) {
					*(float*)(address + 0x1360) = 30.f;
				}

				if (m_vars.m_boost_fx) {
					native::stop_screen_effect("RaceTurbo");
					native::set_vehicle_boost_active(veh, false);
				}

				reset = true;
			} else {
				if (reset) {
					uint64_t address = rage::engine::get_entity_address(veh);
					if (address) {
						*(float*)(address + 0x1360) = 1.f;
					}

					reset = false;
				}
			}
		}
	}
}

vehicle_boost_menu* g_instance;
vehicle_boost_menu* vehicle_boost_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_boost_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}