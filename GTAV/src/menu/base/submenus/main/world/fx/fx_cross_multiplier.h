#pragma once
#include "menu/base/submenu.h"

class fx_cross_multiplier_menu : public menu::submenu::submenu {
public:
	static fx_cross_multiplier_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_cross_multiplier_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::cross::vars {
	struct variables {
		float m_rim_light;
		float m_global_environment_reflection;
		float m_gamma;
		float m_mid_blur;
		float m_far_blur;
		float m_sky_multiplier;
		float m_desaturation;
	};

	extern variables m_vars;
}