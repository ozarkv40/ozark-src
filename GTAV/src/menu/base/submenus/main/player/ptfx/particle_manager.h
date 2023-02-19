#pragma once
#include "menu/base/submenu.h"

class particle_manager_menu : public menu::submenu::submenu {
public:
	static particle_manager_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	particle_manager_menu()
		: menu::submenu::submenu() {}
};

namespace player::ptfx::vars {
	struct looped_particle {
		std::pair<const char*, const char*> m_asset = { "", "" };
		int m_bone = 0;
		float m_scale = 1.f;
		uint32_t m_wait = 0;
		int m_handle = 0;
		bool m_loop_required = false;
		int m_timer = 0;
	};

	struct variables {
		int m_type;
		int m_wait;
		int m_socket;
		bool m_looped;
		float m_scale = 1.f;

		std::vector<looped_particle> m_looped_particles;

		radio_context m_radio = { "commonmenu", "shop_makeup_icon" };
	};

	extern variables m_vars;
}