#pragma once
#include "stdafx.h"
#include "option.h"
#include "util/localization.h"
#include "util/va.h"
#include "menu/base/base.h"
#include "menu/base/renderer.h"
#include "menu/base/util/input.h"
#include "menu/base/util/menu_input.h"
#include "menu/base/util/notify.h"
#include "global/vars.h"
#include "rage/invoker/natives.h"
#include <timeapi.h>

template<typename Type>
struct scroll_struct {
	localization m_name;
	Type m_result;
};

template<typename Type>
class scroll_option : public base_option {
public:
	scroll_option(scroll_option_type type, std::string name)
		: base_option(name, false, true), m_type(type)
	{}

	scroll_option& add_scroll(int& num, int min_, int max_, scroll_struct<Type>* structure) {
		m_has_min = true;
		m_has_max = true;
		m_min = min_;
		m_max = max_ - 1;
		m_number = &num;

		if (*m_number < m_min) *m_number = m_min;
		if (*m_number > m_max) *m_number = m_max;

		m_number_cache = *m_number;
		m_scroll = structure;
		return *this;
	}

	scroll_option& add_toggle(bool& t) {
		m_toggle = &t;
		m_toggle_cache = t;
		return *this;
	}

	scroll_option& add_click(std::function<void()> function) {
		m_on_click = function;
		return *this;
	}

	scroll_option& add_requirement(std::function<bool()> function) {
		m_requirement = function;
		return *this;
	}

	scroll_option& add_update(std::function<void(scroll_option*, int)> function) {
		m_on_update = function;
		return *this;
	}

	scroll_option& add_hover(std::function<void()> function) {
		m_on_hover = function;
		return *this;
	}

	scroll_option& add_tooltip(std::string tooltip) {
		m_tooltip.set(tooltip.c_str());
		return *this;
	}

	scroll_option& add_translate() {
		m_name.set_translate(true);
		m_tooltip.set_translate(true);
		return *this;
	}

	scroll_option& add_hotkey() {
		m_has_hotkey = true;
		return *this;
	}

	scroll_option& set_scroll_speed(uint32_t speed) {
		m_scroll_speed = speed;
		return *this;
	}

	scroll_option& loop() {
		m_loop = true;
		return *this;
	}

	scroll_option& add_offset(float offset) {
		m_offset = offset;
		return *this;
	}

	scroll_option& add_savable(std::stack<std::string> menu_stack) {
		if (menu_stack.size() <= 0) return *this;

		m_savable = true;
		if (m_toggle && m_requirement()) {
			*m_number = util::config::read_int(menu_stack, m_name.get_original().c_str(), (int)*m_number, { "Values" });
			m_number_cache = *m_number;

			if (m_type == TOGGLE && m_toggle) {
				*m_toggle = util::config::read_bool(menu_stack, m_name.get_original().c_str(), *m_toggle);
				m_toggle_cache = *m_toggle;

				if (*m_toggle) {
					m_on_click();
				}
			}
		}

		return *this;
	}

	void render(int position) {
		bool selected = menu::base::is_option_selected(position);
		color_rgba color = selected ? global::ui::g_option_selected : global::ui::g_option;

		m_on_update(this, position);

		menu::renderer::draw_text(m_name.get(), { global::ui::g_position.x + 0.004f + m_offset, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color);

		int size = 26;
		if (global::vars::g_desktop_resolution.x == 5120) {
			size = 20;
		}

		char name_buffer[512];
		/*if (selected) {
			sprintf_s(name_buffer, ("~s~<font face='$Font2' size='" + std::to_string(size) + "'>&#8592;</font> %s ~s~<font face='$Font2' size='" + std::to_string(size) + "'>&#8594;</font> ~m~[%i/%i]").c_str(), m_scroll[*m_number].m_name.get().c_str(), (*m_number) + 1, m_max + 1);
		} else {
			sprintf_s(name_buffer, "%s ~m~[%i/%i]", m_scroll[*m_number].m_name.get().c_str(), (*m_number) + 1, m_max + 1);
		}*/

		sprintf_s(name_buffer, "%s ~m~[%i/%i]", m_scroll[*m_number].m_name.get().c_str(), (*m_number) + 1, m_max + 1);

		switch (m_type) {
			case TOGGLE:
				menu::renderer::draw_sprite({ "ozarktextures", "toggle_circle.png" }, { global::ui::g_position.x + global::ui::g_toggle_position.x - (0.23f - global::ui::g_scale.x), (global::ui::g_position.y + global::ui::g_toggle_position.y) + (position * global::ui::g_option_scale) }, global::ui::g_toggle_scale, 0.f, *m_toggle ? global::ui::g_toggle_on : global::ui::g_toggle_off);
				menu::renderer::draw_text(name_buffer, { global::ui::g_position.x + 0.004f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color, JUSTIFY_RIGHT, { 0.f, (1.0f - (1.0f - (global::ui::g_position.x + (0.315f / 2.f)) - global::ui::g_wrap + (0.22f - global::ui::g_scale.x))) - 0.016f });
				break;

			case SCROLL:
			case SCROLLSELECT:
				menu::renderer::draw_text(name_buffer, { global::ui::g_position.x + 0.004f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color, JUSTIFY_RIGHT, { 0.f, (1.0f - (1.0f - (global::ui::g_position.x + (0.315f / 2.f)) - global::ui::g_wrap + (0.22f - global::ui::g_scale.x))) - 0.005f });
				break;
		}
	}

	void render_selected(int position, std::stack<std::string> submenu_name_stack) {
		m_on_hover();

		if (m_requirement() && menu::input::is_option_pressed()) {
			if (m_type == TOGGLE) {
				*m_toggle = !*m_toggle;
			}

			m_on_click();
		}

		if (m_savable) {
			if (m_number_cache != *m_number) {
				m_number_cache = *m_number;

				util::config::write_int(submenu_name_stack, m_name.get_original().c_str(), *m_number, { "Values" });
			}

			if (m_type == TOGGLE) {
				if (m_toggle_cache != *m_toggle) {
					m_toggle_cache = *m_toggle;
					util::config::write_bool(submenu_name_stack, m_name.get_original().c_str(), *m_toggle);
				}
			}
		}

		if (m_has_hotkey && m_requirement()) {
			if (menu::input::is_just_released(true, VK_F12)) {
				native::play_sound_frontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);

				menu::input::push([this] {
					menu::input::hotkey(m_name.get(), this);
				});
			}
		}

		if (menu::input::is_left_just_pressed()) {
			if (!m_left_disabled) {
				*m_number -= 1;
				if (m_loop) {
					if (*m_number < m_min) *m_number = m_max;
				} else if (*m_number < m_min && m_has_min) *m_number = m_min;

				if (m_type == SCROLL || m_type == TOGGLE) {
					m_on_click();
				}

				native::play_sound_frontend(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
			}

			m_left_disabled = false;
			m_left_timer = 0;
		}

		if (menu::input::is_right_just_pressed()) {
			if (!m_right_disabled) {
				*m_number += 1;
				if (m_loop) {
					if (*m_number > m_max) *m_number = m_min;
				} else if (*m_number > m_max && m_has_max) *m_number = m_max;

				if (m_type == SCROLL || m_type == TOGGLE) {
					m_on_click();
				}

				native::play_sound_frontend(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
			}

			m_right_disabled = false;
			m_right_timer = 0;
		}

		static uint32_t timer = 0;

		if (menu::input::is_left_pressed()) {
			if (++m_left_timer > 20) {
				m_left_disabled = true;
				if ((timeGetTime() - timer) > m_scroll_speed) {
					*m_number -= 1;
					if (m_loop) {
						if (*m_number < m_min) *m_number = m_max;
					} else if (*m_number < m_min && m_has_min) *m_number = m_min;

					if (m_type == SCROLL || m_type == TOGGLE) {
						m_on_click();
					}

					timer = timeGetTime();
					native::play_sound_frontend(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
				}
			}
		}

		if (menu::input::is_right_pressed()) {
			if (++m_right_timer > 20) {
				m_right_disabled = true;
				if ((timeGetTime() - timer) > m_scroll_speed) {
					*m_number += 1;
					if (m_loop) {
						if (*m_number > m_max) *m_number = m_min;
					} else if (*m_number > m_max && m_has_max) *m_number = m_max;

					if (m_type == SCROLL || m_type == TOGGLE) {
						m_on_click();
					}

					timer = timeGetTime();
					native::play_sound_frontend(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
				}
			}
		}
	}

	void invoke_save(std::stack<std::string> submenu_name_stack) {}

	void invoke_hotkey() {
		if (!m_requirement()) return;

		if (m_type == TOGGLE) {
			*m_toggle = !*m_toggle;
		}

		m_on_click();
		
		static std::unordered_map<uint32_t, uint32_t> notifies;
		if (notifies[native::get_hash_key(m_name.get_original().c_str())] > GetTickCount()) return;

		notifies[native::get_hash_key(m_name.get_original().c_str())] = GetTickCount() + 5000;
		menu::notify::stacked(TRANSLATE(t_hotkey), util::va::va("%s %s", TRANSLATE(t_used_hotkey_for), m_name.get().c_str()));
	}

	void write_translation(nlohmann::json& object) {
		for (int i = 0; i < m_max + 1; i++) {
			if (m_scroll[i].m_name.has_translation()) {
				if (object["scrollables"][m_scroll[i].m_name.get_original()].empty()) {
					object["scrollables"][m_scroll[i].m_name.get_original()] = m_scroll[i].m_name.get_original();
				}
			}
		}
	}

	void read_translation(nlohmann::json& object) {
		for (int i = 0; i < m_max + 1; i++) {
			if (m_scroll[i].m_name.has_translation()) {
				std::string name = m_scroll[i].m_name.get_original();
				m_scroll[i].m_name.set_mapped(JsonGet<std::string>(object["scrollables"], name, name).c_str());
			}
		}
	}

	void reset_translation() {
		for (int i = 0; i < m_max + 1; i++) {
			if (m_scroll[i].m_name.has_translation()) {
				m_scroll[i].m_name.reset();
			}
		}
	}
private:
	std::function<void()> m_on_click = []() {};
	std::function<void()> m_on_hover = []() {};
	std::function<void(scroll_option*, int)> m_on_update = [](scroll_option*, int) {};

	scroll_option_type m_type = SCROLL;
	int* m_number = nullptr;
	int m_min = 0;
	int m_max = 0;
	int m_left_timer = 0;
	int m_right_timer = 0;

	bool* m_toggle = nullptr;
	bool m_has_min = false;
	bool m_has_max = false;
	bool m_loop = false;
	bool m_left_disabled = false;
	bool m_right_disabled = false;

	scroll_struct<Type>* m_scroll = nullptr;
	uint32_t m_scroll_speed = 200;
	float m_offset = 0.f;

	int m_number_cache = 0;
	bool m_toggle_cache = false;
};