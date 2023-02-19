#include "vehicle_customs_respray_type.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs_respray.h"
#include "../../vehicle_customs.h"
#include "vehicle_customs_respray_edit.h"

using namespace vehicle::customs::respray::type::vars;

namespace vehicle::customs::respray::type::vars {
	variables m_vars;
}

void vehicle_customs_respray_type_menu::load() {
	set_name("Respray");
	set_parent<vehicle_customs_respray_menu>();

	add_string("Chrome");
	add_string("Classic");
	add_string("Matte");
	add_string("Metallic");
	add_string("Metals");
	add_string("Pearlescent");
}

void vehicle_customs_respray_type_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_respray_type_menu::update_once() {
	clear_options(0);

	vehicle::customs::respray::vars::m_vars.m_update_cache = true;
	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	if (m_vars.m_update_cache) {
		m_vars.m_update_cache = false;

		if (native::get_is_vehicle_primary_colour_custom(menu::player::get_local_player().m_vehicle)) {
			native::clear_vehicle_custom_primary_colour(menu::player::get_local_player().m_vehicle);
		}

		if (native::get_is_vehicle_secondary_colour_custom(menu::player::get_local_player().m_vehicle)) {
			native::clear_vehicle_custom_secondary_colour(menu::player::get_local_player().m_vehicle);
		}

		native::set_vehicle_colours(menu::player::get_local_player().m_vehicle, m_vars.m_paint_index[PRIMARY], m_vars.m_paint_index[SECONDARY]);

		int wheel_color = 0;
		int pearl = 0;
		native::get_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, &pearl, &wheel_color);
		native::set_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, m_vars.m_paint_index[PEARLESCENT], wheel_color);
	}

	int wheel_color = 0;
	native::get_vehicle_colours(menu::player::get_local_player().m_vehicle, &m_vars.m_paint_index[PRIMARY], &m_vars.m_paint_index[SECONDARY]);
	native::get_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, &m_vars.m_paint_index[PEARLESCENT], &wheel_color);

	if (m_vars.m_type == 1 || m_vars.m_type == 2) {
		add_option(submenu_option(get_string("Chrome"))
			.add_submenu<vehicle_customs_respray_edit_menu>()
			.add_click([] { vehicle::customs::respray::edit::vars::m_vars.m_type = 5; }));

		add_option(submenu_option(get_string("Classic"))
			.add_submenu<vehicle_customs_respray_edit_menu>()
			.add_click([] { vehicle::customs::respray::edit::vars::m_vars.m_type = 1; }));

		add_option(submenu_option(get_string("Matte"))
			.add_submenu<vehicle_customs_respray_edit_menu>()
			.add_click([] { vehicle::customs::respray::edit::vars::m_vars.m_type = 3; }));

		add_option(submenu_option(get_string("Metallic"))
			.add_submenu<vehicle_customs_respray_edit_menu>()
			.add_click([] { vehicle::customs::respray::edit::vars::m_vars.m_type = 0; }));

		add_option(submenu_option(get_string("Metals"))
			.add_submenu<vehicle_customs_respray_edit_menu>()
			.add_click([] { vehicle::customs::respray::edit::vars::m_vars.m_type = 4; }));

		// Primary only
		if (m_vars.m_type == 1) {
			add_option(submenu_option(get_string("Pearlescent"))
				.add_submenu<vehicle_customs_respray_edit_menu>()
				.add_click([] { vehicle::customs::respray::edit::vars::m_vars.m_type = 2; }));
		}
	} else {
		// Livery
		std::vector<std::shared_ptr<radio_option>> temp_options;
		int selected_index = 99;

		for (int i = 0; i < native::get_vehicle_livery_count(menu::player::get_local_player().m_vehicle); i++) {
			const char* livery_name = native::get_livery_name(menu::player::get_local_player().m_vehicle, i);
			if (livery_name) {
				temp_options.push_back(add_option(radio_option(native::get_label_text(livery_name))
					.add_radio(m_vars.m_context)
					.add_click([=] { vehicle::customs::respray::vars::m_vars.m_livery = i; })
					.add_hover([=] {
						native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
						native::set_vehicle_livery(menu::player::get_local_player().m_vehicle, i);
					})));

				if (vehicle::customs::respray::vars::m_vars.m_livery == i) {
					selected_index = i;
				}
			}
		}

		if (selected_index != 0) {
			if (selected_index != 99) {
				temp_options[selected_index]->update_selected();
				menu::base::set_current_option(selected_index);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}
	}
}

void vehicle_customs_respray_type_menu::feature_update() {}

vehicle_customs_respray_type_menu* g_instance;
vehicle_customs_respray_type_menu* vehicle_customs_respray_type_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_respray_type_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}