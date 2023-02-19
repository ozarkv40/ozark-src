#pragma once
#include "stdafx.h"
#include "rage/types/base_types.h"
#include "rage/types/generic_types.h"
#include "rage/types/network_types.h"
#include "rage/types/invoker_types.h"
#include "rage/types/script_types.h"
#include "rage/types/ros_types.h"
#include "util/localization.h"
#include <vector>
#include <queue>

#pragma pack(push)
#pragma pack(1)
struct protection_context {
	int m_var = 0;
	localization m_tooltip;

	bool block() {
		return m_var == 2 || m_var == 3 || m_var == 5 || m_var == 7;
	}

	bool notify() {
		return m_var == 1 || m_var == 3 || m_var == 6 || m_var == 7;
	}

	bool redirect() {
		return m_var >= 4;
	}

	bool enabled() {
		return m_var > 0;
	}
};

struct join_timeout_fix {
	Player m_id;
	uint32_t m_script_hash;
	int m_retry_count;
};

struct gs_info_request {
	bool m_finished = false;
	int m_type; // 1 = join blocking, 2 = rid joiner, 69 = ozark
	uint64_t m_rockstar_id;
	uint32_t m_expiry;
	std::function<void(std::string, uint64_t)> m_callback;
};

namespace global::vars {
	extern uint64_t g_ros_init_crypto;
	extern uint64_t g_ros_read_stats_by_gamer;
	extern uint64_t g_ros_download_player_image;
	extern rage::ros::crypto_state g_crypto_state;
	extern rage::ros::ros_state g_primary_ros_state;

	extern bool g_arxan_called[10];
	extern bool g_chinese;
	extern bool g_unloading;
	extern bool g_unloading_queue;
	extern bool g_freemode_terminated;
	extern bool g_reapply_weapons;
	extern HMODULE g_module_handle;
	extern std::pair<uint64_t, uint32_t> g_cheat_address;
	extern std::pair<uint64_t, uint32_t> g_game_address;
	extern HWND g_window;
	extern std::vector<localization*> g_localization_table;
	extern bool g_steam;
	extern bool g_reload_weapons;
	extern std::pair<float, std::string> g_selected_metric_system;
	extern std::unordered_map<uint64_t, std::pair<bool, int>> g_online_rockstar_ids;
	extern std::vector<uint64_t> g_online_rockstar_ids_queue;
	extern std::vector<relay_usage> g_relay_usage;
	extern std::queue<uint32_t> g_geo_queue;
	extern std::unordered_map<uint32_t, geo_ip> g_geo;
	extern rage::types::dictionary* g_custom_dictionary;
	extern rage::types::dictionary* g_player_img_dictionary;
	extern math::vector2<int> g_resolution;
	extern math::vector2<int> g_desktop_resolution;
	extern uint64_t g_texture_bypass;
	extern uint64_t g_marker_bypass;
	extern std::unordered_map<std::string, alignment_test> g_alignment_tests;
	extern std::vector<patches> g_patches;
	extern std::unordered_map<std::string, patches> g_hack_patches;
	extern std::vector<std::pair<uint64_t, int>> g_return_address_node_iterations;
	extern std::unordered_map<uint64_t, uint64_t> g_desyncs_host;
	extern std::unordered_map<Player, desyncs> g_desyncs;
	extern std::vector<join_timeout_fix> g_join_timeout_fix;
	extern std::vector<std::pair<uint64_t, uint64_t>> g_host_desync_logs;
	extern std::unordered_map<int, uint32_t> g_last_synced_player_models;
	extern std::vector<gs_info_request> g_gs_info_requests;
	extern std::unordered_map<uint64_t, uint32_t> g_spoofed_data_join_requests;
	extern std::unordered_map<uint64_t, std::pair<uint32_t, uint32_t>> g_raw_buffer_translations;
	extern std::unordered_map<uint64_t, uint32_t> g_sync_real_ip;
	extern std::unordered_map<uint64_t, uint64_t> g_sync_peer_corruption;
	extern uint8_t g_arxan_restore_bytes[2][2][25];
	extern uint64_t g_arxan_restore_addresses[2];
	extern std::unordered_map<uint64_t, rage::network::read_stats_by_gamer> g_read_stats_by_gamer_results;
	extern std::vector<std::pair<uint32_t, uint8_t*>> g_player_image_queue;
	extern PlayerMenuType g_network_menu_type;
	extern bool g_change_peer;

	// game structures
	extern game_state* g_game_state;
	extern rage::invoker::native_registration** g_native_registration;
	extern rage::network::rs_info* g_rs_info;
	extern rage::types::ped_factory* g_ped_factory;
	extern rage::network::game_camera_angles* g_game_camera_angles;
	extern rage::types::waypoint_data* g_waypoint_data;
	extern rage::network::net_shop_queue* g_net_shop_queue;
	extern rage::types::ui_visual_settings* g_ui_visual_settings;
	extern rage::types::vfx_liquid* g_vfx_liquid;
	extern rage::network::friends* g_friends;
	extern rage::types::texture_store* g_texture_store;
	extern rage::types::store_manager* g_store_manager;
	extern rage::types::memory_heap_pt* g_memory_heap;
	//extern rage::types::replay_interface* g_replay_interface;
	extern rage::types::explosion_data* g_explosion_data;
	extern rage::types::explosion_fx* g_explosion_fx;
	extern rage::network::network_base_config* g_network_base_config;
	extern rage::types::ocean_quads g_ocean_quads;
	extern rage::types::water_tune* g_water_tune;
	extern rage::types::ui_weather* g_ui_weather;
	extern rage::types::ui_puddle* g_ui_puddle;
	extern rage::types::blip_list* g_blip_list;

	// game pools
	extern guid_pool* g_object_pool;
	extern guid_pool* g_ped_pool;
	extern vehicle_pool* g_vehicle_pool;
	extern guid_pool* g_pickup_pool;

	// game lists
	extern hash_list g_weapon_components;
	extern hash_list g_weapon_info;
	extern hash_list g_script_handlers;
	extern std::pair<rage::types::vfx_wheel*, uint8_t> g_vfx_wheel;

	// game addresses
	extern uint64_t g_d3d11_device;
	extern uint64_t g_process_transaction_id;
	extern uint64_t g_sync_data_reader_vtable;
	extern uint64_t g_nullsub;
	extern uint64_t** g_global_cache;
	extern uint64_t g_read_bool_from_bit_buffer;
	extern uint64_t g_read_int_from_bit_buffer;
	extern uint64_t g_read_uint_from_bit_buffer;
	extern uint64_t g_read_byte_from_bit_buffer;
	extern uint64_t g_read_ulonglong_from_bit_Buffer;
	extern uint64_t g_read_short_from_bit_buffer;
	extern uint64_t g_read_vector3_from_bit_buffer;
	extern uint64_t g_read_array_from_bit_buffer;
	extern uint64_t g_read_msg_header_from_bit_buffer;
	extern uint64_t g_read_pickup_from_bit_buffer;
	extern uint64_t g_write_uint_to_bit_buffer;
	extern uint64_t g_sc_game_info_table;
	extern uint64_t g_sc_get_game_info_table;
	extern uint64_t g_game_streamed_scripts;
	extern uint64_t g_get_streamed_script;
	extern uint64_t g_get_third_person_camera;
	extern uint64_t g_third_person_camera;
	extern uint64_t g_get_entity_address;
	extern uint64_t g_get_entity_handle_from_address;
	extern uint64_t g_get_net_game_player_from_index;
	extern uint64_t g_get_model_info;
	extern uint64_t g_set_vehicle_gravity;
	extern uint64_t g_get_vehicle_paint_array;
	extern uint64_t g_draw_origin_index;
	extern uint64_t g_add_to_clock_time;
	extern uint64_t g_dispatch_service_table;
	extern uint64_t g_sync_clock_time;
	extern uint64_t g_send_weather_update;
	extern uint64_t g_get_host_net_game_player;
	extern uint64_t g_send_increment_stat_event;
	extern uint64_t g_update_net_object_owner;
	extern uint64_t g_network_object_manager;
	extern uint64_t g_network_player_manager;
	extern uint64_t g_handle_rotation_values_from_order;
	extern uint64_t g_get_net_game_player_from_handle;
	extern uint64_t g_get_sprite_texture;
	extern uint64_t g_send_text_message_net_msg;
	extern uint64_t g_set_traffic_lights;
	extern uint64_t g_update_traffic_lights;
	extern uint64_t g_set_traffic_light_colors;
	extern uint64_t g_set_vehicle_lights;
	extern uint64_t g_get_sync_tree_from_clone_type;
	extern uint64_t g_get_network_object_from_network_id;
	extern uint64_t g_get_network_config_from_peer;
	extern uint64_t g_network_event_registration;
	extern uint64_t g_update_ui_values;
	extern uint64_t g_update_ui_values_2;
	extern uint64_t g_set_vehicle_neon_ui;
	extern uint64_t g_set_seethrough;
	extern uint64_t g_add_basket_to_queue;
	extern uint64_t g_add_item_to_basket;
	extern uint64_t g_send_session_info_request;
	extern uint64_t g_get_session_info_from_gs;
	extern uint64_t g_send_network_event_reply;
	extern uint64_t g_send_network_event_ack;
	extern uint64_t g_setup_give_control_event;
	extern uint64_t g_send_friend_request;
	extern uint64_t g_get_client_player_key;
	extern uint64_t g_render_water_on_map_intensity;
	extern uint64_t g_map_fog_intensity;
	extern uint64_t g_send_presence_event;
	extern uint64_t g_migrate_script_host;
	extern uint64_t g_is_reported_for_reason;
	extern uint64_t g_chat_info;
	extern uint64_t g_send_matchmaking_request;
	extern uint64_t g_read_xml_string;
	extern uint64_t g_read_xml_node_string;
	extern uint64_t g_register_streaming_file;
	extern uint64_t g_create_game_invite_presence;
	extern uint64_t g_send_game_invite_presence;
	extern uint64_t g_send_game_invite_presence_table;
	extern uint64_t g_send_ragdoll_event;
	extern uint64_t g_grc_texture_factory_dx11;
	extern uint64_t g_thread_alloc;
	extern uint64_t g_setup_dictionary;
	extern uint64_t g_setup_store_item;
	extern uint64_t g_is_valid_pool_slot;
	extern uint64_t g_add_dictionary_to_pool;
	extern uint64_t g_add_grc_texture_to_dictionary;
	extern uint64_t g_get_weather_id;
	extern uint64_t g_weather_table;
	extern uint64_t g_get_font_id_table;
	extern uint64_t g_get_store_module_extension;
	extern uint64_t g_request_streaming_file;
	extern uint64_t g_construct_gfx_font;
	extern uint64_t g_destruct;
	extern uint64_t g_create_id_for_font;
	extern uint64_t g_add_font_lib;
	extern uint64_t g_vertex_begin;
	extern uint64_t g_vertex_end;
	extern uint64_t g_vertex_add;
	extern uint64_t g_render_script_texture;
	extern uint64_t g_font_table;
	extern uint64_t g_font_memory_helper;
	extern uint64_t g_parse_nodes;
	extern uint64_t g_read_new_script_host_message;
	extern uint64_t g_write_gs_item;
	extern uint64_t g_game_script_handler_manager;
	extern uint64_t g_translate_native;
	extern uint64_t g_global_chat_ptr;
	extern uint64_t g_send_global_chat_message;
	extern uint64_t g_add_chat_message;
	extern uint64_t g_chat_config;
	extern uint64_t g_ped_orientation_writer;
	extern uint64_t g_entity_orientation_writer;
	extern uint64_t g_social_club_game_info_table;
	extern uint64_t g_social_club_get_game_info_table;
	extern uint64_t g_reset_script_render_params[2];
	extern uint64_t g_get_player_info_from_net_msg;
	extern uint64_t g_drop_shaders;
	extern uint64_t g_drop_shader_count;
	extern uint64_t g_get_net_msg_net_player;
	extern uint64_t g_ui_3d_draw_manager;
	extern uint64_t g_push_scene_preset_to_manager;
	extern uint64_t g_add_element_to_scene;
	extern uint64_t g_set_scene_element_lighting;
	extern uint64_t g_invalid_string_address;
	extern uint64_t g_construct_read_session_join_request_msg;
	extern uint64_t g_read_session_join_request_msg;
	extern uint64_t g_read_token_from_bit_buffer;
	extern uint64_t g_read_string_from_bit_buffer;
	extern uint64_t g_invite_player;
	extern uint64_t g_sync_data_writer_vtable;

	extern uint32_t g_ozark_detections[100];
}
#pragma pack(pop)