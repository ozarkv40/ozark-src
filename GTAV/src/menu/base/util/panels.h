#pragma once
#include "stdafx.h"
#include "global/ui_vars.h"
#include "rage/types/base_types.h"
#include "rage/types/network_types.h"
#include "rage/types/generic_types.h"
#include <unordered_map>

namespace menu::panels {
	class panel_manager;
	struct panel_child;

	struct panel_custom_recent_player {
		char m_name[0x20];
		char m_ip[16];
		uint64_t m_rockstar_id;
		int m_session_type;
		char m_first_encountered[0x50];
		char m_last_encountered[0x50];
		bool m_in_session;
		bool m_online;
		bool m_has_stats;
		rage::network::read_stats_by_gamer m_stats;
	};

	struct panel_custom_friend {
		char m_name[32];
		uint64_t m_rockstar_id;
		bool m_has_stats;
		rage::network::read_stats_by_gamer m_stats;
		bool m_online;
		bool m_in_session;
		int m_session_type;
	};

	struct panel_custom_overseer {
		char m_name[32];
		uint64_t m_rockstar_id;
		int m_flags;
		bool m_has_stats;
		rage::network::read_stats_by_gamer m_stats;
		bool m_online;
		bool m_in_session;
		int m_session_type;
	};

	struct panel_custom_vehicle_preview {
		uint32_t m_model;
		char m_dict[50];
		char m_name[50];
		char m_manufacturer[12];
		float m_max_speed;
		float m_max_braking;
		float m_max_traction;
		int m_seats;
	};

	struct panel_custom_session_browser {
		uint64_t m_rockstar_id;
		uint64_t m_peer_token;
		char m_name[0x20];
		bool m_has_stats;
		rage::network::read_stats_by_gamer m_stats;
		uint32_t m_local_ip;
	};

	struct panel_custom_player_search {
		uint64_t m_rockstar_id;
		bool m_online;
		char m_name[0x20];
		bool m_has_stats;
		rage::network::read_stats_by_gamer m_stats;
	};

	struct panel_custom_blacklisted_player {
		char m_name[0x20];
		uint64_t m_rockstar_id;
		uint32_t m_blacklisted_time;
	};

	struct panel_custom_screen_ped_preview {
		rage::types::ped* m_ped;
		math::vector3_<float> m_screen_offset;
		bool m_is_player;
		Player m_player;
	};

	struct panel_parent {
		bool m_render; // needed to render *any* children
		std::string m_id; // identifier
		std::string m_name;
		std::unordered_map<int, math::vector2<float>> m_column_offset; // index'd by column
		std::vector<panel_child> m_children_panels;
	};

	struct panel_child {
		panel_parent* m_parent;
		bool m_render; // render this child
		std::string m_id; // identifier
		std::string m_name;

		bool m_double_sided = true;
		int m_index = 0; // render order
		int m_column = 0; // 0 = next to menu, 1 = next to that, etc
		int m_panel_tick_left = 0; // used for drawing
		int m_panel_tick_right = 0; // used for drawing
		int m_panel_option_count_left = 0; // used for drawing
		int m_panel_option_count_right = 0; // used for drawing

		uint8_t m_custom_ptr[0x150]; // struct addresses for passing data
		math::vector2<float>(*m_update)(panel_child&); // callback for rendering, returns total height of rendered element
	};

	class panel {
	public:
		panel(panel_child& child, color_rgba header_color);

		void item(std::string name, std::string value, int font = 0, float font_scale = 0.3f, color_rgba color = { 255, 255, 255, 255 });
		void item(std::string name, std::string sprite_left, std::string sprite_right, int font = 0, float font_scale = 0.3f, color_rgba color = { 255, 255, 255, 255 }, math::vector2<float> scale = { 0.0192f, 0.0336f });
		void item_full(std::string name, std::string value, int font = 0, float font_scale = 0.3f, color_rgba color = { 255, 255, 255, 255 });
		void item_full(std::string name, std::string sprite_left, std::string sprite_right, int font = 0, float font_scale = 0.3f, color_rgba color = { 255, 255, 255, 255 }, math::vector2<float> scale = { 0.0192f, 0.0336f });

		math::vector2<float> get_rendering_position();

		math::vector2<float> get_render_scale() {
			if (m_child) {
				if (m_child->m_panel_tick_left == 0
					&& m_child->m_panel_tick_right == 0) {
					return { 0.f, 0.f };
				}
			}

			return { m_width, m_height };
		}

		math::vector2<float> get_column_adjustment() { return m_column_adjustment; }
		panel_child* get_panel_child() { return m_child; }
		float get_column_offset() { return m_column_offset; }
	private:
		void panel_left_item(std::string name, std::string value, int font, float font_scale, color_rgba color);
		void panel_right_item(std::string name, std::string value, int font, float font_scale, color_rgba color);
		void panel_left_sprite_item(std::string name, std::string sprite_left, std::string sprite_right, int font, float font_scale, color_rgba color = { 255, 255, 255, 255 }, math::vector2<float> scale = { 0.0192f, 0.0336f });
		void panel_right_sprite_item(std::string name, std::string sprite_left, std::string sprite_right, int font, float font_scale, color_rgba color = { 255, 255, 255, 255 }, math::vector2<float> scale = { 0.0192f, 0.0336f });

		panel_child* m_child;
		float m_width = 0.f;
		float m_height = 0.f;
		float m_column_offset = 0.f;
		math::vector2<float> m_column_adjustment;
	};

	class panel_manager {
	public:
		void load();
		void update();
		void cleanup();

		void null_structure(panel_child& _this);
		void set_structure(panel_child& _this, void* data, int size);

		// Panels
		static math::vector2<float> render_panel_player_info_name(panel_child& _this);
		static math::vector2<float> render_panel_player_info_generic(panel_child& _this);
		static math::vector2<float> render_panel_player_info_flags(panel_child& _this);
		static math::vector2<float> render_panel_player_info_vote_kick_queue(panel_child& _this);
		static math::vector2<float> render_panel_player_info_crew(panel_child& _this);
		static math::vector2<float> render_panel_player_info_properties(panel_child& _this);
		static math::vector2<float> render_panel_player_info_stats(panel_child& _this);
		static math::vector2<float> render_panel_player_info_geo(panel_child& _this);

		static math::vector2<float> render_panel_radio(panel_child& _this);
		static math::vector2<float> render_panel_recent_player(panel_child& _this);
		static math::vector2<float> render_panel_friend(panel_child& _this);
		static math::vector2<float> render_panel_overseer(panel_child& _this);
		static math::vector2<float> render_panel_vehicle_preview(panel_child& _this);
		static math::vector2<float> render_panel_host_queue(panel_child& _this);
		static math::vector2<float> render_panel_blacklist(panel_child& _this);
		static math::vector2<float> render_panel_session_browser(panel_child& _this);
		static math::vector2<float> render_panel_player_search(panel_child& _this);
		static math::vector2<float> render_panel_blacklisted_player(panel_child& _this);

		static math::vector2<float> render_panel_clock(panel_child& _this);
		static math::vector2<float> render_panel_outfit_preview(panel_child& _this);

		panel_parent* get_parent(std::string id);
		panel_child& get_child(panel_parent* parent, std::string id);
		void rearrange(panel_parent* parent, std::string id, int new_column, int new_position);
		void toggle_panel_render(std::string parent_id, bool toggle);

		std::vector<panel_parent*>& get_panels() {
			return m_panels;
		}
	private:
		std::vector<panel_parent*> m_panels;
		bool m_rearranging = false;
	};
	
	panel_manager* get_panel_manager();

	inline void load() {
		get_panel_manager()->load();
	}

	inline void update() {
		get_panel_manager()->update();
	}

	inline void cleanup() {
		get_panel_manager()->cleanup();
	}

	inline void null_structure(panel_child& _this) {
		get_panel_manager()->null_structure(_this);
	}

	inline void set_structure(panel_child& _this, void* data, int size) {
		get_panel_manager()->set_structure(_this, data, size);
	}

	inline panel_parent* get_parent(std::string id) {
		return get_panel_manager()->get_parent(id);
	}

	inline panel_child& get_child(panel_parent* parent, std::string id) {
		return get_panel_manager()->get_child(parent, id);
	}

	inline void rearrange(panel_parent* parent, std::string id, int new_column, int new_position) {
		get_panel_manager()->rearrange(parent, id, new_column, new_position);
	}

	inline void toggle_panel_render(std::string parent_id, bool toggle) {
		get_panel_manager()->toggle_panel_render(parent_id, toggle);
	}

	inline std::vector<panel_parent*>& get_panels() {
		return get_panel_manager()->get_panels();
	}
}