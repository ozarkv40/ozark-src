#pragma once
#include "menu/base/submenu.h"

class misc_disables_menu : public menu::submenu::submenu {
public:
	static misc_disables_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	misc_disables_menu()
		: menu::submenu::submenu() {}
};

namespace misc::disables::vars {
	struct variables {
		bool m_disable_phone;
		bool m_disable_calls;
		bool m_disable_stunt_jumps;
		bool m_disable_cinematic_camera;
		bool m_disable_profanity_filter;
		bool m_disable_minimap;
		bool m_disable_hud;
		bool m_disable_chat_on_open;
		bool m_disable_restricted_areas;
		bool m_disable_notifications;
		bool m_disable_loading_prompts;
		bool m_disable_cutscenes;
		bool m_disable_boundry_limit;
		bool m_disable_idle_kick;
		bool m_disable_easy_way_out_limit;
		bool m_disable_passive_mode_limit;
	};

	extern variables m_vars;
}