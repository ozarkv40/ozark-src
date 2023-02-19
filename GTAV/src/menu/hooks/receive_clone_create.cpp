#include "hooks.h"
#include "rage/engine.h"
#include "menu/base/util/notify.h"
#include "util/log.h"
#include "menu/base/util/helpers.h"
#include "rage/invoker/natives.h"
#include "util/caller.h"
#include "util/fiber_pool.h"
#include "menu/base/util/notify.h"
#include "menu/base/util/control.h"
#include "global/lists.h"
#include "menu/base/submenus/main/spawner/object/spawner_object_manage.h"
#include "menu/base/submenus/main/spawner/ped/spawner_ped_manage.h"
#include "menu/base/submenus/main/spawner/vehicle/spawner_vehicle_manage.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/protections.h"
#include "menu/base/submenus/main/protection/protection_entity_events.h"
#include "menu/base/submenus/main/protection/limits/protection_spawn_rate_limit.h"
#include "menu/base/submenus/main/protection/entity/protection_entity_blocking.h"
#include "menu/base/submenus/main/protection/entity/protection_entity_ghosting.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"

struct create_cache_type {
	uint32_t m_last_spawn = 0;
	bool m_sus_last_spawn = false;
	int m_sus_count = 0;
};

struct create_cache {
	std::unordered_map<eNetObjectTypes, create_cache_type> m_cache;
};

static std::unordered_map<Player, create_cache> g_create_cache;

bool menu::hooks::receive_clone_create(uint64_t _this, rage::network::net_game_player* sender, uint64_t r8, eNetObjectTypes type, uint16_t network_id, uint16_t flag, rage::bit_buffer* bit_buffer, uint32_t timestamp) {
	if (menu::helpers::is_valid_net_player(sender) && sender->m_id != -1) {
		if (sender->m_id < 0 || sender->m_id >= 32) {
			LOG_DEV("RCC FAILED - 1");
			return false;
		}

		if (menu::player::get_player(sender->m_id).m_blacklist > GetTickCount()) {
			LOG_DEV("RCC FAILED - 2");
			return false;
		}

		if (protection::entity::vars::m_vars.m_block_modder_create) {
			if (menu::player::get_player(sender->m_id).m_is_modder) {
				LOG_DEV("RCC FAILED - 3");
				return false;
			}
		}

		if (menu::player::get_player(sender->m_id).m_ghost[type]
			|| protection::entity::ghosting::vars::m_vars.m_ghosts[type].m_enabled_for_session) {
			LOG_DEV("RCC FAILED - 4");
			return false;
		}

		if (menu::player::get_player(sender->m_id).m_block_entities[0][type]) {
			LOG_DEV("RCC FAILED - 5");
			return false;
		}
	} else return receive_clone_create_t(_this, sender, r8, type, network_id, flag, bit_buffer, timestamp);

	rage::network::sync_tree* tree = rage::engine::get_sync_tree(type);
	if (!tree) {
		if (protection::events::vars::m_vars.m_crashing.notify()) {
			if (menu::helpers::is_valid_net_player(sender)) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_tree), false, true);
			}
		}

		menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
		protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
		LOG_DEV("RCC FAILED - 6");
		return false;
	}

	if (tree->m_data_node_count <= 0 || tree->m_data_node_count > 100) {
		if (protection::events::vars::m_vars.m_crashing.notify()) {
			if (menu::helpers::is_valid_net_player(sender)) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_bad_node_count), false, true);
			}
		}

		menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
		protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
		LOG_DEV("RCC FAILED - 8");
		return false;
	}

	if (protection::events::vars::m_vars.m_entity_owner_migration.enabled()) {
		rage::network::net_object* object = rage::engine::get_network_object_from_network_id(_this, network_id, false);
		if (object) {
			if (object->m_owner == menu::player::get_local_player().m_id) {
				if (object->m_entity) {
					Entity handle = rage::engine::get_entity_handle(object->m_entity);
					if (handle) {
						bool notified = false;

						if (menu::player::get_local_player().m_in_vehicle) {
							if (handle == menu::player::get_local_player().m_vehicle) {
								if (protection::events::vars::m_vars.m_entity_owner_migration.notify()) {
									notified = true;

									if (menu::helpers::is_valid_net_player(sender)) {
										menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_vehicle_owner_migration), false, protection::events::vars::m_vars.m_entity_owner_migration.block());
									}
								}

								if (protection::events::vars::m_vars.m_entity_owner_migration.block()) {
									LOG_DEV("RCC FAILED - 9");
									return false;
								}
							}
						}

						if (!notified) {
							if (!spawner::vehicle::manage::vars::m_vars.m_vehicles.empty()) {
								for (spawner::vehicle::manage::vars::spawned_vehicle& veh : spawner::vehicle::manage::vars::m_vars.m_vehicles) {
									if (veh.m_handle == handle) {
										if (protection::events::vars::m_vars.m_entity_owner_migration.notify()) {
											if (menu::helpers::is_valid_net_player(sender)) {
												menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_vehicle_owner_migration), false, protection::events::vars::m_vars.m_entity_owner_migration.block());
											}
										}

										if (protection::events::vars::m_vars.m_entity_owner_migration.block()) {
											LOG_DEV("RCC FAILED - 10");
											return false;
										}
									}
								}
							}
						}

						if (!spawner::object::manage::vars::m_vars.m_objects.empty()) {
							for (spawner::object::manage::vars::spawned_object& object : spawner::object::manage::vars::m_vars.m_objects) {
								if (object.m_handle == handle) {
									if (protection::events::vars::m_vars.m_entity_owner_migration.notify()) {
										if (menu::helpers::is_valid_net_player(sender)) {
											menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_object_owner_migration), false, protection::events::vars::m_vars.m_entity_owner_migration.block());
										}
									}

									if (protection::events::vars::m_vars.m_entity_owner_migration.block()) {
										LOG_DEV("RCC FAILED - 11");
										return false;
									}
								}
							}
						}

						if (!spawner::ped::manage::vars::m_vars.m_peds.empty()) {
							for (spawner::ped::manage::vars::spawned_ped& ped : spawner::ped::manage::vars::m_vars.m_peds) {
								if (ped.m_handle == handle) {
									if (protection::events::vars::m_vars.m_entity_owner_migration.notify()) {
										if (menu::helpers::is_valid_net_player(sender)) {
											menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_ped_owner_migration), false, protection::events::vars::m_vars.m_entity_owner_migration.block());
										}
									}

									if (protection::events::vars::m_vars.m_entity_owner_migration.block()) {
										LOG_DEV("RCC FAILED - 12");
										return false;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	uint32_t model_hash = 0;
	uint64_t creation_data = 0;
	if (!menu::helpers::get_node_creation(tree->m_parent_node, bit_buffer, &model_hash, &creation_data)) {
		if (menu::helpers::is_valid_net_player(sender)) {
			LOG("Preventing %s creating, failed getting creation hash (%i)", sender->m_player_info->m_name, type);
		}

		LOG_DEV("RCC FAILED - 13");
		return false;
	}

	if (menu::helpers::is_crash_model(model_hash, type)) {
		if (protection::events::vars::m_vars.m_crashing.notify()) {
			if (menu::helpers::is_valid_net_player(sender)) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_bad_model), false, true);
			}
		}

		menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT);
		protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
		LOG_DEV("RCC FAILED - 14");
		return false;
	}

	uint64_t model_info = rage::engine::get_model_info(model_hash);
	if (model_info) {
		int model_type = (int)(*(uint8_t*)(model_info + 0x9D) & 0x1F); // same
		int vehicle_type = *(int*)(model_info + 0x340);// same

		static std::unordered_map<int, uint16_t> type_translations = {
			{ 0, NetObjectAutomobile }, // car
			{ 1, NetObjectPlane },      // plane
			{ 2, NetObjectTrailer },    // trailer
			{ 3, NetObjectAutomobile }, // quadBike
			{ 5, NetObjectAutomobile }, // submarineCar
			{ 6, NetObjectAutomobile }, // amphibiousAutomobile
			{ 7, NetObjectAutomobile }, // amphQuadbike
			{ 8, NetObjectHeli },       // heli
			{ 9, NetObjectHeli },       // blimp
			{ 10, NetObjectHeli },      // autoGyro (perhaps skylift?)
			{ 11, NetObjectBike },      // bike
			{ 12, NetObjectBike },      // bicycle
			{ 13, NetObjectBoat },      // boat
			{ 14, NetObjectTrain },     // train
			{ 15, NetObjectSubmarine }, // submarine
		};

		static std::unordered_map<eNetObjectTypes, std::pair<std::vector<int>, bool>> translations = {
			{ NetObjectAutomobile, { { 5 }, true } },
			{ NetObjectBike, { { 5 }, true } },
			{ NetObjectBoat, { { 5 }, true } },
			{ NetObjectDoor, { { 1 }, false } },
			{ NetObjectHeli, { { 5 }, true } },
			{ NetObjectObject, { { 1, 4 }, false } },
			{ NetObjectPed, { { 6 }, false } },
			{ NetObjectPickup, { { 1 }, false } },
			{ NetObjectPickupPlacement, { { 1 }, false } },
			{ NetObjectPlane, { { 5 }, true } },
			{ NetObjectSubmarine, { { 5 }, true } },
			{ NetObjectPlayer, { { 6 }, false } },
			{ NetObjectTrailer, { { 5 }, true } },
			{ NetObjectTrain, { { 5 }, true } },
		};

		auto vit = translations.find(type);
		if (vit == end(translations)) {
			LOG_DEV("RCC FAILED - 15");
			return false;
		}

		bool valid_type = false;
		for (int yes : vit->second.first) {
			if (yes == model_type) {
				valid_type = true;
				break;
			}
		}

		if (!valid_type || (vit->second.second && type_translations[vehicle_type] != type)) {
			if (menu::helpers::is_valid_net_player(sender)) {
				menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);

				if (protection::events::vars::m_vars.m_crashing.notify()) {
					menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_quantum), false, true);
				}
			}

			LOG_DEV("RCC FAILED - 16");
			return false;
		}

		// check for vehicles being spawned as objects
		if (vit->second.second && type == NetObjectObject) {
			if (protection::events::vars::m_vars.m_crashing.notify()) {
				if (menu::helpers::is_valid_net_player(sender)) {
					menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_bad_type), false, true);
				}
			}

			LOG_DEV("RCC FAILED - 17");
			return false;
		}
	} else {
		LOG("Preventing %s creating, model doesn't exist (%X)", sender->m_player_info->m_name, model_hash);
		return false;
	}

	// read nodes and test alignment
	global::vars::g_alignment_tests["RCC"].m_block = false;
	global::vars::g_alignment_tests["RCC"].m_monitor = true;
	global::vars::g_alignment_tests["RCC"].m_thread_id = GetCurrentThreadId();

	bit_buffer->set_position(0);
	rage::engine::parse_nodes(tree, 1, 2 - ((flag & 4) != 0 || (flag & 0x40) != 0), bit_buffer, 0);

	global::vars::g_alignment_tests["RCC"].m_monitor = false;
	if (global::vars::g_alignment_tests["RCC"].m_block) {
		if (menu::helpers::is_valid_net_player(sender)) {
			menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
			protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);

			if (protection::events::vars::m_vars.m_crashing.notify()) {
				menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_nodes), false, true);
			}
		}

		LOG_DEV("RCC FAILED - 18");
		return false;
	}

	if (protection::events::vars::m_vars.m_attachments.enabled()) {
		bool vehicle_attachment = false;
		uint16_t connected_id = 0;

		if (menu::helpers::is_node_attached(tree->m_parent_node, &vehicle_attachment, &connected_id)) {
			if (menu::helpers::is_valid_net_player(sender)) {
				if (protection::events::vars::m_vars.m_attachments.notify()) {
					menu::notify::protection(sender->m_player_info->m_name, t_attachment.get() + t_attachment_to.get() + (vehicle_attachment ? t_attachment_vehicle.get() : t_attachment_player.get()) + " - " + menu::helpers::get_net_obj_type_string(type), false, protection::events::vars::m_vars.m_attachments.block());
				}
			}

			if (protection::events::vars::m_vars.m_attachments.block()) {
				LOG_DEV("RCC FAILED - 19");
				return false;
			}
		}

		if (connected_id > 0) {
			if (connected_id == network_id) {
				LOG_DEV("Preventing entity attachment on same id");
				menu::helpers::detach_node(tree->m_parent_node);
				// return false;
			}

			rage::network::net_object* object = rage::engine::get_network_object_from_network_id(_this, connected_id, false);
			if (is_valid_ptr(object) && is_valid_ptr(object->m_entity)) {
				;
			} else {
				LOG_DEV("[create] Preventing entity attachment on invalid net obj from %s", sender->m_player_info->m_name);
				menu::helpers::detach_node(tree->m_parent_node);
				// return false;
			}
		}
	}

	if (protection::events::vars::m_vars.m_cages.enabled()) {
		if (type == NetObjectObject) {
			static uint32_t cages[] = {
				2063962179, 959275690, 1396140175, 2968924808, 2931248133, 1098812088, 379820688, 1692612370,
				2946368461, 1082648418, 3561133533, 3825864590, 3357950520, 4121926986, 109264625, 3955926036, 1181661112,
				joaat("prop_container_01a"), joaat("prop_container_01b"), joaat("prop_container_01c"),
				joaat("prop_container_01d"), joaat("prop_container_01e"), joaat("prop_container_01f"),
				joaat("prop_container_01g"), joaat("prop_container_01h"), joaat("prop_container_01mb"),
				joaat("prop_container_02a"), joaat("prop_container_03a"), joaat("prop_container_03b"),
				joaat("prop_container_03mb"), joaat("prop_container_03_ld"), joaat("prop_container_04a"),
				joaat("prop_container_04mb"), joaat("prop_container_05mb"), joaat("prop_container_door_mb_l"),
				joaat("prop_container_door_mb_r"), joaat("prop_container_hole"), joaat("prop_container_ld"),
				joaat("prop_container_ld2"), joaat("prop_container_old1"), joaat("prop_container_ld"),
				joaat("prop_container_ld2"), joaat("prop_container_old1"), joaat("prop_dog_cage_02"),
				joaat("prop_dog_cage_01"), joaat("prop_dog_cage_02"), joaat("prop_conslift_cage"),
				joaat("prop_rub_cage01a"), joaat("prop_gold_cont_01b"), joaat("prop_gold_trolly"),
				joaat("prop_gold_trolly_full"), joaat("prop_gold_trolly_strap_01"), joaat("prop_cctv_cont_01"),
				joaat("prop_cctv_cont_03"), joaat("prop_cctv_cont_04"), joaat("prop_cctv_cont_05"),
				joaat("prop_cctv_cont_06"), joaat("prop_container_01a"), joaat("prop_container_01b"),
				joaat("prop_container_01c"), joaat("prop_container_01d"), joaat("prop_container_01e"),
				joaat("prop_container_01f"), joaat("prop_container_01g"), joaat("prop_container_01h"),
				joaat("prop_container_01mb"), joaat("prop_container_02a"), joaat("prop_container_03a"),
				joaat("prop_container_03b"), joaat("prop_container_03mb"), joaat("prop_container_03_ld"),
				joaat("prop_container_04a"), joaat("prop_container_04mb"), joaat("prop_container_05mb"),
				joaat("prop_container_door_mb_l"), joaat("prop_container_door_mb_r"), joaat("prop_container_hole"),
				joaat("prop_container_ld"), joaat("prop_container_ld2"), joaat("prop_container_old1"),
				joaat("prop_contnr_pile_01a"), joaat("prop_controller_01"), joaat("prop_control_rm_door_01"),
				joaat("prop_cont_chiller_01"), joaat("prop_container_hole"), joaat("prop_cont_chiller_01"),
				0xC6C3242D, joaat("prop_beach_fire"), 0xA2023E64, 2799454049, 3482883616, 564151899, 710268902,
				3284981583, 3500568834, 1060884015, 4248442390, 4256736313, 2693815128, 1925435073, 682074297,
				3763106032, 621481054, 2908189926, 3763623269, 1369811908, 1098122770
			};

			for (uint32_t hash : cages) {
				if (hash == model_hash) {
					if (menu::helpers::is_valid_net_player(sender)) {
						if (protection::events::vars::m_vars.m_cages.notify()) {
							menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_cage), protection::events::vars::m_vars.m_clone.redirect(), protection::events::vars::m_vars.m_clone.block());
						}

						if (protection::events::vars::m_vars.m_cages.block()) {
							LOG_DEV("RCC FAILED - 20");
							return false;
						}
					}

					break;
				}
			}
		}
	}

	if (protection::events::vars::m_vars.m_clone.enabled()) {
		if (type == NetObjectPed) {
			if (!*(bool*)(creation_data + 0xE1) && !*(bool*)(creation_data + 0xE2)) {
				if (_byteswap_ulong(*(uint32_t*)(bit_buffer->m_raw_buffer)) == 0x1DC17987) {
					if (native::get_entity_model(menu::player::get_local_player().m_ped) == model_hash) {
						if (menu::helpers::is_valid_net_player(sender)) {
							if (protection::events::vars::m_vars.m_clone.redirect()) {
								util::fiber::pool::add([=] {
									native::clone_ped(menu::player::get_player(sender->m_id).m_ped, menu::player::get_player(sender->m_id).m_heading, true, true);
								});
							}

							if (protection::events::vars::m_vars.m_clone.notify()) {
								menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_clone), protection::events::vars::m_vars.m_clone.redirect(), protection::events::vars::m_vars.m_clone.block());
							}

							if (protection::events::vars::m_vars.m_clone.block()) {
								LOG("Preventing %s creating, detected clone", sender->m_player_info->m_name);
								return false;
							}
						}
					}
				}
			}
		}
	}

	if (!protection::limits::spawn::vars::m_vars.m_limits.empty()) {
		auto vit = std::find_if(begin(protection::limits::spawn::vars::m_vars.m_limits), end(protection::limits::spawn::vars::m_vars.m_limits), [=](protection::limits::spawn::vars::entity_rate_limit& limit) {
			return limit.m_model == model_hash;
		});

		if (vit != end(protection::limits::spawn::vars::m_vars.m_limits)) {
			if (vit->m_enabled) {
				LOG_DEV("Limit=%X Last=%i", model_hash, vit->m_last_spawned[sender->m_id]);
				if ((GetTickCount() - vit->m_last_spawned[sender->m_id]) > global::lists::g_timers[vit->m_delay].m_result) {
					vit->m_last_spawned[sender->m_id] = GetTickCount();
				} else {
					LOG("Preventing %s creating model 0x%X (%s) due to entity rate limit", sender->m_player_info->m_name, model_hash, vit->m_comment);
					return false;
				}
			}
		}
	}

	if (protection::vars::m_vars.m_force_visible) {
		menu::helpers::force_node_visible(tree->m_parent_node);
	}

	if (type == NetObjectPed || type == NetObjectObject) {
		if (native::network_is_session_active() && menu::player::get_local_player().m_connected) {
			create_cache_type& cache = g_create_cache[sender->m_id].m_cache[type];
			if (cache.m_last_spawn == 0) {
				cache.m_last_spawn = GetTickCount();
			} else {
				if ((GetTickCount() - cache.m_last_spawn < 500)) {
					cache.m_sus_last_spawn = true;
					cache.m_sus_count++;
				} else {
					cache.m_sus_count = 0;
					cache.m_sus_last_spawn = false;
				}

				cache.m_last_spawn = GetTickCount();

				if (cache.m_sus_count >= 40 && cache.m_sus_last_spawn) {
					LOG("%s might be spamming (%i) - blacklisting and deleting nearby entities of same type", sender->m_player_info->m_name, type);

					util::fiber::pool::add([=] {
						int arr[100];
						memset(arr, 0, sizeof(arr));
						arr[0] = 100;

						if (type == NetObjectPed) {
							int size = native::get_ped_nearby_peds(menu::player::get_local_player().m_ped, arr, menu::player::get_local_player().m_ped);
							LOG_DEV("Size: %i", size);

							for (int i = 0; i < size; i++) {
								if (arr[i] && native::does_entity_exist(arr[i])) {
									if (native::is_ped_a_player(arr[i])) continue;

									LOG_DEV("Deleting ped %x", arr[i]);

									menu::control::simple_request_control(arr[i], true);
									native::set_entity_as_mission_entity(arr[i], true, true);
									native::delete_ped(&arr[i]);
								}
							}
						}
					});

					menu::player::get_player(sender->m_id).m_blacklist = GetTickCount() + 5000;
				}
			}
		}
	}

	return receive_clone_create_t(_this, sender, r8, type, network_id, flag, bit_buffer, timestamp);
}