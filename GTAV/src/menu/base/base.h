#pragma once
#include "stdafx.h"

typedef enum {
	SCROLL,
	TOGGLE,
	SCROLLSELECT
} scroll_option_type;

namespace menu::base {
	class base {
	public:
		void update();
		bool is_option_selected(int option);

		void set_max_options(int val) {
			m_max_options = val;
		}

		void set_current_option(int val) {
			m_current_option = val;
		}

		void set_scroll_offset(int val) {
			m_scroll_offset = val;
		}

		void set_break_scroll(int val) {
			m_break_scroll = val;
		}

		void set_open(bool open) {
			m_open = open;
		}

		void set_disable_input_this_frame() {
			m_disable_input_this_frame = true;
		}

		void set_keyboard_title(std::string title) {
			m_keyboard_title = title;
		}

		int get_max_options() {
			return m_max_options;
		}

		int get_current_option() {
			return m_current_option;
		}

		int get_scroll_offset() {
			return m_scroll_offset;
		}

		int get_break_scroll() {
			return m_break_scroll;
		}

		bool is_input_disabled() {
			return m_input_disabled;
		}

		bool is_open() {
			return m_open;
		}

		std::string get_keyboard_title() {
			return m_keyboard_title;
		}

		void set_open_key(int key) {
			m_open_key = key;
		}

		int get_open_key() {
			return m_open_key;
		}
	private:
		bool m_open;
		int m_open_key = VK_F4;
		bool m_disable_input_this_frame;
		bool m_input_disabled;
		
		int m_max_options = 13;
		int m_current_option;
		int m_scroll_offset;
		int m_break_scroll;

		std::string m_keyboard_title = "";
	};

	base* get_base();

	inline void update() {
		get_base()->update();
	}

	inline bool is_option_selected(int option) {
		return get_base()->is_option_selected(option);
	}

	inline int get_max_options() {
		return get_base()->get_max_options();
	}

	inline int get_current_option() {
		return get_base()->get_current_option();
	}

	inline int get_scroll_offset() {
		return get_base()->get_scroll_offset();
	}

	inline int get_break_scroll() {
		return get_base()->get_break_scroll();
	}

	inline std::string get_keyboard_title() {
		return get_base()->get_keyboard_title();
	}

	inline bool is_open() {
		return get_base()->is_open();
	}

	inline bool is_input_disabled() {
		return get_base()->is_input_disabled();
	}

	inline void set_max_options(int val) {
		get_base()->set_max_options(val);
	}

	inline void set_current_option(int val) {
		get_base()->set_current_option(val);
	}

	inline void set_scroll_offset(int val) {
		get_base()->set_scroll_offset(val);
	}

	inline void set_break_scroll(int val) {
		get_base()->set_break_scroll(val);
	}

	inline void set_open(bool open) {
		get_base()->set_open(open);
	}

	inline void set_keyboard_title(std::string title) {
		get_base()->set_keyboard_title(title);
	}

	inline void set_disable_input_this_frame() {
		get_base()->set_disable_input_this_frame();
	}

	inline void set_open_key(int key) {
		get_base()->set_open_key(key);
	}

	inline int get_open_key() {
		return get_base()->get_open_key();
	}
}