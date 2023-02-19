#pragma once
#include "menu/base/submenu.h"

class vehicle_boost_menu : public menu::submenu::submenu {
public:
	static vehicle_boost_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_boost_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::boost::vars {
	struct variables {
		bool m_boost_fx;
		bool m_boost_sound;
		bool m_nitrous_oxide;
		bool m_unlimited_special_ability;

		int m_boost_forwards = 40;
		int m_boost_backwards = 40;
	};

	void boost(Vehicle ve, bool Forwards, bool disable_fx = false);
	extern variables m_vars;
}