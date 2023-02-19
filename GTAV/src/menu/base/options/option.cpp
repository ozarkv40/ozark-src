#include "option.h"

base_option::base_option() { }

base_option::base_option(std::string name, bool breaker, bool slider, bool input) {
	m_name = localization(name);
	m_break_option = breaker;
	m_slider = slider;
	m_input = input;
}

void base_option::render(int position) {}
void base_option::render_selected(int position, std::stack<std::string> submenu_name_stack) {}
void base_option::invoke_save(std::stack<std::string> submenu_name_stack) {}
void base_option::invoke_hotkey() {}
void base_option::write_translation(nlohmann::json& object) {}
void base_option::read_translation(nlohmann::json& object) {}
void base_option::reset_translation() {}