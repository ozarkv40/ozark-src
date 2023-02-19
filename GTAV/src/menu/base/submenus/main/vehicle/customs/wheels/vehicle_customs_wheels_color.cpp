#include "vehicle_customs_wheels_color.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs_wheels.h"
#include "../../vehicle_customs.h"
#include "vehicle_customs_wheels_type.h"
#include "rage/engine.h"

using namespace vehicle::customs::wheels::color::vars;

namespace vehicle::customs::wheels::color::vars {
	variables m_vars;
}

void vehicle_customs_wheels_color_menu::load() {
	set_name("Wheel Color");
	set_parent<vehicle_customs_wheels_menu>();
}

void vehicle_customs_wheels_color_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
	if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() && menu::base::get_current_option() - menu::base::get_scroll_offset() >= menu::base::get_max_options()) menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);
}

void vehicle_customs_wheels_color_menu::update_once() {
	clear_options(0);

	vehicle::customs::wheels::vars::m_vars.m_update_cache = true;
	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	std::vector<std::shared_ptr<radio_option>> temp_options;

	int selected_index = 99;

	uint64_t paint = rage::engine::get_vehicle_paint(1);
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
							.add_click([=] { vehicle::customs::wheels::vars::m_vars.m_paint_index = paint_index; })
							.add_hover([=] {
								int perl = 0;
								int cur = 0;
								native::get_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, &perl, &cur);
								native::set_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, perl, paint_index);
							})));

						if (paint_index == vehicle::customs::wheels::vars::m_vars.m_paint_index && selected_index == 99) {
							selected_index = i;
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

void vehicle_customs_wheels_color_menu::feature_update() {}

vehicle_customs_wheels_color_menu* g_instance;
vehicle_customs_wheels_color_menu* vehicle_customs_wheels_color_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_wheels_color_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}