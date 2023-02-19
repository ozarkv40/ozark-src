#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/player_manager.h"

class wardrobe_save_load_menu : public menu::submenu::submenu {
public:
	static wardrobe_save_load_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	wardrobe_save_load_menu()
		: menu::submenu::submenu() {}
};

namespace player::wardrobe::saveload::vars {
	void save_outfit(const char* name, menu::player::player_context player);
}