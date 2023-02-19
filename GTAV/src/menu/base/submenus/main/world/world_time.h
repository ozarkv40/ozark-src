#pragma once
#include "menu/base/submenu.h"

class time_menu : public menu::submenu::submenu {
public:
	static time_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	time_menu()
		: menu::submenu::submenu() {}
};

namespace world::time::vars {
	struct variables {
		bool m_sync;
		bool m_lock_time;
		bool m_accelerate_time;
		bool m_system_time;

		int m_time_scale;
		int m_lock_time_var;
		int m_lock_time_freeze[3];
	};
	
	void set_time(int hour, int minute, int second, bool sync_override = true);
	extern variables m_vars;
}