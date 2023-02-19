#include "ui_vars.h"

namespace global::ui {
	float g_option_scale = 0.0315f;
	float g_option_height = g_option_scale * 10.f;

	std::string g_render_queue[100];
	std::string g_rendering_tooltip;
	line_2d* m_line_2d;
	int g_line_2d_index = 0;

	int g_render_queue_index = 0;
	bool g_stop_rendering;
	bool g_rendering_color;
	bool g_render_tooltip = true;
	bool g_render_globe = true;
	bool g_disable_title = false;
	bool g_scroll_lerp = true;
	bool g_input_open;

	float g_wrap = 0.063f;
	float g_delta = 0.f;
	float g_scroll_lerp_speed = 25.f;

	int g_header_font = 0;
	int g_sub_header_font = 4;
	int g_option_font = 4;
	int g_open_tooltip_font = 4;
	int g_tooltip_font = 4;
	int g_stacked_display_font = 0;
	int g_notify_title_font = 0;
	int g_notify_body_font = 0;
	int g_panel_font = 4;

	math::vector2<float> g_position = { 0.70f, 0.3f };
	math::vector2<float> g_scale = { 0.22f, 0.f };
	math::vector2<float> g_submenu_arrow_position = { 0.218f, 0.010f };
	math::vector2<float> g_submenu_arrow_scale = { 0.007f, 0.013f };
	math::vector2<float> g_toggle_position = { 0.221f, 0.016f };
	math::vector2<float> g_toggle_scale = { 0.007f, 0.011f };
	math::vector2<float> g_globe_position = { 0.4405f, 0.328f };
	math::vector2<float> g_globe_scale = { 0.978f, 0.906f };
	math::vector2<float> g_stacked_display_scale = { 0.15f, 0.015f };
	math::vector2<float> g_stacked_display_position = { 0.845f, 0.01f };

	// 76, 37, 219

	color_rgba g_success = color_rgba(70, 219, 37, 255);
	color_rgba g_error = color_rgba(219, 37, 37, 255);
	color_rgba g_main_header = color_rgba(220, 76, 81, 255);
	color_rgba g_sub_header = color_rgba(0, 0, 0, 220);
	color_rgba g_sub_header_text = color_rgba(255, 255, 255, 255);
	color_rgba g_background = color_rgba(0, 0, 0, 255);
	color_rgba g_scroller = color_rgba(186, 65, 69, 255);
	color_rgba g_footer = color_rgba(220, 76, 81, 220);
	color_rgba g_title = color_rgba(255, 255, 255, 255);
	color_rgba g_open_tooltip = color_rgba(220, 76, 81, 255);
	color_rgba g_tooltip = color_rgba(220, 76, 81, 255);
	color_rgba g_option = color_rgba(255, 255, 255, 255);
	color_rgba g_option_selected = color_rgba(255, 255, 255, 255);
	color_rgba g_toggle_on = color_rgba(130, 214, 157, 255);
	color_rgba g_toggle_off = color_rgba(200, 55, 80, 255);
	color_rgba g_break = color_rgba(255, 255, 255, 255);
	color_rgba g_submenu_bar = color_rgba(255, 255, 255, 255);
	color_rgba g_clear_area_range = color_rgba(220, 76, 81, 255);
	color_rgba g_hotkey_bar = color_rgba(220, 76, 81, 255);
	color_rgba g_color_grid_bar = color_rgba(220, 76, 81, 255);
	color_rgba g_notify_bar = color_rgba(220, 76, 81, 255);
	color_rgba g_notify_background = color_rgba(40, 40, 40, 255);
	color_rgba g_panel_bar = color_rgba(220, 76, 81, 255);
	color_rgba g_stacked_display_bar = color_rgba(220, 76, 81, 255);
	color_rgba g_stacked_display_background = color_rgba(0, 0, 0, 180);
	color_rgba g_panel_background = color_rgba(0, 0, 0, 180);
	color_rgba g_hotkey_background = color_rgba(0, 0, 0, 180);
	color_rgba g_color_grid_background = color_rgba(0, 0, 0, 180);
	color_rgba g_hotkey_input = color_rgba(40, 40, 40, 200);
	color_rgba g_instructional_background = color_rgba(0, 0, 0, 255);
	color_rgba g_globe = color_rgba(255, 255, 255, 255);

	menu_texture m_header = menu_texture(&g_main_header);
	menu_texture m_background = menu_texture(&g_background);
	menu_texture m_scroller = menu_texture(&g_scroller);
	menu_texture m_footer = menu_texture(&g_footer);
	menu_texture m_tooltip_background;
	menu_texture m_tooltip_bar;
	menu_texture m_stacked_display_background;
	menu_texture m_stacked_display_bar;
	menu_texture m_panel_background;
	menu_texture m_panel_bar;
	menu_texture m_notify_background;
	menu_texture m_notify_bar;
	menu_texture m_vehicle_stats_background;
	menu_texture m_vehicle_stats_bar;
}