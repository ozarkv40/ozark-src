#pragma once
#include "menu/base/submenu.h"
#include "menu/base/submenus/main/helper/helper_esp.h"

class spawner_ped_manage_menu : public menu::submenu::submenu {
public:
	static spawner_ped_manage_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_ped_manage_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::ped::manage::vars {
	struct spawned_ped {
		Ped m_handle = 0;
		uint32_t m_model_hash = 0;
		std::string m_name = "";
		int m_creation_time = 0;
		helper::esp::vars::esp_context m_esp;
	};

	struct variables {
		helper::esp::vars::esp_context m_esp;
		std::vector<spawned_ped> m_peds;
	};

	extern variables m_vars;
}