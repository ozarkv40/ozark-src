#pragma once
#include "menu/base/submenu.h"
#include "rage/types/network_types.h"

class protection_join_blocking_menu : public menu::submenu::submenu {
public:
	static protection_join_blocking_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_join_blocking_menu()
		: menu::submenu::submenu() {}
};

namespace protection::joining::vars {
	struct variables {
		bool m_block;
		bool m_spoof;
		uint64_t m_target;

		std::shared_ptr<button_option> m_preview_button;
		rage::network::gs_session m_spoof_info;
	};

	void block_resolves();
	extern variables m_vars;
}