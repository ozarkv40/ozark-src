#pragma once
#include "option.h"
#include "menu/base/base.h"
#include "rage/types/base_types.h"
#include "util/math.h"

class button_option : public base_option {
public:
	button_option(std::string name)
		: base_option(name) {}

	button_option& ref() {
		return *this;
	}

	button_option& add_click(std::function<void()> function) {
		m_on_click = function;
		return *this;
	}

	button_option& add_click_this(std::function<void(button_option*)> function) {
		m_on_click_this = function;
		return *this;
	}

	button_option& add_requirement(std::function<bool()> function) {
		m_requirement = function;
		return *this;
	}

	button_option& add_update(std::function<void(button_option*)> function) {
		m_on_update = function;
		return *this;
	}

	button_option& add_update_this(std::function<void(button_option*, int)> function) {
		m_on_update_this = function;
		return *this;
	}

	button_option& add_hover(std::function<void()> function) {
		m_on_hover = function;
		return *this;
	}

	button_option& add_tooltip(std::string tooltip) {
		m_tooltip.set(tooltip.c_str());
		return *this;
	}

	button_option& add_keyboard(std::string title, int max_chars, std::function<void(button_option*, const char*)> function) {
		m_keyboard = { true, false, max_chars, function, title };
		return *this;
	}

	button_option& add_translate() {
		m_name.set_translate(true);
		m_tooltip.set_translate(true);
		return *this;
	}

	button_option& remove_sprite() {
		m_sprite.m_enabled = false;
		return *this;
	}

	button_option& add_sprite(std::pair<std::string, std::string> asset, std::function<bool()> requirement = [] { return true; }) {
		m_sprite = { true, asset, requirement };
		return *this;
	}

	button_option& add_sprite_scale(math::vector2<float> scale) {
		m_sprite.m_scale = scale;
		return *this;
	}

	button_option& add_sprite_rotation() {
		m_sprite.m_rotate = true;
		return *this;
	}

	button_option& add_instructional(std::string text, eScaleformButtons button_option) {
		m_instructionals.push_back({ text, button_option, false });
		return *this;
	}

	button_option& add_instructional(std::string text, eControls button_option) {
		m_instructionals.push_back({ text, button_option, true });
		return *this;
	}

	button_option& add_side_text(std::string text) {
		m_side_text = { true, text };
		return *this;
	}

	button_option& add_hotkey() {
		m_has_hotkey = true;
		return *this;
	}

	button_option& add_offset(float offset) {
		m_offset = offset;
		return *this;
	}

	button_option& add_keyboard_default(std::string de) {
		m_keyboard.m_default_text = de;
		return *this;
	}

	void render(int position);
	void render_selected(int position, std::stack<std::string> submenu_name_stack);
	void invoke_save(std::stack<std::string> submenu_name_stack) {}
	void invoke_hotkey();
	void write_translation(nlohmann::json& object) {}
	void read_translation(nlohmann::json& object) {}
	void reset_translation() {}
private:
	struct Keyboard {
		bool m_enabled = false;
		bool m_is_active = false;
		int m_max_chars = 0;
		std::function<void(button_option*, const char*)> m_callback = {};
		std::string m_title = "";
		std::string m_default_text = "";
	};

	struct Sprite {
		bool m_enabled = false;
		std::pair<std::string, std::string> m_asset = {};
		std::function<bool()> m_requirement = {};
		math::vector2<float> m_scale = { 0.f, 0.f };
		bool m_rotate = false;
		float m_rotation = 0.f;
	};

	struct SideText {
		bool m_enabled = false;
		std::string m_text = "";
	};

	Keyboard m_keyboard;
	Sprite m_sprite;
	SideText m_side_text;
	float m_offset = 0.f;

	std::function<void()> m_on_click = []() {};
	std::function<void(button_option*)> m_on_click_this = [](button_option*) {};
	std::function<void()> m_on_hover = []() {};
	std::function<void(button_option*)> m_on_update = [](button_option*) {};
	std::function<void(button_option*, int)> m_on_update_this = [](button_option*, int) {};
};