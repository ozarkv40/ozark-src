#pragma once
#include "menu/base/submenu.h"

class main_menu : public menu::submenu::submenu {
public:
	static main_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	main_menu()
		: menu::submenu::submenu()
	{}
};

namespace main::vars {
	struct variables {
		int m_scaleform_handle;
		int m_current_index;
		bool m_has_initialized;
		bool m_shown_welcome;
		uint32_t m_cached_time;


		std::unordered_map<uint64_t, int> callers;
	};

	extern variables m_vars;
}