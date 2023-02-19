#pragma once
#include "menu/base/submenu.h"

class hide_info_menu : public menu::submenu::submenu {
public:
	static hide_info_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	hide_info_menu()
		: menu::submenu::submenu() {}
};

namespace settings::hide::vars {
	struct variables {
		bool m_hide_names;
		bool m_hide_ips;
		bool m_hide_rockstar_ids;

		std::unordered_map<uint64_t, std::string> m_cached;
	};

	extern variables m_vars;
}