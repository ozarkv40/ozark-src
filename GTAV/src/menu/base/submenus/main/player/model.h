#pragma once
#include "menu/base/submenu.h"

class model_menu : public menu::submenu::submenu {
public:
	static model_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	model_menu()
		: menu::submenu::submenu() {}
};

namespace player::model::vars {
	struct variables {
		uint32_t m_last_model;
		bool m_reapply;
		int m_popular;
		int m_story;
		int m_animals;
		int m_emergency;
		int m_role;
		int m_ambient;
		int m_misc;
	};

	extern variables m_vars;
}