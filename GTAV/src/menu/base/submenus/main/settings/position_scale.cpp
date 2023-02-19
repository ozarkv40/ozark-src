#include "position_scale.h"
#include "menu/base/submenu_handler.h"
#include "../settings.h"
#include "pos/position_scale_selected.h"

using namespace settings::pos::vars;

namespace settings::pos::vars {
	scroll_struct<math::vector2<float>*> scales[] = {
		{ localization("Menu Position", true), &global::ui::g_position },
		{ localization("Menu Scale", true), &global::ui::g_scale },
		{ localization("Submenu Arrow Position", true), &global::ui::g_submenu_arrow_position },
		{ localization("Submenu Scale", true), &global::ui::g_submenu_arrow_scale },
		{ localization("Toggle Position", true), &global::ui::g_toggle_position },
		{ localization("Toggle Scale", true), &global::ui::g_toggle_scale },
		{ localization("Globe Position", true), &global::ui::g_globe_position },
		{ localization("Globe Scale", true), &global::ui::g_globe_scale },
		{ localization("Stacked Display Scale", true), &global::ui::g_stacked_display_scale },
		{ localization("Stacked Display Position", true), &global::ui::g_stacked_display_position },
	};
}

void position_scale_menu::load() {
	set_name("Position and Scale");
	set_parent<settings_menu>();

	settings::pos::selected::vars::m_vars.m_selected = &global::ui::g_position; // init
	position_scale_selected_menu::get();
}

void position_scale_menu::update() {}

void position_scale_menu::update_once() {
	clear_options(0);

	for (scroll_struct<math::vector2<float>*> scale : scales) {
		add_option(submenu_option(scale.m_name.get())
			.add_submenu<position_scale_selected_menu>()
			.add_click([=] {
				settings::pos::selected::vars::m_vars.m_selected = scale.m_result;
			}));
	}
}

void position_scale_menu::feature_update() {}

position_scale_menu* g_instance;
position_scale_menu* position_scale_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new position_scale_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}