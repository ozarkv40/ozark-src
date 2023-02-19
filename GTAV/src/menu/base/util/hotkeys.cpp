#include "hotkeys.h"
#include "menu/base/base.h"
#include "rage/invoker/natives.h"
#include "Input.h"
#include "util/config.h"
#include "menu/base/submenu_handler.h"

namespace menu::hotkey {
	std::stack<std::string> get_option_name_stack(base_option* parent) {
		if (parent->get_submenu_name_stack()) {
			return *parent->get_submenu_name_stack();
		}

		return {};
	}

	void hotkey::update() {
		if (base::is_input_disabled()) return;

		std::unordered_map<int, bool> just_pressed;
		std::unordered_map<int, bool> just_released;

		for (hotkey_context& key : m_registered_hotkeys) {
			if (!native::is_text_chat_active()) {
				if (key.m_type == 0) {
					if (input::is_just_released(true, key.m_key) || just_released[key.m_key]) {
						just_released[key.m_key] = true;
					}

					if (just_released[key.m_key]) {
						key.m_parent->invoke_hotkey();
					}
				} else if (key.m_type == 1) {
					if (input::is_just_pressed(true, key.m_key) || just_pressed[key.m_key]) {
						just_pressed[key.m_key] = true;
					}

					if (just_pressed[key.m_key]) {
						key.m_parent->invoke_hotkey();
					}
				} else {
					if (input::is_pressed(true, key.m_key)) {
						key.m_parent->invoke_hotkey();
					}
				}
			}
		}
	}

	void hotkey::change_type(int new_type, base_option* parent) {
		for (std::size_t i = 0; i < m_registered_hotkeys.size(); i++) {
			hotkey_context& hotkey = m_registered_hotkeys[i];
			if (hotkey.m_parent == parent) {
				hotkey.m_type = new_type;

				std::stack<std::string> name_stack = get_option_name_stack(parent);
				if (name_stack.size()) {
					util::config::write_int(name_stack, "Type", 0, { "Hotkeys", parent->get_name().get_original() });
				}
			}
		}
	}

	void hotkey::read_hotkey(base_option* parent) {
		std::stack<std::string> name_stack = get_option_name_stack(parent);
		if (name_stack.size()) {
			bool toggled = util::config::read_bool(name_stack, "Toggled", false, { "Hotkeys", parent->get_name().get_original() });
			if (toggled) {
				int key = util::config::read_int(name_stack, "Key", -1, { "Hotkeys", parent->get_name().get_original() });
				int type = util::config::read_int(name_stack, "Type", 0, { "Hotkeys", parent->get_name().get_original() });
				parent->set_hotkey(key);
				m_registered_hotkeys.push_back({ key, parent, type });
			}
		}
	}

	void hotkey::register_hotkey(int key, base_option* parent) {
		m_registered_hotkeys.push_back({ key, parent, 0 });

		std::stack<std::string> name_stack = get_option_name_stack(parent);
		if (name_stack.size()) {
			util::config::write_int(name_stack, "Key", key, { "Hotkeys", parent->get_name().get_original() });
			util::config::write_int(name_stack, "Type", 0, { "Hotkeys", parent->get_name().get_original() });
			util::config::write_bool(name_stack, "Toggled", true, { "Hotkeys", parent->get_name().get_original() });
		}
	}

	void hotkey::unregister_hotkey(base_option* parent) {
		for (std::size_t i = 0; i < m_registered_hotkeys.size(); i++) {
			hotkey_context& hotkey = m_registered_hotkeys[i];
			if (hotkey.m_parent == parent) {
				hotkey.m_parent->set_hotkey(-1);
				m_registered_hotkeys.erase(begin(m_registered_hotkeys) + i);
			}
		}

		std::stack<std::string> name_stack = get_option_name_stack(parent);
		if (name_stack.size()) {
			util::config::write_bool(name_stack, "Toggled", false, { "Hotkeys", parent->get_name().get_original() });
		}
	}

	hotkey* get_hotkey() {
		static hotkey instance;
		return &instance;
	}
}