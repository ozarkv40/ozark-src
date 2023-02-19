#include "submenu_option.h"
#include "menu/base/renderer.h"
#include "menu/base/util/input.h"
#include "menu/base/util/menu_input.h"
#include "menu/base/util/notify.h"
#include "menu/base/submenu_handler.h"
#include "rage/invoker/natives.h"
#include "util/va.h"

void submenu_option::render(int position) {
	bool selected = menu::base::is_option_selected(position);
	color_rgba color = selected ? global::ui::g_option_selected : global::ui::g_option;
	color_rgba bar_color = global::ui::g_submenu_bar;

	m_on_update(this, position);

	menu::renderer::draw_text(m_name.get(), { global::ui::g_position.x + 0.004f + m_offset, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color);

	if (!m_disable_icon) {
		if (m_override.m_enabled) {
			menu::renderer::draw_sprite_aligned(m_override.m_asset, { global::ui::g_position.x + m_override.m_offset.x - (0.23f - global::ui::g_scale.x), global::ui::g_position.y + (position * global::ui::g_option_scale) + m_override.m_offset.y }, m_override.m_scale, 0.f, *m_override.m_color);
		} else {
			menu::renderer::draw_sprite_aligned({ "ozarktextures", "arrow.png" }, { global::ui::g_position.x + global::ui::g_submenu_arrow_position.x - (0.23f - global::ui::g_scale.x), global::ui::g_position.y + (position * global::ui::g_option_scale) + global::ui::g_submenu_arrow_position.y }, global::ui::g_submenu_arrow_scale, 0.f, bar_color);
		}
	}

	if (m_side_text.m_enabled) {
		menu::renderer::draw_text(m_side_text.m_text, { global::ui::g_position.x + 0.004f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color, JUSTIFY_RIGHT, { 0.f, (1.0f - (1.0f - (global::ui::g_position.x + (0.315f / 2.f)) - global::ui::g_wrap)) - 0.005f });
	}
}

void submenu_option::render_selected(int position, std::stack<std::string> submenu_name_stack) {
	m_on_hover(this);

	if (m_has_hotkey && m_requirement()) {
		if (menu::input::is_just_released(true, VK_F12)) {
			native::play_sound_frontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);

			menu::input::push([this] {
				menu::input::hotkey(m_name.get(), this);
			});
		}
	}

	if (m_requirement() && menu::input::is_option_pressed()) {
		m_on_click();
		m_on_click_this(this);
		menu::submenu::handler::set_submenu(m_submenu);
	}
}

void submenu_option::invoke_hotkey() {
	if (!m_requirement()) return;
	m_on_click();

	if (!menu::base::is_open()) menu::base::set_open(true);
	menu::submenu::handler::set_submenu(m_submenu);

	static std::unordered_map<uint32_t, uint32_t> notifies;
	if (notifies[native::get_hash_key(m_name.get_original().c_str())] > GetTickCount()) return;

	notifies[native::get_hash_key(m_name.get_original().c_str())] = GetTickCount() + 5000;
	menu::notify::stacked(TRANSLATE(t_hotkey), util::va::va("%s %s", TRANSLATE(t_used_hotkey_for), m_name.get().c_str()));
}