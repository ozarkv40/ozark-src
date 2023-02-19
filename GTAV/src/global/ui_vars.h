#pragma once
#include "stdafx.h"
#include "util/math.h"
#include "util/localization.h"
#include <unordered_map>

struct color_rgba {
	int r;
	int g;
	int b;
	int a = 255;

	color_rgba()
		: r(0), g(0), b(0), a(0) {}

	color_rgba(int red, int green, int blue, int alpha = 255)
		: r(red), g(green), b(blue), a(alpha) {}

	color_rgba(uint32_t hex)
		: r(hex >> 24), g(((hex >> 16) & 0x00FF)), b(((hex >> 8) & 0x0000FF)), a(hex & 0xFF) {}

	color_rgba opacity(int opacity) {
		return color_rgba(r, g, b, opacity);
	}

	math::vector3_<int> as_vector() {
		return { r, g, b };
	}

	std::initializer_list<int> as_initializer_list() {
		return std::initializer_list<int> { r, g, b, a };
	}

	uint32_t to_argb() {
		uint8_t val[4];
		val[0] = a;
		val[1] = r;
		val[2] = g;
		val[3] = b;

		return *(uint32_t*)&val;
	}
};

struct color_hsv {
	float h;
	float s;
	float v;
};

struct radio_context {
	std::unordered_map<int, bool> m_toggles;
	int m_selected = 0;
	int m_count = 0;
	std::pair<const char*, const char*> m_sprite = { "", "" };

	radio_context(const char* dict, const char* texture) {
		m_sprite = std::make_pair(dict, texture);
		m_selected = 0;
		m_count = 0;
	}

	void reset() {
		m_count = 0;

		for (auto& it : m_toggles) {
			it.second = false;
		}
	}
};

struct menu_texture {
	bool m_enabled;
	radio_context m_context = { "commonmenu", "shop_art_icon" };
	std::string m_texture;
	localization m_submenu_name;
	color_rgba* m_color = nullptr;

	menu_texture() {}

	menu_texture(color_rgba* color) {
		m_color = color;
	}
};

struct line_2d {
	math::vector2<float> m_from;
	math::vector2<float> m_to;
	color_rgba m_color;
};

namespace global::ui {
	extern float g_option_scale;
	extern float g_option_height;

	extern std::string g_render_queue[100];
	extern std::string g_rendering_tooltip;
	extern line_2d* m_line_2d;
	extern int g_line_2d_index;

	extern int g_render_queue_index;
	extern bool g_stop_rendering;
	extern bool g_render_tooltip;
	extern bool g_rendering_color;
	extern bool g_render_globe;
	extern bool g_disable_title;
	extern bool g_scroll_lerp;
	extern bool g_input_open;

	extern float g_wrap;
	extern float g_delta;
	extern float g_scroll_lerp_speed;

	extern int g_header_font;
	extern int g_sub_header_font;
	extern int g_option_font;
	extern int g_open_tooltip_font;
	extern int g_tooltip_font; //
	extern int g_stacked_display_font;
	extern int g_notify_title_font;
	extern int g_notify_body_font;
	extern int g_panel_font;
	
	extern math::vector2<float> g_position;
	extern math::vector2<float> g_scale;
	extern math::vector2<float> g_submenu_arrow_position;
	extern math::vector2<float> g_submenu_arrow_scale;
	extern math::vector2<float> g_toggle_position;
	extern math::vector2<float> g_toggle_scale;
	extern math::vector2<float> g_globe_position;
	extern math::vector2<float> g_globe_scale;
	extern math::vector2<float> g_stacked_display_scale;
	extern math::vector2<float> g_stacked_display_position;

	extern color_rgba g_success;
	extern color_rgba g_error;
	extern color_rgba g_main_header;
	extern color_rgba g_sub_header;
	extern color_rgba g_sub_header_text;
	extern color_rgba g_background;
	extern color_rgba g_scroller;
	extern color_rgba g_footer;
	extern color_rgba g_title;
	extern color_rgba g_open_tooltip;
	extern color_rgba g_tooltip;
	extern color_rgba g_option;
	extern color_rgba g_option_selected;
	extern color_rgba g_toggle_on;
	extern color_rgba g_toggle_off;
	extern color_rgba g_break;
	extern color_rgba g_submenu_bar;
	extern color_rgba g_clear_area_range;
	extern color_rgba g_hotkey_bar;
	extern color_rgba g_notify_bar;
	extern color_rgba g_notify_background;
	extern color_rgba g_panel_bar;
	extern color_rgba g_stacked_display_bar;
	extern color_rgba g_stacked_display_background;
	extern color_rgba g_panel_background;
	extern color_rgba g_hotkey_background;
	extern color_rgba g_hotkey_input;
	extern color_rgba g_instructional_background;
	extern color_rgba g_globe;
	extern color_rgba g_color_grid_background;
	extern color_rgba g_color_grid_bar;

	extern menu_texture m_header;
	extern menu_texture m_background;
	extern menu_texture m_scroller;
	extern menu_texture m_footer;
	extern menu_texture m_tooltip_background;
	extern menu_texture m_tooltip_bar;
	extern menu_texture m_stacked_display_background;
	extern menu_texture m_stacked_display_bar;
	extern menu_texture m_panel_background;
	extern menu_texture m_panel_bar;
	extern menu_texture m_notify_background;
	extern menu_texture m_notify_bar;
	extern menu_texture m_vehicle_stats_background;
	extern menu_texture m_vehicle_stats_bar;
}