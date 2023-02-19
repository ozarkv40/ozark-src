#include "vehicle_customs.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "menu/base/util/global.h"
#include "customs/vehicle_customs_lsc.h"
#include "customs/vehicle_customs_bumpers.h"
#include "customs/vehicle_customs_fender.h"
#include "customs/vehicle_customs_horn.h"
#include "customs/vehicle_customs_lights.h"
#include "customs/vehicle_customs_respray.h"
#include "customs/vehicle_customs_wheels.h"
#include "customs/vehicle_customs_interior.h"
#include "rage/types/global_types.h"

using namespace vehicle::customs::vars;

namespace vehicle::customs::vars {
	variables m_vars;

	scroll_struct<int> shop[] = {
		{ localization("Los Santos Customs", true), 0 },
		{ localization("Benny's Original Motorworks", true), 0 }
	};

	namespace scripts {
		void func_1666(float fParam0, float fParam1, float fParam2, float fParam3, int iParam4, int iParam5, int iParam6, int iParam7) {
			std::pair<std::string, std::string> texture = menu::renderer::get_texture(global::ui::m_vehicle_stats_bar);
			menu::renderer::draw_sprite_aligned(texture, { fParam0, fParam1 }, { fParam2, fParam3 }, 0.f, { iParam4, iParam5, iParam6, iParam7 });
		}

		void draw_vehicle_stat_rects(float fParam0, float fParam1, float fParam2, float fParam3, int iParam4, int iParam5, int iParam6, int iParam7) {
			float fVar0;
			float fVar1;
			float fVar2;
			int iVar3;

			fVar0 = ((125.f - 8.f) * 0.00078125f);
			fVar1 = (125.f * 0.00078125f);
			fVar2 = fParam0;
			iVar3 = 0;
			while (iVar3 < 5) {
				if (fParam2 > ((fVar0 / 100.f) * 20.f)) {
					func_1666(fVar2, fParam1, ((fVar0 / 100.f) * 20.f), fParam3, iParam4, iParam5, iParam6, iParam7);
				} else if (fParam2 > 0.f) {
					func_1666(fVar2, fParam1, fParam2, fParam3, iParam4, iParam5, iParam6, iParam7);
				}

				fParam2 = (fParam2 - ((fVar0 / 100.f) * 20.f));
				fVar2 = (fVar2 + ((fVar1 / 100.f) * 20.f));
				iVar3++;
			}
		}

		void func_1665(int iParam0, int* uParam1, int* uParam2, int* uParam3) {
			switch (iParam0) {
				case 0:
					*uParam1 = 8;
					*uParam2 = 8;
					*uParam3 = 8;
					break;

				case 1:
					*uParam1 = 37;
					*uParam2 = 37;
					*uParam3 = 39;
					break;

				case 22:
					*uParam1 = 140;
					*uParam2 = 146;
					*uParam3 = 154;
					break;

				case 23:
					*uParam1 = 91;
					*uParam2 = 93;
					*uParam3 = 94;
					break;

				case 6:
					*uParam1 = 81;
					*uParam2 = 84;
					*uParam3 = 89;
					break;

				case 111:
					*uParam1 = 240;
					*uParam2 = 240;
					*uParam3 = 240;
					break;

				case 28:
					*uParam1 = 150;
					*uParam2 = 8;
					*uParam3 = 0;
					break;

				case 34:
					*uParam1 = 38;
					*uParam2 = 3;
					*uParam3 = 6;
					break;

				case 88:
					*uParam1 = 245;
					*uParam2 = 137;
					*uParam3 = 15;
					break;

				case 45:
					*uParam1 = 74;
					*uParam2 = 22;
					*uParam3 = 7;
					break;

				case 56:
					*uParam1 = 45;
					*uParam2 = 58;
					*uParam3 = 53;
					break;

				case 58:
					*uParam1 = 71;
					*uParam2 = 120;
					*uParam3 = 60;
					break;

				case 54:
					*uParam1 = 77;
					*uParam2 = 98;
					*uParam3 = 104;
					break;

				case 73:
					*uParam1 = 14;
					*uParam2 = 49;
					*uParam3 = 109;
					break;

				case 68:
					*uParam1 = 22;
					*uParam2 = 34;
					*uParam3 = 72;
					break;

				case 140:
					*uParam1 = 0;
					*uParam2 = 174;
					*uParam3 = 239;
					break;

				case 131:
					*uParam1 = 255;
					*uParam2 = 183;
					*uParam3 = 0;
					break;

				case 90:
					*uParam1 = 142;
					*uParam2 = 140;
					*uParam3 = 70;
					break;

				case 97:
					*uParam1 = 156;
					*uParam2 = 141;
					*uParam3 = 113;
					break;

				case 89:
					*uParam1 = 145;
					*uParam2 = 115;
					*uParam3 = 71;
					break;

				case 105:
					*uParam1 = 98;
					*uParam2 = 68;
					*uParam3 = 40;
					break;

				case 100:
					*uParam1 = 124;
					*uParam2 = 27;
					*uParam3 = 68;
					break;

				case 99:
					*uParam1 = 114;
					*uParam2 = 42;
					*uParam3 = 63;
					break;

				case 136:
					*uParam1 = 246;
					*uParam2 = 151;
					*uParam3 = 153;
					break;

				case 49:
					*uParam1 = 32;
					*uParam2 = 32;
					*uParam3 = 44;
					break;

				case 146:
					*uParam1 = 26;
					*uParam2 = 1;
					*uParam3 = 23;
					break;

				default:
					*uParam1 = 255;
					*uParam2 = 255;
					*uParam3 = 255;
					break;
			}
		}

		int func_243(int iParam0) {
			if (iParam0 != -1) {
				return native::is_bit_set(menu::script_global(rage::global::_155_property_base2).at(iParam0, rage::global::_155_property_base2_size).at(rage::global::_155_property_base2_offset1).as<int>(), 6);
			}
			return 0;
		}

		int func_1027(int iParam0) {
			if (iParam0 != -1) {
				return native::is_bit_set(menu::script_global(rage::global::_155_property_base2).at(iParam0, rage::global::_155_property_base2_size).at(rage::global::_155_property_base2_offset1).at(2).as<int>(), 6);
			}
			return 0;
		}

		int func_1013(int iParam0) {
			if (iParam0 != -1) {
				return native::is_bit_set(menu::script_global(rage::global::_155_property_base2).at(iParam0, rage::global::_155_property_base2_size).at(rage::global::_155_property_base2_offset1).at(3).as<int>(), 4);
			}
			return 0;
		}

		int is_model_a_bicycle(int iParam0) {
			if (iParam0 == joaat("BMX")) {
				return 1;
			}
			if (iParam0 == joaat("CRUISER")) {
				return 1;
			}
			if (iParam0 == joaat("SCORCHER")) {
				return 1;
			}
			if ((iParam0 == joaat("TRIBIKE") || iParam0 == joaat("TRIBIKE2")) || iParam0 == joaat("TRIBIKE3")) {
				return 1;
			}
			if (iParam0 == joaat("FIXTER")) {
				return 1;
			}
			return 0;
		}

		int func_2480(int iParam0) {
			switch (iParam0) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 17:
				case 18:
				case 19:
				case 20:
				case 22:
					return 0;
					break;

				case 14:
					return 3;
					break;

				case 15:
					return 1;
					break;

				case 16:
					return 2;
					break;
			}
			return -1;
		}

		int func_19(int iParam0, int iParam1) {
			switch (iParam0) {
				case 0:
					switch (iParam1) {
						case 0:
							return 0;

						case 1:
							return 1;

						case 2:
							return 2;

						case 3:
							return 3;

						case 4:
							return 4;

						case 5:
							return 5;

						case 6:
							return 6;

						case 7:
							return 7;

						case 8:
							return 8;

						case 9:
							return 9;

						case 10:
							return 10;

						case 11:
							return 11;

						case 12:
							return 12;

						case 13:
							return 13;

						case 14:
							return 17;

						case 15:
							return 18;

						case 16:
							return 19;

						case 17:
							return 20;

						case 18:
							return 22;
					}
					break;

				case 3:
					switch (iParam1) {
						case 0:
							return 14;
					}
					break;

				case 1:
					switch (iParam1) {
						case 0:
							return 15;
					}
					break;

				case 2:
					switch (iParam1) {
						case 0:
							return 16;
					}
					break;
			}
			return -1;
		}

		float func_18(int iParam0) {
			if (iParam0 == 7) {
				return 51.77096f;
			}

			return native::get_vehicle_class_estimated_speed(iParam0);
		}

		bool flag = false;

		void populate_globals(int* uParam0) {
			int iVar0;
			int iVar1;
			float fVar2;

			if (!flag) {
				iVar1 = func_19(uParam0[0], uParam0[1]);
				if (iVar1 == -1) {
					uParam0[0]++;
					uParam0[1] = 0;
					if (uParam0[0] >= 4) {
						flag = 1;
					}
					return;
				} else {
					iVar0 = iVar1;

					if ((iVar0 == 15 || iVar0 == 16) || iVar0 == 14) {
						fVar2 = native::get_vehicle_class_max_agility(iVar0);
					} else {
						fVar2 = native::get_vehicle_class_max_traction(iVar0);
					}

					if (m_vars.m_values[uParam0[0]][0] < func_18(iVar0))
						m_vars.m_values[uParam0[0]][0] = func_18(iVar0);
					if (m_vars.m_values[uParam0[0]][1] < native::get_vehicle_class_max_acceleration(iVar0))
						m_vars.m_values[uParam0[0]][1] = native::get_vehicle_class_max_acceleration(iVar0);
					if (m_vars.m_values[uParam0[0]][2] < native::get_vehicle_class_max_braking(iVar0))
						m_vars.m_values[uParam0[0]][2] = native::get_vehicle_class_max_braking(iVar0);
					if (m_vars.m_values[uParam0[0]][3] < fVar2)
						m_vars.m_values[uParam0[0]][3] = fVar2;

					uParam0[1]++;
				}
			}
		}

		void get_vehicle_stats(int iParam0, vehicle_stats* uParam1) {
			float fVar1;
			int iVar2;
			float fVar3;

			if (func_243(menu::player::get_local_player().m_id) && native::does_entity_exist(menu::script_global(rage::global::_155_customs_base).at(304).at(0).as<Entity>())) {// 1.55 good
				if (iParam0 == menu::script_global(rage::global::_155_customs_base).at(304).at(1).as<Entity>() || iParam0 == menu::script_global(rage::global::_155_customs_base2).as<int>()) {// 1.55 good
					return;
				}
			}

			if (func_1027(menu::player::get_local_player().m_id) && native::does_entity_exist(menu::script_global(rage::global::_155_customs_base).at(308).as<int>())) {// 1.55 good
				if (iParam0 == menu::script_global(rage::global::_155_customs_base).at(308).as<int>()) {// 1.55 good
					return;
				}
			}

			if (func_1013(menu::player::get_local_player().m_id) && native::does_entity_exist(menu::script_global(rage::global::_155_customs_base).at(325).as<int>())) {// 1.55 good
				if (iParam0 == menu::script_global(rage::global::_155_customs_base).at(325).as<int>()) { // 1.55 good
					return;
				}
			}

			if (!native::is_entity_dead(iParam0, 0)) {
				if (!uParam1->m_success) {
					fVar1 = 1.f;
					iVar2 = native::get_entity_model(iParam0);

					if (is_model_a_bicycle(iVar2)) {
						fVar1 = 0.5f;
					} else {
						fVar1 = 1.f;
					}

					uParam1->m_estimated_max_speed = native::get_vehicle_estimated_max_speed(iParam0);
					uParam1->m_braking = (native::get_vehicle_max_braking(iParam0) * fVar1);
					uParam1->m_acceleration = (native::get_vehicle_acceleration(iParam0) * fVar1);

					if (iVar2 == joaat("VOLTIC")) {
						uParam1->m_acceleration = (native::get_vehicle_acceleration(iParam0) * 2.f);
					}

					if (iVar2 == joaat("tezeract")) {
						uParam1->m_acceleration = (native::get_vehicle_acceleration(iParam0) * 2.6753f);
					}

					if (iVar2 == joaat("jester3")) {
						uParam1->m_estimated_max_speed = (native::get_vehicle_estimated_max_speed(iParam0) * 0.9890084f);
					}

					if (iVar2 == joaat("freecrawler")) {
						uParam1->m_estimated_max_speed = (native::get_vehicle_estimated_max_speed(iParam0) * 0.9788762f);
					}

					if (iVar2 == joaat("swinger")) {
						uParam1->m_estimated_max_speed = (native::get_vehicle_estimated_max_speed(iParam0) * 0.9650553f);
					}

					if (iVar2 == joaat("menacer")) {
						uParam1->m_estimated_max_speed = (native::get_vehicle_estimated_max_speed(iParam0) * 0.9730466f);
					}

					if (iVar2 == joaat("speedo4")) {
						uParam1->m_estimated_max_speed = (native::get_vehicle_estimated_max_speed(iParam0) * 0.9426523f);
					}

					if (native::is_this_model_a_heli(iVar2) || native::is_this_model_a_plane(iVar2)) {
						fVar3 = (native::_0xC6AD107DDC9054CC(iVar2) * fVar1);
					} else if (native::is_this_model_a_boat(iVar2)) {
						fVar3 = (native::_0x5AA3F878A178C4FC(iVar2) * fVar1);
					} else {
						fVar3 = (native::get_vehicle_max_traction(iParam0) * fVar1);
					}

					uParam1->m_traction = fVar3;
					if (iVar2 == joaat("T20")) {
						uParam1->m_acceleration = (uParam1->m_acceleration - 0.05f);
					} else if (iVar2 == joaat("VINDICATOR")) {
						uParam1->m_acceleration = (uParam1->m_acceleration - 0.02f);
					}

					while (!flag) {
						populate_globals(m_vars.m_global_stats);
					}

					int iVar4 = func_2480(native::get_vehicle_class(iParam0));
					if (iVar4 == -1) {
						uParam1->m_success = false;
						uParam1->m_estimated_max_speed = 0.f;
						uParam1->m_acceleration = 0.f;
						uParam1->m_braking = 0.f;
						uParam1->m_traction = 0.f;
						return;
					}

					uParam1->m_estimated_max_speed = ((uParam1->m_estimated_max_speed / m_vars.m_values[iVar4][0]) * 100.f);
					if (uParam1->m_estimated_max_speed > 100.f) {
						uParam1->m_estimated_max_speed = 100.f;
					}

					uParam1->m_acceleration = ((uParam1->m_acceleration / m_vars.m_values[iVar4][1]) * 100.f);
					if (uParam1->m_acceleration > 100.f) {
						uParam1->m_acceleration = 100.f;
					}

					uParam1->m_braking = ((uParam1->m_braking / m_vars.m_values[iVar4][2]) * 100.f);
					if (uParam1->m_braking > 100.f) {
						uParam1->m_braking = 100.f;
					}

					uParam1->m_traction = ((uParam1->m_traction / m_vars.m_values[iVar4][3]) * 100.f);
					if (uParam1->m_traction > 100.f) {
						uParam1->m_traction = 100.f;
					}

					uParam1->m_success = true;
				}
			}
		}

		void draw_vehicle_stats(Vehicle Veh) {
			std::vector<std::shared_ptr<base_option>> options = menu::submenu::handler::get_current()->get_options();
			int count = (int)std::count_if(begin(options), end(options), [](std::shared_ptr<base_option> option) { return option->is_visible(); });

			if (count > menu::base::get_max_options()) {
				count = menu::base::get_max_options();
			}

			float Y = global::ui::g_position.y + ((count + 1) * global::ui::g_option_scale) + 0.0025f;

			std::pair<std::string, std::string> texture = menu::renderer::get_texture(global::ui::m_vehicle_stats_background);
			menu::renderer::draw_sprite_aligned(texture, { global::ui::g_position.x, Y }, { global::ui::g_scale.x, 0.15f }, 0.f, global::ui::g_main_header.opacity(220));

			float fVar42 = (125.f - 8.f);

			int iVar43 = 0;
			int iVar44 = 0;
			int iVar45 = 0;
			int iVar46 = 0;

			float new_font_size = menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height);

			float fVar49 = 0.0115f;
			menu::renderer::draw_text("Top Speed", { global::ui::g_position.x + 0.004f, (Y + fVar49) }, new_font_size, global::ui::g_option_font, { 255, 255, 255, 255 });
			fVar49 = (fVar49 + 0.034722f);

			menu::renderer::draw_text("Acceleration", { global::ui::g_position.x + 0.004f, (Y + fVar49) }, new_font_size, global::ui::g_option_font, { 255, 255, 255, 255 });
			fVar49 = (fVar49 + 0.034722f);

			menu::renderer::draw_text("Braking", { global::ui::g_position.x + 0.004f, (Y + fVar49) }, new_font_size, global::ui::g_option_font, { 255, 255, 255, 255 });
			fVar49 = (fVar49 + 0.034722f);

			menu::renderer::draw_text("Traction", { global::ui::g_position.x + 0.004f, (Y + fVar49) }, new_font_size, global::ui::g_option_font, { 255, 255, 255, 255 });

			native::get_hud_colour(1, &iVar43, &iVar44, &iVar45, &iVar46);
			iVar46 = 76;

			float fVar51 = 0.017f;
			draw_vehicle_stat_rects(global::ui::g_position.x + 0.11f, (Y + fVar51), (0.00078125f * fVar42), (0.00138888f * 6.f), iVar43, iVar44, iVar45, iVar46); // faint bars - w=0.09140625

			fVar51 = (fVar51 + 0.034722f);
			draw_vehicle_stat_rects(global::ui::g_position.x + 0.11f, (Y + fVar51), (0.00078125f * fVar42), (0.00138888f * 6.f), iVar43, iVar44, iVar45, iVar46); // faint bars

			fVar51 = (fVar51 + 0.034722f);
			draw_vehicle_stat_rects(global::ui::g_position.x + 0.11f, (Y + fVar51), (0.00078125f * fVar42), (0.00138888f * 6.f), iVar43, iVar44, iVar45, iVar46); // faint bars

			fVar51 = (fVar51 + 0.034722f);
			draw_vehicle_stat_rects(global::ui::g_position.x + 0.11f, (Y + fVar51), (0.00078125f * fVar42), (0.00138888f * 6.f), iVar43, iVar44, iVar45, iVar46); // faint bars

			fVar51 = 0.017f;

			scripts::flag = 0;
			m_vars.m_new_stats.m_success = false;
			get_vehicle_stats(Veh, &m_vars.m_new_stats);

			int iVar58 = 0;
			float fVar52 = 0.f;
			float fVar53 = 0.f;

			float CachedData[] = { m_vars.m_cached_stats.m_estimated_max_speed, m_vars.m_cached_stats.m_acceleration, m_vars.m_cached_stats.m_braking, m_vars.m_cached_stats.m_traction };
			float NewData[] = { m_vars.m_new_stats.m_estimated_max_speed, m_vars.m_new_stats.m_acceleration, m_vars.m_new_stats.m_braking, m_vars.m_new_stats.m_traction };

			while (iVar58 < 4) {
				fVar52 = (0.00078125f * ((fVar42 / 100.f) * (NewData[iVar58] - CachedData[iVar58])));
				fVar53 = (0.00078125f * ((fVar42 / 100.f) * CachedData[iVar58]));

				// handles showing what the upgrade will do for u
				if (fVar52 < 0.f) {
					native::get_hud_colour(6, &iVar43, &iVar44, &iVar45, &iVar46);
					draw_vehicle_stat_rects(global::ui::g_position.x + 0.11f, (Y + fVar51), fVar53, (0.00138888f * 6.f), iVar43, iVar44, iVar45, iVar46); // less -> red
					fVar53 = (fVar53 + fVar52);
				} else {
					native::get_hud_colour(9, &iVar43, &iVar44, &iVar45, &iVar46);
					draw_vehicle_stat_rects(global::ui::g_position.x + 0.11f, (Y + fVar51), (fVar53 + fVar52), (0.00138888f * 6.f), iVar43, iVar44, iVar45, iVar46); // more -> blue
				}

				native::get_hud_colour(1, &iVar43, &iVar44, &iVar45, &iVar46);
				draw_vehicle_stat_rects(global::ui::g_position.x + 0.11f, (Y + fVar51), fVar53, (0.00138888f * 6.f), iVar43, iVar44, iVar45, 255); // old value
				fVar51 = (fVar51 + 0.034722f);
				iVar58++;
			}
		}
	};

	bool can_run_lsc() {
		if (!menu::player::get_local_player().m_in_vehicle) return false;

		for (int i = MOD_SPOILER; i <= MOD_BACKWHEELS; i++) {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, i) > 0) {
				return true;
			}
		}

		return false;
	}

	bool can_run_bennys() {
		if (!menu::player::get_local_player().m_in_vehicle) return false;

		int count = 0;
		for (int i = MOD_PLATEHOLDER; i <= MOD_LIVERY; i++) {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, i) > 0) {
				count++;
			}
		}

		if (count > 1) return true;

		// fuck livery
		if (count == 1) {
			if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_LIVERY) > 0) return false;
			return true;
		}

		return false;
	}

	int get_size() {
		int count = 0;
		count += (int)can_run_lsc();
		count += (int)can_run_bennys();
		return count;
	}

	void update_caches() {
		m_vars.m_cached_stats.m_success = false;
		scripts::get_vehicle_stats(menu::player::get_local_player().m_vehicle, &m_vars.m_cached_stats);
	}

	void cache_vehicle_stats() {
		if (!menu::player::get_local_player().m_in_vehicle) {
			return;
		}

		scripts::flag = 0;
		m_vars.m_global_stats[0] = m_vars.m_global_stats[1] = 0;
		m_vars.m_cached_stats.m_success = false;
		scripts::get_vehicle_stats(menu::player::get_local_player().m_vehicle, &m_vars.m_cached_stats);

		native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
		m_vars.m_cached_stats.m_armor = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARMOR);
		m_vars.m_cached_stats.m_brakes = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BRAKES);
		m_vars.m_cached_stats.m_front_bumper = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER);
		m_vars.m_cached_stats.m_rear_bumper = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER);
		m_vars.m_cached_stats.m_engine = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE);
		m_vars.m_cached_stats.m_exhaust = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_EXHAUST);
		m_vars.m_cached_stats.m_hood = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HOOD);
		m_vars.m_cached_stats.m_horn = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS);
		m_vars.m_cached_stats.m_skirts = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT);
		m_vars.m_cached_stats.m_suspension = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SUSPENSION);
		m_vars.m_cached_stats.m_transmission = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRANSMISSION);
		m_vars.m_cached_stats.m_spoiler = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPOILER);
		m_vars.m_cached_stats.m_grille = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_GRILLE);
		m_vars.m_cached_stats.m_left_fender = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FENDER);
		m_vars.m_cached_stats.m_right_fender = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER);
		m_vars.m_cached_stats.m_roof = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ROOF);
		m_vars.m_cached_stats.m_chassis = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_CHASSIS);
		m_vars.m_cached_stats.m_window_tint = native::get_vehicle_window_tint(menu::player::get_local_player().m_vehicle);
		m_vars.m_cached_stats.m_turbo = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_TURBO);
		m_vars.m_cached_stats.m_lights = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_XENONLIGHTS);
		m_vars.m_cached_stats.m_xenon_color = native::get_vehicle_xenon_lights_colour(menu::player::get_local_player().m_vehicle);
		m_vars.m_cached_stats.m_plate_index = native::get_vehicle_number_plate_text_index(menu::player::get_local_player().m_vehicle);

		// Bennys
		m_vars.m_cached_stats.m_bennys_plateholder = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_PLATEHOLDER);
		m_vars.m_cached_stats.m_bennys_vanity_plate = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_VANITY_PLATES);
		m_vars.m_cached_stats.m_bennys_trim_design = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRIM_DESIGN);
		m_vars.m_cached_stats.m_bennys_ornaments = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ORNAMENTS);
		m_vars.m_cached_stats.m_bennys_interior_design = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DASHBOARD);
		m_vars.m_cached_stats.m_bennys_dials = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DIAL);
		m_vars.m_cached_stats.m_bennys_doors = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DOOR_SPEAKER);
		m_vars.m_cached_stats.m_bennys_seats = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SEATS);
		m_vars.m_cached_stats.m_bennys_steering_wheel = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_STEERINGWHEEL);
		m_vars.m_cached_stats.m_bennys_shifter = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SHIFTER_LEAVERS);
		m_vars.m_cached_stats.m_bennys_plaques = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_PLAQUES);
		m_vars.m_cached_stats.m_bennys_trunk = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRUNK);
		m_vars.m_cached_stats.m_bennys_audio_install = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPEAKERS);
		m_vars.m_cached_stats.m_bennys_hydraulics = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HYDRULICS);
		m_vars.m_cached_stats.m_bennys_engine_block = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE_BLOCK);
		m_vars.m_cached_stats.m_bennys_air_filters = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_AIR_FILTER);
		m_vars.m_cached_stats.m_bennys_stunt_brace = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_STRUTS);
		m_vars.m_cached_stats.m_bennys_arch_covers = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARCH_COVER);
		m_vars.m_cached_stats.m_bennys_aerials = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_AERIALS);
		m_vars.m_cached_stats.m_bennys_rear_stripe_color = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRIM);
		m_vars.m_cached_stats.m_bennys_tank = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TANK);
		m_vars.m_cached_stats.m_bennys_window_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_WINDOWS);
		m_vars.m_cached_stats.m_bennys_livery = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_LIVERY);
		m_vars.m_cached_stats.m_bennys_special_front_rims = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPECIAL_FRONT_RIMS);
		m_vars.m_cached_stats.m_bennys_special_rear_rims = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPECIAL_REAR_RIMS);

		for (int i = 0; i < 4; i++) {
			m_vars.m_cached_stats.m_neon[i] = native::is_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, i);
		}

		native::get_vehicle_neon_lights_colour(menu::player::get_local_player().m_vehicle, &m_vars.m_cached_stats.m_neon_color.r, &m_vars.m_cached_stats.m_neon_color.g, &m_vars.m_cached_stats.m_neon_color.b);
	}

	std::string get_vehicle_mod_name(eVehicleModTypes type, std::string default) {
		if (native::does_text_label_exist(native::get_mod_slot_name(menu::player::get_local_player().m_vehicle, type))) {
			if (strcmp(native::get_label_text(native::get_mod_slot_name(menu::player::get_local_player().m_vehicle, type)), "NULL")) {
				return native::get_label_text(native::get_mod_slot_name(menu::player::get_local_player().m_vehicle, type));
			}
		}

		return default;
	}

	bool can_run_bennys_interior() {
		if (!menu::player::get_local_player().m_in_vehicle) {
			return false;
		}

		native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_DASHBOARD) > 0 
			|| native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_DIAL) > 0 
			|| native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_DOOR_SPEAKER) > 0 
			|| native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SEATS) > 0 
			|| native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_STEERINGWHEEL) > 0 
			|| native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ORNAMENTS) > 0 
			|| native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SHIFTER_LEAVERS) > 0 
			|| native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SPEAKERS) > 0) {
			return true;
		}

		return false;
	}
}

void vehicle_customs_menu::load() {
	set_name("Customs");
	set_parent<vehicle_menu>();

	add_option(scroll_option<int>(SCROLL, "Shop")
		.add_scroll(m_vars.m_type, 0, get_size(), shop)
		.add_update([](scroll_option<int>* option, int pos) { option->add_scroll(m_vars.m_type, 0, get_size(), shop); })
		.add_click([this] { update_once(); }));

	add_string("Armor");
	add_string("Brakes");
	add_string("Bumpers");
	add_string("Chassis");
	add_string("Engine");
	add_string("Exhaust");
	add_string("Fenders");
	add_string("Grille");
	add_string("Hood");
	add_string("Horn");
	add_string("Lights");
	add_string("Plate");
	add_string("Respray");
	add_string("Roof");
	add_string("Skirts");
	add_string("Spoiler");
	add_string("Suspension");
	add_string("Transmission");
	add_string("Turbo");
	add_string("Wheels");
	add_string("Windows");
	add_string("Interior");
	add_string("Aerials");
	add_string("Air Filters");
	add_string("Arch Covers");
	add_string("Engine Block");
	add_string("Hydraulics");
	add_string("Livery");
	add_string("Plaques");
	add_string("Plate Holder");
	add_string("Rear Stripe");
	add_string("Stunt Brace");
	add_string("Tank");
	add_string("Trim Design");
	add_string("Trunk");
	add_string("Vanity Plate");
	add_string("Window Mod");
}

void vehicle_customs_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}

	scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_menu::update_once() {
	if (m_vars.m_type == -1) m_vars.m_type = 0;

	if (m_vars.m_update_cache) {
		m_vars.m_update_cache = false;

		if (menu::player::get_local_player().m_in_vehicle) {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARMOR, m_vars.m_cached_stats.m_armor, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BRAKES, m_vars.m_cached_stats.m_brakes, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER, m_vars.m_cached_stats.m_front_bumper, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER, m_vars.m_cached_stats.m_rear_bumper, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE, m_vars.m_cached_stats.m_engine, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_EXHAUST, m_vars.m_cached_stats.m_exhaust, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HOOD, m_vars.m_cached_stats.m_hood, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS, m_vars.m_cached_stats.m_horn, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT, m_vars.m_cached_stats.m_skirts, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SUSPENSION, m_vars.m_cached_stats.m_suspension, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRANSMISSION, m_vars.m_cached_stats.m_transmission, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPOILER, m_vars.m_cached_stats.m_spoiler, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_GRILLE, m_vars.m_cached_stats.m_grille, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FENDER, m_vars.m_cached_stats.m_left_fender, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER, m_vars.m_cached_stats.m_right_fender, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ROOF, m_vars.m_cached_stats.m_roof, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_CHASSIS, m_vars.m_cached_stats.m_chassis, false);
			native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TURBO, (bool)m_vars.m_cached_stats.m_turbo);
			native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_XENONLIGHTS, (bool)m_vars.m_cached_stats.m_lights);
			native::set_vehicle_xenon_lights_colour(menu::player::get_local_player().m_vehicle, m_vars.m_cached_stats.m_xenon_color);
			native::set_vehicle_window_tint(menu::player::get_local_player().m_vehicle, m_vars.m_cached_stats.m_window_tint);
			native::set_vehicle_number_plate_text_index(menu::player::get_local_player().m_vehicle, m_vars.m_cached_stats.m_plate_index);

			native::set_vehicle_neon_lights_colour(menu::player::get_local_player().m_vehicle, m_vars.m_cached_stats.m_neon_color.r, m_vars.m_cached_stats.m_neon_color.g, m_vars.m_cached_stats.m_neon_color.b);
			
			for (int i = 0; i < 4; i++) {
				native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, i, m_vars.m_cached_stats.m_neon[i]);
			}

			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_PLATEHOLDER, m_vars.m_cached_stats.m_bennys_plateholder, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_VANITY_PLATES, m_vars.m_cached_stats.m_bennys_vanity_plate, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRIM_DESIGN, m_vars.m_cached_stats.m_bennys_trim_design, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_PLAQUES, m_vars.m_cached_stats.m_bennys_plaques, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRUNK, m_vars.m_cached_stats.m_bennys_trunk, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HYDRULICS, m_vars.m_cached_stats.m_bennys_hydraulics, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE_BLOCK, m_vars.m_cached_stats.m_bennys_engine_block, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_AIR_FILTER, m_vars.m_cached_stats.m_bennys_air_filters, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_STRUTS, m_vars.m_cached_stats.m_bennys_stunt_brace, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARCH_COVER, m_vars.m_cached_stats.m_bennys_arch_covers, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_AERIALS, m_vars.m_cached_stats.m_bennys_aerials, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRIM, m_vars.m_cached_stats.m_bennys_rear_stripe_color, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TANK, m_vars.m_cached_stats.m_bennys_tank, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_WINDOWS, m_vars.m_cached_stats.m_bennys_window_mod, false);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_LIVERY, m_vars.m_cached_stats.m_bennys_livery, false);
		}
	}

	cache_vehicle_stats();
	native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);

	clear_options(1);

	// LSC
	if (m_vars.m_type == 0) {
		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ARMOR)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_ARMOR, get_string("Armor")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_ARMOR;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_armor;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_BRAKES)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_BRAKES, get_string("Brakes")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_BRAKES;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_brakes;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER) || native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER)) {
			add_option(submenu_option(get_string("Bumpers"))
				.add_submenu<vehicle_customs_bumper_menu>()
				.add_click(cache_vehicle_stats));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_CHASSIS)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_CHASSIS, get_string("Chassis")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_CHASSIS;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_chassis;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ENGINE)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_ENGINE, get_string("Engine")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_ENGINE;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_engine;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_EXHAUST)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_EXHAUST, get_string("Exhaust")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_EXHAUST;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_exhaust;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FENDER) || native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER)) {
			add_option(submenu_option(get_string("Fenders"))
				.add_submenu<vehicle_customs_fender_menu>()
				.add_click(cache_vehicle_stats));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_GRILLE)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_GRILLE, get_string("Grille")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_GRILLE;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_grille;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_HOOD)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_HOOD, get_string("Hood")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_HOOD;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_hood;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_HORNS)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_HORNS, get_string("Horn")))
				.add_submenu<vehicle_customs_horn_menu>()
				.add_click([] {
					cache_vehicle_stats();
				}));
		}

		add_option(submenu_option(get_string("Lights"))
			.add_submenu<vehicle_customs_lights_menu>()
			.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_XENONLIGHTS;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_lights;
			}));

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_LIVERY)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_LIVERY, get_string("Livery")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_LIVERY;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_livery;
				}));
		}

		add_option(submenu_option(get_string("Plate"))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] { cache_vehicle_stats(); vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_PLATES; }));

		add_option(submenu_option(get_string("Respray"))
			.add_submenu<vehicle_customs_respray_menu>()
			.add_click(cache_vehicle_stats));

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ROOF)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_ROOF, get_string("Roof")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_ROOF;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_roof;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_SIDESKIRT, get_string("Skirts")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_SIDESKIRT;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_skirts;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SPOILER)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_SPOILER, get_string("Spoiler")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
					cache_vehicle_stats();
					vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_SPOILER;
					vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_spoiler;
				}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SUSPENSION)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_SUSPENSION, get_string("Suspension")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] { cache_vehicle_stats(); vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_SUSPENSION; }));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_TRANSMISSION)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_TRANSMISSION, get_string("Transmission")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] { cache_vehicle_stats(); vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_TRANSMISSION; }));
		}

		add_option(submenu_option(get_string("Turbo"))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_TURBO;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_turbo;
			}));

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS) || native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_BACKWHEELS)) {
			add_option(submenu_option(get_string("Wheels"))
				.add_submenu<vehicle_customs_wheels_menu>()
				.add_click(cache_vehicle_stats));

			if (m_vars.m_wheel_sport.empty()) {
				int cached = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 0);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_sport.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 1);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_muscle.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 2);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_lowrider.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 3);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_suv.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 4);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_offroad.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 5);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_tuner.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 6);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_bike.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 7);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_high_end.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 8);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_bennys.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 9);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_bespoke.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 10);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_open.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 11);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_street.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, 12);
				for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS); i++) {
					m_vars.m_wheel_track.push_back({ native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, i), i });
				}

				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, cached);
			}
		}

		if (native::is_this_model_a_car(native::get_entity_model(menu::player::get_local_player().m_vehicle))) {
			add_option(submenu_option(get_string("Windows"))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] { cache_vehicle_stats(); vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_WINDOWS_CUSTOM; }));
		}

		return;
	}

	// Bennys
	if (m_vars.m_type == 1) {
		add_option(submenu_option(get_string("Interior"))
			.add_submenu<vehicle_customs_interior_menu>()
			.add_requirement(can_run_bennys_interior));

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_AERIALS)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_AERIALS, get_string("Aerials")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_AERIALS;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_aerials;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_AIR_FILTER)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_AIR_FILTER, get_string("Air Filters")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_AIR_FILTER;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_air_filters;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ARCH_COVER)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_ARCH_COVER, get_string("Arch Covers")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_ARCH_COVER;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_arch_covers;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ENGINE_BLOCK)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_ENGINE_BLOCK, get_string("Engine Block")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_ENGINE_BLOCK;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_engine_block;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_HYDRULICS)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_HYDRULICS, get_string("Hydraulics")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_HYDRULICS;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_hydraulics;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_LIVERY)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_LIVERY, get_string("Livery")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_LIVERY;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_livery;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_PLAQUES)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_PLAQUES, get_string("Plaques")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_PLAQUES;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_plaques;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_PLATEHOLDER)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_PLATEHOLDER, get_string("Plate Holder")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_PLATEHOLDER;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_plateholder;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_TRIM)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_TRIM, get_string("Rear Stripe")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_TRIM;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_rear_stripe_color;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_STRUTS)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_STRUTS, get_string("Stunt Brace")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_STRUTS;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_stunt_brace;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_TANK)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_TANK, get_string("Tank")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_TANK;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_tank;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_TRIM_DESIGN)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_TRIM_DESIGN, get_string("Trim Design")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_TRIM_DESIGN;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_trim_design;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_TRUNK)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_TRUNK, get_string("Trunk")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_TRUNK;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_trunk;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_VANITY_PLATES)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_VANITY_PLATES, get_string("Vanity Plate")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_VANITY_PLATES;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_vanity_plate;
			}));
		}

		if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_WINDOWS)) {
			add_option(submenu_option(get_vehicle_mod_name(MOD_WINDOWS, get_string("Window Mod")))
				.add_submenu<vehicle_customs_lsc_menu>()
				.add_click([] {
				cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_WINDOWS;
				vehicle::customs::lsc::vars::m_vars.m_value = &m_vars.m_cached_stats.m_bennys_window_mod;
			}));
		}

		return;
	}
}

void vehicle_customs_menu::feature_update() {}

vehicle_customs_menu* g_instance;
vehicle_customs_menu* vehicle_customs_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}