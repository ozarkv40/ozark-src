#pragma once
#include "menu/base/submenu.h"

class weapon_matrix_menu : public menu::submenu::submenu {
public:
	static weapon_matrix_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	weapon_matrix_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::matrix::vars {
	struct variables {
		math::matrix<bool> m_matrix;
		math::matrix<float> m_matrix_val;

		std::unordered_map<rage::types::weapon_info*, math::matrix<float>> m_original;
	};

	extern variables m_vars;
}
