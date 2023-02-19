#include "notify.h"
#include "rage/invoker/natives.h"
#include "menu/base/renderer.h"
#include "util/log.h"
#include "menu/base/util/helpers.h"

namespace menu::notify {
	localization t_blocked("Blocked", true, true);
	localization t_incoming_event("Incoming Event", true, true);
	localization t_event("Event", true, true);
	localization t_from("From", true, true);
	localization t_redirected("Redirected", true, true);

	void notify::update() {
		if (global::ui::g_stop_rendering) {
			for (auto& context = m_context.begin(); context != m_context.end(); context++) {
				context->m_start_time = GetTickCount();
			}

			return;
		}

		float current = 0.f;
		for (auto& context = m_context.begin(); context != m_context.end(); context++) {
			float wrap = 0.1362f;
			float x_offset = 0.006f;
			float text_height = 0.2f;

			if (context->m_has_init) {
				continue;
			}

			context->m_has_init = true;

			if (context->m_text.size() == 1) {
				native::set_text_font(0);
				native::set_text_scale(0.f, text_height);
				native::set_text_wrap(context->x + x_offset, wrap);
				native::begin_text_command_line_count("STRING");
				native::add_text_component_substring_player_name(context->m_text[0].c_str());

				context->m_lines = native::end_text_command_get_line_count(context->x + x_offset, 0.015f);
				current += (context->m_lines * native::get_text_scale_height(text_height, 0)) + (context->m_lines * x_offset) + (x_offset * 3.f);
			} else {
				context->m_max_width = menu::renderer::calculate_string_width(context->m_text[0], 0, text_height) + (x_offset * 2.f);

				for (std::size_t i = 0; i < context->m_text.size(); i++) {
					std::string str = context->m_text[i];

					float width = menu::renderer::calculate_string_width(str, 0, text_height) + (x_offset * 2.f);
					if (context->m_max_width < width) {
						context->m_max_width = width;
					}
				}

				context->m_lines = (int)context->m_text.size();
				current += (context->m_lines * native::get_text_scale_height(text_height, 0)) + (context->m_lines * x_offset) + (x_offset * 3.f);
			}

			current += 0.004f;
			context->m_y = -current;
		}

		float y = 0.01f;
		for (auto& context = m_context.rbegin(); context != m_context.rend(); context++) {
			float x_offset = 0.006f;
			float wrap = context->m_max_width + x_offset;
			float text_height = 0.2f;
			float height = (text_height / 10.f) + ((text_height * 1.1f) / 10.f);
			bool death = false;

			float scaled_body_height = menu::renderer::get_normalized_font_scale(global::ui::g_notify_body_font, text_height);
			float scaled_title_height = menu::renderer::get_normalized_font_scale(global::ui::g_notify_title_font, text_height * 1.1f);

			// nearing death, slide out
			uint32_t end_time = context->m_start_time + context->m_time_limit;
			if (end_time < GetTickCount() || end_time - GetTickCount() < 1000) {
				death = true;
				context->m_y = math::lerp(context->m_y, 1.2f, 5.f * global::ui::g_delta);

				if (context->m_alpha_start == 0) context->m_alpha_start = GetTickCount();
				context->m_alpha = 255 - (((GetTickCount() - context->m_alpha_start) * 255) / 1000);
			} else {
				if (context->m_title_width > context->m_max_width) {
					wrap = context->m_title_width + x_offset;
				}
			}

			if (context->m_title_width == 0.f) {
				context->m_title_width = menu::renderer::calculate_string_width("~bold~" + context->m_title, global::ui::g_notify_title_font, scaled_title_height) + (0.004f * 2.f);
			}

			// if it has one bit of text, calculate the lines
			if (context->m_text.size() == 1) {
				native::set_text_font(global::ui::g_notify_body_font);
				native::set_text_scale(scaled_body_height, scaled_body_height);
				native::set_text_wrap(context->x, wrap - x_offset);
				native::begin_text_command_line_count("STRING");
				native::add_text_component_substring_player_name(context->m_text[0].c_str());

				context->m_lines = native::end_text_command_get_line_count(context->x, y + 0.005f);
				context->m_rendering_text = context->m_text[0];

				if (context->m_lines > 1) {
					height = (context->m_lines * native::get_text_scale_height(scaled_body_height, global::ui::g_notify_body_font)) + 0.034f;
				} else {
					context->m_max_width = menu::renderer::calculate_string_width(context->m_text[0], global::ui::g_notify_body_font, scaled_body_height) + (x_offset * 2.f);
				}
			} else {
				// its a list of lines, calculate the longest line and use that as the width
				std::string full_line = "";
				context->m_max_width = menu::renderer::calculate_string_width(context->m_text[0], global::ui::g_notify_body_font, scaled_body_height) + (x_offset * 2.f);

				for (std::size_t i = 0; i < context->m_text.size(); i++) {
					std::string str = context->m_text[i];

					float width = menu::renderer::calculate_string_width(str, global::ui::g_notify_body_font, scaled_body_height) + (x_offset * 2.f);
					if (context->m_max_width < width) {
						context->m_max_width = width;
					}

					full_line += str;

					if (i != (context->m_text.size() - 1)) {
						full_line += '\n';
					}
				}

				context->m_lines = (int)context->m_text.size();
				context->m_rendering_text = full_line;
				height = (context->m_lines * native::get_text_scale_height(scaled_body_height, global::ui::g_notify_body_font)) + 0.034f;
			}

			if (context->m_text.size() == 4) {
				height += 0.002f;
			}

			// lerp the Y position to account for new notifies
			if (!death) {
				context->m_y = math::lerp(context->m_y, y, 5.f * global::ui::g_delta);
			}

			if (context->m_y + height > 0.7f) {
				context->m_time_limit = 0;
			}

			if (context->m_y <= 1.f) {
				native::clear_help(true);
				native::clear_all_help_messages();

				int rect_alpha = context->m_alpha >= 35 ? context->m_alpha - 35 : 0;
				std::pair<std::string, std::string> texture = menu::renderer::get_texture(global::ui::m_notify_background);
				menu::renderer::draw_sprite_aligned(texture, { context->x, context->m_y }, { context->m_max_width, height }, 0.f, global::ui::g_notify_background.opacity(rect_alpha));

				texture = menu::renderer::get_texture(global::ui::m_notify_bar);
				menu::renderer::draw_sprite_aligned(texture, { context->x, context->m_y }, { 0.002f, height }, 0.f, context->m_color.opacity(rect_alpha));

				math::vector2<float> text_wrap = context->m_text.size() > 1 ? math::vector2<float>(0.f, 1.f) : math::vector2<float>(context->x, wrap);
				menu::renderer::draw_text(context->m_rendering_text, { context->x + x_offset, context->m_y + 0.02f + 0.001f }, scaled_body_height, global::ui::g_notify_body_font, { 255, 255, 255, context->m_alpha }, JUSTIFY_LEFT, text_wrap);
				menu::renderer::draw_text("~bold~" + context->m_title, { context->x + x_offset, context->m_y + 0.003f + 0.001f }, scaled_title_height, global::ui::g_notify_title_font, { 255, 255, 255, context->m_alpha }, JUSTIFY_LEFT);
				y += height + 0.004f;
			}
		}

		for (auto& context = m_context.begin(); context != m_context.end();) {
			if (context->m_start_time + context->m_time_limit < GetTickCount()) {
				context = m_context.erase(context);
				continue;
			}

			context++;
		}
	}

	void notify::stacked(std::string title, std::string text, color_rgba color, uint32_t timeout) {
		notify_context context;
		context.m_text.push_back(text);
		context.m_title = title;
		context.m_color = color;
		context.m_start_time = GetTickCount();
		context.m_time_limit = timeout;

		LOG_CUSTOM("Notify", "%s - %s", title.c_str(), text.c_str());
		m_context.push_back(context);
	}

	void notify::stacked_lines(std::string title, std::vector<std::string> text, color_rgba color) {
		notify_context context;
		for (std::string str : text) context.m_text.push_back(str);

		context.m_title = title;
		context.m_color = color;
		context.m_start_time = GetTickCount();
		context.m_time_limit = 6000;

		m_context.push_back(context);
	}

	void notify::protection(std::string sender, std::string event, bool redirected, bool blocked) {
		uint32_t hash = native::get_hash_key((sender + event + std::to_string(redirected) + std::to_string(blocked)).c_str());

		if (m_protection_spam[hash] > GetTickCount()) {
			return;
		}

		m_protection_spam[hash] = GetTickCount() + 6000;

		if (!sender.empty()) {
			if (sender.compare("LLLLLLLLLLLLLLLLLLLLLLLL")) {
				sender = menu::helpers::clean_name(sender);
			}
		}

		std::vector<std::string> lines;
		if (blocked) lines.push_back(std::string(TRANSLATE(t_blocked)) + " " + TRANSLATE(t_incoming_event));
		else lines.push_back(TRANSLATE(t_incoming_event));

		lines.push_back(std::string(TRANSLATE(t_event)) + ": " + event);

		if (sender.compare("LLLLLLLLLLLLLLLLLLLLLLLL")) {
			lines.push_back(std::string(TRANSLATE(t_from)) + ": " + sender + "~w~");
		}

		if (redirected) {
			lines.push_back(TRANSLATE(t_redirected));
		}

		LOG_CUSTOM("Notify", "%s from %s", event.c_str(), sender != "LLLLLLLLLLLLLLLLLLLLLLLL" ? sender.c_str() : "?");
		stacked_lines("Protection", lines, global::ui::g_error);
	}

	void notify::subtitle(const char* msg) {
		native::begin_text_command_print("STRING");
		native::add_text_component_substring_player_name(msg);
		native::end_text_command_print(3000, true);
	}

	notify* get_notify() {
		static notify instance;
		return &instance;
	}
}