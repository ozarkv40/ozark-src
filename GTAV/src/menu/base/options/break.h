#pragma once
#include "option.h"
#include "menu/base/base.h"
#include "rage/types/base_types.h"

class break_option : public base_option {
public:
	break_option(std::string name)
		: base_option(name) {}

	break_option& add_requirement(std::function<bool()> function) {
		m_requirement = function;
		return *this;
	}

	break_option& add_update(std::function<void(break_option*)> function) {
		m_on_update = function;
		return *this;
	}

	break_option& add_translate() {
		m_name.set_translate(true);
		m_tooltip.set_translate(true);
		return *this;
	}

	void render(int position);
	void render_selected(int position, std::stack<std::string> submenu_name_stack);
	void invoke_save(std::stack<std::string> submenu_name_stack) {}
	void invoke_hotkey() {}
	void write_translation(nlohmann::json& object) {}
	void read_translation(nlohmann::json& object) {}
	void reset_translation() {}
private:
	std::function<void(break_option*)> m_on_update = [](break_option*) {};
};