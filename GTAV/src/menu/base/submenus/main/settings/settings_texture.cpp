#include "settings_texture.h"
#include "menu/base/submenu_handler.h"
#include "settings_textures.h"
#include "util/dirs.h"
#include "menu/base/util/textures.h"

using namespace settings::texture::vars;

namespace settings::texture::vars {
	variables m_vars;
}

void texture_menu::load() {
	set_name("Header");
	set_parent<textures_menu>();

	m_vars.m_toggle_button = add_option(toggle_option("Toggle Texture")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_texture->m_enabled)
		.add_update([](toggle_option* option, int position) {
			option->add_toggle(m_vars.m_texture->m_enabled);
		})
		.add_click([this] {
			if (m_vars.m_texture->m_enabled) {
				menu::notify::stacked(get_string("Textures"), get_string("You might need to change the color of this texture to see it, generally this means setting it to white"));
			}
		}));

	add_option(break_option("Textures")
		.add_translate());

	add_string("~m~None");
	add_string("For your resolution, optimal size for this menu texture is");
	add_string("Please note: this texutre resizes on the");
	add_string("axis, keep this in mind to avoid stretching.");
	add_string("pixels");
	add_string("Textures");
	add_string("You might need to change the color of this texture to see it, generally this means setting it to white");
}

void texture_menu::update() {}

void texture_menu::update_once() {
	menu::textures::update();
	set_name(m_vars.m_texture->m_submenu_name.get());

	if (m_vars.m_pixel_info.m_pixel_size.x) {
		int pixel_x = (int)((float)global::vars::g_resolution.x * m_vars.m_pixel_info.m_pixel_size.x);
		int pixel_y = (int)((float)global::vars::g_resolution.y * m_vars.m_pixel_info.m_pixel_size.y);
		m_vars.m_toggle_button->set_tooltip(util::va::va("%s %ix%i %s. %s",
			get_string("For your resolution, optimal size for this menu texture is").c_str(),
			pixel_x, pixel_y,
			get_string("pixels").c_str(),
			m_vars.m_pixel_info.m_can_resize ? (get_string("Please note: this texutre resizes on the") + " " + m_vars.m_pixel_info.m_resize_type + " " + get_string("axis, keep this in mind to avoid stretching.")).c_str() : ""));
	} else m_vars.m_toggle_button->set_tooltip("");

	int previously_selected = m_vars.m_texture->m_context.m_selected;
	m_vars.m_texture->m_context.m_selected = 0;
	m_vars.m_texture->m_context.reset();

	clear_options(2);

	std::vector<std::shared_ptr<radio_option>> temp;

	for (menu::textures::texture_context texture : menu::textures::get_list()) {
		if (!strstr(texture.m_name.c_str(), "playerimg_")) {
			temp.push_back(add_option(radio_option(texture.m_name)
				.add_radio(m_vars.m_texture->m_context)
				.add_click([] { m_vars.m_texture->m_texture = menu::textures::get_list()[m_vars.m_texture->m_context.m_selected].m_name; })));
		}
	}

	if (previously_selected != 0) {
		if (previously_selected < temp.size()) {
			temp[previously_selected]->update_selected();
		}
	} else {
		m_vars.m_texture->m_texture = "sa7anisafaggot";
	}
}

void texture_menu::feature_update() {}

texture_menu* g_instance;
texture_menu* texture_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new texture_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}