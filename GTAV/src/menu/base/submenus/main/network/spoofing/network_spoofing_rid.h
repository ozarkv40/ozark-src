#pragma once
#include "menu/base/submenu.h"

class network_spoofing_rid_menu : public menu::submenu::submenu {
public:
	static network_spoofing_rid_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_rid_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::rid::vars {
	struct variables {
		uint64_t m_spoofing_rid;
		uint64_t m_temp_spoofing_rid;
		bool m_save_to_config;
		char m_preview_name[50];
		std::shared_ptr<button_option> m_preview_button;
		bool m_loaded;
	};

	void spoof(bool reset, uint64_t rockstar_id = 0);
	extern variables m_vars;
}