#include "renderer.h"
#include "base.h"
#include "submenu_handler.h"
#include "rage/invoker/natives.h"
#include "menu/base/util/textures.h"
#include "menu/base/util/fonts.h"
#include "menu/base/submenus/main.h"
#include <random>

static localization t_tooltip_1("put me in coach", true, true);
static localization t_tooltip_2("i've made a severe and continuous lapse in my judgment", true, true);
static localization t_tooltip_3("nothing. you get nothing here today. fuck you.", true, true);
static localization t_tooltip_4("I'll have you know I graduated top of my class in the Navy Seals", true, true);
static localization t_tooltip_5("penis size should be a volumetric measurement, let me explain...", true, true);
static localization t_tooltip_6("there's no such thing as a \"simp\"", true, true);
static localization t_tooltip_7("ligma", true, true);
static localization t_tooltip_8("sugma", true, true);
static localization t_tooltip_9("hi sisters", true, true);
static localization t_tooltip_10("one does not simply walk into mordor", true, true);
static localization t_tooltip_11("if you spill cleaning product, did you make a mess?", true, true);
static localization t_tooltip_13("bro where the fuck am i?", true, true);
static localization t_tooltip_14("welcome to pogzark :tm:", true, true);
static localization t_tooltip_15("see, the wait paid off didn't it? no??? fuck you then", true, true);
static localization t_tooltip_16("i aint ever gonna stop loving you, bitch", true, true);
static localization t_tooltip_17("ozark update when?", true, true);
static localization t_tooltip_19("sudo rm -f / -no-preserve-root", true, true);
static localization t_tooltip_20("bro that's cap", true, true);
static localization t_tooltip_21("dude, where's my car?", true, true);
static localization t_tooltip_22("rate the ozark exit scam 1 thru 10", true, true);
static localization t_tooltip_23("fuck you", true, true);
static localization t_tooltip_24("sponsored by cheatengine", true, true);
static localization t_tooltip_25("lets play a game; what has pink hair... wait, nevermind", true, true);
static localization t_tooltip_26("\"Such an obvious exit scam\" - DoneWithDegeneracy", true, true);
static localization t_tooltip_27("wow we can edit the weather color, we're so cool", true, true);

namespace menu::renderer {
	std::pair<std::string, std::string> renderer::get_texture(menu_texture texture) {
		if (texture.m_texture != "sa7anisafaggot") {
			if (texture.m_enabled) {
				std::vector<menu::textures::texture_context> list = menu::textures::get_list();

				int texture_index = texture.m_context.m_selected;
				if (texture_index < list.size()) {
					auto vit = std::find_if(begin(list), end(list), [=](menu::textures::texture_context& context) { return context.m_name == texture.m_texture; });
					if (vit != end(list)) {
						return { "ozarktextures", vit->m_name };
					}
				}
			}
		}

		return { "randomha", "yesyesyesyes" };
	}

	void renderer::render() {
		int current_option = base::get_current_option();
		int max_options = base::get_max_options();
		int scroll_offset = base::get_scroll_offset();
		int total_options = menu::submenu::handler::get_total_options();

		m_render_count = math::clamp(current_option - scroll_offset > max_options ? max_options : (current_option - scroll_offset + 1), 0, max_options);
		
		int option_count = total_options > max_options ? max_options : total_options;
		int scroller_position = math::clamp(current_option - scroll_offset > max_options ? max_options : current_option - scroll_offset, 0, max_options);

		// main header
		std::pair<std::string, std::string> texture = get_texture(global::ui::m_header);
		draw_sprite_aligned(texture, { global::ui::g_position.x, global::ui::g_position.y - 0.08f }, { global::ui::g_scale.x, 0.08f }, 0.f, global::ui::g_main_header);

		// globe
		if (global::ui::g_render_globe) {
			if (!native::has_scaleform_movie_loaded(m_globe_handle)) {
				m_globe_handle = native::request_scaleform_movie("MP_MENU_GLARE");
			} else {
				float rotation = native::get_gameplay_cam_rot(2).z;
				rotation -= round(rotation / 360.0f) * 360.0f;
				if (rotation < 0.f) {
					rotation += 360.0f;
				}

				native::push_scaleform_movie_function(m_globe_handle, "SET_DATA_SLOT");
				native::push_scaleform_movie_function_parameter_float(rotation);
				native::pop_scaleform_movie_function_void();
			}

			native::draw_scaleform_movie(m_globe_handle, global::ui::g_position.x + global::ui::g_globe_position.x, global::ui::g_position.y + global::ui::g_globe_position.y, global::ui::g_globe_scale.x, global::ui::g_globe_scale.y, global::ui::g_globe.r, global::ui::g_globe.g, global::ui::g_globe.b, global::ui::g_globe.a, 0);
		}

		// background
		texture = get_texture(global::ui::m_background);
		if (texture.first == "randomha") texture = { "commonmenu", "gradient_bgd" };
		draw_sprite_aligned(texture, global::ui::g_position, { global::ui::g_scale.x, option_count * global::ui::g_option_scale }, 0.f, global::ui::g_background);

		// scroller
		if (global::ui::g_scroll_lerp) {
			m_smooth_scroll = math::lerp(m_smooth_scroll, global::ui::g_position.y + (scroller_position * global::ui::g_option_scale), global::ui::g_delta * global::ui::g_scroll_lerp_speed);
		} else m_smooth_scroll = global::ui::g_position.y + (scroller_position * global::ui::g_option_scale);

		texture = get_texture(global::ui::m_scroller);
		draw_sprite_aligned(texture, { global::ui::g_position.x, m_smooth_scroll }, { global::ui::g_scale.x, global::ui::g_option_scale }, 0.f, global::ui::g_scroller);

		std::vector<std::shared_ptr<base_option>> options = menu::submenu::handler::get_current()->get_options();
		int count = (int)std::count_if(begin(options), end(options), [](std::shared_ptr<base_option> option) { return option->is_visible(); });
		int render_count = count;

		if (render_count > max_options) {
			render_count = max_options;
		}

		// footer
		texture = get_texture(global::ui::m_footer);
		draw_sprite_aligned(texture, { global::ui::g_position.x, global::ui::g_position.y + (render_count * global::ui::g_option_scale) }, { global::ui::g_scale.x, global::ui::g_option_scale }, 0.f, global::ui::g_footer);

		draw_sprite({ "commonmenu", "shop_arrows_upanddown" }, { global::ui::g_position.x + ((global::ui::g_scale.x) * 0.5f), global::ui::g_position.y + (render_count * global::ui::g_option_scale) + (global::ui::g_option_scale * 0.5f) }, { 0.015f, 0.027f }, 0.f, { 255, 255, 255, 255 });

		// option counter
		char counter[50];
		sprintf_s(counter, "%i ~s~&#8226; %i", current_option + 1, count);
		draw_text(counter, { global::ui::g_position.x + 0.004f, global::ui::g_position.y + (render_count * global::ui::g_option_scale) + 0.004f }, get_normalized_font_scale(global::ui::g_sub_header_font, 0.30f), global::ui::g_sub_header_font, global::ui::g_sub_header_text, JUSTIFY_RIGHT, { 0.f, (1.0f - (1.0f - (global::ui::g_position.x + (0.315f / 2.f) - (0.23f - global::ui::g_scale.x)) - .068f)) });
	}

	void renderer::render_title(std::string title) {
		if (global::ui::g_disable_title) return;
		std::transform(begin(title), end(title), begin(title), ::toupper);

		if (menu::submenu::handler::get_current() == main_menu::get()) {
			draw_text("~s~&#248;ZARK " VERSION_TYPE, { global::ui::g_position.x + 0.005f, global::ui::g_position.y - 0.061f }, 0.77f, global::ui::g_header_font, global::ui::g_title, JUSTIFY_LEFT);
		} else {
			std::string input_string = title;
			std::string final_string = title;

			float width = calculate_string_width(input_string, global::ui::g_header_font, 0.77f);
			while (width > global::ui::g_scale.x + (global::ui::g_header_font == menu::fonts::get_font_id("RDR") ? 0.055f : 0.f)) {
				if (input_string.length() > 0) {
					input_string.pop_back();

					while (input_string[input_string.size() - 1] == ' ') {
						input_string.pop_back();
					}
				}

				final_string = input_string + "...";
				width = calculate_string_width(final_string, global::ui::g_header_font, 0.77f);
			}


			draw_text(final_string, { global::ui::g_position.x + 0.005f, global::ui::g_position.y - 0.061f }, 0.77f, global::ui::g_header_font, global::ui::g_title, JUSTIFY_LEFT);
		}
	}

	void renderer::render_tooltip(std::string tooltip) {
		if (!tooltip.empty()) {
			global::ui::g_rendering_tooltip = tooltip;
			float y = 0.f;

			std::vector<std::shared_ptr<base_option>> options = menu::submenu::handler::get_current()->get_options();
			int count = (int)std::count_if(begin(options), end(options), [](std::shared_ptr<base_option> option) { return option->is_visible(); });

			if (count > base::get_max_options()) {
				y = global::ui::g_position.y + ((base::get_max_options() + 1) * global::ui::g_option_scale) + 0.0025f;
			} else {
				y = global::ui::g_position.y + ((count + 1) * global::ui::g_option_scale) + 0.0025f;
			}

			if (global::ui::g_rendering_color) {
				y += 0.032f;
			}

			float scaled_body_height = menu::renderer::get_normalized_font_scale(global::ui::g_tooltip_font, global::ui::g_option_height);
			native::set_text_font(global::ui::g_tooltip_font);
			native::set_text_scale(0.f, scaled_body_height);
			native::set_text_wrap(global::ui::g_position.x + 0.004f, (1.0f - (1.0f - (global::ui::g_position.x + 0.1575f - (0.23f - global::ui::g_scale.x)) - global::ui::g_wrap)));
			native::begin_text_command_line_count("STRING");
			native::add_text_component_substring_player_name(tooltip.c_str());

			float height = global::ui::g_option_scale;

			int lines = native::end_text_command_get_line_count(global::ui::g_position.x + 0.004f, y + 0.005f);
			if (lines > 1) {
				height = (lines * native::get_text_scale_height(scaled_body_height, global::ui::g_tooltip_font)) + (0.005f * lines) + 0.005f;
			}

			std::pair<std::string, std::string> texture = get_texture(global::ui::m_tooltip_background);
			draw_sprite_aligned(texture, { global::ui::g_position.x, y }, { global::ui::g_scale.x, height }, 0.f, global::ui::g_tooltip);
			draw_text(tooltip.c_str(), { global::ui::g_position.x + 0.004f, y + 0.005f }, scaled_body_height, global::ui::g_tooltip_font, { 255, 255, 255, 255 }, JUSTIFY_LEFT, { global::ui::g_position.x + 0.004f, (1.0f - (1.0f - (global::ui::g_position.x + 0.1575f - (0.23f - global::ui::g_scale.x)) - global::ui::g_wrap)) });
		}

		global::ui::g_rendering_color = false;
	}

	void renderer::render_open_tooltip() {
		if (!global::ui::g_render_tooltip) return;

		static localization* names[] = {
			&t_tooltip_1,
			&t_tooltip_2,
			&t_tooltip_3,
			&t_tooltip_4,
			&t_tooltip_5,
			&t_tooltip_6,
			&t_tooltip_7,
			&t_tooltip_8,
			&t_tooltip_9,
			&t_tooltip_10,
			&t_tooltip_11,
			&t_tooltip_13,
			&t_tooltip_14,
			&t_tooltip_15,
			&t_tooltip_16,
			&t_tooltip_17,
			&t_tooltip_19,
			&t_tooltip_20,
			&t_tooltip_21,
			&t_tooltip_22,
			&t_tooltip_23,
			&t_tooltip_24,
			&t_tooltip_25,
			&t_tooltip_26,
			&t_tooltip_27,
		};

		char text[200];

		std::random_device r;
		std::seed_seq seed2 { r(), r(), r(), r(), r(), r(), r(), r() };
		std::mt19937 rng(seed2);
		std::uniform_int_distribution<int> val(0, NUMOF(names) - 1);
		static const int value = val(rng);

		native::set_text_outline();

		if (native::is_input_disabled(2)) {
			sprintf_s(text, "%s\n~c~%s", names[value]->get().c_str(), menu::input::g_key_names[menu::base::get_open_key()]);
			draw_text(text, { 0.5f, 0.09f }, get_normalized_font_scale(global::ui::g_open_tooltip_font, 0.40f), global::ui::g_open_tooltip_font, global::ui::g_open_tooltip, JUSTIFY_CENTER);
		} else {
			sprintf_s(text, "%s\n~c~RB + RIGHT", names[value]->get().c_str());
			draw_text(text, { 0.5f, 0.09f }, get_normalized_font_scale(global::ui::g_open_tooltip_font, 0.40f), global::ui::g_open_tooltip_font, global::ui::g_open_tooltip, JUSTIFY_CENTER);
		}
	}

	void renderer::render_color_preview(color_rgba color) {
		global::ui::g_rendering_color = true;

		std::vector<std::shared_ptr<base_option>> options = menu::submenu::handler::get_current()->get_options();
		int count = (int)std::count_if(begin(options), end(options), [](std::shared_ptr<base_option> option) { return option->is_visible(); });

		if (count > base::get_max_options()) {
			count = base::get_max_options();
		}

		draw_rect({ global::ui::g_position.x, global::ui::g_position.y + ((count + 1) * global::ui::g_option_scale) + 0.0025f }, { global::ui::g_scale.x, global::ui::g_option_scale }, color);
	}

	float renderer::calculate_string_width(std::string string, int font, float scale) {
		native::begin_text_command_width("STRING");
		native::add_text_component_substring_player_name(string.c_str());
		native::set_text_scale(0.f, scale);
		return native::end_text_command_get_width(font);
	}

	float renderer::get_normalized_font_scale(int font, float scale) {
		switch (font) {
			case 0: return (scale * 1.0f);
			case 1: return (scale * 1.3f);
			case 2: return (scale * 1.11f);
			case 4: return (scale * 1.11f);
			case 7: return (scale * 1.29f);
		}

		return scale;
	}

	void renderer::draw_rect(math::vector2<float> position, math::vector2<float> scale, color_rgba color) {
		if (global::ui::g_stop_rendering) return;
		native::draw_rect(position.x + (scale.x * 0.5f), position.y + (scale.y * 0.5f), scale.x, scale.y, color.r, color.g, color.b, color.a, 0);
	}

	void renderer::draw_rect_unaligned(math::vector2<float> position, math::vector2<float> scale, color_rgba color) {
		if (global::ui::g_stop_rendering) return;
		native::draw_rect(position.x, position.y, scale.x, scale.y, color.r, color.g, color.b, color.a, 0);
	}

	void renderer::draw_outlined_rect(math::vector2<float> position, math::vector2<float> scale, float thickness, color_rgba box_color, color_rgba border_color) {
		if (global::ui::g_stop_rendering) return;

		draw_rect({ position.x, position.y }, { scale.x, scale.y }, box_color); // bg
		draw_rect({ position.x, position.y - thickness }, { scale.x, thickness }, border_color); // top
		draw_rect({ position.x, position.y + scale.y }, { scale.x, thickness }, border_color); // bottom

		draw_rect({ position.x - (thickness * 0.60f), position.y - thickness }, { (thickness * 0.60f), scale.y + (thickness * 2.f) }, border_color); // left
		draw_rect({ position.x + scale.x, position.y - thickness }, { (thickness * 0.60f), scale.y + (thickness * 2.f) }, border_color); // right
	}

	void renderer::draw_text(std::string text, math::vector2<float> position, float scale, int font, color_rgba color, eJustify justification, math::vector2<float> wrap) {
		if (global::ui::g_stop_rendering) return;
		native::set_text_wrap(wrap.x, wrap.y);

		if (justification != JUSTIFY_LEFT) {
			native::set_text_justification(justification == JUSTIFY_CENTER ? 0 : 2);
		}

		native::set_text_centre(justification == JUSTIFY_CENTER);
		native::set_text_scale(0.f, scale);
		native::set_text_colour(color.r, color.g, color.b, color.a);
		native::set_text_font(font);
		
		if (text.length() >= 98) {
			global::ui::g_render_queue[global::ui::g_render_queue_index] = text;
			global::ui::g_render_queue_index++;
			global::ui::g_render_queue_index %= 100;
		}

		native::begin_text_command_display_text("STRING");
		native::add_text_component_substring_player_name(text.c_str());
		native::end_text_command_display_text(position.x, position.y, 0);
	}

	void renderer::draw_sprite(std::pair<std::string, std::string> asset, math::vector2<float> position, math::vector2<float> scale, float rotation, color_rgba color) {
		if (global::ui::g_stop_rendering) return;

		if (!native::has_streamed_texture_dict_loaded(asset.first.c_str()) && asset.first != "ozarktextures") {
			native::request_streamed_texture_dict(asset.first.c_str(), true);
		}
		
		native::draw_sprite(asset.first.c_str(), asset.second.c_str(), position.x, position.y, scale.x, scale.y, rotation, color.r, color.g, color.b, color.a, 0);
	}

	void renderer::draw_sprite_aligned(std::pair<std::string, std::string> asset, math::vector2<float> position, math::vector2<float> scale, float rotation, color_rgba color) {
		if (global::ui::g_stop_rendering) return;

		if (!native::has_streamed_texture_dict_loaded(asset.first.c_str()) && asset.first != "ozarktextures") {
			native::request_streamed_texture_dict(asset.first.c_str(), true);
		}
		
		native::draw_sprite(asset.first.c_str(), asset.second.c_str(), position.x + (scale.x * 0.5f), position.y + (scale.y * 0.5f), scale.x, scale.y, rotation, color.r, color.g, color.b, color.a, TRUE);
	}

	void renderer::draw_line(math::vector3<float> from, math::vector3<float> to, color_rgba color) {
		if (global::ui::g_stop_rendering) return;

		native::draw_line(from.x, from.y, from.z, to.x, to.y, to.z, color.r, color.g, color.b, color.a);
	}

	void renderer::draw_line_2d(math::vector3<float> from, math::vector3<float> to, color_rgba color) {
		if (global::ui::g_stop_rendering) return;

		if (global::ui::g_line_2d_index < 5000) {
			line_2d& line = global::ui::m_line_2d[global::ui::g_line_2d_index++];
			line.m_from.x = from.x;
			line.m_from.y = from.y;
			line.m_to.x = to.x;
			line.m_to.y = to.y;
			line.m_color = color;
		}
	}

	int renderer::get_render_count() {
		return m_render_count;
	}

	color_rgba renderer::hsv_to_rgb(float h, float s, float v, int original_alpha) {
		double r = 0.f, g = 0.f, b = 0.f;

		if (s == 0.f) {
			r = v;
			g = v;
			b = v;
		} else {
			int i;
			double f, p, q, t;

			if (h == 360.f) {
				h = 0.f;
			} else h = h / 60.f;

			i = (int)trunc(h);
			f = h - i;

			p = v * (1.f - s);
			q = v * (1.f - (s * f));
			t = v * (1.f - (s * (1.f - f)));

			switch (i) {
				case 0: r = v; g = t; b = p; break;
				case 1: r = q; g = v; b = p; break;
				case 2: r = p; g = v; b = t; break;
				case 3: r = p; g = q; b = v; break;
				case 4: r = t; g = p; b = v; break;
				default: r = v; g = p; b = q; break;
			}
		}

		return color_rgba((int)(r * 255.f), (int)(g * 255.f), (int)(b * 255.f), original_alpha);
	}

	color_hsv renderer::rgb_to_hsv(color_rgba in) {
		color_hsv out;

#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c)  (fmaxf(a, fmaxf(b, c)))

		float r = in.r / 255.0f;
		float g = in.g / 255.0f;
		float b = in.b / 255.0f;

		float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

		float max = max_f(r, g, b);
		float min = min_f(r, g, b);

		v = max;

		if (max == 0.0f) {
			s = 0;
			h = 0;
		} else if (max - min == 0.0f) {
			s = 0;
			h = 0;
		} else {
			s = (max - min) / max;

			if (max == r) {
				h = 60 * ((g - b) / (max - min)) + 0;
			} else if (max == g) {
				h = 60 * ((b - r) / (max - min)) + 120;
			} else {
				h = 60 * ((r - g) / (max - min)) + 240;
			}
		}

		if (h < 0) h += 360.0f;

		out.h = h;
		out.s = s;
		out.v = v;

		return out;
	}

	renderer* get_renderer() {
		static renderer instance;
		return &instance;
	}
}