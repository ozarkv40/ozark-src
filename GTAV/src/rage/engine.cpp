#include "engine.h"
#include "global/vars.h"
#include "util/caller.h"
#include "invoker/natives.h"
#include "menu/base/util/player_manager.h"

namespace rage::engine {
	rage::script::script_header* get_script_program(uint64_t table, int index) {
		return caller::call<rage::script::script_header*>(*(uint64_t*)(table + 0x68), global::vars::g_game_streamed_scripts, index);
	}

	rage::types::store_module* get_store_module_extension(const char* extension) {
		return caller::call<rage::types::store_module*>(global::vars::g_get_store_module_extension, &global::vars::g_store_manager->m_module, extension);
	}

	rage::network::net_game_player* get_net_game_player(int index) {
		return caller::call<rage::network::net_game_player*>(global::vars::g_get_net_game_player_from_index, index);
	}

	rage::network::net_game_player* get_host_net_game_player() {
		return caller::call<rage::network::net_game_player*>(global::vars::g_get_host_net_game_player);
	}

	void get_streamed_script_index(int* index, const char* script_name) {
		caller::call<void>(global::vars::g_get_streamed_script, global::vars::g_game_streamed_scripts, index, script_name);
	}

	void request_streaming_file(int index) {
		caller::call<void>(global::vars::g_request_streaming_file, global::vars::g_store_manager, index, 7);
	}

	int register_streaming_file(const char* file_path, const char* asset_name) {
		int index = -1;
		caller::call<void>(global::vars::g_register_streaming_file, &index, file_path, true, asset_name, false);

		return index;
	}

	uint64_t construct_gfx_font(uint64_t allocation) {
		return caller::call<uint64_t>(global::vars::g_construct_gfx_font, allocation);
	}

	void destruct(uint64_t allocation) {
		caller::call<void>(global::vars::g_destruct, allocation);
	}

	int create_id_for_font(const char* asset_name) {
		static uint8_t junk[2][0x100];
		memset(junk, 0, sizeof(junk));

		return caller::call<int>(global::vars::g_create_id_for_font, asset_name, junk[0], junk[1], 0, -1, -1, 1, 2, 0, 0);
	}

	void add_font_lib(uint64_t allocation, int index) {
		rage::types::store_module* store = get_store_module_extension("gfx");
		caller::call<void>(global::vars::g_add_font_lib, store, allocation, index - store->m_base_index);
	}

	rage::network::net_object* get_network_object(Entity entity) {
		uint64_t address = get_entity_address(entity);
		if (address) {
			return *(rage::network::net_object**)(address + 0xD0);
		}

		return 0;
	}

	int get_network_object_owner(Entity entity) {
		rage::network::net_object* object = get_network_object(entity);
		if (object) {
			return object->m_owner;
		}

		return 0;
	}

	bool update_network_object_owner(Entity entity, int new_owner) {
		rage::network::net_object* object = get_network_object(entity);
		if (object) {
			return caller::call<bool>(global::vars::g_update_net_object_owner, *(uint64_t*)global::vars::g_network_object_manager, object, get_net_game_player(new_owner), 0);
		}

		return false;
	}

	uint64_t get_entity_address(Entity entity) {
		if (entity <= 0) return 0;
		return caller::call<uint64_t>(global::vars::g_get_entity_address, entity);
	}

	Entity get_entity_handle(uint64_t address) {
		return caller::call<Entity>(global::vars::g_get_entity_handle_from_address, address, 0);
	}

	bool process_basket_transaction(int category, int action, int destination, std::vector<rage::network::transaction> items) {
		if (native::network_shop_basket_end())
			_i<int>(0xFA336E7F40C0A0D0);

#undef max
		int transaction_id = std::numeric_limits<int>::max();

		bool result = caller::call<bool>(global::vars::g_add_basket_to_queue, global::vars::g_net_shop_queue, &transaction_id, category, action, destination);
		if (!result || !transaction_id) {
			return false;
		}

		for (std::size_t i = 0; i < items.size(); i++) {
			rage::network::transaction item = items[i];
			caller::call<void>(global::vars::g_add_item_to_basket, global::vars::g_net_shop_queue, (int*)&item);
		}

		if (!caller::call<bool>(global::vars::g_process_transaction_id, global::vars::g_net_shop_queue, transaction_id, 1337)) {
			return false;
		}

		return true;
	}

	std::vector<uint32_t> get_hash_list_from_hash_table(uint32_t count, uint64_t table) {
		std::vector<uint32_t> hashes;

		if (count && table) {
			uint64_t* ptr = (uint64_t*)table;

			for (uint32_t i = 0; i < count; i++) {
				if (ptr[i]) {
					uint32_t hash = *(uint32_t*)(ptr[i] + 0x10);

					if (hash) {
						hashes.push_back(hash);
					}
				}
			}
		}

		return hashes;
	}

	bool is_basket_transaction_queue_busy() {
		return global::vars::g_net_shop_queue->m_is_busy1 || global::vars::g_net_shop_queue->m_is_busy2 || global::vars::g_net_shop_queue->m_is_busy3;
	}

	uint64_t thread_alloc(uint32_t size) {
		return caller::call<uint64_t>(global::vars::g_thread_alloc, size);
	}

	rage::types::dictionary* setup_dictionary(rage::types::dictionary* dictionary, int count) {
		return caller::call<rage::types::dictionary*>(global::vars::g_setup_dictionary, dictionary, count);
	}

	uint32_t* setup_store_item(uint64_t store, uint32_t* out, uint32_t* dictionary_hash) {
		return caller::call<uint32_t*>(global::vars::g_setup_store_item, store, out, dictionary_hash);
	}

	bool is_valid_pool_slot(uint64_t pool, uint32_t slot) {
		return caller::call<bool>(global::vars::g_is_valid_pool_slot, pool, slot);
	}

	void add_dictionary_to_pool(uint64_t pool, uint32_t index, rage::types::dictionary* dictionary) {
		caller::call<void>(global::vars::g_add_dictionary_to_pool, pool, index, dictionary);
	}

	void add_grc_texture_to_dictionary(rage::types::dictionary* dictionary, uint32_t hash, rage::types::grc_texture_dx11* texture) {
		caller::call<void>(global::vars::g_add_grc_texture_to_dictionary, dictionary, hash, texture);
	}

	rage::types::grc_texture_dx11* get_sprite_texture(const char* dictionary, const char* asset) {
		return caller::call<rage::types::grc_texture_dx11*>(global::vars::g_get_sprite_texture, dictionary, asset);
	}

	void send_weather_event(int id, rage::network::net_game_player* target) {
		caller::call<int>(global::vars::g_send_weather_update, true, id, 0, target);
	}

	int get_weather_id(const char* weather) {
		return caller::call<int>(global::vars::g_get_weather_id, global::vars::g_weather_table, weather);
	}

	void send_clock_event(rage::network::net_game_player* target) {
		caller::call<void>(global::vars::g_sync_clock_time, 0, target);
	}

	void add_to_clock_time(int hour, int minute, int second) {
		caller::call<void>(global::vars::g_add_to_clock_time, hour, minute, second);
	}

	uint64_t get_model_info(uint32_t model) {
		int offset = 0xFFFF;
		return caller::call<uint64_t>(global::vars::g_get_model_info, model, &offset);
	}

	void set_vehicle_gravity(uint64_t address, float gravity) {
		caller::call<void>(global::vars::g_set_vehicle_gravity, address, gravity);
	}

	void vertex_begin(int mode, int count) {
		caller::call<void>(global::vars::g_vertex_begin, mode, count);
	}

	void vertex_end() {
		caller::call<void>(global::vars::g_vertex_end);
	}

	void vertex_add(float x, float y, float z, float nx, float ny, float mod, uint32_t color, float u, float v) {
		caller::call<void>(global::vars::g_vertex_add, x, y, z, nx, ny, mod, color, u, v);
	}

	uint64_t get_vehicle_paint(int cat) {
		return caller::call<uint64_t>(global::vars::g_get_vehicle_paint_array, cat, true);
	}

	rage::network::sync_tree* get_sync_tree(eNetObjectTypes type) {
		return caller::call<rage::network::sync_tree*>(global::vars::g_get_sync_tree_from_clone_type, 0, type);
	}

	void parse_nodes(rage::network::sync_tree* tree, int type_bit, int flag, rage::bit_buffer* buffer, uint64_t log_interface) {
		caller::call<void>(global::vars::g_parse_nodes, tree, type_bit, flag, buffer, log_interface);
	}

	rage::network::net_object* get_network_object_from_network_id(uint64_t player_manager, uint16_t network_id, bool unk) {
		return caller::call<rage::network::net_object*>(global::vars::g_get_network_object_from_network_id, player_manager, network_id, unk);
	}

	void send_network_event_ack(uint64_t table, uint8_t* setup_buffer, rage::network::net_game_player* sender, rage::network::net_game_player* receiver, int event_index) {
		caller::call<void>(global::vars::g_send_network_event_ack, table, setup_buffer, sender, receiver, event_index);
	}

	void send_network_event_reply(uint64_t table, uint8_t* setup_buffer, rage::network::net_game_player* sender, rage::network::net_game_player* receiver, int event_index, int event_bitset) {
		caller::call<void>(global::vars::g_send_network_event_reply, table, setup_buffer, sender, receiver, event_index, event_bitset);
	}

	bool setup_give_control_event(uint8_t* data, rage::bit_buffer* buffer) {
		return caller::call<bool>(global::vars::g_setup_give_control_event, data, buffer);
	}

	void send_increment_stat_event(uint32_t hash, int value, rage::network::net_game_player* player) {
		caller::call<void>(global::vars::g_send_increment_stat_event, hash, value, player);
	}

	void set_gsinfo(rage::network::gs_session* gsinfo) {
		caller::call<void>(global::vars::g_write_gs_item, 0, gsinfo, "gsinfo");
	}

	bool get_session_info_from_gs(rage::network::gs_session* gs, const char* str) {
		return caller::call<bool>(global::vars::g_get_session_info_from_gs, gs, str, 0, 0);
	}

	void send_session_info_request(rage::network::rockstar_identifier* targets, int count) {
		caller::call<void>(global::vars::g_send_session_info_request, targets, count);
	}

	uint64_t read_xml_string(uint64_t context, const char* name, int unk1, int unk2) {
		return caller::call<uint64_t>(global::vars::g_read_xml_string, context, name, unk1, unk2);
	}

	const char* read_xml_attribute_string(rage::types::xml_node* node, const char* name, int unk1) {
		return caller::call<const char*>(global::vars::g_read_xml_node_string, node, name, unk1);
	}

	void send_matchmaking_request() {
		caller::call<void>(global::vars::g_send_matchmaking_request, global::vars::g_network_base_config, 1, 1, 1, 1);
	}

	void send_friend_request(uint64_t rockstar_id) {
		rage::network::net_msg_identifier id;
		id.m_rockstar_id = rockstar_id;
		id.m_type = 3;

		caller::call<void>(global::vars::g_send_friend_request, &id, "");
	}

	void migrate_script_host(rage::script::game_script_handler_network_component* comp, rage::network::net_game_player* player) {
		caller::call<void>(global::vars::g_migrate_script_host, comp, player);
	}

	void send_global_chat_message(uint64_t manager, int key, rage::network::global_msg_context* context) {
		uint16_t out_id = 0;
		caller::call<void>(global::vars::g_send_global_chat_message, manager, key, context, 1, &out_id);
	}

	void handle_rotation_values_from_order(math::matrix<float>* matrix, math::vector3_<float>* rotation, int order) {
		caller::call<void>(global::vars::g_handle_rotation_values_from_order, matrix, rotation, order);
	}

	void invite_player(uint64_t rockstar_id) {
		rage::network::net_msg_identifier identifier;
		memset(&identifier, 0, sizeof(identifier));

		identifier.m_rockstar_id = rockstar_id;
		identifier.m_type = 3;

		caller::call<void>(global::vars::g_invite_player, global::vars::g_network_base_config, &identifier, 1, "Invite", "join me pwease", 0);
	}

	uint64_t sc_get_info(const char* identifier) {
		if (global::vars::g_social_club_game_info_table && global::vars::g_social_club_get_game_info_table) {
			int index = caller::call<int>(global::vars::g_social_club_get_game_info_table, identifier, global::vars::g_social_club_game_info_table + 0x20, *(uint32_t*)(global::vars::g_social_club_game_info_table + 0x14));
			if (index >= 0) {
				return (((global::vars::g_social_club_game_info_table + 0x20) + (index * 0x148)));
			}
		}

		return 0;
	}

	const char* sc_get_string(const char* identifier) {
		uint64_t table = sc_get_info(identifier);
		if (table) {
			const char* name = (char*)(table + 0x40);
			if (name && *name != 0xff) {
				return name;
			}
		}

		return nullptr;
	}

	bool is_player_reported(rage::network::net_game_player* player, int category, int reason) {
		return caller::call<bool>(global::vars::g_is_reported_for_reason, player, category, reason);
	}

	void send_text_message_net_msg(rage::network::net_msg_identifier* target, rage::network::net_msg_text_message* identifier) {
		caller::call<int>(global::vars::g_send_text_message_net_msg, global::vars::g_network_base_config, target, identifier);
	}

	void send_ragdoll_event(int player) {
		if (menu::player::get_player(player).m_ped_ptr) {
			if (menu::player::get_player(player).m_ped_ptr->get_net_obj()) {
				caller::call<int>(global::vars::g_send_ragdoll_event, menu::player::get_player(player).m_ped_ptr->get_net_obj()->m_network_id);
			}
		}
	}
}