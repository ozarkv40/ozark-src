#include "hand_trails.h"
#include "menu/base/submenu_handler.h"
#include "../particles.h"
#include "menu/base/util/control.h"
#include "../../helper/helper_color.h"

using namespace player::trails::vars;

namespace player::trails::vars {
	variables m_vars;

	void update_color() {
		if (m_vars.m_trail_bone_left && m_vars.m_trail_bone_right) {
			native::set_particle_fx_looped_colour(m_vars.m_trail_bone_left, (float)m_vars.m_trail_color.r, (float)m_vars.m_trail_color.g, (float)m_vars.m_trail_color.b, true);
			native::set_particle_fx_looped_colour(m_vars.m_trail_bone_right, (float)m_vars.m_trail_color.r, (float)m_vars.m_trail_color.g, (float)m_vars.m_trail_color.b, true);
		}
	}

	void start_trails() {
		menu::control::request_particle({ "scr_minigametennis", "scr_tennis_ball_trail" }, [](std::pair<const char*, const char*> anim) {
			native::use_particle_fx_asset_next_call(anim.first);
			m_vars.m_trail_bone_left = native::start_particle_fx_looped_on_entity_bone2(anim.second, menu::player::get_local_player().m_ped, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, native::get_ped_bone_index(menu::player::get_local_player().m_ped, 0x8cbd), 1.f, true, true, true, 0, 0, 0);

			native::use_particle_fx_asset_next_call(anim.first);
			m_vars.m_trail_bone_right = native::start_particle_fx_looped_on_entity_bone2(anim.second, menu::player::get_local_player().m_ped, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, native::get_ped_bone_index(menu::player::get_local_player().m_ped, 0x188e), 1.f, true, true, true, 0, 0, 0);

			update_color();
		});
	}
}

void hand_trails_menu::load() {
	set_name("Hand Trails");
	set_parent<particle_menu>();

	add_option(toggle_option("Toggle Hand Trails")
		.add_translate()
		.add_toggle(m_vars.m_trails)
		.add_click([] {
			if (!m_vars.m_trails) {
				native::remove_particle_fx(m_vars.m_trail_bone_left, true);
				native::remove_particle_fx(m_vars.m_trail_bone_right, true);
			} else {
				start_trails();
			}
		}));

	add_option(submenu_option("Edit Color")
		.add_translate()
		.add_submenu<helper_color_menu>()
		.add_click([this] {
			helper_color_menu::get()->set_name(get_name().get(), false, false);
			helper_color_menu::get()->set_parent<hand_trails_menu>();
			helper::color::vars::m_vars.m_color = &m_vars.m_trail_color;
			helper::color::vars::m_vars.m_callback = update_color;
		})
		.add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, &m_vars.m_trail_color));
}

void hand_trails_menu::update() {}

void hand_trails_menu::update_once() {}

void hand_trails_menu::feature_update() {}

hand_trails_menu* g_instance;
hand_trails_menu* hand_trails_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new hand_trails_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
