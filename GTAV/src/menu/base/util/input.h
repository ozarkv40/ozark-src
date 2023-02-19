#pragma once
#include "stdafx.h"

namespace menu::input {
	class input {
	public:
		static LRESULT APIENTRY window_process_callback(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

		void update();
		void scroll_up(bool disable_sound = false);
		void scroll_down(bool disable_sound = false);
		void scroll_bottom(bool disable_sound = false);
		void scroll_top(bool disable_sound = false);
		void cleanup();

		bool is_just_released(bool keyboard, int key, bool override_input = false);
		bool is_just_pressed(bool keyboard, int key, bool override_input = false);
		bool is_pressed(bool keyboard, int key, bool override_input = false);

		bool is_open_bind_pressed(bool override_input = false);
		bool is_option_pressed(bool override_input = false);
		bool is_left_just_pressed(bool override_input = false);
		bool is_right_just_pressed(bool override_input = false);
		bool is_left_pressed(bool override_input = false);
		bool is_right_pressed(bool override_input = false);

		void set_last_key(int key) { m_last_key = key; }

		WNDPROC get_windows_process() { return m_windows_process; }
		int get_last_key() { return m_last_key; }
	private:
		struct KeyboardState {
			uint32_t m_time;
			bool m_is_with_alt;
			bool m_was_down_before;
			bool m_is_up_now;
			bool m_just_up;
			bool m_just_down;
		};

		KeyboardState m_key_states[255];
		WNDPROC m_windows_process;
		int m_last_key;
	};

	input* get_input();

	inline void update() {
		get_input()->update();
	}

	inline void scroll_up(bool disable_sound = false) {
		get_input()->scroll_up(disable_sound);
	}

	inline void scroll_down(bool disable_sound = false) {
		get_input()->scroll_down(disable_sound);
	}

	inline void scroll_bottom(bool disable_sound = false) {
		get_input()->scroll_bottom(disable_sound);
	}

	inline void scroll_top(bool disable_sound = false) {
		get_input()->scroll_top(disable_sound);
	}

	inline void cleanup() {
		get_input()->cleanup();
	}

	inline bool is_just_released(bool keyboard, int key, bool override_input = false) {
		return get_input()->is_just_released(keyboard, key, override_input);
	}

	inline bool is_just_pressed(bool keyboard, int key, bool override_input = false) {
		return get_input()->is_just_pressed(keyboard, key, override_input);
	}

	inline bool is_pressed(bool keyboard, int key, bool override_input = false) {
		return get_input()->is_pressed(keyboard, key, override_input);
	}

	inline bool is_open_bind_pressed(bool override_input = false) {
		return get_input()->is_open_bind_pressed(override_input);
	}

	inline bool is_option_pressed(bool override_input = false) {
		return get_input()->is_option_pressed(override_input);
	}

	inline bool is_left_just_pressed(bool override_input = false) {
		return get_input()->is_left_just_pressed(override_input);
	}

	inline bool is_right_just_pressed(bool override_input = false) {
		return get_input()->is_right_just_pressed(override_input);
	}

	inline bool is_left_pressed(bool override_input = false) {
		return get_input()->is_left_pressed(override_input);
	}

	inline bool is_right_pressed(bool override_input = false) {
		return get_input()->is_right_pressed(override_input);
	}

	inline void set_last_key(int key) {
		get_input()->set_last_key(key);
	}

	inline WNDPROC get_windows_process() {
		return get_input()->get_windows_process();
	}

	inline int get_last_key() {
		return get_input()->get_last_key();
	}
}