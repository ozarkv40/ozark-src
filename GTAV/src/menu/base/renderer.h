#pragma once
#include "stdafx.h"
#include "global/ui_vars.h"
#include "util/math.h"

enum eJustify {
	JUSTIFY_LEFT,
	JUSTIFY_RIGHT,
	JUSTIFY_CENTER,
};

namespace menu::renderer {
#undef DrawText
	class renderer {
	public:
		void render();

		void render_title(std::string title);
		void render_tooltip(std::string tooltip);
		void render_open_tooltip();
		void render_color_preview(color_rgba color);

		float calculate_string_width(std::string string, int font, float scale);
		float get_normalized_font_scale(int font, float scale);
		std::pair<std::string, std::string> get_texture(menu_texture texture);

		void draw_rect(math::vector2<float> position, math::vector2<float> scale, color_rgba color);
		void draw_rect_unaligned(math::vector2<float> position, math::vector2<float> scale, color_rgba color);
		void draw_outlined_rect(math::vector2<float> position, math::vector2<float> scale, float thickness, color_rgba box_color, color_rgba border_color);
		void draw_text(std::string text, math::vector2<float> position, float scale, int font, color_rgba color, eJustify justification, math::vector2<float> wrap = { 0.f, 5.f });
		void draw_sprite(std::pair<std::string, std::string> asset, math::vector2<float> position, math::vector2<float> scale, float rotation, color_rgba color);
		void draw_sprite_aligned(std::pair<std::string, std::string> asset, math::vector2<float> position, math::vector2<float> scale, float rotation, color_rgba color);
		void draw_line(math::vector3<float> from, math::vector3<float> to, color_rgba color);
		void draw_line_2d(math::vector3<float> from, math::vector3<float> to, color_rgba color);

		color_hsv rgb_to_hsv(color_rgba in);
		color_rgba hsv_to_rgb(float h, float s, float v, int original_alpha = 255);

		int get_render_count();
		void set_smooth_scroll(float val) { m_smooth_scroll = val; }
		float get_smooth_scroll() { return m_smooth_scroll; }
	private:
		float m_smooth_scroll = global::ui::g_position.y;
		int m_render_count;
		int m_globe_handle;
	};

	renderer* get_renderer();

	inline void render() {
		get_renderer()->render();
	}

	inline void render_open_tooltip() {
		get_renderer()->render_open_tooltip();
	}

	inline int get_render_count() {
		return get_renderer()->get_render_count();
	}

	inline void render_title(std::string title) {
		get_renderer()->render_title(title);
	}

	inline void render_tooltip(std::string tooltip) {
		get_renderer()->render_tooltip(tooltip);
	}

	inline void render_color_preview(color_rgba color) {
		get_renderer()->render_color_preview(color);
	}

	inline float calculate_string_width(std::string string, int font, float scale) {
		return get_renderer()->calculate_string_width(string, font, scale);
	}

	inline float get_normalized_font_scale(int font, float scale) {
		return get_renderer()->get_normalized_font_scale(font, scale);
	}

	inline void draw_rect(math::vector2<float> position, math::vector2<float> scale, color_rgba color) {
		get_renderer()->draw_rect(position, scale, color);
	}

	inline void draw_rect_unaligned(math::vector2<float> position, math::vector2<float> scale, color_rgba color) {
		get_renderer()->draw_rect_unaligned(position, scale, color);
	}

	inline void draw_outlined_rect(math::vector2<float> position, math::vector2<float> scale, float thickness, color_rgba box_color, color_rgba border_color) {
		get_renderer()->draw_outlined_rect(position, scale, thickness, box_color, border_color);
	}

	inline void draw_text(std::string text, math::vector2<float> position, float scale, int font, color_rgba color, eJustify justification = JUSTIFY_LEFT, math::vector2<float> wrap = { 0.f, 5.f }) {
		get_renderer()->draw_text(text, position, scale, font, color, justification, wrap);
	}

	inline void draw_sprite(std::pair<std::string, std::string> asset, math::vector2<float> position, math::vector2<float> scale, float rotation, color_rgba color) {
		get_renderer()->draw_sprite(asset, position, scale, rotation, color);
	}

	inline void draw_sprite_aligned(std::pair<std::string, std::string> asset, math::vector2<float> position, math::vector2<float> scale, float rotation, color_rgba color) {
		get_renderer()->draw_sprite_aligned(asset, position, scale, rotation, color);
	}

	inline void draw_line(math::vector3<float> from, math::vector3<float> to, color_rgba color) {
		get_renderer()->draw_line(from, to, color);
	}

	inline void draw_line_2d(math::vector3<float> from, math::vector3<float> to, color_rgba color) {
		get_renderer()->draw_line_2d(from, to, color);
	}

	inline std::pair<std::string, std::string> get_texture(menu_texture texture) {
		return get_renderer()->get_texture(texture);
	}

	inline void set_smooth_scroll(float val) {
		get_renderer()->set_smooth_scroll(val);
	}

	inline float get_smooth_scroll() {
		return get_renderer()->get_smooth_scroll();
	}

	inline color_hsv rgb_to_hsv(color_rgba in) {
		return get_renderer()->rgb_to_hsv(in);
	}

	inline color_rgba hsv_to_rgb(float h, float s, float v, int original_alpha = 255) {
		return get_renderer()->hsv_to_rgb(h, s, v, original_alpha);
	}
}