#include "submenu_handler.h"
#include "base.h"
#include "rage/invoker/natives.h"
#include "global/ui_vars.h"
#include "submenus/main.h"

namespace menu::submenu::handler {
	void submenu_handler::load() {
		m_main = m_current = main_menu::get();
	}

	void submenu_handler::update() {
		if (m_current) {
			m_current->update_menu();

			if (m_next) {
				menu::base::set_current_option(m_next_current_option);
				menu::base::set_scroll_offset(m_next_scroll_offset);

				m_current = m_next;
				m_next = nullptr;
				m_current->update_once();
			}
		}
	}

	void submenu_handler::feature_update() {
		if (native::network_is_player_connected(native::player_id())) {
			for (submenu* submenu : m_submenus) {
				submenu->feature_update();
			}
		}
	}

	void submenu_handler::cleanup() {
		for (submenu* submenu : m_submenus) {
			delete submenu;
		}
	}

	void submenu_handler::add_submenu(submenu* submenu) {
		m_submenus.push_back(submenu);
	}

	void submenu_handler::set_submenu(submenu* submenu) {
		menu::renderer::set_smooth_scroll(global::ui::g_position.y);

		m_current->set_old_current_option(menu::base::get_current_option());
		m_current->set_old_scroll_offset(menu::base::get_scroll_offset());
		
		m_next_current_option = 0;
		m_next_scroll_offset = 0;

		m_previous = m_current;
		m_next = submenu;
	}

	void submenu_handler::set_submenu_previous(bool reset) {
		m_previous = m_current;
		if (m_current->get_parent() == nullptr) {
			m_next = m_main;
			m_next_current_option = 0;
			m_next_scroll_offset = 0;
			menu::base::set_open(false);
		} else {
			m_next = m_current->get_parent();

			if (reset) {
				m_next_current_option = 0;
				m_next_scroll_offset = 0;
				menu::renderer::set_smooth_scroll(global::ui::g_position.y);
			} else {
				m_next_current_option = m_next->get_old_current_option();
				m_next_scroll_offset = m_next->get_old_scroll_offset();

				int max_options = base::get_max_options();
				int scroller_position = math::clamp(m_next_current_option - m_next_scroll_offset > max_options ? max_options : m_next_current_option - m_next_scroll_offset, 0, max_options);
				menu::renderer::set_smooth_scroll(global::ui::g_position.y + (scroller_position * global::ui::g_option_scale));
			}
		}

		global::ui::g_rendering_tooltip.clear();
	}

	submenu_handler* get_submenu_handler() {
		static submenu_handler instance;
		return &instance;
	}
}