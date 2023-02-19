#include "vehicle_customs_respray_edit.h"
#include "menu/base/submenu_handler.h"
#include "vehicle_customs_respray_type.h"
#include "../../vehicle_customs.h"
#include "rage/engine.h"

using namespace vehicle::customs::respray::edit::vars;

namespace vehicle::customs::respray::edit::vars {
	variables m_vars;
}

void vehicle_customs_respray_edit_menu::load() {
	set_name("Respray");
	set_parent<vehicle_customs_respray_type_menu>();
}

void vehicle_customs_respray_edit_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
	if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() && menu::base::get_current_option() - menu::base::get_scroll_offset() >= menu::base::get_max_options()) menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);
}

void vehicle_customs_respray_edit_menu::update_once() {
	clear_options(0);

	vehicle::customs::respray::type::vars::m_vars.m_update_cache = true;
	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	std::vector<std::shared_ptr<radio_option>> temp_options;
	int selected_index = 99;

	uint64_t paint = rage::engine::get_vehicle_paint(m_vars.m_type);
	if (paint) {
		uint64_t paint_info = *(uint64_t*)paint;
		if (paint_info) {
			uint16_t paint_count = *(uint16_t*)(paint + 0x8);
			for (uint16_t i = 0; i < paint_count; i++) {
				uint64_t paint_meta = paint_info + (uint64_t(i) << 4);
				if (paint_meta) {
					const char* paint_label = *(const char**)paint_meta;
					if (paint_label) {
						int paint_index = (int)*(uint8_t*)(paint_meta + 0x8);
						temp_options.push_back(add_option(radio_option(native::get_label_text(paint_label))
							.add_radio(m_vars.m_context)
							.add_click([=] {
								if (m_vars.m_type == 2) {
									vehicle::customs::respray::type::vars::m_vars.m_paint_index[vehicle::customs::respray::type::vars::PEARLESCENT] = paint_index;
								} else {
									if (vehicle::customs::respray::type::vars::m_vars.m_type == 1) {
										vehicle::customs::respray::type::vars::m_vars.m_paint_index[vehicle::customs::respray::type::vars::PRIMARY] = paint_index;
									} else {
										vehicle::customs::respray::type::vars::m_vars.m_paint_index[vehicle::customs::respray::type::vars::SECONDARY] = paint_index;
									}
								}
							})
							.add_hover([=] {
								if (m_vars.m_type == 2) {
									// PEARLESCENT
									int wheel_color = 0;
									int pearl_color = 0;
									native::get_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, &pearl_color, &wheel_color);
									native::set_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, paint_index, wheel_color);
								} else {
									if (native::get_is_vehicle_primary_colour_custom(menu::player::get_local_player().m_vehicle)) {
										native::clear_vehicle_custom_primary_colour(menu::player::get_local_player().m_vehicle);
									}

									if (native::get_is_vehicle_secondary_colour_custom(menu::player::get_local_player().m_vehicle)) {
										native::clear_vehicle_custom_secondary_colour(menu::player::get_local_player().m_vehicle);
									}

									if (vehicle::customs::respray::type::vars::m_vars.m_type == 1) {
										// PRIMARY
										int primary = 0;
										int secondary = 0;
										native::get_vehicle_colours(menu::player::get_local_player().m_vehicle, &primary, &secondary);
										native::set_vehicle_colours(menu::player::get_local_player().m_vehicle, paint_index, secondary);
									} else {
										// SECONDARY
										int primary = 0;
										int secondary = 0;
										native::get_vehicle_colours(menu::player::get_local_player().m_vehicle, &primary, &secondary);
										native::set_vehicle_colours(menu::player::get_local_player().m_vehicle, primary, paint_index);
									}
								}
							})));

						if (selected_index == 99) {
							if (m_vars.m_type == 2) {
								// PEARLESCENT
								if (paint_index == vehicle::customs::respray::type::vars::m_vars.m_paint_index[vehicle::customs::respray::type::vars::PEARLESCENT]) {
									selected_index = i;
								}
							} else {
								if (vehicle::customs::respray::type::vars::m_vars.m_type == 1) {
									if (paint_index == vehicle::customs::respray::type::vars::m_vars.m_paint_index[vehicle::customs::respray::type::vars::PRIMARY]) {
										selected_index = i;
									}
								} else {
									if (paint_index == vehicle::customs::respray::type::vars::m_vars.m_paint_index[vehicle::customs::respray::type::vars::SECONDARY]) {
										selected_index = i;
									}
								}
							}
						}
					}
				}
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

void vehicle_customs_respray_edit_menu::feature_update() {}

vehicle_customs_respray_edit_menu* g_instance;
vehicle_customs_respray_edit_menu* vehicle_customs_respray_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_respray_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}