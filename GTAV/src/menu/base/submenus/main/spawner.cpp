#include "spawner.h"
#include "menu/base/submenu_handler.h"
#include "../main.h"
#include "util/memory/memory.h"
#include "menu/base/util/control.h"
#include "menu/base/util/global.h"
#include "rage/engine.h"
#include "util/fiber_pool.h"
#include "global/lists.h"
#include "menu/base/submenus/main/vehicle.h"
#include "spawner/vehicle/spawner_vehicle_settings.h"
#include "spawner/vehicle/spawner_vehicle_selected.h"
#include "spawner/vehicle/spawner_vehicle_modded.h"
#include "spawner/vehicle/spawner_vehicle_garage.h"
#include "spawner/vehicle/spawner_vehicle_manage.h"
#include "spawner/object/spawner_object_settings.h"
#include "spawner/object/spawner_object_select.h"
#include "spawner/object/spawner_object_manage.h"
#include "spawner/object/spawner_object_building.h"
#include "spawner/ped/spawner_ped_settings.h"
#include "spawner/ped/spawner_ped_manage.h"
#include "menu/base/util/panels.h"
#include "menu/base/submenus/main/network/players/network_players_selected.h"
#include "menu/base/submenus/main/network/network_session.h"
#include "rage/types/global_types.h"
#include "spawner/vehicle/spawner_vehicle_save.h"

using namespace spawner::vars;

namespace spawner::vars {
	variables m_vars;

	scroll_struct<int> type[] = {
		{ localization("Vehicle", true), 0 },
		{ localization("Object", true), 0 },
		{ localization("Ped", true), 0 },
	};

	namespace script {
		// Freemode, search for "case joaat("TECHNICAL"):"
		bool func_1081(int iParam0) {
			return iParam0 == 49;
		}

		bool func_1080(int iParam0) {
			return iParam0 == 50;
		}

		int func_8789(int iParam0) {
			switch (iParam0) {
				case 0x3af76f4a:
					return 533;

				case 0x381e10bd:
					return 530;

				case 0xceb28249:
					return 531;

				case 0xed62bfa9:
					return 531;

				case 0x9dae1398:
					return 528;

				case 0x4662bcbb:
					return 534;

				case 0x50d4d19f:
					return 534;

				case 0x28ad20e1:
					return 529;

				case 0x8e08ec82:
					return 532;

				case 0xa1355f67:
					return 512;

				case 0x2189d250:
					return 558;

				case 0x34b82784:
					return 559;

				case 0xfe141da6:
					return 560;

				case 0x711d4738:
					return 561;

				case 0xb7d9f7f1:
					return 562;

				case 0x8fd54ebb:
					return 563;

				case 0xa52f6866:
					return 572;

				case 0xfe0a508c:
					return 573;

				case 0x89ba59f5:
					return 574;

				case 0xc3f25753:
					return 575;

				case 0xfd707ede:
					return 576;

				case 0x96e24857:
					return 577;

				case 0xd35698ef:
					return 578;

				case 0x5d56f01b:
					return 579;

				case 0x3dc92356:
					return 580;

				case 0xad6065c0:
					return 581;

				case 0xc5dd6967:
					return 582;

				case 0x9a9eb7de:
					return 583;

				case 0xe8983f9f:
					return 584;

				case 0x3e2e4f8a:
					return 585;

				case 0x19dd9ed1:
					if (func_1081(menu::script_global(4456448).at(133963).as<int>()) || func_1080(menu::script_global(4456448).at(133963).as<int>())) { // 1.55 done
						return 225;
					}
					break;

				case 0x83051506:
					if (func_1081(menu::script_global(4456448).at(133963).as<int>())) {// 1.55 done
						return 534;
					}
					break;

				case 0x34dba661:
					return 595;

				case 0x586765fb:
					return 596;

				case 0x58cdaf30:
					return 597;

				case 0xaa6f980a:
					return 598;

				case 0x9b16a3b4:
					return 599;

				case 0x1aad0ded:
					return 600;

				case 0xf34dfb25:
					return 601;

				case 0x46699f47:
					return 602;

				case 0xd6bc7523:
					return 603;

				case 0x81bd2ed0:
					return 589;

				case 0x64de07a1:
					return 640;

				case 0xd17099d:
					return 637;

				case 0x73f4110e:
					return 636;

				case 0x6290f15b:
					return 635;

				case 0x7b54a9d3:
					return 639;

				case 0xd4ae63d9:
					return 612;

				case 0x4abebf23:
					return 613;

				case 0x36a167e0:
					return 348;
			}
			return -1;
		}

		int func_8783(int iParam0) {
			switch (iParam0) {
				case 0x711d4738:
					return 0;

				case 0xfe141da6:
					return 1;

				case 0x8fd54ebb:
					return 2;

				case 0x2189d250:
					return 3;

				case 0xb7d9f7f1:
					return 4;

				case 0x34b82784:
					return 5;
			}

			return -1;
		}

		int func_8782(uint32_t iParam0) {
			switch (iParam0) { // good
				case 0x96e24857:
					return menu::script_global(rage::global::_155_tunables).at(22394).as<int>(); // 1.55 done

				case 0xc5dd6967:
					return menu::script_global(rage::global::_155_tunables).at(22395).as<int>();// 1.55 done

				case 0xa52f6866:
					return menu::script_global(rage::global::_155_tunables).at(22396).as<int>();// 1.55 done

				case 0x89ba59f5:
					return menu::script_global(rage::global::_155_tunables).at(22397).as<int>();// 1.55 done

				case 0x9a9eb7de:
					return menu::script_global(rage::global::_155_tunables).at(22398).as<int>();// 1.55 done

				case 0x5d56f01b:
					return menu::script_global(rage::global::_155_tunables).at(22399).as<int>();// 1.55 done

				case 0x3e2e4f8a:
					return menu::script_global(rage::global::_155_tunables).at(22400).as<int>();// 1.55 done

				case 0xfe0a508c:
					return menu::script_global(rage::global::_155_tunables).at(22401).as<int>();// 1.55 done

				case 0xc3f25753:
					return menu::script_global(rage::global::_155_tunables).at(22402).as<int>();// 1.55 done

				case 0xd35698ef:
					return menu::script_global(rage::global::_155_tunables).at(22403).as<int>();// 1.55 done

				case 0xad6065c0:
					return menu::script_global(rage::global::_155_tunables).at(22404).as<int>();// 1.55 done

				case 0xe8983f9f:
					return menu::script_global(rage::global::_155_tunables).at(22405).as<int>();// 1.55 done

				case 0x3dc92356:
					return menu::script_global(rage::global::_155_tunables).at(22406).as<int>();// 1.55 done

				case 0xfd707ede:
					return menu::script_global(rage::global::_155_tunables).at(22407).as<int>();// 1.55 done
			}

			return 0;
		}

		int func_8788(int iParam0) {
			switch (iParam0) {
				case 0x586765fb:
					return 0;
					break;

				case 0x46699f47:
					return 1;
					break;

				case 0x9b16a3b4:
					return 2;
					break;

				case 0x34dba661:
					return 3;
					break;

				case 0xd6bc7523:
					return 4;
					break;

				case 0xf34dfb25:
					return 5;
					break;

				case 0xaa6f980a:
					return 6;
					break;

				case 0x1aad0ded:
					return 7;
					break;

				case 0x58cdaf30:
					return 8;
					break;
			}
			return -1;
		}

		int func_8785(int iParam0) {
			if ((iParam0 == joaat("LAZER") || iParam0 == joaat("BESRA")) || iParam0 == joaat("HYDRA")) {
				return 1;
			}
			return 0;
		}

		int func_8787(int iParam0) {
			if ((((((((((iParam0 == joaat("TECHNICAL") || iParam0 == joaat("INSURGENT")) || iParam0 == joaat("INSURGENT2")) || iParam0 == joaat("LIMO2")) || iParam0 == joaat("TECHNICAL2")) || iParam0 == joaat("BOXVILLE5")) || iParam0 == joaat("INSURGENT3")) || iParam0 == joaat("TECHNICAL3")) || iParam0 == joaat("barrage")) || iParam0 == joaat("caracara")) || iParam0 == joaat("HALFTRACK")) {
				return 1;
			}
			return 0;
		}

		int func_1079(int iParam0, bool bParam1) {
			switch (iParam0) {
				case 0x3af76f4a:
				case 0x381e10bd:
				case 0xceb28249:
				case 0xed62bfa9:
				case 0x9dae1398:
				case 0x4662bcbb:
				case 0x28ad20e1:
				case 0x8e08ec82:
				case 0xa1355f67:
				case 0xd17099d:
				case 0x73f4110e:
				case 0x6290f15b:
				case 0x8fd54ebb:
					return 1;

				case 0x19dd9ed1:
					if (func_1081(menu::script_global(4456448).at(133963).as<int>()) || func_1080(menu::script_global(4456448).at(133963).as<int>())) {// 1.55 done
						if (!bParam1) {
							return 1;
						}
					}
					break;

				case 0x50d4d19f:
				case 0x83051506:
					if (func_1081(menu::script_global(4456448).at(133963).as<int>())) {// 1.55 done
						return 1;
					}
					break;
			}

			return 0;
		}

		int get_blip_sprite_for_vehicle(uint32_t iParam0) {
			if (func_1079(iParam0, 0)) {
				return func_8789(iParam0);
			}
			if (func_8783(iParam0) != -1) {
				return func_8789(iParam0);
			}
			if (func_8782(iParam0) > 0) {
				return func_8789(iParam0);
			}
			if (func_8788(iParam0) != -1) {
				return func_8789(iParam0);
			}
			if (iParam0 == joaat("avenger")) {
				return 589;
			}
			if (iParam0 == joaat("seasparrow")) {
				return 612;
			}
			if (iParam0 == joaat("blimp3")) {
				return 638;
			} else if (iParam0 == joaat("pbus2")) {
				return 631;
			} else if (iParam0 == joaat("terbyte")) {
				return 632;
			} else if (iParam0 == joaat("strikeforce")) {
				return 640;
			} else if (iParam0 == joaat("menacer")) {
				return 633;
			} else if (iParam0 == joaat("scramjet")) {
				return 634;
			} else if (iParam0 == joaat("oppressor2")) {
				return 639;
			}
			if ((iParam0 == joaat("bruiser") || iParam0 == joaat("bruiser2")) || iParam0 == joaat("bruiser3")) {
				return 658;
			} else if ((iParam0 == joaat("brutus") || iParam0 == joaat("brutus2")) || iParam0 == joaat("brutus3")) {
				return 659;
			} else if ((iParam0 == joaat("cerberus") || iParam0 == joaat("cerberus2")) || iParam0 == joaat("cerberus3")) {
				return 660;
			} else if ((iParam0 == joaat("deathbike") || iParam0 == joaat("deathbike2")) || iParam0 == joaat("deathbike3")) {
				return 661;
			} else if ((iParam0 == joaat("dominator4") || iParam0 == joaat("dominator5")) || iParam0 == joaat("dominator6")) {
				return 662;
			} else if ((iParam0 == joaat("impaler2") || iParam0 == joaat("impaler3")) || iParam0 == joaat("impaler4")) {
				return 663;
			} else if ((iParam0 == joaat("imperator") || iParam0 == joaat("imperator2")) || iParam0 == joaat("imperator3")) {
				return 664;
			} else if ((iParam0 == joaat("issi4") || iParam0 == joaat("issi5")) || iParam0 == joaat("issi6")) {
				return 665;
			} else if ((iParam0 == joaat("monster3") || iParam0 == joaat("monster4")) || iParam0 == joaat("monster5")) {
				return 666;
			} else if ((iParam0 == joaat("scarab") || iParam0 == joaat("scarab2")) || iParam0 == joaat("scarab3")) {
				return 667;
			} else if ((iParam0 == joaat("slamvan4") || iParam0 == joaat("slamvan5")) || iParam0 == joaat("slamvan6")) {
				return 668;
			} else if ((iParam0 == joaat("zr380") || iParam0 == joaat("zr3802")) || iParam0 == joaat("zr3803")) {
				return 669;
			} else if (iParam0 == joaat("rrocket")) {
				return 226;
			}
			if (native::is_this_model_a_bike(iParam0)) {
				return 226;
			} else if (native::is_this_model_a_heli(iParam0)) {
				return 64;
			} else if (native::is_this_model_a_boat(iParam0)) {
				return 410;
			} else if (func_8785(iParam0)) {
				return 424;
			} else if (native::is_this_model_a_plane(iParam0)) {
				return 423;
			} else if (native::is_this_model_a_quadbike(iParam0)) {
				return 512;
			} else if (iParam0 == joaat("RHINO")) {
				return 421;
			} else if (iParam0 == joaat("submersible") || iParam0 == joaat("submersible2")) {
				return 308;
			} else if (func_8787(iParam0)) {
				return 426;
			} else {
				return 225;
			}
			return 225;
		}
	}

	void populate_vehicle_list() {
		util::fiber::pool::add([] {
			struct hash_node {
				uint32_t m_model_hash;
				uint16_t m_data;
				uint16_t m_padding;
				hash_node* m_next;
			};

			for (std::vector<uint32_t>& hashes : m_vars.m_vehicle_hashes) {
				hashes.clear();
			}

			uint16_t hash_table_count = *(uint16_t*)memory::read_instruction(global::vars::g_get_model_info);
			uint64_t hash_table = *(uint64_t*)memory::read_instruction(global::vars::g_get_model_info + 0x7E);
			hash_node** hash_map = *(hash_node***)memory::read_instruction(global::vars::g_get_model_info + 0x21);

			for (uint16_t i = 0; i < hash_table_count; i++) {
				for (hash_node* current = hash_map[i]; current; current = current->m_next) {
					uint64_t element = *(uint64_t*)(hash_table + (current->m_data * 8));
					if (element) {
						uint8_t ModelType = *(uint8_t*)(element + 0x9D) & 0x1F;
						if (ModelType == 5) {
							if (current->m_model_hash) {
								uint8_t type = *(uint8_t*)(element + 0x548) & 0x1F;
								m_vars.m_vehicle_hashes[type].push_back(current->m_model_hash);
							}
						}
					}
				}
			}
		});
	}

	const char* get_class_name(int class_id) {
		char buffer[32];
		sprintf_s(buffer, "VEH_CLASS_%d", class_id);
		return !strcmp(native::get_label_text(buffer), "NULL") ? "" : native::get_label_text(buffer);
	}

	void do_spawn_vehicle(uint32_t model, std::function<void(Entity)> callback, bool garage, Player player_id) {
		if (native::is_model_in_cdimage(model) && native::is_model_a_vehicle(model)) {
			util::fiber::pool::add([=] {
				menu::control::simple_request_model(model);

				menu::player::player_context& target = menu::player::get_player(player_id);

				bool network = target.m_id != menu::player::get_local_player().m_id;
				bool spawn_vectored = false;
				float old_speed = 0.f;

				if (spawner::vehicle::settings::vars::m_vars.m_delete_current
					&& !network) {
					if (target.m_in_vehicle) {
						if (native::get_ped_in_vehicle_seat(target.m_vehicle, -1, 0) == target.m_ped) {
							old_speed = native::get_entity_speed(target.m_vehicle);
							native::set_entity_as_mission_entity(target.m_vehicle, true, true);
							native::delete_entity(&target.m_vehicle);
						} else {
							spawn_vectored = true;
						}
					}
				}

				math::vector3<float> coords;

				Entity vehicle = 0;
				if (!network && spawner::vehicle::settings::vars::m_vars.m_teleport_inside && !spawn_vectored) {
					vehicle = native::create_vehicle(model, target.m_coords.x, target.m_coords.y, target.m_coords.z, target.m_heading, true, false, false);
					coords = target.m_coords;
				} else {
					coords = target.m_coords + (native::get_entity_forward_vector(target.m_entity) * 5.f);
					vehicle = native::create_vehicle(model, coords.x, coords.y, coords.z, target.m_heading, true, false, false);
				}

				if (native::does_entity_exist(vehicle)) {
					native::set_entity_as_mission_entity(vehicle, true, true);
					native::set_vehicle_on_ground_properly(vehicle, 1);

					native::set_vehicle_dirt_level(vehicle, 0);
					native::set_vehicle_radio_station(vehicle, "OFF");

					if (spawner::vehicle::settings::vars::m_vars.m_air_vehicles_in_air) {
						if (native::is_this_model_a_plane(model) || native::is_this_model_a_heli(model)) {
							math::vector3<float> coords = native::get_entity_coords(vehicle, true);
							native::set_entity_coords(vehicle, coords.x, coords.y, coords.z + spawner::vehicle::settings::vars::m_vars.m_spawn_height, 0, 0, 0, 0);
							native::set_vehicle_engine_on(vehicle, true, true, false);
							native::set_heli_blades_full_speed(vehicle);
							native::set_vehicle_forward_speed(vehicle, 100);
						}
					}

					if (spawner::vehicle::settings::vars::m_vars.m_fade) {
						native::network_fade_in_entity(vehicle, true, false);
					}

					if (spawner::vehicle::settings::vars::m_vars.m_blip) {
						Blip blip = native::add_blip_for_entity(vehicle);
						native::set_blip_sprite(blip, script::get_blip_sprite_for_vehicle(model));
						native::set_blip_display(blip, 8);
						native::set_blip_category(blip, 4);
					}

					native::decor_set_int(vehicle, "MPBitset", 0);
					native::set_vehicle_is_stolen(vehicle, false);

					if (network) {
						if (target.m_gift_vehicle || spawner::vehicle::settings::vars::m_vars.m_session_gift) {
							uint32_t player_hash = native::network_hash_from_player_handle(target.m_id);
							native::decor_set_int(vehicle, "Player_Vehicle", player_hash);
							native::decor_set_int(vehicle, "Previous_Owner", player_hash);
							native::decor_set_int(vehicle, "Veh_Modded_By_Player", player_hash);
							native::decor_set_int(vehicle, "Not_Allow_As_Saved_Veh", 0);
							native::decor_set_int(vehicle, "PV_Slot", 2);
						}
					}

					if (spawner::vehicle::settings::vars::m_vars.m_teleport_inside && !network) {
						native::set_ped_into_vehicle(target.m_ped, vehicle, -1);
						native::set_vehicle_engine_on(vehicle, true, true, false);
						native::set_vehicle_forward_speed(vehicle, old_speed);
					}

					if (spawner::vehicle::settings::vars::m_vars.m_godmode) {
						native::set_entity_invincible(vehicle, true);
						native::set_entity_proofs(vehicle, true, true, true, true, true, true, true, true);
						native::set_vehicle_can_be_visibly_damaged(vehicle, false);
						native::set_vehicle_engine_on(vehicle, true, true, true);
					}

					if (spawner::vehicle::settings::vars::m_vars.m_particle_fx) {
						menu::control::request_particle({ "proj_indep_firework_v2", "scr_firework_indep_repeat_burst_rwb" }, [=] (std::pair<const char*, const char*> asset) {
							native::start_particle_fx_non_looped_at_coord2("scr_firework_indep_repeat_burst_rwb", coords.x, coords.y, coords.z, 0, 0, 0, 1.2f, true, true, true);
						});
					}

					if (spawner::vehicle::settings::vars::m_vars.m_upgrades && !garage) {
						::vehicle::vars::max_upgrades(vehicle, spawner::vehicle::settings::vars::m_vars.m_upgrades_var);
					}

					if (spawner::vehicle::settings::vars::m_vars.m_notification) {
						menu::notify::stacked("Spawner", util::va::va("%s %s!", native::get_label_text(native::get_display_name_from_vehicle_model(model)), spawner_menu::get()->get_string("spawned").c_str()));
					}

					callback(vehicle);
					vehicle::manage::vars::m_vars.m_vehicles.push_back({ vehicle, model, native::get_game_timer() });
				}
			});
		}
	}

	void spawn_vehicle(uint32_t model, std::function<void(Entity)> callback, bool garage) {
		switch (m_vars.m_flag) {
			case SPAWNER_SELF:
				do_spawn_vehicle(model, callback, garage, menu::player::get_local_player().m_id);
				break;

			case SPAWNER_PLAYER:
				do_spawn_vehicle(model, callback, garage, menu::player::get_selected_player().m_id);
				break;

			case SPAWNER_SESSION:
				menu::player::for_each([=] (menu::player::player_context& player) {
					do_spawn_vehicle(model, callback, garage, player.m_id);
				});

				break;
		}
	}

	void do_spawn_object(uint32_t model, std::string esp_name, std::function<void(Entity)> callback, Player player_id) {
		if (native::is_model_in_cdimage(model)) {
			util::fiber::pool::add([=] {
				menu::control::simple_request_model(model);

				menu::player::player_context& target = menu::player::get_player(player_id);

				bool network = target.m_id != menu::player::get_local_player().m_id;
				math::vector3<float> coords = target.m_coords;
				Entity object = 0;

				if (!network) {
					object = native::create_object(model, target.m_coords.x, target.m_coords.y, target.m_coords.z, true, true, false);
				} else {
					coords = target.m_coords + (native::get_entity_forward_vector(target.m_entity) * 5.f);
					object = native::create_object(model, coords.x, coords.y, coords.z, true, true, false);
				}

				if (native::does_entity_exist(object)) {
					std::string name = "";
					if (esp_name.empty()) {
						name = util::va::va("%X", model);
					} else name = esp_name;

					if (spawner::object::settings::vars::m_vars.m_fade) {
						native::network_fade_in_entity(object, true, false);
					}

					if (spawner::object::settings::vars::m_vars.m_blip) {
						Blip blip = native::add_blip_for_entity(object);
						native::set_blip_sprite(blip, 408);
						native::set_blip_colour(blip, 17);
						native::set_blip_display(blip, 8);
						native::set_blip_category(blip, 4);
					}

					if (spawner::object::settings::vars::m_vars.m_particle_fx) {
						menu::control::request_particle({ "proj_indep_firework_v2", "scr_firework_indep_repeat_burst_rwb" }, [=] (std::pair<const char*, const char*> asset) {
							native::start_particle_fx_non_looped_at_coord2("scr_firework_indep_repeat_burst_rwb", coords.x, coords.y, coords.z, 0, 0, 0, 1.2f, true, true, true);
						});
					}

					if (spawner::object::settings::vars::m_vars.m_notification) {
						menu::notify::stacked("Spawner", util::va::va("%s %s!", name.c_str(), spawner_menu::get()->get_string("spawned").c_str()));
					}

					callback(object);
					spawner::object::manage::vars::m_vars.m_objects.push_back({ object, model, name, native::get_game_timer() });
				}
			});
		}
	}

	void spawn_object(uint32_t model, std::string esp_name, std::function<void(Entity)> callback) {
		switch (m_vars.m_flag) {
			case SPAWNER_SELF:
				do_spawn_object(model, esp_name, callback, menu::player::get_local_player().m_id);
				break;

			case SPAWNER_PLAYER:
				do_spawn_object(model, esp_name, callback, menu::player::get_selected_player().m_id);
				break;

			case SPAWNER_SESSION:
				menu::player::for_each([=] (menu::player::player_context& player) {
					do_spawn_object(model, esp_name, callback, player.m_id);
				});

				break;
		}
	}

	void do_spawn_ped(uint32_t model, std::string esp_name, std::function<void(Entity)> callback, Player player_id) {
		if (native::is_model_in_cdimage(model)) {
			util::fiber::pool::add([=] {
				menu::control::simple_request_model(model);

				menu::player::player_context& target = menu::player::get_player(player_id);

				bool network = target.m_id != menu::player::get_local_player().m_id;
				math::vector3<float> coords = target.m_coords;
				Entity ped = 0;

				if (!network) {
					ped = native::create_ped(21, model, target.m_coords.x, target.m_coords.y, target.m_coords.z, 0.f, true, false);
				} else {
					coords = target.m_coords + (native::get_entity_forward_vector(target.m_entity) * 5.f);
					ped = native::create_ped(21, model, coords.x, coords.y, coords.z, 0.f, true, false);
				}

				if (native::does_entity_exist(ped)) {
					std::string name = "";
					if (esp_name.empty()) {
						name = std::string(util::va::va("%X", model));
					} else name = esp_name;

					if (spawner::ped::settings::vars::m_vars.m_fade) {
						native::network_fade_in_entity(ped, true, false);
					}

					if (spawner::ped::settings::vars::m_vars.m_blip) {
						Blip blip = native::add_blip_for_entity(ped);
						native::set_blip_sprite(blip, 408);
						native::set_blip_colour(blip, 17);
						native::set_blip_display(blip, 8);
						native::set_blip_category(blip, 4);
					}

					if (spawner::ped::settings::vars::m_vars.m_particle_fx) {
						menu::control::request_particle({ "proj_indep_firework_v2", "scr_firework_indep_repeat_burst_rwb" }, [=] (std::pair<const char*, const char*> asset) {
							native::start_particle_fx_non_looped_at_coord2("scr_firework_indep_repeat_burst_rwb", coords.x, coords.y, coords.z, 0, 0, 0, 1.2f, true, true, true);
						});
					}

					if (spawner::ped::settings::vars::m_vars.m_notification) {
						menu::notify::stacked("Spawner", util::va::va("%s %s!", name.c_str(), spawner_menu::get()->get_string("spawned").c_str()));
					}

					callback(ped);
					spawner::ped::manage::vars::m_vars.m_peds.push_back({ ped, model, name, native::get_game_timer() });
				}
			});
		}
	}

	void spawn_ped(uint32_t model, std::string esp_name, std::function<void(Entity)> callback) {
		switch (m_vars.m_flag) {
			case SPAWNER_SELF:
				do_spawn_ped(model, esp_name, callback, menu::player::get_local_player().m_id);
				break;

			case SPAWNER_PLAYER:
				do_spawn_ped(model, esp_name, callback, menu::player::get_selected_player().m_id);
				break;

			case SPAWNER_SESSION:
				menu::player::for_each([=] (menu::player::player_context& player) {
					do_spawn_ped(model, esp_name, callback, player.m_id);
				});

				break;
		}
	}
}

void spawner_menu::load() {
	set_name("Spawner");
	set_parent<main_menu>();

	add_option(scroll_option<int>(SCROLL, "Spawn Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(type), type)
		.add_click([this] { update_once(); }));

	for (int i = 0; i < 23; i++) {
		add_string(get_class_name(i));
	}

	add_string("Input the model! (Hint: name, hash or numeric)");
	add_string("Spawn Settings");
	add_string("Manage Spawned Vehicles");
	add_string("Manage Spawned Objects");
	add_string("Input Custom Vehicle");
	add_string("Input Custom Object");
	add_string("Modded Vehicles");
	add_string("Garage Vehicles");
	add_string("Categories");
	add_string("spawned");
	add_string("Small");
	add_string("Medium");
	add_string("Large");
	add_string("Save and Load");

	populate_vehicle_list();

	spawner_vehicle_selected_menu::get();
	spawner_vehicle_settings_menu::get();
	spawner_vehicle_manage_menu::get();
	spawner_vehicle_modded_menu::get();
	spawner_vehicle_garage_menu::get();

	spawner_object_settings_menu::get();
	spawner_object_manage_menu::get();
	spawner_object_building_menu::get();
	spawner_object_select_menu::get();

	spawner_ped_settings_menu::get();
	spawner_ped_manage_menu::get();
}

void spawner_menu::update() {}

void spawner_menu::update_once() {
	clear_options(1);

	switch (m_vars.m_flag) {
		case SPAWNER_SELF:
			set_parent<main_menu>();
			break;

		case SPAWNER_PLAYER:
			set_parent<network_players_selected_menu>();
			break;

		case SPAWNER_SESSION:
			set_parent<network_session_menu>();
			break;
	}

	menu::panels::toggle_panel_render("PANEL_VEHICLE_PREVIEW", false);

	// Vehicle
	if (m_vars.m_type == 0) {
		add_option(submenu_option(get_string("Spawn Settings"))
			.add_submenu<spawner_vehicle_settings_menu>());

		add_option(submenu_option(get_string("Save and Load"))
			.add_submenu<spawner_vehicle_save_menu>());

		add_option(submenu_option(get_string("Manage Spawned Vehicles"))
			.add_submenu<spawner_vehicle_manage_menu>()
			.add_requirement([] { return m_vars.m_flag == SPAWNER_SELF; }));

		add_option(submenu_option(get_string("Modded Vehicles"))
			.add_submenu<spawner_vehicle_modded_menu>()
			.add_requirement([] { return m_vars.m_flag == SPAWNER_SELF; }));

		add_option(submenu_option(get_string("Garage Vehicles"))
			.add_submenu<spawner_vehicle_garage_menu>());

		add_option(button_option(get_string("Input Custom Vehicle"))
			.add_keyboard(get_string("Input the model! (Hint: name, hash or numeric)"), 30, [](button_option* option, const char* text) {
				if (text) {
					if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
						// hash
						spawn_vehicle((uint32_t)_strtoui64(text, 0, 0));
					} else {
						std::string str_name(text);
						if (std::find_if(str_name.begin(), str_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == str_name.end()) {
							// numeric
							spawn_vehicle((uint32_t)atoi(text));
						} else {
							// name
							spawn_vehicle(native::get_hash_key(text));
						}
					}
				}
			}));

		add_option(break_option(get_string("Categories")));

		for (int i = 0; i < 23; i++) {
			add_option(submenu_option(get_string(get_class_name(i)))
				.add_submenu<spawner_vehicle_selected_menu>()
				.add_click([=] { spawner::vehicle::selected::vars::m_vars.m_selected = i; }));
		}

		return;
	}

	// Object
	if (m_vars.m_type == 1) {
		add_option(submenu_option(get_string("Spawn Settings"))
			.add_submenu<spawner_object_settings_menu>());

		add_option(submenu_option(get_string("Manage Spawned Objects"))
			.add_submenu<spawner_object_manage_menu>()
			.add_requirement([] { return m_vars.m_flag == SPAWNER_SELF; }));

		add_option(submenu_option(get_string("Buildings"))
			.add_submenu<spawner_object_building_menu>());

		add_option(button_option(get_string("Input Custom Object"))
			.add_keyboard(get_string("Input the model! (Hint: name, hash or numeric)"), 30, [](button_option* option, const char* text) {
				if (text) {
					if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
						// hash
						spawn_object((uint32_t)_strtoui64(text, 0, 0), text);
					} else {
						std::string str_name(text);
						if (std::find_if(str_name.begin(), str_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == str_name.end()) {
							// numeric
							spawn_object((uint32_t)atoi(text), text);
						} else {
							// name
							spawn_object(native::get_hash_key(text), text);
						}
					}
				}
			}));

		add_option(break_option(get_string("Categories")));

		add_option(submenu_option(get_string("Small"))
			.add_submenu<spawner_object_select_menu>()
			.add_click([] {
				spawner::object::select::vars::m_vars.m_list = global::lists::g_object_model_small;
				spawner::object::select::vars::m_vars.m_size = NUMOF(global::lists::g_object_model_small);
			}));

		add_option(submenu_option(get_string("Medium"))
			.add_submenu<spawner_object_select_menu>()
			.add_click([] {
				spawner::object::select::vars::m_vars.m_list = global::lists::g_object_model_medium;
				spawner::object::select::vars::m_vars.m_size = NUMOF(global::lists::g_object_model_medium);
			}));

		add_option(submenu_option(get_string("Large"))
			.add_submenu<spawner_object_select_menu>()
			.add_click([] {
				spawner::object::select::vars::m_vars.m_list = global::lists::g_object_model_large;
				spawner::object::select::vars::m_vars.m_size = NUMOF(global::lists::g_object_model_large);
			}));

		add_option(submenu_option(get_string("Flags"))
			.add_submenu<spawner_object_select_menu>()
			.add_click([] {
				spawner::object::select::vars::m_vars.m_list = global::lists::g_object_model_flags;
				spawner::object::select::vars::m_vars.m_size = NUMOF(global::lists::g_object_model_flags);
			}));

		return;
	}

	// Ped
	if (m_vars.m_type == 2) {
		add_option(submenu_option(get_string("Spawn Settings"))
			.add_submenu<spawner_ped_settings_menu>());

		add_option(submenu_option(get_string("Manage Spawned Peds"))
			.add_submenu<spawner_ped_manage_menu>()
			.add_requirement([] { return m_vars.m_flag == SPAWNER_SELF; }));

		add_option(button_option(get_string("Input Custom Ped"))
			.add_keyboard(get_string("Input the model! (Hint: name, hash or numeric)"), 30, [](button_option* option, const char* text) {
			if (text) {
				if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
					// hash
					spawn_ped((uint32_t)_strtoui64(text, 0, 0), text);
				} else {
					std::string str_name(text);
					if (std::find_if(str_name.begin(), str_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == str_name.end()) {
						// numeric
						spawn_ped((uint32_t)atoi(text), text);
					} else {
						// name
						spawn_ped(native::get_hash_key(text), text);
					}
				}
			}
		}));

		add_option(break_option(get_string("Categories")));

		add_option(scroll_option<uint32_t>(SCROLLSELECT, "Popular")
			.add_translate()
			.add_scroll(m_vars.m_popular, 0, NUMOF(global::lists::g_ped_model_popular), global::lists::g_ped_model_popular).loop()
			.add_click([] { spawn_ped(global::lists::g_ped_model_popular[m_vars.m_popular].m_result, global::lists::g_ped_model_popular[m_vars.m_popular].m_name.get()); }));

		add_option(scroll_option<uint32_t>(SCROLLSELECT, "Story")
			.add_translate()
			.add_scroll(m_vars.m_story, 0, NUMOF(global::lists::g_ped_model_story), global::lists::g_ped_model_story).loop()
			.add_click([] { spawn_ped(global::lists::g_ped_model_story[m_vars.m_story].m_result, global::lists::g_ped_model_story[m_vars.m_story].m_name.get()); }));

		add_option(scroll_option<uint32_t>(SCROLLSELECT, "Animals")
			.add_translate()
			.add_scroll(m_vars.m_animals, 0, NUMOF(global::lists::g_ped_model_animal), global::lists::g_ped_model_animal).loop()
			.add_click([] { spawn_ped(global::lists::g_ped_model_animal[m_vars.m_animals].m_result, global::lists::g_ped_model_animal[m_vars.m_animals].m_name.get()); }));

		add_option(scroll_option<uint32_t>(SCROLLSELECT, "Emergency")
			.add_translate()
			.add_scroll(m_vars.m_emergency, 0, NUMOF(global::lists::g_ped_model_emergency), global::lists::g_ped_model_emergency).loop()
			.add_click([] { spawn_ped(global::lists::g_ped_model_emergency[m_vars.m_emergency].m_result, global::lists::g_ped_model_emergency[m_vars.m_emergency].m_name.get()); }));

		add_option(scroll_option<uint32_t>(SCROLLSELECT, "Role")
			.add_translate()
			.add_scroll(m_vars.m_role, 0, NUMOF(global::lists::g_ped_model_role), global::lists::g_ped_model_role).loop()
			.add_click([] { spawn_ped(global::lists::g_ped_model_role[m_vars.m_role].m_result, global::lists::g_ped_model_role[m_vars.m_role].m_name.get()); }));

		add_option(scroll_option<uint32_t>(SCROLLSELECT, "Ambient")
			.add_translate()
			.add_scroll(m_vars.m_ambient, 0, NUMOF(global::lists::g_ped_model_ambient), global::lists::g_ped_model_ambient).loop()
			.add_click([] { spawn_ped(global::lists::g_ped_model_ambient[m_vars.m_ambient].m_result, global::lists::g_ped_model_ambient[m_vars.m_ambient].m_name.get()); }));

		add_option(scroll_option<uint32_t>(SCROLLSELECT, "Misc")
			.add_translate()
			.add_scroll(m_vars.m_misc, 0, NUMOF(global::lists::g_ped_model_misc), global::lists::g_ped_model_misc).loop()
			.add_click([] { spawn_ped(global::lists::g_ped_model_misc[m_vars.m_misc].m_result, global::lists::g_ped_model_misc[m_vars.m_misc].m_name.get()); }));
	}
}

void spawner_menu::feature_update() {}

spawner_menu* g_instance;
spawner_menu* spawner_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}