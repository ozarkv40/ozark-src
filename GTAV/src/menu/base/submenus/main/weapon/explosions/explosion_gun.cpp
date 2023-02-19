#include "explosion_gun.h"
#include "menu/base/submenu_handler.h"
#include "../weapon_mods.h"
#include "menu/base/util/raycast.h"
#include "global/lists.h"

using namespace weapon::explosion::gun::vars;

namespace weapon::explosion::gun::vars {
	variables m_vars;
}

void explosion_gun_menu::load() {
	set_name("Explosion Gun");
	set_parent<weapon_mods_menu>();

	add_option(toggle_option("Toggle Explosion Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<ExplosionTypes>(SCROLL, "Explosion")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(global::lists::g_explosions), global::lists::g_explosions).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Audible")
		.add_translate()
		.add_toggle(m_vars.m_audible).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Invisible")
		.add_translate()
		.add_toggle(m_vars.m_invisible).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(SCROLL, "Radius")
		.add_translate()
		.add_number(m_vars.m_radius, "%.1f", 0.1f).add_min(0.f).add_max(100.f).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(SCROLL, "Camera Shake")
		.add_translate()
		.add_number(m_vars.m_camera_shake, "%.1f", 0.1f).add_min(0.f).add_max(100.f).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<Ped>(TOGGLE, "Owner")
		.add_translate()
		.add_toggle(m_vars.m_change_owner)
		.add_click([] {
			m_vars.m_owner_id = m_vars.m_change_owner_list[m_vars.m_change_owner_value].m_result;
		})
		.add_scroll(m_vars.m_change_owner_value, 0, NUMOF(m_vars.m_change_owner_list), m_vars.m_change_owner_list)
		.add_update([](scroll_option<int>* option, int position) { option->add_scroll(m_vars.m_change_owner_value, 0, NUMOF(m_vars.m_change_owner_list), m_vars.m_change_owner_list); })
		.add_requirement([] { return m_vars.m_list_size >= 1; }));
}

void explosion_gun_menu::update() {
	m_vars.m_list_size = 0;
	menu::player::for_each([&](menu::player::player_context& player) {
		m_vars.m_change_owner_list[m_vars.m_list_size].m_name.set(player.m_name);
		m_vars.m_change_owner_list[m_vars.m_list_size].m_result = player.m_id;

		if (m_vars.m_change_owner) {
			if (m_vars.m_owner_id == player.m_id) {
				m_vars.m_change_owner_value = m_vars.m_list_size;
			}
		}

		m_vars.m_list_size++;
	});
}

void explosion_gun_menu::update_once() {}

void explosion_gun_menu::feature_update() {
	if (m_vars.m_toggle) {
		if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
			menu::raycast cast = menu::raycast_infront(9999.f);
			if (cast.hit_something()) {
				math::vector3<float> coords = cast.get_coords();
				native::add_owned_explosion(m_vars.m_change_owner ? menu::player::get_player(m_vars.m_change_owner_list[m_vars.m_owner_id].m_result).m_ped : menu::player::get_local_player().m_ped, coords.x, coords.y, coords.z, m_vars.m_type, m_vars.m_radius, m_vars.m_audible, m_vars.m_invisible, m_vars.m_camera_shake);
			}
		}
	}
}

explosion_gun_menu* g_instance;
explosion_gun_menu* explosion_gun_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new explosion_gun_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}