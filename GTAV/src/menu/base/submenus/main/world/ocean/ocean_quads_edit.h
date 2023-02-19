#pragma once
#include "menu/base/submenu.h"

class ocean_quads_edit_menu : public menu::submenu::submenu {
public:
	static ocean_quads_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	ocean_quads_edit_menu()
		: menu::submenu::submenu() {}
};

namespace world::ocean::quads::edit::vars {
	struct variables {
		rage::types::ocean_calming_quad* m_calming;
		rage::types::ocean_wave_quad* m_wave;
		rage::types::ocean_quad* m_ocean;

		bool m_clear;
	};

	extern variables m_vars;
}
