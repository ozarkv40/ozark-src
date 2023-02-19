#pragma once
#include "menu/base/submenu.h"

class spawner_ped_settings_menu : public menu::submenu::submenu {
public:
	static spawner_ped_settings_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_ped_settings_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::ped::settings::vars {
	struct variables {
		bool m_notification;
		bool m_blip;
		bool m_particle_fx;
		bool m_fade;
	};

	extern variables m_vars;
}