#pragma once
#include "menu/base/submenu.h"

class translation_menu : public menu::submenu::submenu {
public:
	static translation_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	translation_menu()
		: menu::submenu::submenu() {}
};

namespace settings::translation::vars {
	struct variables {
		std::vector<std::pair<std::string, struct stat>> m_cached_translations;
		int m_list_size;
		int m_update_translation;
		scroll_struct<int> m_translation_list[100];
	};

	void load_translation(std::string file);
	extern variables m_vars;
}