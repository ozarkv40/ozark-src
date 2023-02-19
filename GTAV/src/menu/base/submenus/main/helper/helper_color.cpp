#include "helper_color.h"
#include "menu/base/submenu_handler.h"
#include "../../main.h"
#include "../settings/color/color_sync.h"
#include "color/helper_color_preset.h"

using namespace helper::color::vars;

namespace helper::color::vars {
	variables m_vars;

	scroll_struct<int> type[] = {
		{ localization("RGBA", true), 0 },
		{ localization("HSVA", true), 0 },
	};
}

void helper_color_menu::load() {
	set_name("Color", false, false);
	set_parent<main_menu>();

	// [s] Presets
	// [s] Sync With...
	// Open Color Picker
	// ~ Custom Editor ~
	// Type <RGBA, HSVA>
	// ...
	// 

	add_option(submenu_option("Presets")
		.add_translate()
		.add_submenu<helper_color_preset_menu>()
		.add_click([] { helper::color::preset::vars::m_vars.m_color = m_vars.m_color; }));

	add_option(submenu_option("Sync With...")
		.add_translate()
		.add_submenu<color_selected_sync_menu>()
		.add_click([] { settings::color::sync::vars::m_vars.m_color = m_vars.m_color; }));

	add_option(button_option("Open Color Picker")
		.add_translate()
		.add_click([this] {
			menu::input::push([this] {
				menu::input::color(m_vars.m_color);
				m_vars.m_callback();
			});
		}));

	add_option(break_option("Custom Editor")
		.add_translate());

	add_option(scroll_option<int>(SCROLL, "Color Format")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(type), type)
		.add_click([this] { update_once(); })
		.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); }));

	add_string("[R]ed");
	add_string("[G]reen");
	add_string("[B]lue");
	add_string("[A]lpha");
	add_string("[H]ue");
	add_string("[S]aturation");
	add_string("[V]alue");
}

void helper_color_menu::update() {}

void helper_color_menu::update_once() {
	clear_options(5);

	// RGBA
	if (m_vars.m_type == 0) {
		add_option(number_option<int>(SCROLL, get_string("[R]ed"))
			.add_number(m_vars.m_color->r, "%i", 1).add_min(0).add_max(255).can_loop()
			.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); })
			.add_click(m_vars.m_callback));

		add_option(number_option<int>(SCROLL, get_string("[G]reen"))
			.add_number(m_vars.m_color->g, "%i", 1).add_min(0).add_max(255).can_loop()
			.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); })
			.add_click(m_vars.m_callback));

		add_option(number_option<int>(SCROLL, get_string("[B]lue"))
			.add_number(m_vars.m_color->b, "%i", 1).add_min(0).add_max(255).can_loop()
			.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); })
			.add_click(m_vars.m_callback));

		add_option(number_option<int>(SCROLL, get_string("[A]lpha"))
			.add_number(m_vars.m_color->a, "%i", 1).add_min(0).add_max(255).can_loop()
			.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); })
			.add_click(m_vars.m_callback));

		return;
	}

	m_vars.m_hsv = menu::renderer::rgb_to_hsv(*m_vars.m_color);

	m_vars.m_hsv.s *= 100.f;
	m_vars.m_hsv.v *= 100.f;

	add_option(number_option<float>(SCROLL, get_string("[H]ue"))
		.add_number(m_vars.m_hsv.h, "%.2f", 0.01f).add_min(0.f).add_max(360.f).set_scroll_speed(0)
		.add_click([] {
			*m_vars.m_color = menu::renderer::hsv_to_rgb(m_vars.m_hsv.h, m_vars.m_hsv.s / 100.f, m_vars.m_hsv.v / 100.f, m_vars.m_color->a);
			m_vars.m_callback();
		})
		.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); }));

	add_option(number_option<float>(SCROLL, get_string("[S]aturation"))
		.add_number(m_vars.m_hsv.s, "%.2f", 0.01f).add_min(0.f).add_max(100.f).set_scroll_speed(0)
		.add_click([] {
			*m_vars.m_color = menu::renderer::hsv_to_rgb(m_vars.m_hsv.h, m_vars.m_hsv.s / 100.f, m_vars.m_hsv.v / 100.f, m_vars.m_color->a);
			m_vars.m_callback();
		})
		.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); }));

	add_option(number_option<float>(SCROLL, get_string("[V]alue"))
		.add_number(m_vars.m_hsv.v, "%.2f", 0.01f).add_min(0.f).add_max(100.f).set_scroll_speed(0)
		.add_click([] {
			*m_vars.m_color = menu::renderer::hsv_to_rgb(m_vars.m_hsv.h, m_vars.m_hsv.s / 100.f, m_vars.m_hsv.v / 100.f, m_vars.m_color->a);
			m_vars.m_callback();
		})
		.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); }));

	add_option(number_option<int>(SCROLL, get_string("[A]lpha"))
		.add_number(m_vars.m_color->a, "%i", 1).add_min(0).add_max(255).can_loop()
		.add_hover([] { menu::renderer::render_color_preview(*m_vars.m_color); })
		.add_click(m_vars.m_callback));
}

void helper_color_menu::feature_update() {}

helper_color_menu* g_instance;
helper_color_menu* helper_color_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new helper_color_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}