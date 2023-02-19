#include "button.h"
#include "menu/base/renderer.h"
#include "menu/base/util/instructionals.h"
#include "menu/base/util/input.h"
#include "menu/base/util/menu_input.h"
#include "menu/base/util/hotkeys.h"
#include "menu/base/util/notify.h"
#include "rage/invoker/natives.h"
#include "util/fiber_pool.h"
#include "util/fiber.h"
#include "util/va.h"

void button_option::render(int position) {
	bool selected = menu::base::is_option_selected(position);
	color_rgba color = selected ? global::ui::g_option_selected : global::ui::g_option;

	m_on_update(this);
	m_on_update_this(this, position);

	menu::renderer::draw_text(m_name.get(), { global::ui::g_position.x + 0.004f + m_offset, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color);

	if (m_keyboard.m_enabled) {
		menu::renderer::draw_sprite({ "ozarktextures", "keyboard.png" }, { global::ui::g_position.x + 0.209f - (0.22f - global::ui::g_scale.x), global::ui::g_position.y + 0.016f + (position * global::ui::g_option_scale) }, { 0.015f * 0.9f, 0.022f * 0.9f }, 0.f, { 255, 255, 255, 255 });
	} else if (m_sprite.m_enabled && m_sprite.m_requirement()) {
		color_rgba _color = color;
		std::string sprite_name = m_sprite.m_asset.second;
		if (strstr(sprite_name.c_str(), "shop_") && sprite_name.compare("shop_tick_icon")) {
			sprite_name += "_a";
			_color = { 255, 255, 255, 255 };
		}

		if (m_sprite.m_rotate) {
			m_sprite.m_rotation++;
			if (m_sprite.m_rotation > 360.f) {
				m_sprite.m_rotation = 0.f;
			}
		}

		menu::renderer::draw_sprite({ m_sprite.m_asset.first, sprite_name }, { global::ui::g_position.x + 0.2195f - (0.23f - global::ui::g_scale.x), global::ui::g_position.y + 0.016f + (position * global::ui::g_option_scale) }, m_sprite.m_scale, m_sprite.m_rotation, _color);
	}

	if (m_side_text.m_enabled) {
		float mod = 0.f;
		if (m_keyboard.m_enabled) {
			mod = 0.0135f + 0.002f;
		} else if (m_sprite.m_enabled && m_sprite.m_requirement()) {
			mod = m_sprite.m_scale.x + 0.002f;
		}

		menu::renderer::draw_text(m_side_text.m_text, { global::ui::g_position.x + 0.004f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color, JUSTIFY_RIGHT, { 0.f, (1.0f - (1.0f - (global::ui::g_position.x + (0.315f / 2.f)) - global::ui::g_wrap)) - 0.005f - mod });
	}
}

void button_option::render_selected(int position, std::stack<std::string> submenu_name_stack) {
	m_on_hover();

	if (m_instructionals.size()) {
		instructionals::setup();

		for (std::tuple<std::string, int, bool>& instructional : m_instructionals) {
			if (std::get<2>(instructional)) {
				instructionals::add_instructional(std::get<0>(instructional), (eControls)std::get<1>(instructional));
			} else {
				instructionals::add_instructional(std::get<0>(instructional), (eScaleformButtons)std::get<1>(instructional));
			}
		}

		instructionals::close();
	}

	if (m_requirement() && menu::input::is_option_pressed()) {
		m_on_click();
		m_on_click_this(this);

		if (m_keyboard.m_enabled) {
			m_keyboard.m_is_active = true;
			menu::base::set_keyboard_title(m_keyboard.m_title);
			native::display_onscreen_keyboard(0, "Ozark", "", m_keyboard.m_default_text.c_str(), "", "", "", m_keyboard.m_max_chars);
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

	if (m_keyboard.m_enabled) {
		if (m_keyboard.m_is_active) {
			int status = native::update_onscreen_keyboard();
			if (status == 0) {
				menu::base::set_disable_input_this_frame();
			} else if (status == 1) {
				if (m_keyboard.m_callback) {
					m_keyboard.m_callback(this, native::get_onscreen_keyboard_result());
				}

				m_keyboard.m_is_active = false;
			} else if (status > 1) {
				m_keyboard.m_is_active = false;
			}
		}
	}
}

void button_option::invoke_hotkey() {
	if (!m_requirement()) return;

	m_on_click();
	m_on_click_this(this);

	if (m_keyboard.m_enabled) {
		if (!m_keyboard.m_is_active) {
			m_keyboard.m_is_active = true;
			menu::base::set_keyboard_title(m_keyboard.m_title);

			util::fiber::pool::add([this] {
				native::display_onscreen_keyboard(0, "Ozark", "", "", "", "", "", m_keyboard.m_max_chars);

				while (m_keyboard.m_is_active) {
					util::fiber::go_to_main();

					int status = native::update_onscreen_keyboard();
					if (status == 0) {
						menu::base::set_disable_input_this_frame();
					} else if (status == 1) {
						if (m_keyboard.m_callback) {
							m_keyboard.m_callback(this, native::get_onscreen_keyboard_result());
						}

						m_keyboard.m_is_active = false;
					} else if (status > 1) {
						m_keyboard.m_is_active = false;
					}
				}
			});
		}
	}

	static std::unordered_map<uint32_t, uint32_t> notifies;
	if (notifies[native::get_hash_key(m_name.get_original().c_str())] > GetTickCount()) return;

	notifies[native::get_hash_key(m_name.get_original().c_str())] = GetTickCount() + 5000;
	menu::notify::stacked(TRANSLATE(t_hotkey), util::va::va("%s %s", TRANSLATE(t_used_hotkey_for), m_name.get().c_str()));
}