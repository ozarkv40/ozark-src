#include "hooks.h"
#include "util/caller.h"
#include "menu/base/util/helpers.h"
#include "menu/base/submenus/main/network/network_spoofing.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_player_rotation.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_vehicle_rotation.h"
#include "rage/engine.h"
#include "util/memory/memory.h"
#include "menu/base/submenus/main/network/players/network_players_removals.h"

void handle_node(rage::network::data_node* node, rage::network::net_object* object, uint32_t node_name) {
	switch (node_name) {
		case joaat("CPedMovementDataNode"): {
			rage::network::net_object* node_accessor_object = caller::call<rage::network::net_object*>(*(uint64_t*)(object->m_vtable + 0x8), object, 5);
			caller::call<void>(*(uint64_t*)(node_accessor_object->m_vtable + 0x58), node_accessor_object, node->m_data_node_common_operations->m_data);
			
			*(bool*)(node->m_data_node_common_operations->m_data + 0xC0) = *(float*)(node->m_data_node_common_operations->m_data + 0xC4) != 0.0f;
			*(bool*)(node->m_data_node_common_operations->m_data + 0xC1) = *(float*)(node->m_data_node_common_operations->m_data + 0xC8) != 0.0f;

			if (network::spoofing::vars::m_vars.m_movement_animation) {
				if (global::vars::g_ped_factory) {
					if (global::vars::g_ped_factory->m_local_ped) {
						if (global::vars::g_ped_factory->m_local_ped->get_net_obj()) {
							if (object->m_network_id == global::vars::g_ped_factory->m_local_ped->get_net_obj()->m_network_id) {
								*(bool*)(node->m_data_node_common_operations->m_data + 0xC0) = false;
								*(bool*)(node->m_data_node_common_operations->m_data + 0xC1) = false;
							}
						}
					}
				}
			}

			break;
		}

		case joaat("CPedOrientationDataNode"): {
			rage::network::net_object* node_accessor_object = caller::call<rage::network::net_object*>(*(uint64_t*)(object->m_vtable + 0x8), object, 5);
			if (*(uint64_t*)(node_accessor_object->m_vtable + 0x28) == global::vars::g_ped_orientation_writer) {
				uint64_t entity_object = *(uint64_t*)((uint64_t)node_accessor_object - 0x1B0);
				if (entity_object) {
					*(float*)(node->m_data_node_common_operations->m_data + 0xC0) = *(float*)(entity_object + 0x580);

					float v4 = *(float*)(node->m_data_node_common_operations->m_data + 0xC0);
					float v5 = v4;

					*(float*)(node->m_data_node_common_operations->m_data + 0xC4) = *(float*)(entity_object + 0x584);

					if ((v4 + 3.1415927f) < 0.0f) {
						v5 = v4 + 6.2831855f;
					}

					if ((3.1415927f - v4) < 0.0f) {
						v5 = v4 - 6.2831855f;
					}

					*(float*)(node->m_data_node_common_operations->m_data + 0xC0) = v5;

					float v6 = *(float*)(node->m_data_node_common_operations->m_data + 0xC4);
					float v7 = v6;

					if ((v6 + 3.1415927f) < 0.0f) {
						v7 = v6 + 6.2831855f;
					}

					if ((3.1415927f - v6) < 0.0f) {
						v7 = v6 - 6.2831855f;
					}

					*(float*)(node->m_data_node_common_operations->m_data + 0xC4) = v7;
				} else {
					*(float*)(node->m_data_node_common_operations->m_data + 0xC4) = 0.f;
					*(float*)(node->m_data_node_common_operations->m_data + 0xC0) = 0.f;
				}

				network::spoofing::rotation::player::vars::variables& vars = network::spoofing::rotation::player::vars::m_vars;
				if (vars.m_spinbot || vars.m_face_direction || vars.m_jitter) {
					if (global::vars::g_ped_factory) {
						if (global::vars::g_ped_factory->m_local_ped) {
							if (global::vars::g_ped_factory->m_local_ped->get_net_obj()) {
								if (object->m_network_id == global::vars::g_ped_factory->m_local_ped->get_net_obj()->m_network_id) {
									if (vars.m_spinbot || vars.m_jitter) {
										*(float*)(node->m_data_node_common_operations->m_data + 0xC0) = vars.m_hook_value.x;
										*(float*)(node->m_data_node_common_operations->m_data + 0xC4) = vars.m_hook_value.y;
										return;
									}

									if (vars.m_face_direction) {
										float val = 0.f;

										switch (vars.m_face_direction_val) {
											case 0: val = -90.f; break;
											case 1: val = 90.f; break;
											case 2: val = 180.f; break;
										}

										if (vars.m_relative) {
											val += menu::player::get_local_player().m_heading;
										}

										if (val > 180.f) val = -180.f + (val - 180.f);

										*(float*)(node->m_data_node_common_operations->m_data + 0xC0) = val * 0.0174532924f;
										*(float*)(node->m_data_node_common_operations->m_data + 0xC4) = val * 0.0174532924f;
									}
								}
							}
						}
					}
				}
			}

			break;
		}

		case joaat("CEntityOrientationDataNode"): {
			rage::network::net_object* node_accessor_object = caller::call<rage::network::net_object*>(*(uint64_t*)(object->m_vtable + 0x8), object, 6);
			if (*(uint64_t*)(node_accessor_object->m_vtable + 0x18) == global::vars::g_entity_orientation_writer) {
				struct orientation {
					char _0x0000[0xC0];
					math::matrix<float> m_transform;
				}; orientation* _orientation = (orientation*)node->m_data_node_common_operations->m_data;

				uint64_t entity = ((rage::network::net_object*)((uint64_t)node_accessor_object - 0xC8))->m_entity;
				if (entity) {
					memcpy(&_orientation->m_transform, (math::matrix<float>*)(entity + 0x60), sizeof(_orientation->m_transform));
				} else {
					memset(&_orientation->m_transform, 0, sizeof(_orientation->m_transform));
					_orientation->m_transform.m_elements[0][0] = 1.f;
					_orientation->m_transform.m_elements[1][1] = 1.f;
					_orientation->m_transform.m_elements[2][2] = 1.f;
				}

				network::spoofing::rotation::vehicle::vars::variables& vars = network::spoofing::rotation::vehicle::vars::m_vars;
				if (vars.m_spinbot || vars.m_static || vars.m_jitter) {
					if (menu::player::get_local_player().m_in_vehicle) {
						if (global::vars::g_ped_factory) {
							if (global::vars::g_ped_factory->m_local_ped) {
								if ((uint64_t)global::vars::g_ped_factory->m_local_ped->m_vehicle == entity) {
									rage::engine::handle_rotation_values_from_order(&_orientation->m_transform, &vars.m_hook_value, 2);
								}
							}
						}
					}
				}
			}

			break;
		}
	}
}

void handle_node_caller(rage::network::data_node* node, rage::network::net_object* object, bool recursive) {
	if (recursive) {
		menu::helpers::node_foreach(node, [=](std::string name, rage::network::data_node* child) {
			handle_node(child, object, native::get_hash_key(name.c_str()));
		});
	} else {
		uint64_t vtable = *(uint64_t*)((uint64_t)node);
		handle_node(node, object, native::get_hash_key(menu::helpers::get_vtable_name(vtable).c_str()));
	}
}

bool menu::hooks::compress_data_node(rage::network::data_node* node, uint32_t flag1, uint64_t flag2, rage::network::net_object* object, rage::bit_buffer* buffer, uint32_t bitsize, uint64_t unk1, bool unk2, uint64_t unk3) {
	if ((flag1 & node->m_flag) != 0 && (!node->m_flag3 || ((uint32_t)flag2 & node->m_flag3) != 0)) {
		auto& removal = network::players::removals::vars::m_vars;
		if (removal.m_targeted_crash || removal.m_session_crash) {
			removal.m_broken_entities[object] = removal.m_targeted_crash_target;

			removal.m_break_nodes = true;
			removal.m_break_node_threads[1] = GetCurrentThreadId();

			bool _return = compress_data_node_t(node, flag1, flag2, object, buffer, bitsize, unk1, unk2, unk3);

			removal.m_break_nodes = false;
			removal.m_break_node_threads[1] = 0;

			return true;
		}

		handle_node_caller(node, object, true);
	}

	return compress_data_node_t(node, flag1, flag2, object, buffer, bitsize, unk1, unk2, unk3);
}

bool menu::hooks::compress_data_node2(rage::network::data_node* node, rage::network::net_object* object) {
	uint64_t rcx = (uint64_t)node;
	uint64_t rcx_vtable = *(uint64_t*)rcx;

	if (!caller::call<bool>(*(uint64_t*)(rcx_vtable + 0xD0), rcx, 0))
		return false;

	uint64_t v4 = caller::call<uint64_t>(*(uint64_t*)(object->m_vtable + 0x20), object);
	uint64_t v5 = caller::call<uint64_t>(*(uint64_t*)(*(uint64_t*)(v4) + 0x8), v4);

	if (!v5)
		return false;

	auto& removal = network::players::removals::vars::m_vars;
	if (removal.m_targeted_crash || removal.m_session_crash) {
		removal.m_broken_entities[object] = removal.m_targeted_crash_target;

		removal.m_break_nodes = true;
		removal.m_break_node_threads[0] = GetCurrentThreadId();

		bool _return = compress_data_node2_t(node, object);

		removal.m_break_nodes = false;
		removal.m_break_node_threads[0] = 0;

		return true;
	}

	handle_node_caller(node, object, false);
	return compress_data_node2_t(node, object);
}