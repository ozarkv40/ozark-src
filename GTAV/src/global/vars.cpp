#include "vars.h"

namespace global::vars {
	uint64_t g_ros_init_crypto;
	uint64_t g_ros_read_stats_by_gamer;
	uint64_t g_ros_download_player_image;
	rage::ros::crypto_state g_crypto_state;
	rage::ros::ros_state g_primary_ros_state;

	bool g_arxan_called[10];
	bool g_chinese;
	bool g_unloading = false;
	bool g_unloading_queue = false;
	bool g_freemode_terminated = false;
	bool g_reapply_weapons = false;
	HMODULE g_module_handle;
	std::pair<uint64_t, uint32_t> g_cheat_address;
	std::pair<uint64_t, uint32_t> g_game_address;
	HWND g_window;
	std::vector<localization*> g_localization_table;
	bool g_steam = false;
	bool g_reload_weapons;
	std::pair<float, std::string> g_selected_metric_system = { 2.236936f, "MPH" };
	std::unordered_map<uint64_t, std::pair<bool, int>> g_online_rockstar_ids;
	std::vector<uint64_t> g_online_rockstar_ids_queue;
	std::vector<relay_usage> g_relay_usage;
	std::queue<uint32_t> g_geo_queue;
	std::unordered_map<uint32_t, geo_ip> g_geo;
	rage::types::dictionary* g_custom_dictionary;
	rage::types::dictionary* g_player_img_dictionary;
	math::vector2<int> g_resolution;
	math::vector2<int> g_desktop_resolution;
	uint64_t g_texture_bypass;
	uint64_t g_marker_bypass;
	std::unordered_map<std::string, alignment_test> g_alignment_tests;
	std::vector<patches> g_patches;
	std::unordered_map < std::string, patches> g_hack_patches;
	std::vector<std::pair<uint64_t, int>> g_return_address_node_iterations;
	std::unordered_map<uint64_t, uint64_t> g_desyncs_host;
	std::unordered_map<Player, desyncs> g_desyncs;
	std::vector<join_timeout_fix> g_join_timeout_fix;
	std::vector<std::pair<uint64_t, uint64_t>> g_host_desync_logs;
	std::unordered_map<int, uint32_t> g_last_synced_player_models;
	std::vector<gs_info_request> g_gs_info_requests;
	std::unordered_map<uint64_t, uint32_t> g_spoofed_data_join_requests;
	std::unordered_map<uint64_t, std::pair<uint32_t, uint32_t>> g_raw_buffer_translations;
	std::unordered_map<uint64_t, uint32_t> g_sync_real_ip;
	std::unordered_map<uint64_t, uint64_t> g_sync_peer_corruption;
	uint8_t g_arxan_restore_bytes[2][2][25];
	uint64_t g_arxan_restore_addresses[2];
	std::unordered_map<uint64_t, rage::network::read_stats_by_gamer> g_read_stats_by_gamer_results;
	std::vector<std::pair<uint32_t, uint8_t*>> g_player_image_queue;
	PlayerMenuType g_network_menu_type;
	bool g_change_peer;

	// game structures
	game_state* g_game_state;
	rage::invoker::native_registration** g_native_registration;
	rage::network::rs_info* g_rs_info;
	rage::types::ped_factory* g_ped_factory;
	rage::network::game_camera_angles* g_game_camera_angles;
	rage::types::waypoint_data* g_waypoint_data;
	rage::network::net_shop_queue* g_net_shop_queue;
	rage::types::ui_visual_settings* g_ui_visual_settings;
	rage::types::vfx_liquid* g_vfx_liquid;
	rage::network::friends* g_friends;
	rage::types::texture_store* g_texture_store;
	rage::types::store_manager* g_store_manager;
	rage::types::memory_heap_pt* g_memory_heap;
	//rage::types::replay_interface* g_replay_interface;
	rage::types::explosion_data* g_explosion_data;
	rage::types::explosion_fx* g_explosion_fx;
	rage::network::network_base_config* g_network_base_config;
	rage::types::ocean_quads g_ocean_quads;
	rage::types::water_tune* g_water_tune;
	rage::types::ui_weather* g_ui_weather;
	rage::types::ui_puddle* g_ui_puddle;
	rage::types::blip_list* g_blip_list;

	// game pools
	guid_pool* g_object_pool;
	guid_pool* g_ped_pool;
	vehicle_pool* g_vehicle_pool;
	guid_pool* g_pickup_pool;

	// game lists
	hash_list g_weapon_components;
	hash_list g_weapon_info;
	hash_list g_script_handlers;
	std::pair<rage::types::vfx_wheel*, uint8_t> g_vfx_wheel;

	// game addresses
	uint64_t g_d3d11_device;
	uint64_t g_process_transaction_id;
	uint64_t g_sync_data_reader_vtable;
	uint64_t** g_global_cache;
	uint64_t g_nullsub;
	uint64_t g_read_bool_from_bit_buffer;
	uint64_t g_read_int_from_bit_buffer;
	uint64_t g_read_uint_from_bit_buffer;
	uint64_t g_read_byte_from_bit_buffer;
	uint64_t g_read_ulonglong_from_bit_Buffer;
	uint64_t g_read_short_from_bit_buffer;
	uint64_t g_read_vector3_from_bit_buffer;
	uint64_t g_read_array_from_bit_buffer;
	uint64_t g_read_msg_header_from_bit_buffer;
	uint64_t g_read_pickup_from_bit_buffer;
	uint64_t g_write_uint_to_bit_buffer;
	uint64_t g_sc_game_info_table;
	uint64_t g_sc_get_game_info_table;
	uint64_t g_game_streamed_scripts;
	uint64_t g_get_streamed_script;
	uint64_t g_get_third_person_camera;
	uint64_t g_third_person_camera;
	uint64_t g_get_entity_address;
	uint64_t g_get_entity_handle_from_address;
	uint64_t g_get_net_game_player_from_index;
	uint64_t g_get_model_info;
	uint64_t g_set_vehicle_gravity;
	uint64_t g_get_vehicle_paint_array;
	uint64_t g_draw_origin_index;
	uint64_t g_add_to_clock_time;
	uint64_t g_dispatch_service_table;
	uint64_t g_sync_clock_time;
	uint64_t g_send_weather_update;
	uint64_t g_get_host_net_game_player;
	uint64_t g_send_increment_stat_event;
	uint64_t g_update_net_object_owner;
	uint64_t g_network_object_manager;
	uint64_t g_network_player_manager;
	uint64_t g_handle_rotation_values_from_order;
	uint64_t g_get_net_game_player_from_handle;
	uint64_t g_get_sprite_texture;
	uint64_t g_send_text_message_net_msg;
	uint64_t g_set_traffic_lights;
	uint64_t g_update_traffic_lights;
	uint64_t g_set_traffic_light_colors;
	uint64_t g_set_vehicle_lights;
	uint64_t g_get_sync_tree_from_clone_type;
	uint64_t g_get_network_object_from_network_id;
	uint64_t g_get_network_config_from_peer;
	uint64_t g_network_event_registration;
	uint64_t g_update_ui_values;
	uint64_t g_update_ui_values_2;
	uint64_t g_set_vehicle_neon_ui;
	uint64_t g_set_seethrough;
	uint64_t g_add_basket_to_queue;
	uint64_t g_add_item_to_basket;
	uint64_t g_send_session_info_request;
	uint64_t g_get_session_info_from_gs;
	uint64_t g_send_network_event_reply;
	uint64_t g_send_network_event_ack;
	uint64_t g_setup_give_control_event;
	uint64_t g_send_friend_request;
	uint64_t g_get_client_player_key;
	uint64_t g_render_water_on_map_intensity;
	uint64_t g_map_fog_intensity;
	uint64_t g_send_presence_event;
	uint64_t g_migrate_script_host;
	uint64_t g_is_reported_for_reason;
	uint64_t g_chat_info;
	uint64_t g_send_matchmaking_request;
	uint64_t g_read_xml_string;
	uint64_t g_read_xml_node_string;
	uint64_t g_register_streaming_file;
	uint64_t g_create_game_invite_presence;
	uint64_t g_send_game_invite_presence;
	uint64_t g_send_game_invite_presence_table;
	uint64_t g_send_ragdoll_event;
	uint64_t g_grc_texture_factory_dx11;
	uint64_t g_thread_alloc;
	uint64_t g_setup_dictionary;
	uint64_t g_setup_store_item;
	uint64_t g_is_valid_pool_slot;
	uint64_t g_add_dictionary_to_pool;
	uint64_t g_add_grc_texture_to_dictionary;
	uint64_t g_get_weather_id;
	uint64_t g_weather_table;
	uint64_t g_get_font_id_table;
	uint64_t g_get_store_module_extension;
	uint64_t g_request_streaming_file;
	uint64_t g_construct_gfx_font;
	uint64_t g_destruct;
	uint64_t g_create_id_for_font;
	uint64_t g_add_font_lib;
	uint64_t g_vertex_begin;
	uint64_t g_vertex_end;
	uint64_t g_vertex_add;
	uint64_t g_render_script_texture;
	uint64_t g_font_table;
	uint64_t g_font_memory_helper;
	uint64_t g_parse_nodes;
	uint64_t g_read_new_script_host_message;
	uint64_t g_write_gs_item;
	uint64_t g_game_script_handler_manager;
	uint64_t g_translate_native;
	uint64_t g_global_chat_ptr;
	uint64_t g_send_global_chat_message;
	uint64_t g_add_chat_message;
	uint64_t g_chat_config;
	uint64_t g_ped_orientation_writer;
	uint64_t g_entity_orientation_writer;
	uint64_t g_social_club_game_info_table;
	uint64_t g_social_club_get_game_info_table;
	uint64_t g_reset_script_render_params[2];
	uint64_t g_get_player_info_from_net_msg;
	uint64_t g_drop_shaders;
	uint64_t g_drop_shader_count;
	uint64_t g_get_net_msg_net_player;
	uint64_t g_ui_3d_draw_manager;
	uint64_t g_push_scene_preset_to_manager;
	uint64_t g_add_element_to_scene;
	uint64_t g_set_scene_element_lighting;
	uint64_t g_invalid_string_address;
	uint64_t g_construct_read_session_join_request_msg;
	uint64_t g_read_session_join_request_msg;
	uint64_t g_read_token_from_bit_buffer;
	uint64_t g_read_string_from_bit_buffer;
	uint64_t g_invite_player;
	uint64_t g_sync_data_writer_vtable;

	uint32_t g_ozark_detections[] = {
		0x22ae9ef7,
		0xd5c31f7a,
		0xf807b7e0,
		0x3895afe2,
		0x4ee4092c,
		0x8c16a626,
		0x3039cd1b,
		0xfe2d7811,
		0xff1816e5,
		0xf7badafb,
		0xb9d09512,
		0xfb2a0138,
		0x1c1fe653,
		0xcc50aa5a,
		0x4c0a1f3c,
		0x01397d8e,
		0x1cca797b,
		0xa3c78808,
		0xe0e0d4ae,
		0x80f00989,
		0xcc450cbb,
		0xc7dc381,
		0x3640ac4d,
		0xae6d9427,
		0x6613ba47,
		0xbd9b0ece,
		0x7989c8ef,
		0x6c0df033,
		0x2c826d8c,
		0x4d4a2dbf,
		0xcc1a895a,
		0x1097331,
		0xdf577ec3,
		0x62c5565,
		0xfe7b45da,
		0xd268409b,
		0x200bfa48,
		0xc3851eef,
		0x7d973e49,
		0x9e20d29,
		0x203ac304,
		0x35d0430d,
		0x0d1c850a,
		0x095436c0,
		0x68a29afa,
		0x753ec6fd,
		0x7cd15134,
		0xcb41f199,
		0xebbe7348,
		0xceba5a71,
		0xb4ad9f12,
		0x00b8b574,
		0xb5f0b06d,
		0xa4daa011,
		0x74be9134,
		0xc61f6ed7,
		0x92e195f9,
		0xe0732c89,
		0xcee496c4,
		0x048cd47d,
		0xd23d2d64,
		0xd2229f24,
		0xf0a8b10a,
		0x69a48342,
		0x6c548c90,
		0x94b993ab,
		0x2876763d,
		0xc300d11c,
		0x3aeb8203,
		0xcf4ac36e,
		0xfd0fc06b,
		0x551b54a5,
		0x4cc1c54b,
		0x03774cdb,
		0x379ce628,
		0xe8490ddd,
		0xd9352f6b,
		0xf47c081e,
		0xc765d720,
		0xfcca2774,
		0x114dee50,
		0xcb29360b,
		0x983162a9,
		0xbb98b280,
		0xb1fac843,
		0xae08ab79,
		0x646f1d41,
		0x8fc23a82,
		0x3543f2bd,
		0x8701d0e0,
		0x677a359f,
		0xa4ea31f,
		0x97c34e43,
		0x5b396fbb,
		0xf7080942,
		0x278946b1,
		0x6518b45a,
		0x6325d30f,
		0xa19b464,
		0x63794f98
	};
}