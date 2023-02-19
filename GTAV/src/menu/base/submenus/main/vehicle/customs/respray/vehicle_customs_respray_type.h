#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_respray_type_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_respray_type_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_respray_type_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::respray::type::vars {
	enum ePaintIndexs {
		PRIMARY,
		SECONDARY,
		PEARLESCENT
	};

	struct variables {
		bool m_update_cache;
		int m_type;
		int m_paint_index[3];
		radio_context m_context = { "commonmenu", "shop_garage_icon" };
	};

	extern variables m_vars;
}