#include "submenu.h"
#include "renderer.h"
#include "submenu_handler.h"
#include "base.h"
#include "util/instructionals.h"
#include "util/hotkeys.h"

namespace menu::submenu {
	void submenu::update_menu() {
		update();

		renderer::render_title(m_name.get());

		handler::set_total_options(0);
		handler::set_current_options_without_breaks(0);
		handler::set_total_options_without_breaks(0);

		bool slider = false;
		bool input = false;
		bool hotkey = false;

		if (m_options.size() > 0) {
			std::vector<std::shared_ptr<base_option>> options;
			options.reserve(m_options.size());

			int relative_position = 0;
			int visibility_offset = 0;

			for (std::shared_ptr<base_option> option : m_options) {
				if (option->is_visible()) {
					visibility_offset++;
					options.push_back(option);

					handler::set_total_options(handler::get_total_options() + 1);
					if (!option->is_break()) {
						if (visibility_offset <= base::get_current_option()) {
							handler::set_current_options_without_breaks(handler::get_current_options_without_breaks() + 1);
						}

						handler::set_total_options_without_breaks(handler::get_total_options_without_breaks() + 1);
					}
				}
			}

			for (int i = base::get_scroll_offset(); i < base::get_scroll_offset() + base::get_max_options(); i++) {
				if (i >= 0 && i < options.size()) {
					if (relative_position >= base::get_max_options()) break;

					options.at(i).get()->render(relative_position);

					if (relative_position == base::get_current_option() - base::get_scroll_offset()) {
						if (base::is_open()) {
							renderer::render_tooltip(options.at(i).get()->get_tooltip().get());
							options.at(i).get()->render_selected(relative_position, m_submenu_name_stack);
							
							slider = options.at(i).get()->is_slider();
							input = options.at(i).get()->is_input();
							hotkey = options.at(i).get()->has_hotkey();
						}
					}

					relative_position++;
				}
			}
		}

		if (m_default_instructionals) {
			instructionals::standard(slider, input, hotkey);
		}
	}

	void submenu::clear_options(int offset) {
		if (offset > m_options.size()) return;

		for (std::shared_ptr<base_option>& option : m_options) {
			if (option->has_hotkey()) {
				hotkey::unregister_hotkey(&*option);
			}
		}

		m_options.resize(offset);
	}

	std::string submenu::get_string(std::string str) {
		for (localization local : m_strings) {
			if (!local.get_original().compare(str)) {
				return local.get();
			}
		}

		return str;
	}

	void submenu::set_name(std::string str, bool translation, bool searchable) {
		if (!str.empty() && str.length() > 0) {
			m_name.set(str);
			m_name.set_translate(true);
			m_can_be_searched = searchable;
		}
	}

	void submenu::load() {}
	void submenu::update_once() {}
	void submenu::update() {}
	void submenu::feature_update() {}
}