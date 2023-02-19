#include "spawner_vehicle_garage.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"
#include "menu/base/util/global.h"
#include "menu/base/util/helpers.h"
#include "menu/base/util/stats.h"
#include "garage/spawner_vehicle_garage_selected.h"
#include "rage/types/global_types.h"

using namespace spawner::vehicle::garage::vars;

namespace spawner::vehicle::garage::vars {
	variables m_vars;

	const char* garage_labels[] = {
		"PROPERTY_HOUSE",
		"MULTI_PROPERTY_1",
		"MULTI_PROPERTY_2",
		"MULTI_PROPERTY_3",
		"MULTI_PROPERTY_4",
		"PROP_OFFICE",
		"PROP_CLUBHOUSE",
		"MULTI_PROPERTY_5",
		"PROP_OFFICE_GAR1",
		"PROP_OFFICE_GAR2",
		"PROP_OFFICE_GAR3",
		"PROP_IE_WAREHOUSE",
		"PROP_HANGAR",
		"PROP_DEFUNCBASE",
		"PROP_NIGHTCLUB",
		"PROP_MEGAWARE_GAR1",
		"PROP_MEGAWARE_GAR2",
		"PROP_MEGAWARE_GAR3",
		"PROP_ARENAWARS_GAR1",
		"PROP_ARENAWARS_GAR2",
		"PROP_ARENAWARS_GAR3",
		"PROP_CASINO_GAR1",
		"PROP_ARCADE_GAR1",
		"MULTI_PROPERTY_6",
		"MULTI_PROPERTY_7"
	};

	namespace scripts {
		int func_603(int iParam0, int iParam1) {
			if (iParam1 == -1) {
				switch (iParam0) {
					case 91:
					case 92:
					case 93:
					case 94:
					case 95:
					case 96:
					case 97:
					case 98:
					case 99:
					case 100:
					case 101:
					case 102:
						return 1;
						break;
				}
			} else if (iParam1 == 91) {
				switch (iParam0) {
					case 91:
					case 92:
					case 93:
					case 94:
					case 95:
					case 96:
						return 1;
						break;
				}
			} else if (iParam1 == 97) {
				switch (iParam0) {
					case 97:
					case 98:
					case 99:
					case 100:
					case 101:
					case 102:
						return 1;
						break;
				}
			}
			return 0;
		}

		int func_604(int iParam0) {
			switch (iParam0) {
				case 87:
				case 88:
				case 89:
				case 90:
					return 1;
					break;
			}
			return 0;
		}

		int func_607(int iParam0) {
			if (iParam0 != -1) {
				return native::is_bit_set(menu::script_global(rage::global::_155_player_stats_struct).at(iParam0, rage::global::_155_player_stats_size).at(rage::global::_155_property_int_offset_16).at(rage::global::_155_property_int_offset_16_1).as<int>(), 2);
			}

			return 0;
		}

		int func_285(int iParam0) {
			if (iParam0 != -1) {
				return native::is_bit_set(menu::script_global(rage::global::_155_property_base2).at(iParam0, rage::global::_155_property_base2_size).at(rage::global::_155_property_base2_flag).as<int>(), 9);
			}
			return 0;
		}

		// updated
		bool func_606(int iParam0, bool bParam1) {
			if (menu::script_global(rage::global::_155_property_base3).as<int>() != -1) {
				if (!func_607(menu::script_global(rage::global::_155_property_base3).as<int>())) {
					return 0;
				}

				if (bParam1) {
					if (menu::player::get_local_player().m_id != menu::script_global(rage::global::_155_property_base3).as<int>()) {
						if (native::is_bit_set(menu::script_global(rage::global::_155_property_base2).at(menu::script_global(rage::global::_155_property_base3).as<int>(), rage::global::_155_property_base2_size).at(rage::global::_155_property_base2_flag).as<int>(), 24) || func_285(menu::script_global(rage::global::_155_property_base3).as<int>())) {
							return 1;
						}
					}
				}
			}

			return native::is_bit_set(menu::script_global(rage::global::_155_property_base2).at(iParam0, rage::global::_155_property_base2_size).at(rage::global::_155_property_base2_flag).as<int>(), 24);
		}

		// updated
		int func_605(int iParam0, bool bParam1, bool bParam2) {
			if (bParam2) {
				return func_606(menu::player::get_local_player().m_id, 0);
			}
			if (bParam1) {
				if (func_606(menu::player::get_local_player().m_id, 0)) {
					return 0;
				}
				switch (iParam0) {
					case 103:
					case 106:
					case 109:
					case 112:
					case 104:
					case 107:
					case 110:
					case 113:
					case 105:
					case 108:
					case 111:
					case 114:
						return 1;
						break;
				}
			}
			switch (iParam0) {
				case 103:
				case 106:
				case 109:
				case 112:
				case 104:
				case 107:
				case 110:
				case 113:
				case 105:
				case 108:
				case 111:
				case 114:
					return 1;
					break;
			}
			return 0;
		}

		// updated
		int func_609(int iParam0) {
			iParam0 = (iParam0 - 1000);
			if (iParam0 >= 0 && iParam0 <= 4) {
				return iParam0;
			}
			return -1;
		}

		// updated
		int func_1452(int iParam0) {
			switch (iParam0) {
				case 0:
					return 156;

				case 2:
					return 223;

				case 1:
					return 224;

				case 3:
					return 278;
			}
			return -1;
		}

		// updated
		int get_garage_vehicle_max_count(int iParam0, int iParam1 = -1, bool bParam2 = true) {
			if (iParam0 == -1) {
				if (iParam1 >= 1) {
					if (func_605(iParam1, 0, 0)) {
						return 20;
					} else if (func_604(iParam1)) {
						return 0;
					} else if (func_603(iParam1, -1)) {
						return 10;
					} else if (iParam1 == 115) {
						return 8;
					} else if (iParam1 == 116) {
						return 20;
					} else if (iParam1 == 117) {
						return 7;
					} else if (iParam1 == 118) {
						return 1;
					} else if ((iParam1 == 119 || iParam1 == 120) || iParam1 == 121) {
						return 10;
					} else if (iParam1 == 122) {
						return 9;
					} else if (iParam1 == 123 || iParam1 == 124) {
						return 10;
					} else if (iParam1 == 125) {
						return 10;
					} else if (iParam1 == 126) {
						return 10;
					} else if (iParam1 == 127) {
						return 10;
					} else if (iParam1 <= 127 && iParam1 > 0) {
						if (menu::script_global(rage::global::_155_property_base4).at(iParam1, rage::global::_155_property_base4_size).at(rage::global::_155_property_base4_flag).as<int>() == 2) {
							if (bParam2) {
								return 3;
							} else {
								return 2;
							}
						} else if (menu::script_global(rage::global::_155_property_base4).at(iParam1, rage::global::_155_property_base4_size).at(rage::global::_155_property_base4_flag).as<int>() == 6) {
							if (bParam2) {
								return 8;
							} else {
								return 6;
							}
						} else if (menu::script_global(rage::global::_155_property_base4).at(iParam1, rage::global::_155_property_base4_size).at(rage::global::_155_property_base4_flag).as<int>() == 10) {
							if (bParam2) {
								return 13;
							} else {
								return 10;
							}
						}
					}
				}
			}
			switch (iParam0) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 7:
				case 23:
				case 24:
					return 13;
					break;

				case 5:
					return 0;
					break;

				case 6:
					return 10;
					break;

				case 8:
				case 9:
				case 10:
					return 20;
					break;

				case 11:
					return 8;
					break;

				case 12:
					return 20;
					break;

				case 13:
					return 7;
					break;

				case 14:
					return 1;
					break;

				case 15:
				case 16:
				case 17:
					return 10;
					break;

				case 18:
				case 19:
				case 20:
					return 10;
					break;

				case 21:
					return 10;
					break;

				case 22:
					return 10;
					break;

				case 25:
					return 10;
					break;
			}
			return 0;
		}

		// updated
		int func_1451(int iParam0) {
			int iVar0;

			switch (iParam0) {
				case 8:
					return 88;
					break;

				case 9:
					return 108;
					break;

				case 10:
					return 128;
					break;

				case 11:
					return 148;
					break;

				case 6:
					return 65;
					break;

				case 7:
					return 75;
					break;

				case 5:
					return -1;
					break;

				case 12:
					return 159;
					break;

				case 13:
					return 179;
					break;

				case 14:
					return 191;
					break;

				case 15:
					return 192;
					break;

				case 16:
					return 202;
					break;

				case 17:
					return 212;
					break;

				case 18:
					return 227;
					break;

				case 19:
					return 237;
					break;

				case 20:
					return 247;
					break;

				case 21:
					return 258;
					break;

				case 22:
					return 268;
					break;

				case 23:
					return 281;
					break;

				case 24:
					return 294;
					break;

				case 25:
					return 307;
					break;
			}
			if (iParam0 >= 1000) {
				iVar0 = func_609(iParam0);
				return func_1452(iVar0);
			}
			return (get_garage_vehicle_max_count(iParam0, -1, 1) * iParam0);
		}

		void func_1149(int iParam0, int* iParam1, bool bParam2) {
			if (menu::script_global(rage::global::_155_tunables).at(rage::global::_155_property_int_offset_17).as<int>()) {
				*iParam1 = iParam0;
			}

			if (iParam0 >= 0) {
				*iParam1 = (menu::script_global(rage::global::_155_property_base5).at(iParam0).as<int>() - 1);
			} else {
				*iParam1 = -1;
			}
		}

		// updated
		char* func_2031(int iParam0) {
			switch (iParam0) {
				case 1:
					return "MP_HANGAR_1";
					break;

				case 2:
					return "MP_HANGAR_2";
					break;

				case 3:
					return "MP_HANGAR_3";
					break;

				case 4:
					return "MP_HANGAR_4";
					break;

				case 5:
					return "MP_HANGAR_5";
					break;
			}
			return "";
		}

		int func_981(int iParam0) {
			if (iParam0 != -1) {
				return menu::script_global(rage::global::_155_player_stats_struct).at(iParam0, rage::global::_155_player_stats_size).at(rage::global::_155_property_int_offset_16).at(rage::global::_155_property_int_offset_16_2).as<int>();
			}
			return 0;
		}

		int func_979(int iParam0) {
			if (iParam0 != -1) {
				return menu::script_global(rage::global::_155_player_stats_struct).at(iParam0, rage::global::_155_player_stats_size).at(rage::global::_155_property_int_offset_16).at(rage::global::_155_property_int_offset_16_3).as<int>();
			}
			return 0;
		}

		// updated
		char* func_2030(int iParam0) {
			switch (iParam0) {
				case 1:
					return "MP_DBASE_1";
					break;

				case 2:
					return "MP_DBASE_2";
					break;

				case 3:
					return "MP_DBASE_3";
					break;

				case 4:
					return "MP_DBASE_4";
					break;

				case 5:
					return "MP_DBASE_6";
					break;

				case 6:
					return "MP_DBASE_7";
					break;

				case 7:
					return "MP_DBASE_8";
					break;

				case 8:
					return "MP_DBASE_9";
					break;

				case 9:
					return "MP_DBASE_10";
					break;
			}
			return "";
		}
	}

	template<typename T>
	T get_slot_trait(int slot, int trait) {
		return *menu::script_global(rage::global::_155_garage_base).at(slot, rage::global::_155_garage_size).at(trait).get<T>();
	}

    template<typename T>
    void set_slot_trait(int slot, int trait, T value) {
        *menu::script_global(rage::global::_155_garage_base).at(slot, rage::global::_155_garage_size).at(trait).get<T>() = value;
        native::set_bit(menu::script_global(rage::global::_155_garage_base).at(slot, rage::global::_155_garage_size).at(103).get<int>(), 12);
    }

	const char* get_garage_name(int id) {
		const char* label = "Garage";

		int index = stats<int>::get(garage_labels[id]);
		if (index > 0) {
			if (index > 115) {
				if (index == 116) {
					label = (scripts::func_2031(scripts::func_981(menu::player::get_local_player().m_id)));
				}

				if (index == 117) {
					label = (scripts::func_2030(scripts::func_979(menu::player::get_local_player().m_id)));
				}

				if (index == 118) {
					label = ("MP_BHUB_CLUBG");
				}

				if (index == 119) {
					label = "MP_BHUB_GAR1";
				}

				if (index == 120) {
					label = "MP_BHUB_GAR2";
				}

				if (index == 121) {
					label = "MP_BHUB_GAR3";
				}

				if (index == 122) {
					label = "ARENA_GAR_F0";
				}

				if (index == 123) {
					label = "ARENA_GAR_F1";
				}

				if (index == 124) {
					label = "ARENA_GAR_F2";
				}

				if (index == 125) {
					label = "CASINO_GARNAME";
				}

				if (index == 126) {
					label = "ARCADE_GARNAME";
				}

				label = native::get_label_text(label);
			} else {
				label = menu::helpers::get_location_from_id(index).c_str();
			}
		}

		return label;
	}
}

void spawner_vehicle_garage_menu::load() {
	set_name("Garage Vehicles");
	set_parent<spawner_menu>();

	add_string("~m~No Garages");
}

void spawner_vehicle_garage_menu::update() {}

void spawner_vehicle_garage_menu::update_once() {
	clear_options(0);

	for (std::vector<int>& vec : m_vars.m_valid_slots) vec.clear();

	for (int i = 0; i < NUMOF(garage_labels); i++) {
		int ivar4 = scripts::func_1451(i);
		for (int j = 0; j < scripts::get_garage_vehicle_max_count(i, -1, 1); j++) {
			int slot = 0;
			scripts::func_1149((j + ivar4), &slot, 1);

			if (slot >= 0 && get_slot_trait<uint32_t>(slot, 66) != 0 && native::is_model_in_cdimage(get_slot_trait<uint32_t>(slot, 66))) {
				m_vars.m_valid_slots[i].push_back(slot);
			}
		}

		if (!m_vars.m_valid_slots[i].empty()) {
			add_option(submenu_option(get_garage_name(i))
				.add_submenu<spawner_vehicle_garage_selected_menu>()
				.add_click([=] {
					spawner_vehicle_garage_selected_menu::get()->set_name(get_garage_name(i), false, false);
					spawner::vehicle::garage::selected::vars::m_vars.m_slot = i;
				}));
		}
	}

	if (get_options().size() == 0) {
		add_option(button_option(get_string("~m~No Garages")));
	}
}

void spawner_vehicle_garage_menu::feature_update() {}

spawner_vehicle_garage_menu* g_instance;
spawner_vehicle_garage_menu* spawner_vehicle_garage_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_vehicle_garage_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}