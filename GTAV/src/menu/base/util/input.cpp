#include "Input.h"
#include "menu/base/base.h"
#include "menu/base/submenu_handler.h"
#include "global/vars.h"
#include "rage/invoker/natives.h"
#include "menu/base/submenus/main/misc/scripthook.h"

namespace menu::input {
	LRESULT APIENTRY input::window_process_callback(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
		switch (msg) {
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP: {
				if (param < 255) {
					get_input()->m_key_states[param].m_time = GetTickCount();
					get_input()->m_key_states[param].m_is_with_alt = (msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP);
					get_input()->m_key_states[param].m_was_down_before = (lparam >> 30) & 1;
					get_input()->m_key_states[param].m_is_up_now = (msg == WM_SYSKEYUP || msg == WM_KEYUP);
					if (!get_input()->m_key_states[param].m_was_down_before) get_input()->m_key_states[param].m_just_down = !(msg == WM_SYSKEYUP || msg == WM_KEYUP);

					if (get_input()->m_key_states[param].m_is_up_now) {
						get_input()->set_last_key((int)param);
					}
				}

				for (auto function : misc::scripthook::vars::m_vars.m_keyboards) {
					function((uint32_t)param, lparam & 0xFFFF, (lparam >> 16) & 0xFF, (lparam >> 24) & 1, (msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP), (lparam >> 30) & 1, (msg == WM_SYSKEYUP || msg == WM_KEYUP));
				}

				break;
			}
		}

		return CallWindowProc(get_input()->get_windows_process(), hwnd, msg, param, lparam);
	}

	void input::update() {
		if (!m_windows_process) {
			m_windows_process = (WNDPROC)SetWindowLongPtrA(global::vars::g_window, GWLP_WNDPROC, (LONG_PTR)window_process_callback);
		}

		if (menu::base::is_input_disabled()) return;

		static uint32_t counter = 0;
		static int delay = 150;

		if (counter < GetTickCount()) {
			if (is_open_bind_pressed()) {
				native::play_sound_frontend(-1, "Back", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
				menu::base::set_open(!menu::base::is_open());
				counter = GetTickCount() + 300;
			} else {
				if (menu::base::is_open()) {
					if (is_pressed(true, VK_NUMPAD8) || is_pressed(false, ControlFrontendUp)) {
						if (menu::base::get_current_option() == 0) {
							scroll_bottom();
						} else {
							scroll_up();
						}

						if (delay > 120) delay -= 15;
					} else if (is_pressed(true, VK_NUMPAD2) || is_pressed(false, ControlFrontendDown)) {
						if (menu::base::get_current_option() >= menu::submenu::handler::get_total_options() - 1) {
							scroll_top();
						} else {
							scroll_down();
						}
					} else if (is_just_pressed(true, VK_NUMPAD0) || is_just_released(false, ControlFrontendCancel)) {
						menu::submenu::handler::set_submenu_previous(false);
						native::play_sound_frontend(-1, "Back", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
					} else {
						delay = 150;
						return;
					}

					if (delay > 80) delay -= 15;
					counter = GetTickCount() + delay;
				}
			}
		}
	}

	void input::scroll_up(bool disable_sound) {
		if (menu::submenu::handler::get_total_options() == 0) return;
		menu::base::set_current_option(menu::base::get_current_option() - 1);

		if ((menu::base::get_scroll_offset() > 0 && menu::base::get_current_option() - menu::base::get_scroll_offset() == -1))
			menu::base::set_scroll_offset(menu::base::get_scroll_offset() - 1);

		if (!disable_sound) native::play_sound_frontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		menu::base::set_break_scroll(1);
	}

	void input::scroll_down(bool disable_sound) {
		if (menu::submenu::handler::get_total_options() == 0) return;
		menu::base::set_current_option(menu::base::get_current_option() + 1);

		if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() 
			&& menu::base::get_current_option() - menu::base::get_scroll_offset() == menu::base::get_max_options())
			menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);

		if (!disable_sound) native::play_sound_frontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		menu::base::set_break_scroll(2);
	}

	void input::scroll_bottom(bool disable_sound) {
		if (menu::submenu::handler::get_total_options() == 0) return;
		menu::base::set_current_option(menu::submenu::handler::get_total_options() - 1);

		if (menu::submenu::handler::get_total_options() >= menu::base::get_max_options()) menu::base::set_scroll_offset(menu::submenu::handler::get_total_options() - menu::base::get_max_options());

		int current_option = base::get_current_option();
		int max_options = base::get_max_options();
		int scroll_offset = base::get_scroll_offset();
		int total_options = menu::submenu::handler::get_total_options();
		int scroller_position = math::clamp(current_option - scroll_offset > max_options ? max_options : current_option - scroll_offset, 0, max_options);
		menu::renderer::set_smooth_scroll(global::ui::g_position.y + (scroller_position * global::ui::g_option_scale));
		
		if (!disable_sound) native::play_sound_frontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		menu::base::set_break_scroll(3);
	}

	void input::scroll_top(bool disable_sound) {
		if (menu::submenu::handler::get_total_options() == 0) return;

		menu::base::set_current_option(0);
		menu::base::set_scroll_offset(0);

		int current_option = base::get_current_option();
		int max_options = base::get_max_options();
		int scroll_offset = base::get_scroll_offset();
		int total_options = menu::submenu::handler::get_total_options();
		int scroller_position = math::clamp(current_option - scroll_offset > max_options ? max_options : current_option - scroll_offset, 0, max_options);
		menu::renderer::set_smooth_scroll(global::ui::g_position.y + (scroller_position * global::ui::g_option_scale));

		if (!disable_sound) native::play_sound_frontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		menu::base::set_break_scroll(4);
	}

	bool input::is_just_released(bool keyboard, int key, bool override_input) {
		if (menu::base::is_input_disabled() && !override_input) return false;

		if (keyboard) {
			bool result = GetTickCount() < (m_key_states[key].m_time + 100) && m_key_states[key].m_is_up_now;
			memset(&m_key_states[key], 0, sizeof(m_key_states[0]));
			return result;
		}

		return native::is_disabled_control_just_released(0, key);
	}

	bool input::is_just_pressed(bool keyboard, int key, bool override_input) {
		if (menu::base::is_input_disabled() && !override_input) return false;


		if (keyboard) {
			bool result = GetTickCount() - 100 < m_key_states[key].m_time && !m_key_states[key].m_is_up_now && m_key_states[key].m_just_down;
			if (result) m_key_states[key].m_just_down = false;
			return result;

			// return ((GetAsyncKeyState(key) & 0xFFFF) == 0x8001);
		}

		return native::is_disabled_control_just_pressed(0, key);
	}

	bool input::is_pressed(bool keyboard, int key, bool override_input) {
		if (menu::base::is_input_disabled() && !override_input) return false;

		if (keyboard) {
			return GetTickCount() < (m_key_states[key].m_time + 600000) && !m_key_states[key].m_is_up_now;
			// return (GetAsyncKeyState(key) & 0x8000);
		}

		return native::is_disabled_control_pressed(0, key);
	}

	bool input::is_open_bind_pressed(bool override_input) {
		return (is_pressed(false, ControlFrontendRb) && is_pressed(false, ControlFrontendRight)) || is_pressed(true, menu::base::get_open_key(), override_input);
	}

	bool input::is_option_pressed(bool override_input) {
		if (menu::base::is_input_disabled() && !override_input) return false;

		if (native::is_disabled_control_just_released(0, ControlFrontendAccept) || is_just_pressed(true, VK_NUMPAD5, override_input)) {
			native::play_sound_frontend(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
			return true;
		}

		return false;
	}

	bool input::is_left_just_pressed(bool override_input) {
		if (menu::base::is_input_disabled() && !override_input) return false;
		return is_just_pressed(false, ControlFrontendLeft) || is_just_pressed(true, VK_NUMPAD4, override_input);
	}

	bool input::is_right_just_pressed(bool override_input) {
		if (menu::base::is_input_disabled() && !override_input) return false;
		return is_just_pressed(false, ControlFrontendRight) || is_just_pressed(true, VK_NUMPAD6, override_input);
	}

	bool input::is_left_pressed(bool override_input) {
		if (menu::base::is_input_disabled() && !override_input) return false;
		return is_pressed(false, ControlFrontendLeft) || is_pressed(true, VK_NUMPAD4, override_input);
	}

	bool input::is_right_pressed(bool override_input) {
		if (menu::base::is_input_disabled() && !override_input) return false;
		return is_pressed(false, ControlFrontendRight) || is_pressed(true, VK_NUMPAD6, override_input);
	}

	void input::cleanup() {
		SetWindowLongPtrA(global::vars::g_window, GWLP_WNDPROC, (LONG_PTR)m_windows_process);
	}

	input* get_input() {
		static input instance;
		return &instance;
	}
}