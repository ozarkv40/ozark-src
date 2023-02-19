#pragma once
#include "menu/base/submenu.h"
#include "../../helper/helper_esp.h"

class spawner_object_manage_menu : public menu::submenu::submenu {
public:
	static spawner_object_manage_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_object_manage_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::object::manage::vars {
	struct spawned_object {
		Object m_handle = 0;
		uint32_t m_model_hash = 0;
		std::string m_name = "";
		int m_creation_time = 0;
		helper::esp::vars::esp_context m_esp;
	};

	struct variables {
		helper::esp::vars::esp_context m_esp;
		std::vector<spawned_object> m_objects;
	};

	extern variables m_vars;
}