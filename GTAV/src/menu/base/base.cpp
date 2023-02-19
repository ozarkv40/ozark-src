#include "base.h"
#include "renderer.h"
#include "rage/invoker/natives.h"
#include "submenu_handler.h"

namespace menu::base {
	void base::update() {
		if (m_disable_input_this_frame) {
			m_disable_input_this_frame = false;
			m_input_disabled = true;
		} else m_input_disabled = false;

		if (m_open) {
			native::set_input_exclusive(2, INPUT_FRONTEND_ACCEPT);
			native::set_input_exclusive(2, INPUT_FRONTEND_CANCEL);
			native::set_input_exclusive(2, INPUT_FRONTEND_DOWN);
			native::set_input_exclusive(2, INPUT_FRONTEND_UP);
			native::set_input_exclusive(2, INPUT_FRONTEND_LEFT);
			native::set_input_exclusive(2, INPUT_FRONTEND_RIGHT);
			// native::disable_control_action(0, INPUT_NEXT_CAMERA, true);
			native::disable_control_action(0, INPUT_VEH_SELECT_NEXT_WEAPON, true);
			native::disable_control_action(0, INPUT_FRONTEND_RIGHT, true);
			native::disable_control_action(0, INPUT_FRONTEND_DOWN, true);
			native::disable_control_action(0, INPUT_FRONTEND_LEFT, true);
			native::disable_control_action(0, INPUT_FRONTEND_UP, true);
			native::disable_control_action(0, INPUT_ARREST, true);
			native::disable_control_action(0, INPUT_CONTEXT, true);
			native::disable_control_action(0, INPUT_MELEE_BLOCK, true);
			native::disable_control_action(2, INPUT_FRONTEND_UP, true);
			native::disable_control_action(0, INPUT_HUD_SPECIAL, true);
			native::disable_control_action(0, INPUT_VEH_CIN_CAM, true);
			native::disable_control_action(2, INPUT_VEH_CIN_CAM, true);
			native::disable_control_action(0, INPUT_VEH_HEADLIGHT, true);
			native::disable_control_action(2, INPUT_FRONTEND_LEFT, true);
			native::disable_control_action(2, INPUT_FRONTEND_DOWN, true);
			native::disable_control_action(2, INPUT_FRONTEND_RDOWN, true);
			native::disable_control_action(2, INPUT_FRONTEND_RIGHT, true);
			native::disable_control_action(0, INPUT_CHARACTER_WHEEL, true);
			native::disable_control_action(0, INPUT_VEH_RADIO_WHEEL, true);
			native::disable_control_action(2, INPUT_FRONTEND_CANCEL, true);
			native::disable_control_action(0, INPUT_MELEE_ATTACK_LIGHT, true);
			native::disable_control_action(0, INPUT_MELEE_ATTACK_HEAVY, true);
			native::disable_control_action(0, INPUT_SELECT_CHARACTER_TREVOR, true);
			native::disable_control_action(0, INPUT_SELECT_CHARACTER_MICHAEL, true);
			native::disable_control_action(0, INPUT_SELECT_CHARACTER_FRANKLIN, true);
			native::disable_control_action(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, true);

			menu::renderer::render();
			menu::submenu::handler::update();
		} else {
			if (global::ui::g_render_tooltip) {
				menu::renderer::render_open_tooltip();
			}
		}
	}

	bool base::is_option_selected(int option) {
		if (global::ui::g_scroll_lerp) {
			float expected = global::ui::g_position.y + (option * global::ui::g_option_scale);
			float current = menu::renderer::get_smooth_scroll();
			float buffer = (global::ui::g_option_scale * 0.5f);

			return current >= expected - buffer && current <= expected + buffer;
		} else return menu::renderer::get_render_count() == option + 1;
	}

	base* get_base() {
		static base instance;
		return &instance;
	}
}