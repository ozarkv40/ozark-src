#pragma once
#include "menu/base/submenu.h"

class ocean_menu : public menu::submenu::submenu {
public:
	static ocean_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	ocean_menu()
		: menu::submenu::submenu() {}
};

namespace world::ocean::vars {
	enum eOceanTasks {
		OCEAN_DISABLE,
		OCEAN_CLEAR,
		OCEAN_FIERCE
	};

	enum eOceanTypes {
		OCEAN_TYPE_OCEAN,
		OCEAN_TYPE_WAVE,
		OCEAN_TYPE_CALMING
	};

	struct variables {
		bool m_disable_ocean;
		bool m_clear_ocean;
		bool m_fierce_ocean;
		bool m_part_water;

		float m_wave_intensity;
	};

	void ocean_loop(eOceanTypes type, std::function<void(uint64_t)> callback);
	void ocean_task(eOceanTypes type, eOceanTasks task);
	extern variables m_vars;
}