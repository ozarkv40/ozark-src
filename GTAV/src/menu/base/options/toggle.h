#pragma once
#include "stdafx.h"
#include "option.h"
#include "menu/base/base.h"
#include "util/config.h"

class toggle_option : public base_option {
public:
	toggle_option(std::string name)
		: base_option(name)
	{}

	toggle_option& add_click(std::function<void()> function) {
		m_on_click = function;
		return *this;
	}

	toggle_option& add_requirement(std::function<bool()> function) {
		m_requirement = function;
		return *this;
	}

	toggle_option& add_update(std::function<void(toggle_option*, int)> function) {
		m_on_update = function;
		return *this;
	}

	toggle_option& add_hover(std::function<void()> function) {
		m_on_hover = function;
		return *this;
	}

	toggle_option& add_tooltip(std::string tooltip) {
		m_tooltip.set(tooltip.c_str());
		return *this;
	}

	toggle_option& add_translate() {
		m_name.set_translate(true);
		m_tooltip.set_translate(true);
		return *this;
	}

	toggle_option& add_hotkey() {
		m_has_hotkey = true;
		return *this;
	}

	toggle_option& add_toggle(bool& tog) {
		m_toggle = &tog;
		return *this;
	}

	toggle_option& add_savable(std::stack<std::string> menu_stack) {
		if (menu_stack.size() <= 0) return *this;

		m_savable = true;
		if (m_toggle && m_requirement()) {
			*m_toggle = util::config::read_bool(menu_stack, m_name.get_original().c_str(), *m_toggle);
			if (*m_toggle) {
				m_on_click();
			}
		}

		return *this;
	}

	toggle_option& add_offset(float offset) {
		m_offset = offset;
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
	float m_offset = 0.f;
	bool* m_toggle = nullptr;

	std::function<void()> m_on_click = []() {};
	std::function<void()> m_on_hover = []() {};
	std::function<void(toggle_option*, int)> m_on_update = [](toggle_option*, int) {};
};