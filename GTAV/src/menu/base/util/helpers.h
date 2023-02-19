#pragma once
#include "stdafx.h"
#include "rage/types/base_types.h"
#include "global/ui_vars.h"
#include "rage/types/network_types.h"
#include "menu/base/util/player_manager.h"
#include "rage/types/bit_buffer.h"

static localization t_type_automobile("Automobile", true, true);
static localization t_type_bike("Bike", true, true);
static localization t_type_boat("Boat", true, true);
static localization t_type_door("Door", true, true);
static localization t_type_heli("Heli", true, true);
static localization t_type_object("Object", true, true);
static localization t_type_ped("Ped", true, true);
static localization t_type_pickup("Pickup", true, true);
static localization t_type_plane("Plane", true, true);
static localization t_type_submarine("Submarine", true, true);
static localization t_type_player("Player", true, true);
static localization t_type_trailer("Trailer", true, true);
static localization t_type_train("Train", true, true);
static localization t_clone("Clone", true, true);
static localization t_cage("Cage", true, true);
static localization t_attachment("Attachment", true, true);
static localization t_crash_outfit("Crash - Invalid Outfit", true, true);
static localization t_crash_nodes("Crash - Alignment", true, true);
static localization t_crash_tree("Crash - Sync Tree", true, true);
static localization t_crash_bad_node_count("Crash - Bad Node Count", true, true);
static localization t_crash_bad_model("Crash - Bad Model", true, true);
static localization t_crash_bad_type("Crash - Bad Type", true, true);
static localization t_crash_quantum("Crash - Quantum Paste", true, true);
static localization t_attachment_to(" to ", true, true);
static localization t_attachment_player("Player", true, true);
static localization t_attachment_vehicle("Vehicle", true, true);
static localization t_vehicle_owner_migration("Vehicle Owner Migration", true, true);
static localization t_ped_owner_migration("Ped Owner Migration", true, true);
static localization t_object_owner_migration("Object Owner Migration", true, true);

namespace menu::helpers {
	std::string get_net_obj_type_string(eNetObjectTypes type);
	std::string clean_name(std::string fixed);
	std::string get_location_from_id(int id);
	std::string get_vtable_name(uint64_t table);
	std::string get_vtable_name_full(uint64_t table);
	bool is_valid_net_player(rage::network::net_game_player* sender);
	bool is_rockstar_ip(uint32_t ip);
	bool is_crash_model(uint32_t model, eNetObjectTypes type);
	bool is_node_attached(rage::network::data_node* node, bool* veh, uint16_t* out_net_id = nullptr);
	bool get_node_creation(rage::network::data_node* node, rage::bit_buffer* buffer, uint32_t* hash, uint64_t* data);
	void get_node_position(rage::network::data_node* node, math::vector3<float>* out);
	void node_foreach(rage::network::data_node* node, std::function<void(std::string, rage::network::data_node*)> callback);
	void node_foreach_tree(rage::network::sync_tree* tree, std::function<void(std::string, rage::network::data_node*)> callback);
	void force_node_visible(rage::network::data_node* node);
	void detach_node(rage::network::data_node* node);
	void flag_modder(int id, menu::player::ePlayerReportReasons reason, bool blacklist = false);
	menu::player::player_context& get_player_from_peer(uint64_t peer);
	menu::player::player_context& get_player_from_ip(uint32_t ip);
	menu::player::player_context& get_player_from_rid(uint64_t rid);
	void trigger_script_event(std::vector<int> args, int count, Player bitset);
	Player get_net_msg_sender(uint64_t raw_buffer);
	std::string get_gs_type(int type);
	color_rgba get_color_from_blip(int id);

	template<typename T>
	std::pair<bool, T*> get_node_struct(std::unordered_map<std::string, rage::network::data_node*> nodes, std::string name) {
		if (nodes[name]) {
			if (nodes[name]->is_data_node()) {
				if (nodes[name]->m_data_node_common_operations) {
					if (nodes[name]->m_data_node_common_operations->m_data) {
						return { true, (T*)nodes[name]->m_data_node_common_operations->m_data };
					}
				}
			}
		}

		return { false, nullptr };
	}
}