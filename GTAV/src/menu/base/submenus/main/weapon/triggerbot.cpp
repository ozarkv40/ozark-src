#include "triggerbot.h"
#include "menu/base/submenu_handler.h"
#include "weapon_mods.h"
#include "menu/base/util/timers.h"
#include "global/lists.h"
#include "aimbot.h"

using namespace weapon::triggerbot::vars;

namespace weapon::triggerbot::vars {
	variables m_vars;
}

void triggerbot_menu::load() {
	set_name("Triggerbot");
	set_parent<aimbot_menu>();

	add_option(toggle_option("Toggle Triggerbot")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_enable).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(SCROLL, "Aim Entity")
		.add_translate()
		.add_scroll(m_vars.m_aim_entity, 0, NUMOF(weapon::aimbot::vars::aim_entity), weapon::aimbot::vars::aim_entity).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(SCROLL, "Aim Tag")
		.add_translate()
		.add_scroll(m_vars.m_aim_tag, 0, NUMOF(global::lists::g_ped_bones), global::lists::g_ped_bones).add_savable(get_submenu_name_stack()));

	add_option(number_option<int>(SCROLL, "Bullet Delay")
		.add_translate()
		.add_number(m_vars.m_delay, "%i", 20).add_min(0).add_max(2000).add_savable(get_submenu_name_stack()));
}

void triggerbot_menu::update() {}

void triggerbot_menu::update_once() {}

void triggerbot_menu::feature_update() {
	if (m_vars.m_enable) {
		Entity aimed_entity = 0;
		static int timer = 0;

		if (native::get_entity_player_is_free_aiming_at(menu::player::get_local_player().m_id, &aimed_entity)) {
			if (!native::is_entity_a_ped(aimed_entity) || native::is_entity_dead(aimed_entity, 0)) return;
			if (m_vars.m_aim_entity == 0 && !native::is_ped_a_player(aimed_entity)) return;
			if (m_vars.m_aim_entity == 1 && native::is_ped_a_player(aimed_entity)) return;

			math::vector3<float> bone = native::get_ped_bone_coords(aimed_entity, global::lists::g_ped_bones[m_vars.m_aim_tag].m_result, 0.f, 0.f, 0.f);
			if (!bone.is_null()) {
				menu::timers::run_timed(&timer, m_vars.m_delay, [=] {
					native::set_ped_shoots_at_coord(menu::player::get_local_player().m_ped, bone.x, bone.y, bone.z, true);
				});
			}
		}
	}
}

triggerbot_menu* g_instance;
triggerbot_menu* triggerbot_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new triggerbot_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
