#pragma once
#include "stdafx.h"
#include "rage/types/base_types.h"
#include "util/localization.h"

namespace instructionals {
	static localization t_open_category("Open Category", true, true);
	static localization t_close_menu("Close Menu", true, true);
	static localization t_scroll("Scroll", true, true);
	static localization t_select("Select", true, true);
	static localization t_back("Back", true, true);
	static localization t_rainbow_config("Rainbow Config", true, true);
	static localization t_adjust("Adjust", true, true);
	static localization t_input("Input", true, true);
	static localization t_add_hotkey("Add Hotkey", true, true);

	class instructionals {
	public:
		void setup();
		void add_instructional(std::string text, eControls control);
		void add_instructional(std::string text, eScaleformButtons button_option);
		void add_instructional(std::string text, int vk);
		void close();
	private:
		int m_count = 0;
		int m_handle = 0;
	};

	instructionals* get_instructionals();

	inline void setup() {
		get_instructionals()->setup();
	}

	inline void add_instructional(std::string text, eControls control) {
		get_instructionals()->add_instructional(text, control);
	}

	inline void add_instructional(std::string text, eScaleformButtons button_option) {
		get_instructionals()->add_instructional(text, button_option);
	}

	inline void add_instructional(std::string text, int vk) {
		get_instructionals()->add_instructional(text, vk);
	}

	inline void close() {
		get_instructionals()->close();
	}

	inline void main_menu() {
		get_instructionals()->setup();
		get_instructionals()->add_instructional(TRANSLATE(t_open_category), ControlFrontendAccept);
		get_instructionals()->add_instructional(TRANSLATE(t_close_menu), ControlFrontendCancel);
		get_instructionals()->add_instructional(TRANSLATE(t_scroll), ARROW_UP_DOWN);
		get_instructionals()->close();
	}

	inline void standard(bool scroller, bool keyboard, bool hotkey) {
		get_instructionals()->setup();
		get_instructionals()->add_instructional(TRANSLATE(t_select), ControlFrontendAccept);
		get_instructionals()->add_instructional(TRANSLATE(t_back), ControlFrontendCancel);
		get_instructionals()->add_instructional(TRANSLATE(t_scroll), ARROW_UP_DOWN);

		if (scroller) get_instructionals()->add_instructional(TRANSLATE(t_adjust), ARROW_LEFT_RIGHT);
		if (keyboard) get_instructionals()->add_instructional(TRANSLATE(t_input), ControlPhoneSelect);
		if (hotkey) get_instructionals()->add_instructional(TRANSLATE(t_add_hotkey), VK_F12);

		get_instructionals()->close();
	}

	inline void rainbow(bool scroller = false, bool keyboard = false, bool hotkey = false) {
		get_instructionals()->setup();
		get_instructionals()->add_instructional(TRANSLATE(t_select), ControlFrontendAccept);
		get_instructionals()->add_instructional(TRANSLATE(t_back), ControlFrontendCancel);
		get_instructionals()->add_instructional(TRANSLATE(t_scroll), ARROW_UP_DOWN);
		get_instructionals()->add_instructional(TRANSLATE(t_rainbow_config), ControlFrontendX);

		if (scroller) get_instructionals()->add_instructional(TRANSLATE(t_adjust), ARROW_LEFT_RIGHT);
		if (keyboard) get_instructionals()->add_instructional(TRANSLATE(t_input), ControlPhoneSelect);
		if (hotkey) get_instructionals()->add_instructional(TRANSLATE(t_add_hotkey), VK_F12);

		get_instructionals()->close();
	}
}