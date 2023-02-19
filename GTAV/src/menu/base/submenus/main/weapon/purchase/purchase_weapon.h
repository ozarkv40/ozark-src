#pragma once
#include "menu/base/submenu.h"

class purchase_weapon_menu : public menu::submenu::submenu {
public:
	static purchase_weapon_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	purchase_weapon_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::purchase::weapon::vars {
	struct variables {
		std::shared_ptr<base_option> m_button;
	};

	namespace scripts {
		const char* func_181(int iParam0, int iParam1);
		void func_116(char* sParam0, const char* cParam1, uint32_t iParam5, int iParam6, int iParam7, int iParam8, int iParam9, int iParam10, bool bParam11, bool bParam12);
		int func_57(int iParam0);
		int func_117(int iParam0);
	}

	extern variables m_vars;
}