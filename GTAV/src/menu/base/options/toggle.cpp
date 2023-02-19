#include "toggle.h"
#include "menu/base/renderer.h"
#include "menu/base/util/instructionals.h"
#include "menu/base/util/input.h"
#include "menu/base/util/menu_input.h"
#include "menu/base/util/hotkeys.h"
#include "menu/base/util/notify.h"
#include "rage/invoker/natives.h"
#include "util/fiber_pool.h"
#include "util/fiber.h"
#include "util/va.h"

void toggle_option::render(int position) {
	bool selected = menu::base::is_option_selected(position);
	color_rgba color = selected ? global::ui::g_option_selected : global::ui::g_option;
	color_rgba toggle_color = *m_toggle ? global::ui::g_toggle_on : global::ui::g_toggle_off;

	m_on_update(this, position);

	menu::renderer::draw_text(m_name.get(), { global::ui::g_position.x + 0.004f + m_offset, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color);
	menu::renderer::draw_sprite({ "ozarktextures", "toggle_circle.png" }, { global::ui::g_position.x + global::ui::g_toggle_position.x - (0.23f - global::ui::g_scale.x), global::ui::g_position.y + global::ui::g_toggle_position.y + (position * global::ui::g_option_scale) }, global::ui::g_toggle_scale, 0.f, toggle_color);
}

void toggle_option::render_selected(int position, std::stack<std::string> submenu_name_stack) {
	m_on_hover();

	if (m_has_hotkey && m_requirement()) {
		if (menu::input::is_just_released(true, VK_F12)) {
			native::play_sound_frontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);

			menu::input::push([this] {
				menu::input::hotkey(m_name.get(), this);
			});
		}
	}

	if (m_toggle && m_requirement() && menu::input::is_option_pressed()) {
		*m_toggle = !*m_toggle;
		m_on_click();

		if (m_savable) {
			util::config::write_bool(submenu_name_stack, m_name.get_original(), *m_toggle);
		}
	}
}

void toggle_option::invoke_hotkey() {
	if (!m_requirement()) return;

	*m_toggle = !*m_toggle;
	m_on_click();

	static std::unordered_map<uint32_t, uint32_t> notifies;
	if (notifies[native::get_hash_key(m_name.get_original().c_str())] > GetTickCount()) return;

	notifies[native::get_hash_key(m_name.get_original().c_str())] = GetTickCount() + 5000;
	menu::notify::stacked(TRANSLATE(t_hotkey), util::va::va("%s %s", TRANSLATE(t_used_hotkey_for), m_name.get().c_str()));
}