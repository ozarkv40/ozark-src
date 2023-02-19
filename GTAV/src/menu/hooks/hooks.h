#pragma once
#include "stdafx.h"
#include "rage/types/network_types.h"
#include "rage/invoker/invoker.h"

namespace menu::hooks {
	extern uint64_t g_rcs_caller_functions[5];

	void wait(rage::invoker::native_context*);
	void stat_get_int(rage::invoker::native_context*);
	void set_current_ped_weapon(rage::invoker::native_context*);
	void disable_control_action(rage::invoker::native_context*);
	void set_warning_message_2(rage::invoker::native_context*);
	void terminate_this_thread(rage::invoker::native_context*);

	// anti-cheat start
	void add_metric_to_json_array(uint32_t ecx, uint64_t rdx, uint64_t r8, rage::network::metric* metric);
	inline decltype(&add_metric_to_json_array) add_metric_to_json_array_t;

	void rockstar_integrity(uint64_t rcx);
	inline decltype(&rockstar_integrity) rockstar_integrity_t;

	void send_network_event(uint64_t table, uint64_t event);
	inline decltype(&send_network_event) send_network_event_t;

	bool process_transaction_id(uint64_t manager, int id, uint64_t table);
	inline decltype(&process_transaction_id) process_transaction_id_t;

	BOOL get_thread_context(HANDLE thread, LPCONTEXT context);
	inline decltype(&get_thread_context) get_thread_context_t;
	// anti-cheat end

	void pack_clone_create(uint64_t _this, rage::network::net_object* net_obj, rage::network::net_game_player* player, uint64_t sync_data);
	inline decltype(&pack_clone_create) pack_clone_create_t;

	bool pack_clone_sync(uint64_t _this, rage::network::net_object* net_obj, rage::network::net_game_player* net_game_player);
	inline decltype(&pack_clone_sync) pack_clone_sync_t;

	void* get_font_id(uint64_t font, int id);
	inline decltype(&get_font_id) get_font_id_t;

	uint64_t format_engine_string(uint64_t rcx, uint64_t rdx, uint32_t r8d, const char* r9, uint32_t stack);
	inline decltype(&format_engine_string) format_engine_string_t;

	int get_engine_string_line_count(uint64_t rcx, const char* rdx, float xmm2, uint64_t r9, bool stack);
	inline decltype(&get_engine_string_line_count) get_engine_string_line_count_t;

	FARPROC get_proc_address(HMODULE mod, LPCSTR name);
	inline decltype(&get_proc_address) get_proc_address_t;

	bool shoot_bullet(rage::types::weapon* weapon, uint64_t shooter_info, math::vector3_<float>* start_pos, math::vector3_<float>* end_pos);
	inline decltype(&shoot_bullet) shoot_bullet_t;

	bool shoot_projectile(rage::types::weapon* weapon, uint64_t shooter_info, math::vector3_<float>* start_pos, math::vector3_<float>* end_pos);
	inline decltype(&shoot_projectile) shoot_projectile_t;

	bool render_script_textures(uint64_t table, uint32_t edx, uint32_t r8d);
	inline decltype(&render_script_textures) render_script_textures_t;

	uint64_t get_next_grc_texture(uint64_t table);
	inline decltype(&get_next_grc_texture) get_next_grc_texture_t;

	void reset_script_render_params();
	inline decltype(&reset_script_render_params) reset_script_render_params_t;

	int get_next_marker_texture_index(rage::types::marker_table* table);
	inline decltype(&get_next_marker_texture_index) get_next_marker_texture_index_t;

	void translate_marker_to_screen(rage::types::marker_table* table);
	inline decltype(&translate_marker_to_screen) translate_marker_to_screen_t;

	void render_markers_to_screen(rage::types::marker_table* table);
	inline decltype(&render_markers_to_screen) render_markers_to_screen_t;

	int add_marker_to_table(rage::types::marker_table* table, uint64_t marker);
	inline decltype(&add_marker_to_table) add_marker_to_table_t;

	bool read_unsigned_int_from_buffer(rage::bit_buffer_sync_instance* _this, uint32_t* output, int count);
	inline decltype(&read_unsigned_int_from_buffer) read_unsigned_int_from_buffer_t;

	bool read_unsigned_short_from_buffer(rage::bit_buffer_sync_instance* _this, uint16_t* output, int count);
	inline decltype(&read_unsigned_short_from_buffer) read_unsigned_short_from_buffer_t;

	bool read_unsigned_char_from_buffer(rage::bit_buffer_sync_instance* _this, uint8_t* output, int count);
	inline decltype(&read_unsigned_char_from_buffer) read_unsigned_char_from_buffer_t;

	bool read_int_from_buffer(rage::bit_buffer_sync_instance* _this, int* output, int count);
	inline decltype(&read_int_from_buffer) read_int_from_buffer_t;

	bool read_short_from_buffer(rage::bit_buffer_sync_instance* _this, short* output, int count);
	inline decltype(&read_short_from_buffer) read_short_from_buffer_t;

	bool read_char_from_buffer(rage::bit_buffer_sync_instance* _this, char* output, int count);
	inline decltype(&read_char_from_buffer) read_char_from_buffer_t;

	bool read_bool_from_buffer(rage::bit_buffer_sync_instance* _this, bool* output);
	inline decltype(&read_bool_from_buffer) read_bool_from_buffer_t;

	bool read_long_long_from_buffer(rage::bit_buffer_sync_instance* _this, long long* output, int count);
	inline decltype(&read_long_long_from_buffer) read_long_long_from_buffer_t;

	bool read_unsigned_long_long_from_buffer(rage::bit_buffer_sync_instance* _this, uint64_t* output, int count);
	inline decltype(&read_unsigned_long_long_from_buffer) read_unsigned_long_long_from_buffer_t;

	bool read_float_from_buffer(rage::bit_buffer_sync_instance* _this, float* output, float mod, int count);
	inline decltype(&read_float_from_buffer) read_float_from_buffer_t;

	bool read_unsigned_float_from_buffer(rage::bit_buffer_sync_instance* _this, float* output, float mod, int count);
	inline decltype(&read_unsigned_float_from_buffer) read_unsigned_float_from_buffer_t;

	bool read_network_id_from_buffer(rage::bit_buffer_sync_instance* _this, short* output);
	inline decltype(&read_network_id_from_buffer) read_network_id_from_buffer_t;

	bool read_array_from_buffer(rage::bit_buffer_sync_instance* _this, int* output, int count, int unk);
	inline decltype(&read_array_from_buffer) read_array_from_buffer_t;

	bool read_string_from_buffer(rage::bit_buffer_sync_instance* _this, char* output, int length);
	inline decltype(&read_string_from_buffer) read_string_from_buffer_t;

	bool write_unsigned_int_from_buffer(rage::bit_buffer_sync_instance* _this, uint32_t* output, int count);
	inline decltype(&write_unsigned_int_from_buffer) write_unsigned_int_from_buffer_t;

	bool write_unsigned_short_from_buffer(rage::bit_buffer_sync_instance* _this, uint16_t* output, int count);
	inline decltype(&write_unsigned_short_from_buffer) write_unsigned_short_from_buffer_t;

	bool write_unsigned_char_from_buffer(rage::bit_buffer_sync_instance* _this, uint8_t* output, int count);
	inline decltype(&write_unsigned_char_from_buffer) write_unsigned_char_from_buffer_t;

	bool write_int_from_buffer(rage::bit_buffer_sync_instance* _this, int* output, int count);
	inline decltype(&write_int_from_buffer) write_int_from_buffer_t;

	bool write_short_from_buffer(rage::bit_buffer_sync_instance* _this, short* output, int count);
	inline decltype(&write_short_from_buffer) write_short_from_buffer_t;

	bool write_char_from_buffer(rage::bit_buffer_sync_instance* _this, char* output, int count);
	inline decltype(&write_char_from_buffer) write_char_from_buffer_t;

	bool write_bool_from_buffer(rage::bit_buffer_sync_instance* _this, bool* output);
	inline decltype(&write_bool_from_buffer) write_bool_from_buffer_t;

	bool write_long_long_from_buffer(rage::bit_buffer_sync_instance* _this, long long* output, int count);
	inline decltype(&write_long_long_from_buffer) write_long_long_from_buffer_t;

	bool write_unsigned_long_long_from_buffer(rage::bit_buffer_sync_instance* _this, uint64_t* output, int count);
	inline decltype(&write_unsigned_long_long_from_buffer) write_unsigned_long_long_from_buffer_t;

	bool write_float_from_buffer(rage::bit_buffer_sync_instance* _this, float* output, float mod, int count);
	inline decltype(&write_float_from_buffer) write_float_from_buffer_t;

	bool write_unsigned_float_from_buffer(rage::bit_buffer_sync_instance* _this, float* output, float mod, int count);
	inline decltype(&write_unsigned_float_from_buffer) write_unsigned_float_from_buffer_t;

	bool write_network_id_from_buffer(rage::bit_buffer_sync_instance* _this, short* output);
	inline decltype(&write_network_id_from_buffer) write_network_id_from_buffer_t;

	bool write_array_from_buffer(rage::bit_buffer_sync_instance* _this, int* output, int count, int unk);
	inline decltype(&write_array_from_buffer) write_array_from_buffer_t;

	bool write_string_from_buffer(rage::bit_buffer_sync_instance* _this, char* output, int length);
	inline decltype(&write_string_from_buffer) write_string_from_buffer_t;

	uint64_t construct_in_frame(uint64_t in_frame, uint64_t rdx, uint64_t r8, uint64_t r9d, uint64_t s_rbp, uint64_t s_rsi, uint16_t s_r15w, uint64_t s_rax);
	inline decltype(&construct_in_frame) construct_in_frame_t;

	uint64_t destruct_in_frame(uint64_t in_frame, uint8_t dl);
	inline decltype(&destruct_in_frame) destruct_in_frame_t;

	bool receive_clone_create(uint64_t _this, rage::network::net_game_player* sender, uint64_t r8, eNetObjectTypes type, uint16_t network_id, uint16_t flag, rage::bit_buffer* bit_buffer, uint32_t timestamp);
	inline decltype(&receive_clone_create) receive_clone_create_t;

	int receive_clone_sync(uint64_t _this, rage::network::net_game_player* sender, uint64_t r8, eNetObjectTypes type, uint16_t network_id, rage::bit_buffer* bit_buffer, uint16_t sequence_id, int timestamp);
	inline decltype(&receive_clone_sync) receive_clone_sync_t;

	bool receive_clone_sync_caller(uint64_t _this, uint64_t rdx);
	inline decltype(&receive_clone_sync_caller) receive_clone_sync_caller_t;

	bool receive_clone_remove(uint64_t _this, rage::network::net_game_player* sender, uint64_t r8, uint16_t network_id, uint64_t unk);
	inline decltype(&receive_clone_remove) receive_clone_remove_t;

	bool receive_broadcast(uint64_t _this, rage::network::net_game_player* sender, rage::bit_buffer* bit_buffer, uint32_t bit_count, uint16_t network_id);
	inline decltype(&receive_broadcast) receive_broadcast_t;

	void receive_network_event(uint64_t _this, rage::network::net_game_player* sender, rage::network::net_game_player* receiver, uint16_t event_id, int event_index, int event_bitset, uint32_t bit_buffer_size, rage::bit_buffer* bit_buffer);
	inline decltype(&receive_network_event) receive_network_event_t;

	bool read_chat_message(rage::network::global_msg_context* context, rage::bit_buffer* bit_buffer);
	inline decltype(&read_chat_message) read_chat_message_t;

	bool receive_text_message(rage::network::net_msg_text_message* identifier, rage::bit_buffer* bit_buffer);
	inline decltype(&receive_text_message) receive_text_message_t;

	bool receive_session_info(uint64_t rcx);
	inline decltype(&receive_session_info) receive_session_info_t;

	bool receive_presence_event(uint64_t rcx, uint64_t rdx, const char** payload, uint64_t r9);
	inline decltype(&receive_presence_event) receive_presence_event_t;

	bool receive_session_join_request(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9, int stack);
	inline decltype(&receive_session_join_request) receive_session_join_request_t;

	uint64_t process_game_event(uint64_t _this);
	inline decltype(&process_game_event) process_game_event_t;

	uint64_t handle_desync_negotiation(uint64_t rcx, uint64_t rdx, uint64_t r8);
	inline decltype(&handle_desync_negotiation) handle_desync_negotiation_t;

	bool host_handle_desync_request(uint64_t rcx, uint64_t rdx, rage::network::list_kick_peers* peers, uint32_t r9d);
	inline decltype(&host_handle_desync_request) host_handle_desync_request_t;

	bool read_blacklist_message(uint64_t rcx, uint64_t rdx);
	inline decltype(&read_blacklist_message) read_blacklist_message_t;

	bool read_new_script_host_message(uint64_t rcx, uint64_t rdx);
	inline decltype(&read_new_script_host_message) read_new_script_host_message_t;

	void update_player_script_status(rage::script::game_script_handler_network_component* component, uint64_t rdx, uint64_t r8);
	inline decltype(&update_player_script_status) update_player_script_status_t;

	void process_relay_usage(uint8_t cl, uint64_t rdx, rage::network::event_added_gamer* gamer, uint32_t r9d, uint64_t stack);
	inline decltype(&process_relay_usage) process_relay_usage_t;

	void apply_player_physical_index(uint64_t network_player_manager, rage::network::net_game_player* player, uint8_t slot);
	inline decltype(&apply_player_physical_index) apply_player_physical_index_t;

	bool write_player_game_state_data_node(uint64_t rcx, uint64_t rdx);
	inline decltype(&write_player_game_state_data_node) write_player_game_state_data_node_t;

	void write_ped_health_data_node(uint64_t rcx, uint64_t rdx);
	inline decltype(&write_ped_health_data_node) write_ped_health_data_node_t;

	void write_gs_item(int index, rage::network::gs_session* data, const char* type);
	inline decltype(&write_gs_item) write_gs_item_t;

	bool read_matchmaking_response(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&read_matchmaking_response) read_matchmaking_response_t;

	bool write_matchmaking_request(uint64_t rcx, uint32_t rs_index, uint32_t available_slots, uint64_t filter_info, uint32_t max_results, uint64_t stack_20, uint64_t stack_18);
	inline decltype(&write_matchmaking_request) write_matchmaking_request_t;

	bool write_encrypted_string_to_request(uint64_t rcx, const char* name, char* value, bool encrypted, uint64_t stack_3C8, uint64_t stack_3C0);
	inline decltype(&write_encrypted_string_to_request) write_encrypted_string_to_request_t;

	void send_global_chat_message(uint64_t manager, int key, rage::network::global_msg_context* context, uint64_t unk1, uint64_t unk2);
	inline decltype(&send_global_chat_message) send_global_chat_message_t;

	const char* get_gxt_label(uint64_t table, const char* label);
	inline decltype(&get_gxt_label) get_gxt_label_t;

	const char* get_gxt_label_from_hash(uint64_t table, uint32_t label_hash);
	inline decltype(&get_gxt_label_from_hash) get_gxt_label_from_hash_t;

	int check_chat_profanity(uint64_t rcx, uint64_t rdx, uint64_t r8);
	inline decltype(&check_chat_profanity) check_chat_profanity_t;

	int check_string_profanity(uint64_t rcx, uint64_t rdx, uint64_t r8);
	inline decltype(&check_string_profanity) check_string_profanity_t;

	bool send_join_request_message(rage::network::join_request* rcx, uint64_t rdx, uint32_t r8d, uint64_t r9);
	inline decltype(&send_join_request_message) send_join_request_message_t;

	bool get_peer_address(uint64_t* peer);
	inline decltype(&get_peer_address) get_peer_address_t;

	bool send_add_gamer_to_session(uint64_t rcx, rage::network::network_gamer_cmd* gamer);
	inline decltype(&send_add_gamer_to_session) send_add_gamer_to_session_t;

	bool has_ros_privilege(uint64_t ros_table, int privilege);
	inline decltype(&has_ros_privilege) has_ros_privilege_t;

	bool compress_data_node(rage::network::data_node* node, uint32_t flag1, uint64_t flag2, rage::network::net_object* object, rage::bit_buffer* buffer, uint32_t bitsize, uint64_t unk1, bool unk2, uint64_t unk3);
	inline decltype(&compress_data_node) compress_data_node_t;

	bool compress_data_node2(rage::network::data_node* node, rage::network::net_object* object);
	inline decltype(&compress_data_node2) compress_data_node2_t;

	bool write_player_gamer_data_node(rage::network::player_gamer_data_node* node, rage::bit_buffer_sync_instance* buffer);
	inline decltype(&write_player_gamer_data_node) write_player_gamer_data_node_t;

	void apply_weather_meta(uint64_t meta);
	inline decltype(&apply_weather_meta) apply_weather_meta_t;

	bool read_kick_player_message(uint64_t rcx, uint64_t rdx);
	inline decltype(&read_kick_player_message) read_kick_player_message_t;

	bool write_net_msg_identifier(rage::bit_buffer* buffer, uint64_t rdx, int r8d);
	inline decltype(&write_net_msg_identifier) write_net_msg_identifier_t;

	bool write_ulonglong_to_bit_buffer(rage::bit_buffer* buffer, uint64_t rdx, int r8);
	inline decltype(&write_ulonglong_to_bit_buffer) write_ulonglong_to_bit_buffer_t;

	// crash start
	int apply_vehicle_data__crash(rage::network::net_object* object, uint64_t node_data);
	inline decltype(&apply_vehicle_data__crash) apply_vehicle_data__crash_t;

	eThreadState tick_script_thread__crash(rage::script::gta_thread* _this, uint32_t instruction_count);
	inline decltype(&tick_script_thread__crash) tick_script_thread__crash_t;

	uint64_t attach_trailer__crash(uint64_t trailer, uint16_t flag);
	inline decltype(&attach_trailer__crash) attach_trailer__crash_t;

	uint64_t attach_trailer_audio__crash(uint64_t audio_entity, uint64_t rdx);
	inline decltype(&attach_trailer_audio__crash) attach_trailer_audio__crash_t;

	// resource_streamed_script* load_script_resource__crash(resource_streamed_script_handler* handler, uint16_t resource_id);
	// inline decltype(&load_script_resource__crash) load_script_resource__crash_t;

	void destruct_script_handler__crash(uint64_t _this);
	inline decltype(&destruct_script_handler__crash) destruct_script_handler__crash_t;

	bool shit_scripts2__crash(uint64_t rcx, uint16_t dx, uint32_t r8d, bool r9b);
	inline decltype(&shit_scripts2__crash) shit_scripts2__crash_t;

	uint64_t shit_scripts__crash(uint64_t rcx, uint64_t rdx);
	inline decltype(&shit_scripts__crash) shit_scripts__crash_t;

	uint64_t rid0__crash(uint64_t rcx, uint64_t rdx);
	inline decltype(&rid0__crash) rid0__crash_t;

	uint64_t sub_140AD8424__crash(uint64_t rcx, int edx, uint32_t r8d); // previously sub_140AFB59C
	inline decltype(&sub_140AD8424__crash) sub_140AD8424__crash_t;
	// crash end

	// arxan start
	void arxan_integrity_start1(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_start1) arxan_integrity_start1_t;

	void arxan_integrity_end1(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_end1) arxan_integrity_end1_t;

	void arxan_integrity_start2(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_start2) arxan_integrity_start2_t;

	void arxan_integrity_end2(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_end2) arxan_integrity_end2_t;

	void arxan_integrity_start3(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_start3) arxan_integrity_start3_t;

	void arxan_integrity_end3(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_end3) arxan_integrity_end3_t;

	void arxan_integrity_start4(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_start4) arxan_integrity_start4_t;

	void arxan_integrity_end4(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_end4) arxan_integrity_end4_t;

	void arxan_integrity_start5(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_start5) arxan_integrity_start5_t;

	void arxan_integrity_end5(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);
	inline decltype(&arxan_integrity_end5) arxan_integrity_end5_t;
	// arxan end

	bool spoofing();
	bool bypass();
	bool globals();
	bool globals_in_game();
	bool hooks();
}