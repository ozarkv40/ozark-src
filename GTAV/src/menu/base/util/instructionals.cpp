#include "instructionals.h"
#include "rage/invoker/natives.h"
#include "global/ui_vars.h"

namespace instructionals {
	static const char* g_key_names_instructional[254] = {
		"F10",
		"F10",
		"F10",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"BACKSPACE",
		"TAB",
		"TAB",
		"TAB",
		"NUM 5",
		"ENTER",
		"ENTER",
		"ENTER",
		"SHIFT",
		"CTRL",
		"ALT",
		"ALT",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"ESC",
		"ESC",
		"ESC",
		"ESC",
		"ESC",
		"SPACE",
		"NUM 9",
		"NUM 3",
		"NUM 1",
		"NUM 7",
		"LEFT",
		"UP",
		"RIGHT",
		"DOWN",
		"NUM 2",
		"NUM 2",
		"NUM 2",
		"NUM 2",
		"NUM 0",
		"DELETE",
		"NUM DECIMAL",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Z",
		"Z",
		"Z",
		"Z",
		"Z",
		"N0",
		"N1",
		"N2",
		"N3",
		"N4",
		"N5",
		"N6",
		"N7",
		"N8",
		"N9",
		"*",
		"NUM PLUS",
		"NUM PLUS",
		"NUM SUB",
		"NUM DECIMAL",
		"/",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"Pause",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SHIFT",
		"RIGHT SHIFT",
		"CTRL",
		"CTRL",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"M",
		"D",
		"C",
		"B",
		"P",
		"Q",
		"J",
		"G",
		"G",
		"G",
		"G",
		"F",
		"F",
		"F",
		";",
		"=",
		",",
		"-",
		".",
		"/",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"[",
		"null",
		"]",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null"
	};

	void instructionals::setup() {
		if (!native::has_scaleform_movie_loaded(m_handle)) {
			m_handle = native::request_scaleform_movie("instructional_buttons");
			return;
		}

		native::push_scaleform_movie_function(m_handle, "CLEAR_ALL");
		native::pop_scaleform_movie_function_void();

		native::push_scaleform_movie_function(m_handle, "TOGGLE_MOUSE_BUTTONS");
		native::push_scaleform_movie_function_parameter_bool(1);
		native::pop_scaleform_movie_function_void();

		native::push_scaleform_movie_function(m_handle, "SET_MAX_WIDTH");
		native::push_scaleform_movie_function_parameter_float(1.f);
		native::pop_scaleform_movie_function_void();
	}

	void instructionals::add_instructional(std::string text, eControls control) {
		native::push_scaleform_movie_function(m_handle, "SET_DATA_SLOT");
		native::push_scaleform_movie_function_parameter_int(m_count++);

		native::_0xE83A3E3557A56640(native::get_control_instructional_button(0, control, true)); // problem!

		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(text.c_str());
		native::end_text_command_scaleform_string();

		native::push_scaleform_movie_function_parameter_bool(true);
		native::push_scaleform_movie_function_parameter_int(control);

		native::pop_scaleform_movie_function_void();
	}

	void instructionals::add_instructional(std::string text, eScaleformButtons button_option) {
		native::push_scaleform_movie_function(m_handle, "SET_DATA_SLOT");
		native::push_scaleform_movie_function_parameter_int(m_count++);

		native::push_scaleform_movie_function_parameter_int(button_option);

		native::begin_text_command_scaleform_string("STRING");
		native::add_text_component_substring_player_name(text.c_str());
		native::end_text_command_scaleform_string();

		native::push_scaleform_movie_function_parameter_bool(true);
		native::push_scaleform_movie_function_parameter_int(button_option);

		native::pop_scaleform_movie_function_void();
	}

	void instructionals::add_instructional(std::string text, int vk) {
		native::push_scaleform_movie_function(m_handle, "SET_DATA_SLOT");
		native::push_scaleform_movie_function_parameter_int(m_count++);

		native::_0xE83A3E3557A56640(("t_" + (std::string)g_key_names_instructional[vk]).c_str());
		native::push_scaleform_movie_function_parameter_string(text.c_str());
		native::push_scaleform_movie_function_parameter_bool(true);
		native::push_scaleform_movie_function_parameter_int(vk);

		native::pop_scaleform_movie_function_void();
	}

	void instructionals::close() {
		native::push_scaleform_movie_function(m_handle, "SET_BACKGROUND_COLOUR");
		native::push_scaleform_movie_function_parameter_int(global::ui::g_instructional_background.r);
		native::push_scaleform_movie_function_parameter_int(global::ui::g_instructional_background.g);
		native::push_scaleform_movie_function_parameter_int(global::ui::g_instructional_background.b);
		native::push_scaleform_movie_function_parameter_int(80);
		native::pop_scaleform_movie_function_void();

		native::push_scaleform_movie_function(m_handle, "DRAW_INSTRUCTIONAL_BUTTONS");
		native::push_scaleform_movie_function_parameter_int(0);
		native::pop_scaleform_movie_function_void();

		native::draw_scaleform_movie_fullscreen(m_handle, 255, 255, 255, 255, 0);
		m_count = 0;
	}

	instructionals* get_instructionals() {
		static instructionals instance;
		return &instance;
	}
}