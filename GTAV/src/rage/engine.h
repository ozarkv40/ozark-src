#pragma once
#include "stdafx.h"
#include "rage/types/script_types.h"
#include "rage/types/generic_types.h"
#include "rage/types/network_types.h"

namespace rage::engine {
	rage::script::script_header* get_script_program(uint64_t table, int index);
	rage::types::store_module* get_store_module_extension(const char* extension);
	rage::network::net_game_player* get_net_game_player(int index);
	rage::network::net_game_player* get_host_net_game_player();
	rage::network::net_object* get_network_object(Entity entity);
	rage::types::grc_texture_dx11* get_sprite_texture(const char* dictionary, const char* asset);

	void get_streamed_script_index(int* index, const char* script_name);
	void request_streaming_file(int index);
	int register_streaming_file(const char* file_path, const char* asset_name);
	uint64_t construct_gfx_font(uint64_t allocation);
	void destruct(uint64_t allocation);
	int create_id_for_font(const char* asset_name);
	void add_font_lib(uint64_t allocation, int index);
	int get_network_object_owner(Entity entity);
	bool update_network_object_owner(Entity entity, int new_owner);
	uint64_t get_entity_address(Entity entity);
	Entity get_entity_handle(uint64_t address);
	bool process_basket_transaction(int category, int action, int destination, std::vector<rage::network::transaction> items);
	std::vector<uint32_t> get_hash_list_from_hash_table(uint32_t count, uint64_t table);
	bool is_basket_transaction_queue_busy();
	uint64_t thread_alloc(uint32_t size);
	rage::types::dictionary* setup_dictionary(rage::types::dictionary* dictionary, int count);
	uint32_t* setup_store_item(uint64_t store, uint32_t* out, uint32_t* dictionary_hash);
	bool is_valid_pool_slot(uint64_t pool, uint32_t slot);
	void add_dictionary_to_pool(uint64_t pool, uint32_t index, rage::types::dictionary* dictionary);
	void add_grc_texture_to_dictionary(rage::types::dictionary* dictionary, uint32_t hash, rage::types::grc_texture_dx11* texture);
	void send_weather_event(int id, rage::network::net_game_player* target = nullptr);
	int get_weather_id(const char* weather);
	void send_clock_event(rage::network::net_game_player* target = nullptr);
	void add_to_clock_time(int hour, int minute, int second);
	uint64_t get_model_info(uint32_t model);
	void set_vehicle_gravity(uint64_t address, float gravity);
	void vertex_begin(int mode, int count);
	void vertex_end();
	void vertex_add(float x, float y, float z, float nx, float ny, float mod, uint32_t color, float u, float v);
	uint64_t get_vehicle_paint(int cat);
	rage::network::sync_tree* get_sync_tree(eNetObjectTypes type);
	void parse_nodes(rage::network::sync_tree* tree, int type_bit, int flag, rage::bit_buffer* buffer, uint64_t log_interface);
	rage::network::net_object* get_network_object_from_network_id(uint64_t player_manager, uint16_t network_id, bool unk);
	void send_network_event_ack(uint64_t table, uint8_t* setup_buffer, rage::network::net_game_player* sender, rage::network::net_game_player* receiver, int event_index);
	void send_network_event_reply(uint64_t table, uint8_t* setup_buffer, rage::network::net_game_player* sender, rage::network::net_game_player* receiver, int event_index, int event_bitset);
	bool setup_give_control_event(uint8_t* data, rage::bit_buffer* buffer);
	void send_increment_stat_event(uint32_t hash, int value, rage::network::net_game_player* player);
	void set_gsinfo(rage::network::gs_session* gsinfo);
	bool get_session_info_from_gs(rage::network::gs_session* gs, const char* str);
	void send_session_info_request(rage::network::rockstar_identifier* targets, int count);
	uint64_t read_xml_string(uint64_t context, const char* name, int unk1, int unk2);
	const char* read_xml_attribute_string(rage::types::xml_node* node, const char* name, int unk1);
	void send_matchmaking_request();
	void send_friend_request(uint64_t rockstar_id);
	void migrate_script_host(rage::script::game_script_handler_network_component* comp, rage::network::net_game_player* player);
	void send_global_chat_message(uint64_t manager, int key, rage::network::global_msg_context* context);
	void handle_rotation_values_from_order(math::matrix<float>* matrix, math::vector3_<float>* rotation, int order);
	void invite_player(uint64_t rockstar_id);
	uint64_t sc_get_info(const char* identifier);
	const char* sc_get_string(const char* identifier);
	bool is_player_reported(rage::network::net_game_player* player, int category, int reason);
	void send_text_message_net_msg(rage::network::net_msg_identifier* target, rage::network::net_msg_text_message* identifier);
	void send_ragdoll_event(int player);
}