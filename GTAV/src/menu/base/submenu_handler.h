#pragma once
#include "stdafx.h"
#include "submenu.h"
#include "menu/base/options/submenu_option.h"
#include "menu/base/util/player_manager.h"
#include <vector>

namespace menu::submenu::handler {
	class submenu_handler {
	public:
		void load();
		void update();
		void feature_update();
		void cleanup();

		void add_submenu(submenu* submenu);
		void set_submenu(submenu* submenu);
		void set_submenu_previous(bool reset = false);

		int get_total_options() { return m_total_options; }
		int get_current_options_without_breaks() { return m_current_options_without_breaks; }
		int get_total_options_without_breaks() { return m_total_options_without_breaks; }

		void set_total_options(int val) { m_total_options = val; }
		void set_current_options_without_breaks(int val) { m_current_options_without_breaks = val; }
		void set_total_options_without_breaks(int val) { m_total_options_without_breaks = val; }

		submenu* get_current() { return m_current; }
		submenu* get_previous() { return m_previous; }

		void set_previous(submenu* submenu) { m_previous = submenu; }
		std::vector<submenu*>& get_submenus() { return m_submenus; }
	private:
		submenu* m_main = nullptr;
		submenu* m_current = nullptr;
		submenu* m_next = nullptr;
		submenu* m_previous = nullptr;
		std::vector<submenu*> m_submenus = {};

		int m_total_options = 0;
		int m_current_options_without_breaks = 0;
		int m_total_options_without_breaks = 0;
		int m_next_current_option = 0;
		int m_next_scroll_offset = 0;
	};

	submenu_handler* get_submenu_handler();

	inline void load() {
		get_submenu_handler()->load();
	}

	inline void update() {
		get_submenu_handler()->update();
	}

	inline void feature_update() {
		get_submenu_handler()->feature_update();
	}

	inline void cleanup() {
		get_submenu_handler()->cleanup();
	}

	inline void add_submenu(submenu* submenu) {
		get_submenu_handler()->add_submenu(submenu);
	}

	inline void set_submenu(submenu* submenu) {
		get_submenu_handler()->set_submenu(submenu);
	}

	inline void set_submenu_previous(bool reset = false) {
		get_submenu_handler()->set_submenu_previous(reset);
	}

	inline int get_total_options() {
		return get_submenu_handler()->get_total_options();
	}

	inline int get_current_options_without_breaks() {
		return get_submenu_handler()->get_current_options_without_breaks();
	}

	inline int get_total_options_without_breaks() {
		return get_submenu_handler()->get_total_options_without_breaks();
	}

	inline void set_total_options(int val) {
		get_submenu_handler()->set_total_options(val);
	}

	inline void set_current_options_without_breaks(int val) {
		get_submenu_handler()->set_current_options_without_breaks(val);
	}

	inline void set_total_options_without_breaks(int val) {
		get_submenu_handler()->set_total_options_without_breaks(val);
	}

	inline submenu* get_current() {
		return get_submenu_handler()->get_current();
	}

	inline submenu* get_previous() {
		return get_submenu_handler()->get_previous();
	}

	inline void set_previous(submenu* submenu) {
		get_submenu_handler()->set_previous(submenu);
	}

	inline std::vector<submenu*>& get_submenus() {
		return get_submenu_handler()->get_submenus();
	}
}