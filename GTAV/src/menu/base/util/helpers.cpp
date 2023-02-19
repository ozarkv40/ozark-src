#include "helpers.h"
#include "util/util.h"
#include "rage/invoker/natives.h"
#include "rage/engine.h"
#include "util/caller.h"
#include "util/log.h"

extern "C" LPSTR __cdecl __unDName(char* buffer, const char* mangled, int length, void* (*alloc_fn)(size_t), void(*free_fn)(void*), unsigned short flags);

namespace menu::helpers {
	struct sector_data_node {
		math::vector3_<int> m_pos;
	};

	struct object_sector_data_node {
		bool m_high_res;
		math::vector3_<float> m_pos;
	};

	bool is_rockstar_ip(uint32_t ip) {
		return (ip >= 0x68FF6800 && ip <= 0x68FF6BFF)
			|| (ip >= 0xC051F000 && ip <= 0xC051F7FF)
			|| (ip >= 0x8B8AE000 && ip <= 0x8B8AE5FF)
			|| (ip >= 0x8B8AE700 && ip <= 0x8B8AF6FF)
			|| (ip >= 0x8B8AFF00 && ip <= 0x8B8AFFFF)
			|| (ip >= 0xC7A83D00 && ip <= 0xC7A83EFF)
			|| (ip >= 0xC7E5E000 && ip <= 0xC7E5E0FF)
			|| (ip >= 0xD1CCF000 && ip <= 0xD1CCF6FF)
			|| (ip >= 0xD1CCF800 && ip <= 0xD1CCFAFF)
			|| (ip >= 0xD1CCFC00 && ip <= 0xD1CCFCFF)
			|| (ip >= 0xB9384000 && ip <= 0xB93843FF);
	};

	bool is_valid_net_player(rage::network::net_game_player* sender) {
		return is_valid_ptr(sender) && is_valid_ptr(sender->m_player_info);
	}

	void flag_modder(int id, menu::player::ePlayerReportReasons reason, bool blacklist) {
		if (id == -1) return;
		menu::player::get_player(id).m_modder_flags[reason] = true;

		if (blacklist) {
			menu::player::get_player(id).m_blacklist = GetTickCount() + 15000;
		}
	}

	menu::player::player_context& get_player_from_ip(uint32_t ip) {
		int id = -1;

		menu::player::for_each([&](menu::player::player_context& player) {
			if (is_valid_net_player(player.m_net_player)) {
				if (player.m_net_player->m_player_info->m_external_ip == ip) {
					id = player.m_id;
				}
			}
		}, true, true);

		static menu::player::player_context _static;
		if (id == -1) return _static;
		return menu::player::get_player(id);
	}

	menu::player::player_context& get_player_from_peer(uint64_t peer) {
		int id = -1;

		menu::player::for_each([&](menu::player::player_context& player) {
			if (is_valid_net_player(player.m_net_player)) {
				if (player.m_net_player->m_player_info->m_host_token == peer) {
					id = player.m_id;
				}
			}
		}, true, true);

		static menu::player::player_context _static;
		if (id == -1) return _static;
		return menu::player::get_player(id);
	}

	menu::player::player_context& get_player_from_rid(uint64_t rid) {
		int id = -1;

		menu::player::for_each([&](menu::player::player_context& player) {
			if (is_valid_net_player(player.m_net_player)) {
				if (player.m_net_player->m_player_info->m_identifier.m_rockstar_id == rid) {
					id = player.m_id;
				}
			}
		}, true, true);

		static menu::player::player_context _static;
		_static.m_id = -1;
		if (id == -1) return _static;
		return menu::player::get_player(id);
	}

	std::string get_net_obj_type_string(eNetObjectTypes type) {
		switch (type) {
			case NetObjectAutomobile: return TRANSLATE(t_type_automobile);
			case NetObjectBike: return TRANSLATE(t_type_bike);
			case NetObjectBoat: return TRANSLATE(t_type_boat);
			case NetObjectDoor: return TRANSLATE(t_type_door);
			case NetObjectHeli: return TRANSLATE(t_type_heli);
			case NetObjectObject: return TRANSLATE(t_type_object);
			case NetObjectPed: return TRANSLATE(t_type_ped);
			case NetObjectPickup: return TRANSLATE(t_type_pickup);
			case NetObjectPlane: return TRANSLATE(t_type_plane);
			case NetObjectSubmarine: return TRANSLATE(t_type_submarine);
			case NetObjectPlayer: return TRANSLATE(t_type_player);
			case NetObjectTrailer: return TRANSLATE(t_type_trailer);
			case NetObjectTrain: return TRANSLATE(t_type_train);
		}

		return "";
	}

	std::string clean_name(std::string fixed) {
		if (!fixed.empty()) {
			if (strstr(fixed.c_str(), "~")) {
				std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ<>0123456789��";

				for (char c : alphabet) {
					char b[2];
					snprintf(b, 2, "%c", c);
					util::replace_string(fixed, (std::string("~") + b + std::string("~")), "");
				}

				util::replace_string(fixed, "~bold~", "");
				util::replace_string(fixed, "~italic~", "");
				util::replace_string(fixed, "~ws~", "");
				util::replace_char(fixed, '\n', "");
			}
		}

		return fixed;
	}

	std::string get_location_from_id(int id) {
		const char* _return = "";
		switch (id) {
			case 0:
				_return = "MP_REP_PROP_1";
				break;
			case 1:
				_return = "MP_PROP_1";
				break;

			case 2:
				_return = "MP_PROP_2";
				break;

			case 3:
				_return = "MP_PROP_3";
				break;

			case 4:
				_return = "MP_PROP_4";
				break;

			case 5:
				_return = "MP_PROP_5";
				break;

			case 6:
				_return = "MP_PROP_6";
				break;

			case 7:
				_return = "MP_PROP_7";
				break;

			case 8:
				_return = "MP_PROP_8";
				break;

			case 9:
				_return = "MP_PROP_9";
				break;

			case 10:
				_return = "MP_PROP_10";
				break;

			case 11:
				_return = "MP_PROP_11";
				break;

			case 12:
				_return = "MP_PROP_12";
				break;

			case 13:
				_return = "MP_PROP_13";
				break;

			case 14:
				_return = "MP_PROP_14";
				break;

			case 15:
				_return = "MP_PROP_15";
				break;

			case 16:
				_return = "MP_PROP_16";
				break;

			case 17:
				_return = "MP_PROP_17";
				break;

			case 18:
				_return = "MP_PROP_18";
				break;

			case 19:
				_return = "MP_PROP_19";
				break;

			case 20:
				_return = "MP_PROP_20";
				break;

			case 21:
				_return = "MP_PROP_21";
				break;

			case 22:
				_return = "MP_PROP_22";
				break;

			case 23:
				_return = "MP_PROP_23";
				break;

			case 24:
				_return = "MP_PROP_24";
				break;

			case 25:
				_return = "MP_PROP_25";
				break;

			case 26:
				_return = "MP_PROP_26";
				break;

			case 27:
				_return = "MP_PROP_27";
				break;

			case 28:
				_return = "MP_PROP_28";
				break;

			case 29:
				_return = "MP_PROP_29";
				break;

			case 30:
				_return = "MP_PROP_30";
				break;

			case 31:
				_return = "MP_PROP_31";
				break;

			case 32:
				_return = "MP_PROP_32";
				break;

			case 33:
				_return = "MP_PROP_33";
				break;

			case 34:
				_return = "MP_PROP_34";
				break;

			case 35:
				_return = "MP_PROP_35";
				break;

			case 36:
				_return = "MP_PROP_36";
				break;

			case 37:
				_return = "MP_PROP_37";
				break;

			case 38:
				_return = "MP_PROP_38";
				break;

			case 39:
				_return = "MP_PROP_39";
				break;

			case 40:
				_return = "MP_PROP_40";
				break;

			case 41:
				_return = "MP_PROP_41";
				break;

			case 42:
				_return = "MP_PROP_42";
				break;

			case 43:
				_return = "MP_PROP_43";
				break;

			case 44:
				_return = "MP_PROP_44";
				break;

			case 45:
				_return = "MP_PROP_45";
				break;

			case 46:
				_return = "MP_PROP_46";
				break;

			case 47:
				_return = "MP_PROP_48";
				break;

			case 48:
				_return = "MP_PROP_49";
				break;

			case 49:
				_return = "MP_PROP_50";
				break;

			case 50:
				_return = "MP_PROP_51";
				break;

			case 51:
				_return = "MP_PROP_52";
				break;

			case 52:
				_return = "MP_PROP_57";
				break;

			case 53:
				_return = "MP_PROP_59";
				break;

			case 54:
				_return = "MP_PROP_60";
				break;

			case 55:
				_return = "MP_PROP_61";
				break;

			case 56:
				_return = "MP_PROP_62";
				break;

			case 57:
				_return = "MP_PROP_63";
				break;

			case 58:
				_return = "MP_PROP_64";
				break;

			case 59:
				_return = "MP_PROP_65";
				break;

			case 60:
				_return = "MP_PROP_66";
				break;

			case 61:
				_return = "MP_PROP_67";
				break;

			case 62:
				_return = "MP_PROP_68";
				break;

			case 63:
				_return = "MP_PROP_69";
				break;

			case 64:
				_return = "MP_PROP_70";
				break;

			case 65:
				_return = "MP_PROP_71";
				break;

			case 66:
				_return = "MP_PROP_72";
				break;

			case 67:
				_return = "MP_PROP_73";
				break;

			case 68:
				_return = "MP_PROP_74";
				break;

			case 69:
				_return = "MP_PROP_75";
				break;

			case 70:
				_return = "MP_PROP_76";
				break;

			case 71:
				_return = "MP_PROP_77";
				break;

			case 72:
				_return = "MP_PROP_78";
				break;

			case 83:
				_return = "MP_PROP_79";
				break;

			case 84:
				_return = "MP_PROP_80";
				break;

			case 85:
				_return = "MP_PROP_81";
				break;

			case 73:
				_return = "MP_PROP_83";
				break;

			case 74:
				_return = "MP_PROP_84";
				break;

			case 75:
				_return = "MP_PROP_85";
				break;

			case 76:
				_return = "MP_PROP_86";
				break;

			case 77:
				_return = "MP_PROP_87";
				break;

			case 78:
				_return = "MP_PROP_89";
				break;

			case 79:
				_return = "MP_PROP_90";
				break;

			case 80:
				_return = "MP_PROP_92";
				break;

			case 81:
				_return = "MP_PROP_94";
				break;

			case 82:
				_return = "MP_PROP_95";
				break;

			case 86:
				_return = "PM_SPAWN_Y";
				break;

			case 87:
				_return = "MP_PROP_OFF1";
				break;

			case 88:
				_return = "MP_PROP_OFF2";
				break;

			case 89:
				_return = "MP_PROP_OFF3";
				break;

			case 90:
				_return = "MP_PROP_OFF4";
				break;

			case 91:
				_return = "MP_PROP_CLUBH1";
				break;

			case 92:
				_return = "MP_PROP_CLUBH2";
				break;

			case 93:
				_return = "MP_PROP_CLUBH3";
				break;

			case 94:
				_return = "MP_PROP_CLUBH4";
				break;

			case 95:
				_return = "MP_PROP_CLUBH5";
				break;

			case 96:
				_return = "MP_PROP_CLUBH6";
				break;

			case 97:
				_return = "MP_PROP_CLUBH7";
				break;

			case 98:
				_return = "MP_PROP_CLUBH8";
				break;

			case 99:
				_return = "MP_PROP_CLUBH9";
				break;

			case 100:
				_return = "MP_PROP_CLUBH10";
				break;

			case 101:
				_return = "MP_PROP_CLUBH11";
				break;

			case 102:
				_return = "MP_PROP_CLUBH12";
				break;

			case 103:
			case 106:
			case 109:
			case 112:
				_return = "MP_PROP_OFFG1";
				break;

			case 104:
			case 107:
			case 110:
			case 113:
				_return = "MP_PROP_OFFG2";
				break;

			case 105:
			case 108:
			case 111:
			case 114:
				_return = "MP_PROP_OFFG3";
				break;

			case 115:
				_return = "IE_WARE_1";
				break;
		}

		return native::get_label_text(_return);
	}

	std::string get_vtable_name(uint64_t table) {
		uint64_t object_locator = *(uint64_t*)(table - 8);
		if (object_locator) {
			uint32_t offset = *(uint32_t*)(object_locator + 0xC);
			if (offset) {
				const char* string = (const char*)(global::vars::g_game_address.first + offset + 0x10);
				if (string) {
					std::string str(string);
					if (str.find(".?A") == 0) {
						str = str.substr(4, str.length());
					}

					if (str.find("NodeCommonDataOperations") != std::string::npos) {
						str = str.substr(2, str.length());

						std::size_t at = str.find_first_of('@');
						if (at != std::string::npos) {
							std::string base_class = str.substr(at + 1);
							if (!base_class.empty()) {
								at = base_class.find_first_of("@@");
								if (at != std::string::npos) {
									str = base_class.substr(0, at);
									if (!str.empty()) {
										if (str.length() > 2) {
											if (str[0] == 'V' && str[1] == 'C') {
												str = "NodeCommonDataOperations<" + str.substr(1) + ">";
											}
										}
									}
								}
							}
						}

					} else if (str.find("AutoIdDesc__") != std::string::npos) {
						std::size_t at = str.find("AutoIdDesc__");
						if (at == 0) {
							at = str.find_first_of('@');
							if (at != std::string::npos) {
								str = str.substr(13);
								str = str.substr(0, str.find('@'));
							}
						} else {
							at = str.find("::AutoIdDesc__");
							if (at != std::string::npos) {
								str = str.substr(0, at);
							}
						}
					} else {
						std::size_t at = str.find_first_of('@');
						if (at > 0 && at < 0xffff) {
							str = str.substr(0, at);
						}
					}

					return str;
				}

				return string;
			}
		}

		return "";
	}

	std::string get_vtable_name_full(uint64_t table) {
		uint64_t object_locator = *(uint64_t*)(table - 8);
		if (object_locator) {
			uint32_t offset = *(uint32_t*)(object_locator + 0xC);
			if (offset) {
				const char* string = (const char*)(global::vars::g_game_address.first + offset + 0x10);
				if (string) {
					std::string str(string);
					if (str[0] == '.') {
						str = str.substr(1);
					}

					char temp[512];
					return std::string(__unDName(temp, str.c_str(), sizeof(temp), malloc, free, 0xA800));
				}

				return string;
			}
		}

		return "";
	}

	bool is_crash_model(uint32_t model, eNetObjectTypes type) {
		switch (model) {
			case 0x3F039CBA:
			case 0x856CFB02:
			case 0x2D7030F3:
			case 0x0703F106:
			case 0x431d501c:
			case 0x1CFC0E72:
			case 0x1E15B3EC:
			case 0x1CB5C0C3:
				return true;
		}

		if (type == NetObjectPickup) {
			switch (model) {
				case 0x5FC8A70:
				case 0xB9402F87:
					return true;
			}
		}

		return false;
	}

	void detach_node(rage::network::data_node* node) {
		std::unordered_map<std::string, rage::network::data_node*> nodes;
		node_foreach(node, [&] (std::string name, rage::network::data_node* ptr) {
			nodes[name] = ptr;
		});

		auto [has_physical, physical_attach] = get_node_struct<rage::network::attach_data_node>(nodes, "CPhysicalAttachDataNode");
		auto [has_ped, ped_attach] = get_node_struct<rage::network::attach_data_node>(nodes, "CPedAttachDataNode");

		if (has_physical) {
			physical_attach->m_attached = false;
		}

		if (has_ped) {
			ped_attach->m_attached = false;
		}
	}

	void force_node_visible(rage::network::data_node* node) {
		std::unordered_map<std::string, rage::network::data_node*> nodes;
		node_foreach(node, [&](std::string name, rage::network::data_node* ptr) {
			nodes[name] = ptr;
		});

		struct physical_game_state_data_node {
			char _0x0000[0xC0];
			bool m_visible;
		};

		auto [has_physical, physical] = get_node_struct<physical_game_state_data_node>(nodes, "CPhysicalGameStateDataNode");

		if (has_physical) {
			physical->m_visible = true;
		}

		// CPhysicalScriptGameStateDataNode
	}

	void node_foreach_tree(rage::network::sync_tree* tree, std::function<void(std::string, rage::network::data_node*)> callback) {
		for (int i = 0; i < tree->m_data_node_count; i++) {
			rage::network::data_node* node = tree->m_nodes[i];
			if (node) {
				callback("", node);
			}
		}
	}

	void node_foreach(rage::network::data_node* node, std::function<void(std::string, rage::network::data_node*)> callback) {
		if (is_valid_ptr(node)) {
			rage::network::data_node* current = node;
			while (is_valid_ptr(current) && is_valid_ptr(*(uint64_t*)((uint64_t)current))) {
				if (current->is_data_node()) {
					if (current->m_data_node_common_operations) {
						if (current->m_data_node_common_operations->m_data) {
							std::string name = get_vtable_name(*(uint64_t*)((uint64_t)current));
							if (!name.empty()) {
								callback(name, current);
							}
						}
					}
				}

				if (current->is_parent_node()) {
					if (current->m_child_count > 0) {
						rage::network::data_node* children = current->m_first_child;
						if (is_valid_ptr(children)) {
							node_foreach(children, callback);
						}
					}
				}

				current = current->m_next;
			}
		}
	}

	bool is_node_attached(rage::network::data_node* node, bool* veh, uint16_t* out_net_id) {
		*veh = false;

		std::unordered_map<std::string, rage::network::data_node*> nodes;
		node_foreach(node, [&](std::string name, rage::network::data_node* ptr) {
			nodes[name] = ptr;
		});

		auto [has_physical, physical_attach] = get_node_struct<rage::network::attach_data_node>(nodes, "CPhysicalAttachDataNode");
		auto [has_ped, ped_attach] = get_node_struct<rage::network::attach_data_node>(nodes, "CPedAttachDataNode");

		if (has_physical) {
			if (physical_attach->m_attached) {
				LOG_DEV("ENTITY ATTACHED! NETID: %i", physical_attach->m_network_id);
				if (out_net_id) *out_net_id = physical_attach->m_network_id;

				if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr)) {
					if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr->get_net_obj())) {
						if (menu::player::get_local_player().m_ped_ptr->get_net_obj()->m_network_id == physical_attach->m_network_id) {
							return true;
						}
					}
				}

				if (menu::player::get_local_player().m_in_vehicle) {
					if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr)) {
						if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr->m_vehicle)) {
							if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr->m_vehicle->get_net_obj())) {
								LOG_DEV("MY VEH ID: %i", menu::player::get_local_player().m_ped_ptr->m_vehicle->get_net_obj()->m_network_id);
								if (menu::player::get_local_player().m_ped_ptr->m_vehicle->get_net_obj()->m_network_id == physical_attach->m_network_id) {
									*veh = true;
									return true;
								}
							}

							for (int i = -1; i < native::get_vehicle_number_of_passengers(menu::player::get_local_player().m_vehicle); i++) {
								Ped ped = native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, i, 0);
								if (ped) {
									rage::types::ped* p = (rage::types::ped*)rage::engine::get_entity_address(ped);
									if (p) {
										if (p->get_net_obj()) {
											if (p->get_net_obj()->m_network_id == physical_attach->m_network_id) {
												*veh = true;
												return true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		if (has_ped) {
			if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr)) {
				if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr->get_net_obj())) {
					if (menu::player::get_local_player().m_ped_ptr->get_net_obj()->m_network_id == ped_attach->m_network_id) {
						return true;
					}
				}
			}

			if (menu::player::get_local_player().m_in_vehicle) {
				if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr)) {
					if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr->m_vehicle)) {
						if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr->m_vehicle->get_net_obj())) {
							if (menu::player::get_local_player().m_ped_ptr->m_vehicle->get_net_obj()->m_network_id == ped_attach->m_network_id) {
								*veh = true;
								return true;
							}
						}

						for (int i = -1; i < native::get_vehicle_number_of_passengers(menu::player::get_local_player().m_vehicle); i++) {
							Ped ped = native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, i, 0);
							if (ped) {
								rage::types::ped* p = (rage::types::ped*)rage::engine::get_entity_address(ped);
								if (p) {
									if (p->get_net_obj()) {
										if (p->get_net_obj()->m_network_id == ped_attach->m_network_id) {
											*veh = true;
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		return false;
	}

	bool get_node_creation(rage::network::data_node* node, rage::bit_buffer* buffer, uint32_t* hash, uint64_t* data) {
		if (is_valid_ptr(node)) {
			rage::network::data_node* current = node;
			while (is_valid_ptr(current) && is_valid_ptr(*(uint64_t*)((uint64_t)current))) {
				if (current->is_data_node()) {
					if (current->m_data_node_common_operations) {
						if (current->m_data_node_common_operations->m_data) {
							std::string name = get_vtable_name(*(uint64_t*)((uint64_t)current));
							if (!name.empty()) {
								if (strstr(name.c_str(), "CreationDataNode") && !strstr(name.c_str(), "CAutomobileCreation")) {
									*data = current->m_data_node_common_operations->m_data;
									switch (native::get_hash_key(name.c_str())) {
										case joaat("CDoorCreationDataNode"):
										case joaat("CPlayerCreationDataNode"):
										case joaat("CVehicleCreationDataNode"):
											return buffer->read_uint(hash, 0x20);

										case joaat("CObjectCreationDataNode"): {
											uint32_t unk = 0;
											if (buffer->read_uint(&unk, 5)) {
												if ((unk & 0xFFFFFFFD) != 0) {
													return buffer->read_uint(hash, 0x20);
												}
											}

											return false;
										}

										case joaat("CPedCreationDataNode"): {
											bool temp = false;
											if (buffer->read_bool(&temp)) {
												if (buffer->read_bool(&temp)) {
													if (buffer->read_uint(hash, 4)) {
														return buffer->read_uint(hash, 0x20);
													}
												}
											}

											return false;
										}

										case joaat("CPickupCreationDataNode"): {
											rage::bit_buffer_sync_instance sync_reader = buffer->create_reader();

											bool unk = false;
											if (buffer->read_bool(&unk)) {
												bool success = false;
												uint32_t pickup_hash = 0;
												uint32_t hash2 = 0;
												uint8_t unk_data[0x200];

												if (unk) {
													success = caller::call<bool>(global::vars::g_read_pickup_from_bit_buffer, unk_data, &sync_reader);
													pickup_hash = *(uint32_t*)&unk_data[0x8];
												} else {
													success = buffer->read_uint(&pickup_hash, 0x20);
												}

												if (success) {
													unk = *(uint32_t*)(&unk_data[84]) > 0;
													if (buffer->read_bool(&unk)) {
														if (unk) {
															success = buffer->read_uint(&hash2, 0x20);
														}

														if (success) {
															*hash = *(uint32_t*)(&unk_data[88]);

															unk = *(uint32_t*)(&unk_data[88]) != 0;
															if (buffer->read_bool(&unk)) {
																if (unk) {
																	return buffer->read_uint(hash, 0x20);
																}
															}
														}
													}
												}
											}

											return false;
										}
									}
								}
							}
						}
					}
				}

				if (current->is_parent_node()) {
					if (current->m_child_count > 0) {
						rage::network::data_node* children = current->m_first_child;
						if (is_valid_ptr(children)) {
							if (get_node_creation(children, buffer, hash, data)) {
								return true;
							}
						}
					}
				}

				current = current->m_next;
			}
		}

		return false;
	}

	void get_node_position(rage::network::data_node* node, math::vector3<float>* out) {
		std::unordered_map<std::string, rage::network::data_node*> nodes;
		node_foreach(node, [&](std::string name, rage::network::data_node* ptr) {
			if (strstr(name.c_str(), "Sector")) {
				nodes[name] = ptr;
			}
		});

		auto [has_sector_data, sector_data] = get_node_struct<sector_data_node>(nodes, "CSectorDataNode");
		auto [has_sector_position_data, sector_position_data] = get_node_struct<sector_data_node>(nodes, "CSectorPositionDataNode");
		auto [has_sector_player_data, sector_player_data] = get_node_struct<sector_data_node>(nodes, "CPlayerSectorPosNode");
		auto [has_sector_object_data, sector_object_data] = get_node_struct<object_sector_data_node>(nodes, "CObjectSectorPosNode");
		auto [has_sector_ped_data, sector_ped_data] = get_node_struct<sector_data_node>(nodes, "CPedSectorPosMapNode");

		math::vector3_<int> sector;
		sector.x = has_sector_data ? sector_data->m_pos.x : 512;
		sector.y = has_sector_data ? sector_data->m_pos.y : 512;
		sector.z = has_sector_data ? sector_data->m_pos.z : 0;

		math::vector3_<float> sector_pos;
		sector_pos.x = 
			(has_sector_position_data) ? sector_position_data->m_pos.x :
				(has_sector_player_data) ? sector_player_data->m_pos.x :
					(has_sector_object_data) ? sector_object_data->m_pos.x :
						(has_sector_ped_data) ? sector_ped_data->m_pos.x :
							0.0f;
		sector_pos.y =
			(has_sector_position_data) ? sector_position_data->m_pos.y :
				(has_sector_player_data) ? sector_player_data->m_pos.y :
					(has_sector_object_data) ? sector_object_data->m_pos.y :
						(has_sector_ped_data) ? sector_ped_data->m_pos.y :
							0.0f;
		sector_pos.z =
			(has_sector_position_data) ? sector_position_data->m_pos.z :
				(has_sector_player_data) ? sector_player_data->m_pos.z :
					(has_sector_object_data) ? sector_object_data->m_pos.z :
						(has_sector_ped_data) ? sector_ped_data->m_pos.z :
							0.0f;

		out->x = ((sector.x - 512.0f) * 54.0f) + sector_pos.x;
		out->y = ((sector.y - 512.0f) * 54.0f) + sector_pos.y;
		out->z = ((sector.z * 69.0f) + sector_pos.z) - 1700.0f;
	}

	void trigger_script_event(std::vector<int> args, int count, Player bitset) {
		int bits = 0;
		native::set_bit(&bits, bitset);
		if (bits != 0) {
			int64_t* _args = new int64_t[count];
			for (int i = 0; i < args.size(); i++) {
				_args[i] = args[i];
			}

			native::trigger_script_event(1, _args, count, bits);

			delete[] _args;
		}
	}

	Player get_net_msg_sender(uint64_t raw_buffer) {
		uint32_t id = -1;
		uint8_t pattern[] = { 0xC9, 0x18 };

		for (auto& buffer : global::vars::g_raw_buffer_translations) {
			uint64_t start = buffer.first;
			uint64_t end = start +  buffer.second.second;

			if (raw_buffer >= start && raw_buffer <= end) {
				id = buffer.second.first;
				break;
			}
		}

		if (id != -1) {
			rage::network::net_game_player* player = caller::call<rage::network::net_game_player*>(global::vars::g_get_net_msg_net_player, id);
			if (player) {
				if (player->m_id >= 0 && player->m_id <= 31) {
					if (menu::player::get_player(player->m_id).m_connected) {
						return player->m_id;
					}
				}
			}
		}

		return -1;
	}

	std::string get_gs_type(int type) {
		switch (type) {
			case 0: return "Invite Only";
			case 1: return "Friends Only";
			case 2: return "Crew Only";
			case 4: return "Heist";
			case 5: return "Public";
		}

		return "Unknown";
	}

	color_rgba get_color_from_blip(int id) {
		switch (id) {
			case 1: return { 0xe13b3bff };
			case 2: return { 0x79ce79ff };
			case 3: return { 0x65b9e7ff };
			case 4: return { 0xf1f1f1ff };
			case 5: return { 0xf0cb58ff };
			case 6: return { 0xc65859ff };
			case 7: return { 0xa175b4ff };
			case 8: return { 0xff81c8ff };
			case 9: return { 0xf7a580ff };
			case 10: return { 0xb6968bff };
			case 11: return { 0x92d0abff };
			case 12: return { 0x78adb3ff };
			case 13: return { 0xd5d3e8ff };
			case 14: return { 0x95859fff };
			case 15: return { 0x71c8c2ff };
			case 16: return { 0xd8c69eff };
			case 17: return { 0xec9359ff };
			case 18: return { 0x9ecdebff };
			case 19: return { 0xb6698dff };
			case 20: return { 0x95927fff };
			case 21: return { 0xaa7b67ff };
			case 22: return { 0xb4abacff };
			case 23: return { 0xe993a0ff };
			case 24: return { 0xbfd863ff };
			case 25: return { 0x17815dff };
			case 26: return { 0x80c7ffff };
			case 27: return { 0xaf45e7ff };
			case 28: return { 0xd0ac18ff };
			case 29: return { 0x4f6ab1ff };
			case 30: return { 0x35aabcff };
			case 31: return { 0xbda284ff };
			case 32: return { 0xcde2ffff };
			case 33: return { 0xf1f19bff };
			case 34: return { 0xee91a4ff };
			case 35: return { 0xf98f8fff };
			case 36: return { 0xfdf0aaff };
			case 37: return { 0xf1f1f1ff };
			case 38: return { 0x3776bdff };
			case 39: return { 0x9f9f9fff };
			case 40: return { 0x555555ff };
			case 41: return { 0xf29e9eff };
			case 42: return { 0x6db8d7ff };
			case 43: return { 0xb0eeafff };
			case 44: return { 0xffa75fff };
			case 45: return { 0xf1f1f1ff };
			case 46: return { 0xecf029ff };
			case 47: return { 0xff9a18ff };
			case 48: return { 0xf745a5ff };
			case 49: return { 0xe13b3bff };
			case 50: return { 0x8a6de3ff };
			case 51: return { 0xff8b5cff };
			case 52: return { 0x426d42ff };
			case 53: return { 0xb3ddf3ff };
			case 54: return { 0x3a647aff };
			case 55: return { 0xa0a0a0ff };
			case 56: return { 0x847232ff };
			case 57: return { 0x65b9e7ff };
			case 58: return { 0x4c4276ff };
			case 59: return { 0xe13b3bff };
			case 60: return { 0xf0cb58ff };
			case 61: return { 0xce3f99ff };
			case 62: return { 0xcfcfcfff };
			case 63: return { 0x286b9fff };
			case 64: return { 0xd87b1bff };
			case 65: return { 0x8e8393ff };
			case 66: return { 0xf0cb58ff };
			case 67: return { 0x65b9e7ff };
			case 68: return { 0x64b7e4ff };
			case 69: return { 0x79ce79ff };
			case 70: return { 0xf0cb58ff };
			case 71: return { 0xf0cb58ff };
			case 73: return { 0xf0cb58ff };
			case 74: return { 0x65b9e7ff };
			case 75: return { 0xe13b3bff };
			case 76: return { 0x782424ff };
			case 77: return { 0x65b9e7ff };
			case 78: return { 0x3a647aff };
			case 81: return { 0xf2a40cff };
			case 82: return { 0xa4ccaaff };
			case 83: return { 0xa854f2ff };
		}

		return { 255, 255, 255 };
	}
}