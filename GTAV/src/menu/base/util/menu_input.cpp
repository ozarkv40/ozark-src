#include "menu_input.h"
#include "menu/base/base.h"
#include "util/fiber.h"
#include "util/va.h"
#include "menu/base/renderer.h"
#include "menu/base/util/input.h"
#include "menu/base/util/hotkeys.h"

namespace menu::input {
	localization t_enter_to_add("enter to add, escape to cancel", true, true);

	void menu_input::update() {
		if (!base::is_open()) return;

		for (std::function<void()> function : m_queue) {
			function();
		}

		m_queue.clear();
	}

	void menu_input::push(std::function<void()> function) {
		m_queue.push_back(function);
	}

	void menu_input::color(color_rgba* option) {
		global::ui::g_input_open = true;

		bool exit = false;
		bool accepted = false;
		int selection_count = 50;
		int grid_count = 50;
		int alpha_slider = option->a;

		color_hsv original_hsv = menu::renderer::rgb_to_hsv(*option);
		color_rgba original_rgb = *option;

		float hue_slider = original_hsv.h;
		int slider_x = 50 - (int)(original_hsv.s * 50);
		int slider_y = 50 - (int)(original_hsv.v * 50);

		bool slider_selected = false;
		bool alpha_selected = false;

		while (!exit) {
			util::fiber::go_to_main();
			menu::base::set_disable_input_this_frame();

			static float w = 0.25f;
			static float h = 0.675f;
			static float x = 0.5f - (w * 0.5f);
			static float y = 0.235f;
			static float bezzel = 0.007875f / 2.f;

			// bar
			menu::renderer::draw_rect({ x, y - bezzel }, { w, bezzel }, global::ui::g_color_grid_bar); // header

			// background
			menu::renderer::draw_rect({ x, y }, { w, h }, global::ui::g_color_grid_background);

			// x * (1.f / grid_count)
			// y * (1.f / grid_count)

			// hsv/alpha bar
			for (int i = 0; i <= selection_count; i++) {
				// hsv
				float base_w = w / (selection_count + 3);
				float base_x = x + base_w;
				float base_y = y + 0.015f;
				menu::renderer::draw_rect({ base_x + (base_w * i), base_y }, { base_w, base_w * 2.f }, menu::renderer::hsv_to_rgb(i * (360.f / selection_count), 1.f, 1.f));

				// alpha
				int alpha = (255 * i) / selection_count;
				// 1.f - ((1.f / grid_count) * slider_x)
				menu::renderer::draw_rect({ base_x + (base_w * i), base_y + (base_w * 3.f) }, { base_w, base_w * 2.f }, menu::renderer::hsv_to_rgb(hue_slider, 1.f - ((1.f / grid_count) * slider_x), 1.f - ((1.f / grid_count) * slider_y), alpha));
			}

			// hsv grid
			for (int xx = 0; xx <= grid_count; xx++) {
				for (int yy = 0; yy <= grid_count; yy++) {
					float base_w = w / (grid_count + 3);
					float base_x = x + base_w;
					float base_y = y + 0.015f;

					menu::renderer::draw_rect({ base_x + (base_w * xx), base_y + (base_w * 6.f) + ((base_w * 2.f) * yy) }, { base_w, base_w * 2.f }, menu::renderer::hsv_to_rgb(hue_slider, 1.f - ((1.f / grid_count) * xx), 1.f - ((1.f / grid_count) * yy)));
				}
			}

			color_rgba selected_color = menu::renderer::hsv_to_rgb(hue_slider, 1.f - ((1.f / grid_count) * slider_x), 1.f - ((1.f / grid_count) * slider_y), alpha_slider);
			color_hsv selected_hsv = menu::renderer::rgb_to_hsv(selected_color);

			float base_w = 0.0047f;
			float box_width = 0.0768f;
			float base_y = (y + 0.015f) + (base_w * 6.f) + ((base_w * 2.f) * 52);

			// R/H/A box
			menu::renderer::draw_rect({ x + base_w, base_y }, { box_width, 0.036f }, { 255, 255, 255, 200 }); // r
			menu::renderer::draw_rect({ x + base_w + (box_width * 1.f) + 0.005f, base_y }, { box_width, 0.036f }, { 255, 255, 255, 200 }); // h
			menu::renderer::draw_rect({ x + base_w + (box_width * 2.f) + 0.01f, base_y }, { box_width, 0.036f }, { 255, 255, 255, 200 }); // a

			// R/H/A text
			menu::renderer::draw_text("R", { x + base_w + 0.0025f, base_y + 0.006f }, 0.35f, 0, { 0, 0, 0, 255 }); // r identifier
			menu::renderer::draw_text("H", { x + base_w + (box_width * 1.f) + 0.005f + 0.0025f, base_y + 0.006f }, 0.35f, 0, { 0, 0, 0, 255 }); // h identifier
			menu::renderer::draw_text("A", { x + base_w + (box_width * 2.f) + 0.01f + 0.0025f, base_y + 0.006f }, 0.35f, 0, { 0, 0, 0, 255 }); // a identifier

			// R/H/A text box
			menu::renderer::draw_rect({ x + base_w + 0.013f, base_y }, { 0.001f, 0.036f }, { 0, 0, 0, 180 }); // r
			menu::renderer::draw_rect({ x + base_w + (box_width * 1.f) + 0.005f + 0.013f, base_y }, { 0.001f, 0.036f }, { 0, 0, 0, 180 }); // h
			menu::renderer::draw_rect({ x + base_w + (box_width * 2.f) + 0.01f + 0.013f, base_y }, { 0.001f, 0.036f }, { 0, 0, 0, 180 }); // a

			// R/H/A values
			menu::renderer::draw_text(std::to_string(selected_color.r), { x + base_w + ((box_width + 0.0125f) / 2.f), base_y + 0.008f }, 0.3f, 0, { 0, 0, 0, 255 }, JUSTIFY_CENTER); // r
			menu::renderer::draw_text(util::va::va("%.2f", selected_hsv.h), { x + base_w + (box_width * 1.f) + 0.005f + ((box_width + 0.0125f) / 2.f), base_y + 0.008f }, 0.3f, 0, { 0, 0, 0, 255 }, JUSTIFY_CENTER); // h
			menu::renderer::draw_text(std::to_string(selected_color.a), { x + base_w + (box_width * 2.f) + 0.01f + ((box_width + 0.0125f) / 2.f), base_y + 0.008f }, 0.3f, 0, { 0, 0, 0, 255 }, JUSTIFY_CENTER); // a

			base_y = (y + 0.015f) + (base_w * 6.f) + ((base_w * 2.f) * 57);
			
			// G/S/HEX box
			menu::renderer::draw_rect({ x + base_w, base_y }, { box_width, 0.036f }, { 255, 255, 255, 200 }); // g
			menu::renderer::draw_rect({ x + base_w + (box_width * 1.f) + 0.005f, base_y }, { box_width, 0.036f }, { 255, 255, 255, 200 }); // s
			menu::renderer::draw_rect({ x + base_w + (box_width * 2.f) + 0.01f, base_y }, { box_width, 0.036f }, { 255, 255, 255, 200 }); // hex

			// G/S/HEX text
			menu::renderer::draw_text("G", { x + base_w + 0.0025f, base_y + 0.006f }, 0.35f, 0, { 0, 0, 0, 255 }); // g identifier
			menu::renderer::draw_text("S", { x + base_w + (box_width * 1.f) + 0.005f + 0.0025f, base_y + 0.006f }, 0.35f, 0, { 0, 0, 0, 255 }); // s identifier
			
			// G/S/HEX text box
			menu::renderer::draw_rect({ x + base_w + 0.013f, base_y }, { 0.001f, 0.036f }, { 0, 0, 0, 180 }); // g
			menu::renderer::draw_rect({ x + base_w + (box_width * 1.f) + 0.005f + 0.013f, base_y }, { 0.001f, 0.036f }, { 0, 0, 0, 180 }); // s

			// G/S/HEX values
			menu::renderer::draw_text(std::to_string(selected_color.g), { x + base_w + ((box_width + 0.0125f) / 2.f), base_y + 0.008f }, 0.3f, 0, { 0, 0, 0, 255 }, JUSTIFY_CENTER); // g
			menu::renderer::draw_text(util::va::va("%.2f", selected_hsv.s * 100.f), { x + base_w + (box_width * 1.f) + 0.005f + ((box_width + 0.0125f) / 2.f), base_y + 0.008f }, 0.3f, 0, { 0, 0, 0, 255 }, JUSTIFY_CENTER); // s
			menu::renderer::draw_text(util::va::va("#%02X%02X%02X%02X", selected_color.r, selected_color.g, selected_color.b, selected_color.a), { x + base_w + (box_width * 2.f) + 0.01f + (box_width / 2.f), base_y + 0.008f }, 0.3f, 0, { 0, 0, 0, 255 }, JUSTIFY_CENTER); // hex

			base_y = (y + 0.015f) + (base_w * 6.f) + ((base_w * 2.f) * 62);

			// B/V box
			menu::renderer::draw_rect({ x + base_w, base_y }, { box_width, 0.036f }, { 255, 255, 255, 200 }); // b
			menu::renderer::draw_rect({ x + base_w + (box_width * 1.f) + 0.005f, base_y }, { box_width, 0.036f }, { 255, 255, 255, 200 }); // v

			// B/V text
			menu::renderer::draw_text("B", { x + base_w + 0.0025f, base_y + 0.006f }, 0.35f, 0, { 0, 0, 0, 255 }); // g identifier
			menu::renderer::draw_text("V", { x + base_w + (box_width * 1.f) + 0.005f + 0.0025f, base_y + 0.006f }, 0.35f, 0, { 0, 0, 0, 255 }); // s identifier

			// B/V text box
			menu::renderer::draw_rect({ x + base_w + 0.013f, base_y }, { 0.001f, 0.036f }, { 0, 0, 0, 180 }); // g
			menu::renderer::draw_rect({ x + base_w + (box_width * 1.f) + 0.005f + 0.013f, base_y }, { 0.001f, 0.036f }, { 0, 0, 0, 180 }); // s
			menu::renderer::draw_rect({ x + base_w + (box_width * 2.f) + 0.01f, base_y }, { box_width, 0.036f }, selected_color); // preview

			// B/V values
			menu::renderer::draw_text(std::to_string(selected_color.b), { x + base_w + ((box_width + 0.0125f) / 2.f), base_y + 0.008f }, 0.3f, 0, { 0, 0, 0, 255 }, JUSTIFY_CENTER); // b
			menu::renderer::draw_text(util::va::va("%.2f", selected_hsv.v * 100.f), { x + base_w + (box_width * 1.f) + 0.005f + ((box_width + 0.0125f) / 2.f), base_y + 0.008f }, 0.3f, 0, { 0, 0, 0, 255 }, JUSTIFY_CENTER); // v

			base_w = w / (grid_count + 3);
			float base_x = x + base_w;
			base_y = y + 0.015f;

			// grid selector
			menu::renderer::draw_outlined_rect({ base_x + (base_w * slider_x), base_y + (base_w * 6.f) + ((base_w * 2.f) * slider_y) }, { base_w, base_w * 2.f }, 0.001f, menu::renderer::hsv_to_rgb(hue_slider, 1.f - ((1.f / grid_count) * slider_x), 1.f - ((1.f / grid_count) * slider_y)), !((alpha_selected || slider_selected)) ? color_rgba(255, 255, 255, 255) : color_rgba(196, 196, 196, 255));

			// hsv bar selector
			base_w = w / (selection_count + 3);
			base_x = x + base_w;
			base_y = y + 0.015f;
			menu::renderer::draw_outlined_rect({ base_x + (base_w * (hue_slider / 7.2f)), base_y }, { base_w, base_w * 2.f }, 0.001f, menu::renderer::hsv_to_rgb(hue_slider, 1.f, 1.f), slider_selected ? color_rgba(255, 255, 255, 255) : color_rgba(196, 196, 196, 255));

			// alpha bar selector
			menu::renderer::draw_outlined_rect({ base_x + (base_w * (alpha_slider / 5.1f)), base_y + (base_w * 3.f) }, { base_w, base_w * 2.f }, 0.001f, { 0, 0, 0, 0 }, alpha_selected ? color_rgba(255, 255, 255, 255) : color_rgba(196, 196, 196, 255));

			// set the color
			*option = menu::renderer::hsv_to_rgb(hue_slider, 1.f - ((1.f / grid_count) * slider_x), 1.f - ((1.f / grid_count) * slider_y), alpha_slider);
			
			// input
			bool left_press = menu::input::is_left_just_pressed() 
				|| menu::input::is_just_pressed(false, ControlFrontendLeft, true);

			bool right_press = menu::input::is_right_just_pressed() 
				|| menu::input::is_just_pressed(false, ControlFrontendRight, true);

			bool up_press =menu::input::is_just_pressed(true, VK_NUMPAD8, true)
				|| menu::input::is_just_pressed(false, ControlFrontendUp, true);

			bool down_press = menu::input::is_just_pressed(true, VK_NUMPAD2, true)
				|| menu::input::is_just_pressed(false, ControlFrontendDown, true);

			bool left_held = menu::input::is_left_pressed() 
				|| menu::input::is_pressed(false, ControlFrontendLeft, true);

			bool right_held = menu::input::is_right_pressed() 
				|| menu::input::is_pressed(false, ControlFrontendRight, true);

			bool up_held = menu::input::is_pressed(true, VK_NUMPAD8, true)
				|| menu::input::is_pressed(false, ControlFrontendUp, true);

			bool down_held = menu::input::is_pressed(true, VK_NUMPAD2, true)
				|| menu::input::is_pressed(false, ControlFrontendDown, true);

			static bool m_left_disabled = false;
			static bool m_right_disabled = false;
			static int m_left_timer = 0;
			static int m_right_timer = 0;

			static bool m_up_disabled = false;
			static bool m_down_disabled = false;
			static int m_up_timer = 0;
			static int m_down_timer = 0;

			auto input_left = [&] {
				if (slider_selected) {
					hue_slider -= 1.5f;
					if (hue_slider < 0.f) hue_slider = 360.f;
				} else if (alpha_selected) {
					alpha_slider--;
					if (alpha_slider < 0) alpha_slider = 255;
				} else {
					if (slider_x > 0) slider_x--;
				}
			};

			auto input_right = [&] {
				if (slider_selected) {
					hue_slider += 1.5f;
					if (hue_slider > 360.f) hue_slider = 0.f;
				} else if (alpha_selected) {
					alpha_slider++;
					if (alpha_slider > 255) alpha_slider = 0;
				} else {
					if (slider_x < grid_count) slider_x++;
				}
			};

			auto input_up = [&] {
				if (!slider_selected && !alpha_selected) {
					if (slider_y == 0) {
						alpha_selected = true;
					} else {
						if (slider_y > 0) slider_y--;
					}
				} else if (alpha_selected) {
					alpha_selected = false;
					slider_selected = true;
				}
			};

			auto input_down = [&] {
				if (slider_selected) {
					slider_selected = false;
					alpha_selected = true;
				} else if (alpha_selected) {
					alpha_selected = false;
				} else {
					if (slider_y < grid_count) slider_y++;
				}
			};

			if (left_press) {
				if (!m_left_disabled) {
					input_left();
				}

				m_left_disabled = false;
				m_left_timer = 0;
			}

			if (right_press) {
				if (!m_right_disabled) {
					input_right();
				}

				m_right_disabled = false;
				m_right_timer = 0;
			}

			if (left_held) {
				if (++m_left_timer > 20) {
					m_left_disabled = true;
					input_left();
				}
			}

			if (right_held) {
				if (++m_right_timer > 20) {
					m_right_disabled = true;
					input_right();
				}
			}

			if (up_press) {
				if (!m_up_disabled) {
					input_up();
				}

				m_up_disabled = false;
				m_up_timer = 0;
			}

			if (down_press) {
				if (!m_down_disabled) {
					input_down();
				}

				m_down_disabled = false;
				m_down_timer = 0;
			}

			if (up_held) {
				if (++m_up_timer > 20) {
					m_up_disabled = true;
					input_up();
				}
			}

			if (down_held) {
				if (++m_down_timer > 20) {
					m_down_disabled = true;
					input_down();
				}
			}

			if (menu::input::is_option_pressed(true)) {
				exit = true;
				accepted = true;
			} else if (menu::input::is_just_released(true, VK_ESCAPE, true)
				|| menu::input::is_just_released(true, VK_NUMPAD0, true)
				|| menu::input::is_just_pressed(false, ControlFrontendCancel, true)) {
				accepted = false;
				exit = true;
			}
		}

		if (!accepted) {
			*option = original_rgb;
		}

		global::ui::g_input_open = false;
	}

	int menu_input::get_key(std::string name, int default_key) {
		global::ui::g_input_open = true;

		char local_name[0x80];
		strcpy_s(local_name, name.c_str());

		bool exit = false;
		bool accepted = false;
		int input_key = default_key;

		while (!exit) {
			util::fiber::go_to_main();
			menu::base::set_disable_input_this_frame();

			float w = 0.16f;
			float h = 0.12f;
			float x = 0.5f - (w * 0.5f);
			float y = 0.5f - (h * 0.5f);
			float bezzel = 0.007875f / 2.f;

			menu::renderer::draw_rect({ x, y }, { w, bezzel }, global::ui::g_hotkey_bar); // header
			menu::renderer::draw_rect({ x, y + bezzel }, { w, h }, global::ui::g_hotkey_background); // bg

			menu::renderer::draw_text(local_name, { x + (w * 0.5f), y + bezzel + (h * 0.15f) }, global::ui::g_option_height, 0, color_rgba(255, 255, 255), JUSTIFY_CENTER); // option name
			menu::renderer::draw_rect({ x + ((w * 0.1f) * 0.5f), y + bezzel + ((h * 0.7f) * 0.5f) + ((h * 0.2f) * 0.5f) }, { w * 0.9f, h * 0.3f }, global::ui::g_hotkey_input); // input box

			menu::renderer::draw_text(TRANSLATE(t_enter_to_add), { x + (w * 0.5f), y + bezzel + (h * 0.8f) }, 0.25f, 0, color_rgba(255, 255, 255), JUSTIFY_CENTER); // help test

			int last_key = menu::input::get_last_key();
			if (last_key != VK_RETURN && last_key != VK_ESCAPE && last_key != VK_BACK) {
				input_key = last_key;
			}

			menu::renderer::draw_text(g_key_names[input_key], { x + (w * 0.5f), y + bezzel + ((h * 0.7f) * 0.5f) + ((h * 0.3f) * 0.5f) }, 0.35f, 0, color_rgba(255, 255, 255), JUSTIFY_CENTER);

			if (menu::input::is_option_pressed(true)) {
				accepted = true;
				exit = true;
			} else if (menu::input::is_just_released(true, VK_ESCAPE, true)) {
				accepted = false;
				exit = true;
			}
		}

		global::ui::g_input_open = false;
		return input_key;
	}

	void menu_input::hotkey(std::string name, base_option* option) {
		global::ui::g_input_open = true;

		char local_name[0x80];
		strcpy_s(local_name, name.c_str());

		bool exit = false;
		bool accepted = false;
		int input_key = option->has_hotkey() && option->get_hotkey() != -1 ? option->get_hotkey() : 0;

		while (!exit) {
			util::fiber::go_to_main();
			menu::base::set_disable_input_this_frame();

			float w = 0.16f;
			float h = 0.12f;
			float x = 0.5f - (w * 0.5f);
			float y = 0.5f - (h * 0.5f);
			float bezzel = 0.007875f / 2.f;

			menu::renderer::draw_rect({ x, y }, { w, bezzel }, global::ui::g_hotkey_bar); // header
			menu::renderer::draw_rect({ x, y + bezzel }, { w, h }, global::ui::g_hotkey_background); // bg

			menu::renderer::draw_text(local_name, { x + (w * 0.5f), y + bezzel + (h * 0.15f) }, global::ui::g_option_height, 0, color_rgba(255, 255, 255), JUSTIFY_CENTER); // option name
			menu::renderer::draw_rect({ x + ((w * 0.1f) * 0.5f), y + bezzel + ((h * 0.7f) * 0.5f) + ((h * 0.2f) * 0.5f) }, { w * 0.9f, h * 0.3f }, global::ui::g_hotkey_input); // input box

			menu::renderer::draw_text(TRANSLATE(t_enter_to_add), { x + (w * 0.5f), y + bezzel + (h * 0.8f) }, 0.25f, 0, color_rgba(255, 255, 255), JUSTIFY_CENTER); // help test

			int last_key = menu::input::get_last_key();
			if (last_key != VK_RETURN && last_key != VK_ESCAPE && last_key != VK_BACK && last_key != menu::base::get_open_key()) {
				input_key = last_key;
			}

			if (input_key != VK_F12) {
				menu::renderer::draw_text(g_key_names[input_key], { x + (w * 0.5f), y + bezzel + ((h * 0.7f) * 0.5f) + ((h * 0.3f) * 0.5f) }, 0.35f, 0, color_rgba(255, 255, 255), JUSTIFY_CENTER);
			}

			if (menu::input::is_option_pressed(true)) {
				accepted = true;
				exit = true;
			} else if (menu::input::is_just_released(true, VK_ESCAPE, true)) {
				accepted = false;
				exit = true;
			}
		}

		if (accepted && input_key && input_key != VK_F12) {
			menu::hotkey::unregister_hotkey(option);
			option->set_hotkey(input_key);
			menu::hotkey::register_hotkey(input_key, option);
		}

		global::ui::g_input_open = false;
	}

	menu_input* get_menu_input() {
		static menu_input instance;
		return &instance;
	}
}