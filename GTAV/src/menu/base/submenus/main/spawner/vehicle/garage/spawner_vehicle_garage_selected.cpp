#include "spawner_vehicle_garage_selected.h"
#include "menu/base/submenu_handler.h"
#include "../spawner_vehicle_garage.h"
#include "menu/base/util/global.h"
#include "../../../spawner.h"
#include "rage/types/global_types.h"

using namespace spawner::vehicle::garage::selected::vars;

namespace spawner::vehicle::garage::selected::vars {
	variables m_vars;

	enum GlobalGarageIndices { // void func_355(bool bParam0, var uParam1)
		Garage_PlateType = 0,
		Garage_PlateText = 1,
		Garage_PaintPrimary = 5,
		Garage_PaintSecondary = 6,
		Garage_PaintPearlescant = 7,
		Garage_PaintRim = 8,
		Garage_ModCount = 9,
		Garage_Spoiler = 10,
		Garage_FrontBumper = 11,
		Garage_RearBumper = 12,
		Garage_Skirts = 13,
		Garage_Exhaust = 14,
		Garage_Frame = 15,
		Garage_Grille = 16,
		Garage_Hood = 17,
		Garage_LeftFender = 18,
		Garage_RightFender = 19,
		Garage_Roof = 20,
		Garage_Engine = 21,
		Garage_Brakes = 22,
		Garage_Transmission = 23,
		Garage_Horn = 24,
		Garage_Suspension = 25,
		Garage_Armor = 26,
		Garage_UNK_17 = 27,
		Garage_Turbo = 28,
		Garage_UNK_19 = 29,
		Garage_TireSmoke = 30,
		Garage_UNK_21 = 31,
		Garage_Xenon = 32,
		Garage_FrontRims = 33,
		Garage_RearRims = 34,

		// Bennys
		Garage_PlateHolder,
		Garage_VanityPlates,
		Garage_TrimDesign,
		Garage_Ornaments,
		Garage_Dashboard,
		Garage_Dial,
		Garage_DoorSpeaker,
		Garage_Seats,
		Garage_SteeringWheel,
		Garage_ShifterLeavers,
		Garage_Plaques,
		Garage_Speakers,
		Garage_Trunk,
		Garage_Hydrulics,
		Garage_EngineBlock,
		Garage_AirFilter,
		Garage_Struts,
		Garage_ArchCovers,
		Garage_Aerials,
		Garage_Trim,
		Garage_Tank,
		Garage_Windows,
		Garage_UNK47,
		Garage_Livery,
		Garage_FrontWheelCustom,
		Garage_RearWheelCustom,

		Garage_SmokeR = 62,
		Garage_SmokeG = 63,
		Garage_SmokeB = 64,

		Garage_WindowTint = 65,
		Garage_Model = 66,
		Garage_ConvertibleRoofState = 68,
		Garage_WheelType = 69,
		Garage_CustomR = 71,
		Garage_CustomG = 72,
		Garage_CustomB = 73,
		Garage_NeonR = 74,
		Garage_NeonG = 75,
		Garage_NeonB = 76,
		Garage_AppearanceBitset = 77,				// Custom Paints
		/**/Garage_AppearanceBitset_SecondaryCustom = 12,
		Garage_GeneralBitset = 103,					// Insurance
		Garage_DefaultRadioStation = 120,
	};

	template<typename T>
	T get_slot_trait(int Slot, int Trait) {
		return *menu::script_global(rage::global::_155_garage_base).at(Slot, rage::global::_155_garage_size).at(Trait).get<T>();
	}

	template<typename T>
	void set_slot_trait(int Slot, int Trait, T Value) {
		menu::script_global(rage::global::_155_garage_base).at(Slot, rage::global::_155_garage_size).at(Trait).as<T>() = Value;
		native::set_bit(menu::script_global(rage::global::_155_garage_base).at(Slot, rage::global::_155_garage_size).at(Garage_GeneralBitset).get<int>(), 12);
	}

	namespace scripts {
		int func_1086(int iParam0, int iParam1) {
			switch (iParam0) {
				case joaat("faction2"):
				case joaat("buccaneer2"):
				case joaat("chino2"):
				case joaat("moonbeam2"):
				case joaat("primo2"):
				case joaat("voodoo"):
					return 1;
					break;

				case joaat("sabregt2"):
					if (!menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset1).as<int>()) {
						return 0;
					} else {
						return 1;
					}
					break;

				case joaat("tornado5"):
					if (!menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset2).as<int>()) {
						return 0;
					} else {
						return 1;
					}
					break;

				case joaat("virgo2"):
					if (!menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset3).as<int>()) {
						return 0;
					} else {
						return 1;
					}
					break;

				case joaat("minivan2"):
					if (!menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset4).as<int>()) {
						return 0;
					} else {
						return 1;
					}
					break;

				case joaat("slamvan3"):
					if (!menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset5).as<int>()) {
						return 0;
					} else {
						return 1;
					}
					break;

				case joaat("faction3"):
					if (!menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset6).as<int>()) {
						return 0;
					} else {
						return 1;
					}
					break;

				case joaat("sultanrs"):
				case joaat("banshee2"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("comet3"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset7).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("diablous2"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset8).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("fcr2"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset9).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("elegy"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset10).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("nero2"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset11).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("italigtb2"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset12).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("specter2"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset13).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("technical3"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset14).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("insurgent3"):
					if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset15).as<int>()) {
						if ((iParam1 & 1) != 0) {
							return 0;
						}
						return 1;
					}
					return 0;
					break;

				case joaat("slamvan4"):
				case joaat("slamvan5"):
				case joaat("slamvan6"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("issi4"):
				case joaat("issi5"):
				case joaat("issi6"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("impaler2"):
				case joaat("impaler3"):
				case joaat("impaler4"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("deathbike"):
				case joaat("deathbike2"):
				case joaat("deathbike3"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("monster3"):
				case joaat("monster4"):
				case joaat("monster5"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("dominator4"):
				case joaat("dominator5"):
				case joaat("dominator6"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("bruiser"):
				case joaat("bruiser2"):
				case joaat("bruiser3"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("youga3"):
				case joaat("gauntlet5"):
				case joaat("yosemite3"):
					if ((iParam1 & 1) != 0) {
						return 0;
					}
					return 1;
					break;

				case joaat("manana2"):
				case joaat("peyote3"):
				case joaat("glendale2"):
					return 1;
					break;
			}
			return 0;
		}

		int func_1085(int iParam0, int iParam1) {
			int iVar0;
			int iVar1;
			float fVar2;
			int iVar3;

			if (native::does_entity_exist(iParam0) && native::is_vehicle_driveable(iParam0, 0)) {
				switch (native::get_entity_model(iParam0)) {
					case joaat("tornado5"):
						switch (iParam1) {
							case 0:
								return 0;
								break;

							case 1:
								return 1;
								break;

							case 2:
								return 2;
								break;

							case 3:
								return 3;
								break;

							case 4:
								return 4;
								break;

							case 5:
								return 4;
								break;
						}
						break;

					case joaat("faction3"):
						return 3;
						break;
				}

				iVar0 = native::get_num_vehicle_mods(iParam0, 38);
				iVar1 = native::get_num_vehicle_mods(iParam0, 24);
				fVar2 = (float(iParam1 + 1) / float(iVar0));
				iVar3 = (int)(floor((float(iVar1) * fVar2)) - 1);
				if (iVar3 < 0) {
					iVar3 = 0;
				}
				if (iVar3 >= iVar0) {
					iVar3 = (iVar0 - 1);
				}
				return iVar3;
			}
			return 0;
		}

		bool script_apply_mods(Vehicle* iParam0, int Slot) {
			int iVar0;

			if (!native::is_vehicle_driveable(*iParam0, 0)) {
				return 0;
			}

			if (native::get_num_mod_kits(*iParam0) == 0) {
				return 0;
			}

			native::set_vehicle_mod_kit(*iParam0, 0);

			iVar0 = 0;
			while (iVar0 < get_slot_trait<int>(Slot, 9)) {
				if ((((iVar0 == 17 || iVar0 == 18) || iVar0 == 19) || iVar0 == 20) || iVar0 == 21) {
					native::toggle_vehicle_mod(*iParam0, iVar0, get_slot_trait<int>(Slot, 10 + iVar0) > 0);
				} else if (iVar0 == 22) {
					if (get_slot_trait<int>(Slot, 10 + iVar0) > 0) {
						native::toggle_vehicle_mod(*iParam0, iVar0, true);
						if (get_slot_trait<int>(Slot, 10 + iVar0) == 1) {
							native::set_vehicle_xenon_lights_colour(*iParam0, 255);
						} else {
							native::set_vehicle_xenon_lights_colour(*iParam0, (get_slot_trait<int>(Slot, 10 + iVar0) - 2));
						}
					} else {
						native::toggle_vehicle_mod(*iParam0, iVar0, false);
					}
				} else if (native::get_vehicle_mod(*iParam0, iVar0) != (get_slot_trait<int>(Slot, 10 + iVar0) - 1)) {
					native::remove_vehicle_mod(*iParam0, iVar0);
					if (get_slot_trait<int>(Slot, 10 + iVar0) > 0) {
						if (iVar0 == 23) {
							native::set_vehicle_mod(*iParam0, iVar0, (get_slot_trait<int>(Slot, 10 + iVar0) - 1), get_slot_trait<int>(Slot, Garage_FrontWheelCustom) > 0);
						} else if (iVar0 == 24) {
							native::set_vehicle_mod(*iParam0, iVar0, (get_slot_trait<int>(Slot, 10 + iVar0) - 1), get_slot_trait<int>(Slot, Garage_RearWheelCustom) > 0);
						} else {
							native::set_vehicle_mod(*iParam0, iVar0, (get_slot_trait<int>(Slot, 10 + iVar0) - 1), false);
						}
					}
				}

				iVar0++;
			}

			if (func_1086(native::get_entity_model(*iParam0), 1) && native::get_vehicle_mod(*iParam0, 24) != func_1085(*iParam0, (get_slot_trait<int>(Slot, 39) - 1))) {
				native::set_vehicle_mod(*iParam0, 24, func_1085(*iParam0, (get_slot_trait<int>(Slot, 39) - 1)), false);
			}

			native::set_vehicle_strong(*iParam0, true);
			native::set_vehicle_has_strong_axles(*iParam0, true);
			return 1;
		}
	}

	void apply_mods(Vehicle veh, int slot) {
		native::set_vehicle_number_plate_text_index(veh, get_slot_trait<int>(slot, Garage_PlateType));
		native::set_vehicle_number_plate_text(veh, (const char*)menu::script_global(rage::global::_155_garage_base).at(slot, rage::global::_155_garage_size).at(Garage_PlateText).get<uint64_t>());

		native::set_vehicle_wheel_type(veh, get_slot_trait<int>(slot, Garage_WheelType));

		scripts::script_apply_mods(&veh, slot);
		native::set_vehicle_window_tint(veh, get_slot_trait<int>(slot, Garage_WindowTint));

		int convertible_roof_state = get_slot_trait<int>(slot, Garage_ConvertibleRoofState);
		if ((convertible_roof_state == 0 || convertible_roof_state == 3) || convertible_roof_state == 5) {
			native::raise_convertible_roof(veh, true);
		} else {
			native::lower_convertible_roof(veh, true);
		}

		native::set_vehicle_neon_light_enabled(veh, 0, native::is_bit_set(get_slot_trait<int>(slot, Garage_AppearanceBitset), 30));
		native::set_vehicle_neon_light_enabled(veh, 1, native::is_bit_set(get_slot_trait<int>(slot, Garage_AppearanceBitset), 31));
		native::set_vehicle_neon_light_enabled(veh, 2, native::is_bit_set(get_slot_trait<int>(slot, Garage_AppearanceBitset), 28));
		native::set_vehicle_neon_light_enabled(veh, 3, native::is_bit_set(get_slot_trait<int>(slot, Garage_AppearanceBitset), 29));

		int pearlescant = get_slot_trait<int>(slot, Garage_PaintPearlescant);
		if (pearlescant < 0) { pearlescant = 0; }

		int rim = get_slot_trait<int>(slot, Garage_PaintRim);
		if (rim < 0) { rim = 0; }

		native::set_vehicle_extra_colours(veh, pearlescant, rim);

		if (get_slot_trait<int>(slot, Garage_PaintPrimary) != -1 && get_slot_trait<int>(slot, Garage_PaintSecondary) != -1) {
			native::set_vehicle_colours(veh, get_slot_trait<int>(slot, Garage_PaintPrimary), get_slot_trait<int>(slot, Garage_PaintSecondary));
		}

		color_rgba smoke_color;
		smoke_color.r = get_slot_trait<int>(slot, Garage_SmokeR);
		smoke_color.g = get_slot_trait<int>(slot, Garage_SmokeG);
		smoke_color.b = get_slot_trait<int>(slot, Garage_SmokeB);

		native::set_vehicle_tyre_smoke_color(veh, smoke_color.r, smoke_color.g, smoke_color.b);

		color_rgba neon_color;
		neon_color.r = get_slot_trait<int>(slot, Garage_NeonR);
		neon_color.g = get_slot_trait<int>(slot, Garage_NeonG);
		neon_color.b = get_slot_trait<int>(slot, Garage_NeonB);

		native::set_vehicle_neon_lights_colour(veh, neon_color.r, neon_color.g, neon_color.b);

		color_rgba custom_color;
		custom_color.r = get_slot_trait<int>(slot, Garage_CustomR);
		custom_color.g = get_slot_trait<int>(slot, Garage_CustomG);
		custom_color.b = get_slot_trait<int>(slot, Garage_CustomB);

		if (native::is_bit_set(get_slot_trait<int>(slot, Garage_AppearanceBitset), 13)) {
			native::set_vehicle_custom_primary_colour(veh, custom_color.r, custom_color.g, custom_color.b);
		}

		if (native::is_bit_set(get_slot_trait<int>(slot, Garage_AppearanceBitset), 12)) {
			native::set_vehicle_custom_secondary_colour(veh, custom_color.r, custom_color.g, custom_color.b);
		}
	}

	void spawn_vehicle(int slot) {
		spawner::vars::spawn_vehicle(get_slot_trait<uint32_t>(slot, Garage_Model), [=](Entity vehicle) {
			apply_mods(vehicle, slot);
		}, true);
	}
}

void spawner_vehicle_garage_selected_menu::load() {
	set_name("Garage Vehicles");
	set_parent<spawner_vehicle_garage_menu>();
}

void spawner_vehicle_garage_selected_menu::update() {}

void spawner_vehicle_garage_selected_menu::update_once() {
	clear_options(0);

	for (int slot : spawner::vehicle::garage::vars::m_vars.m_valid_slots[m_vars.m_slot]) {
		add_option(button_option(native::get_label_text(native::get_display_name_from_vehicle_model(get_slot_trait<uint32_t>(slot, Garage_Model))))
			.add_click([=] { spawn_vehicle(slot); }));
	}
}

void spawner_vehicle_garage_selected_menu::feature_update() {}

spawner_vehicle_garage_selected_menu* g_instance;
spawner_vehicle_garage_selected_menu* spawner_vehicle_garage_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_vehicle_garage_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}