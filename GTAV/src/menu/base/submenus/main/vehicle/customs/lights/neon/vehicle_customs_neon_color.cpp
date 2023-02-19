#include "vehicle_customs_neon_color.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs_neon.h"
#include "../../../vehicle_customs.h"

using namespace vehicle::customs::neon::color::vars;

namespace vehicle::customs::neon::color::vars {
	variables m_vars;

	std::vector<std::pair<color_rgba, int>> color_map = {
		{ { 222, 222, 255 }, 0 },
		{ { 2, 21, 255 }, 1 },
		{ { 3, 83, 255 }, 2 },
		{ { 0, 255, 140 }, 3 },
		{ { 94, 255, 1 }, 4 },
		{ { 255, 255, 0 }, 5 },
		{ { 255, 150, 0 }, 6 },
		{ { 255, 62, 0 }, 7 },
		{ { 255, 1, 1 }, 8 },
		{ { 255, 50, 100 }, 9 },
		{ { 255, 5, 190 }, 10 },
		{ { 35, 1, 255 }, 11 },
		{ { 15, 3, 255 }, 12 }
	};

	void update_color_preview(color_rgba col) {
		for (int i = 0; i < 4; i++) {
			if (native::is_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, i)) {
				native::set_vehicle_neon_lights_colour(menu::player::get_local_player().m_vehicle, col.r, col.g, col.b);
			}
		}
	}

	void update_color(color_rgba col) {
		vehicle::customs::vars::m_vars.m_cached_stats.m_neon_color = col;
	}
}

void vehicle_customs_neon_color_menu::load() {
	set_name("Neon Color");
	set_parent<vehicle_customs_neon_menu>();

	add_string("White");
	add_string("Blue");
	add_string("Electric Blue");
	add_string("Mint Green");
	add_string("Lime Green");
	add_string("Yellow");
	add_string("Golden Shower");
	add_string("Orange");
	add_string("Red");
	add_string("Pony Pink");
	add_string("Hot Pink");
	add_string("Purple");
	add_string("Blacklight");
}

void vehicle_customs_neon_color_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
	if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() && menu::base::get_current_option() - menu::base::get_scroll_offset() >= menu::base::get_max_options()) menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);
}

void vehicle_customs_neon_color_menu::update_once() {
	clear_options(0);
	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	std::vector<std::shared_ptr<radio_option>> temp_options;

	temp_options.push_back(add_option(radio_option(get_string("White"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 222, 222, 255 }); })
		.add_hover([] { update_color_preview({ 222, 222, 255 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Blue"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 2, 21, 255 }); })
		.add_hover([] { update_color_preview({ 2, 21, 255 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Electric Blue"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 3, 83, 255 }); })
		.add_hover([] { update_color_preview({ 3, 83, 255 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Mint Green"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 0, 255, 140 }); })
		.add_hover([] { update_color_preview({ 0, 255, 140 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Lime Green"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 94, 255, 1 }); })
		.add_hover([] { update_color_preview({ 94, 255, 1 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Yellow"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 255, 255, 0 }); })
		.add_hover([] { update_color_preview({ 255, 255, 0 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Golden Shower"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 255, 150, 0 }); })
		.add_hover([] { update_color_preview({ 255, 150, 0 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Orange"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 255, 62, 0 }); })
		.add_hover([] { update_color_preview({ 255, 62, 0 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Red"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 255, 1, 1 }); })
		.add_hover([] { update_color_preview({ 255, 1, 1 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Pony Pink"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 255, 50, 100 }); })
		.add_hover([] { update_color_preview({ 255, 50, 100 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Hot Pink"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 255, 5, 190 }); })
		.add_hover([] { update_color_preview({ 255, 5, 190 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Purple"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 35, 1, 255 }); })
		.add_hover([] { update_color_preview({ 35, 1, 255 }); })));

	temp_options.push_back(add_option(radio_option(get_string("Blacklight"))
		.add_radio(m_vars.m_context)
		.add_click([] { update_color({ 15, 3, 255 }); })
		.add_hover([] { update_color_preview({ 15, 3, 255 }); })));

	for (std::pair<color_rgba, int>& map : color_map) {
		color_rgba color = vehicle::customs::vars::m_vars.m_cached_stats.m_neon_color;
		if (color.r == map.first.r
			&& color.g == map.first.g
			&& color.b == map.first.b) {
			if (map.second != 0) {
				temp_options[map.second]->update_selected();
				menu::base::set_current_option(map.second);
			}

			break;
		}
	}
}

void vehicle_customs_neon_color_menu::feature_update() {}

vehicle_customs_neon_color_menu* g_instance;
vehicle_customs_neon_color_menu* vehicle_customs_neon_color_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_neon_color_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}