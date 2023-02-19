#pragma once
#include "stdafx.h"
#include "rage/types/base_types.h"
#include "rage/types/network_types.h"
#include "rage/types/generic_types.h"
#include "menu/base/submenus/main/helper/helper_esp.h"
#include <functional>

namespace menu::player {
	enum ePlayerReportReasons {
		REASON_INVALID_MODEL,
		REASON_SPOOFED_NAME,
		REASON_SPOOFED_PEER,
		REASON_SPOOFED_RID,
		REASON_SPOOFED_IP,
		REASON_CRC_FLOOD,
		REASON_CRC_COMPROMISED,
		REASON_CRC_NOT_REPLIED,
		REASON_INFO_CHANGE_1,
		REASON_INFO_CHANGE_2,
		REASON_INFO_CHANGE_4,
		REASON_INFO_CHANGE_5,
		REASON_INFO_CHANGE_6,
		REASON_INFO_CHANGE_7,
		REASON_ARXAN,
		REASON_SPOOFED_CHAT,
		REASON_SPOOFED_TEXT,
		REASON_CRASH_ATTEMPT,
		REASON_WEATHER_CHANGE,
		REASON_SPECTATING,
		REASON_EXPLOSIVE_AMMO,
		REASON_EXPLOSIVE_MELEE,
		REASON_FIRE_AMMO,
		REASON_SUPER_JUMP,
		REASON_MONEY_DROP,
		REASON_RP_DROP,
		REASON_QUANTUM_KICK,
		REASON_SCRIPT_MIGRATION,
		REASON_PROFANITY,
		REASON_JOIN_TIMEOUT,
		REASON_INFO_MISMATCH,
		REASON_MENU_CHERAX,
		REASON_MENU_IMPULSE,
		REASON_MENU_IMPULSE_VIP,
		REASON_MENU_IMPULSE_STAFF,
		REASON_MENU_IMPULSE_BLOCK,
		REASON_GHOST,
		REASON_END
	};

	std::string get_report_reason(ePlayerReportReasons reason);

#pragma pack(push)
#pragma pack(1)
	struct player_context {
		std::string m_name = "";
		std::unordered_map<ePlayerReportReasons, bool> m_modder_flags;
		std::string m_text_message_msg = "";
		std::unordered_map<int, bool> m_chat_command;

		Player m_id = 0;
		Ped m_ped = 0;
		Entity m_entity = 0;
		Entity m_weapon_entity = 0;
		Vehicle m_vehicle = 0;

		rage::network::net_game_player* m_net_player = nullptr;
		rage::types::ped* m_ped_ptr = nullptr;
		rage::network::network_handle m_network_handle;
		helper::esp::vars::esp_context m_esp;

		bool m_ozark = false;
		bool m_ran_ozark = false;
		bool m_cached_model = false;
		bool m_exists = false;
		bool m_connected = false;
		bool m_alive = false;
		bool m_in_vehicle = false;
		bool m_has_weapon_in_hand = false;
		bool m_is_aiming = false;
		bool m_is_modder = false;
		bool m_is_friend = false;
		bool m_is_script_host = false;
		bool m_rockstar_developer = false;

		math::vector3<float> m_coords = {};
		math::vector3<float> m_rotation = {};

		uint32_t m_weapon_hash = 0;
		uint32_t m_model = 0;
		float m_heading = 0.f;
		int m_ped_headshot = 0;

		uint32_t m_blacklist = 0;
		bool m_ghost[14];
		bool m_block_entities[2][14];
		char m_text_message_final[100];

		float m_explosion_radius;
		float m_explosion_camera_shake;

		bool m_gift_vehicle = false;
		bool m_chat_target = false;
		bool m_sync_interval_toggle = false;
		bool m_spectate = false;
		bool m_demi_godmode = false;
		bool m_off_the_radar = false;
		bool m_disable_police = false;
		bool m_kill_killers = false;
		bool m_force_visible = false;
		bool m_chat_commands = false;
		bool m_drop_toggle = false;
		bool m_drop_stealth = false;
		bool m_freeze = false;
		bool m_simple_explode = false;
		bool m_kick_from_vehicle = false;
		bool m_taze = false;
		bool m_ragdoll = false;
		bool m_glitch_physics = false;
		bool m_forcefield = false;
		bool m_rain_rockets = false;
		bool m_always_wanted = false;
		bool m_block_passive = false;
		bool m_cage = false;
		bool m_ceo = false;
		bool m_set_on_fire = false;
		bool m_blame = false;
		bool m_send_to_island = false;
		bool m_vehicle_ram = false;
		bool m_clone = false;
		bool m_hostile_peds = false;
		bool m_hostile_vehicles = false;
		bool m_show_message = false;
		bool m_attacker_invincibility = false;
		bool m_attacker_invisibility = false;
		bool m_explosion_sound = false;
		bool m_explosion_loop = false;
		bool m_fake_money_drop = false;
		bool m_attachment_randomize_bone = false;
		bool m_attachment_randomize_rotation = false;
		bool m_vehicle_godmode = false;
		bool m_vehicle_disable_collision = false;
		bool m_vehicle_slippy_wheels = false;
		bool m_vehicle_freeze = false;

		int m_drop_type;
		int m_drop_pickup;
		int m_drop_weapon;
		int m_drop_money_model;
		int m_drop_money_style;
		int m_drop_money_delay;
		int m_drop_money_timer;
		int m_sync_interval;
		int m_demi_godmode_timer;
		int m_off_the_radar_timer;
		int m_disable_police_timer;
		int m_bodyguard_count = 1;
		int m_commend;
		int m_outfit;
		int m_text_message_color;
		int m_text_message_font;
		int m_text_message_size;
		int m_text_message_count;
		int m_kick_from_vehicle_timer;
		int m_taze_timer;
		int m_ragdoll_timer;
		int m_glitch_physics_timer;
		int m_rain_rockets_timer;
		int m_always_wanted_timer;
		int m_cage_type;
		int m_cage_timer;
		int m_ceo_type;
		int m_ceo_timer;
		int m_set_on_fire_timer;
		int m_blame_timer;
		int m_send_to_island_timer;
		int m_vehicle_ram_timer;
		int m_vehicle_ram_type;
		int m_clone_type;
		int m_clone_timer;
		int m_hostile_peds_timer;
		int m_hostile_vehicles_timer;
		int m_show_message_type;
		int m_show_message_timer;
		int m_attacker_type;
		int m_attacker_count = 1;
		int m_explosion_type;
		int m_explosion_visual;
		int m_fake_money_drop_timer;
		int m_remove_weapon_group_type;
		int m_attachment_bone;
		int m_attachment_custom;
		int m_attachment_peds;
		int m_attachment_vehicles;
		int m_attachment_objects;
		int m_attachment_flags;
		int m_vehicle_upgrades;
		int m_vehicle_downgrades;
		int m_vehicle_acrobatics;
		int m_vehicle_boost_forwards;
		int m_vehicle_boost_backwards;
		int m_vehicle_rotate;

		void reset() {
			uint64_t base = (uint64_t)this;
			memset((void*)(base + offsetof(player_context, m_id)), 0, sizeof(player_context) - offsetof(player_context, m_id));

			m_name = std::string("");
			m_text_message_msg = "";
			m_chat_command.clear();
			m_modder_flags.clear();

			m_esp.m_ped = true;
			m_esp.m_name_text_color = color_rgba(255, 255, 255, 255);
			m_esp.m_name_bg_color = color_rgba(0, 0, 0, 180);
			m_esp.m_snapline_color = color_rgba(255, 0, 255, 255);
			m_esp.m_2d_box_color = color_rgba(255, 0, 255, 255);
			m_esp.m_2d_corners_color = color_rgba(255, 0, 255, 255);
			m_esp.m_3d_box_color = color_rgba(255, 0, 255, 255);
			m_esp.m_skeleton_bones_color = color_rgba(255, 0, 255, 255);
			m_esp.m_skeleton_joints_color = color_rgba(255, 0, 255, 255);
			m_esp.m_weapon_color = color_rgba(255, 255, 255, 255);

			m_bodyguard_count = 1;
			m_text_message_size = 1;
			m_attacker_count = 1;
			m_ozark = false;
			m_ran_ozark = false;

			m_drop_money_delay = 6;
		}
	};
#pragma pack(pop)

	class player_manager {
	public:
		void update();
		void for_each(std::function<void(player_context&)> callback, bool bypass_excludes = false, bool bypass_ghost = false);
		player_context& random(int ignore_index = -1);

		player_context& get_player(int index);
		player_context& get_local_player();
		player_context& get_selected_player();
		bool is_excluded(Player id);
	private:
		player_context m_players[32];
	};

	player_manager* get_player_manager();

	inline player_context& get_player(int index) {
		return get_player_manager()->get_player(index);
	}

	inline player_context& get_local_player() {
		return get_player_manager()->get_local_player();
	}

	inline player_context& get_selected_player() {
		return get_player_manager()->get_selected_player();
	}

	inline player_context& random(int ignore_index = -1) {
		return get_player_manager()->random(ignore_index);
	}

	inline void for_each(std::function<void(player_context&)> callback, bool bypass_excludes = false, bool bypass_ghost = false) {
		get_player_manager()->for_each(callback, bypass_excludes, bypass_ghost);
	}

	inline void update() {
		get_player_manager()->update();
	}

	inline bool is_excluded(Player id) {
		return get_player_manager()->is_excluded(id);
	}
}