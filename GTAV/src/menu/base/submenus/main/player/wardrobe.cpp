#include "wardrobe.h"
#include "menu/base/submenu_handler.h"
#include "appearance.h"
#include "wardrobe_save_load.h"
#include "menu/base/util/panels.h"

using namespace player::wardrobe::vars;

namespace player::wardrobe::vars {
	variables m_vars;

	scroll_struct<std::pair<int, math::vector3_<float>>> components[] = {
		{ localization("Face", true), { 0, { 0.000f, 0.300f, -0.300f } } },
		{ localization("Mask", true), { 1, { 0.000f, 0.300f, -0.300f } } },
		{ localization("Hair", true), { 2, { 0.000f, 0.300f, -0.300f } } },
		{ localization("Torso", true), { 3, { 0.000f, -0.400f, 0.100f } } },
		{ localization("Leg", true), { 4, { 0.000f, -0.400f, 0.800f } } },
		{ localization("Misc", true), { 5, { 0.00f, -2.00f, 0.40f } } },
		{ localization("Shoes", true), { 6, { 0.000f, 0.000f, 1.200f } } },
		{ localization("Accessories", true), { 7, { 0.00f, -2.00f, 0.40f } } },
		{ localization("Undershirt", true), { 8, { 0.000f, -0.400f, 0.100f } } },
		{ localization("Kevlar", true), { 9, { 0.000f, -0.400f, 0.100f } } },
		{ localization("Badge", true), { 10, { 0.000f, -0.400f, 0.100f } } },
		{ localization("Torso 2", true), { 11, { 0.000f, -0.400f, 0.100f } } }
	};

	scroll_struct<std::pair<int, math::vector3_<float>>> accessories[] = {
		{ localization("Hats", true), { 0, { 0.000f, 0.300f, -0.300f } } },
		{ localization("Glasses", true), { 1, { 0.000f, 0.300f, -0.300f } } },
		{ localization("Ears", true), { 2, { 0.000f, 0.300f, -0.300f } } },
		{ localization("Watches", true), { 6, { 0.300f, 0.750f, 0.400f /*RIGHT*/ } } },
		{ localization("Bracelets", true), { 7, { 0.300f, 0.750f, 0.400f /*RIGHT*/ } } },
	};

	void remove_camera() {
		if (native::does_cam_exist(m_vars.m_preview_cam)) {
			native::set_cam_active(m_vars.m_preview_cam, false);
			native::render_script_cams(false, true, 1000, true, false, 0);
			native::destroy_cam(m_vars.m_preview_cam, false);
		}
	}

	void change_zoom(int type) {
		if (!m_vars.m_zoom_to_body_part || menu::player::get_local_player().m_in_vehicle) {
			menu::panels::panel_custom_screen_ped_preview preview;
			preview.m_is_player = false;
			preview.m_ped = global::vars::g_ped_factory->m_local_ped;
			preview.m_screen_offset = { 0.00f, -2.00f, 0.40f };
			menu::panels::set_structure(menu::panels::get_child(menu::panels::get_parent("PANEL_OUTFIT"), "PANEL_OUTFIT_INFO"), (void*)&preview, sizeof(preview));
			return;
		}

		math::vector3_<float> to_lerp;
		if (type == 1) to_lerp = components[m_vars.m_clothing].m_result.second;
		else if(type == 2) to_lerp = accessories[m_vars.m_accessory].m_result.second;
		else to_lerp = accessories[m_vars.m_accessory_clear].m_result.second;

		if (type == 1337) {
			to_lerp = { 0.00f, -2.00f, 0.40f };
		}

		m_vars.m_current_offset.x = math::lerp(m_vars.m_current_offset.x, to_lerp.x, 5.f * global::ui::g_delta);
		m_vars.m_current_offset.y = math::lerp(m_vars.m_current_offset.y, to_lerp.y, 5.f * global::ui::g_delta);
		m_vars.m_current_offset.z = math::lerp(m_vars.m_current_offset.z, to_lerp.z, 5.f * global::ui::g_delta);

		menu::panels::panel_custom_screen_ped_preview preview;
		preview.m_is_player = false;
		preview.m_ped = global::vars::g_ped_factory->m_local_ped;
		preview.m_screen_offset.x = m_vars.m_current_offset.x;
		preview.m_screen_offset.y = m_vars.m_current_offset.y;
		preview.m_screen_offset.z = m_vars.m_current_offset.z;

		menu::panels::set_structure(menu::panels::get_child(menu::panels::get_parent("PANEL_OUTFIT"), "PANEL_OUTFIT_INFO"), (void*)&preview, sizeof(preview));
	}
}

void wardrobe_menu::load() {
	set_name("Wardrobe");
	set_parent<appearance_menu>();

	add_option(submenu_option("Save and Load")
		.add_translate().add_hotkey()
		.add_submenu<wardrobe_save_load_menu>());

	add_option(toggle_option("Zoom to Body Part")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_zoom_to_body_part).add_savable(get_submenu_name_stack())
		.add_tooltip("Zooms the player preview to the body part being edited"));

	add_option(break_option("Customization")
		.add_translate());

	add_option(scroll_option<std::pair<int, math::vector3_<float>>>(SCROLL, "Clothing")
		.add_translate()
		.add_scroll(m_vars.m_clothing, 0, NUMOF(components), components)
		.add_click([] {
			m_vars.m_clothing_model = native::get_ped_drawable_variation(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first);
			m_vars.m_clothing_variation = native::get_ped_texture_variation(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first);
		})
		.add_hover([] { change_zoom(1); }));

	add_option(number_option<int>(SCROLL, "Clothing Model")
		.add_translate()
		.add_number(m_vars.m_clothing_model, "%i", 1).add_min(-1).add_max(0).show_max()
		.add_click([] {
			native::set_ped_component_variation(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first, m_vars.m_clothing_model, native::get_ped_texture_variation(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first), 0);
			m_vars.m_clothing_variation = native::get_ped_texture_variation(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first);
		})
		.add_update([](number_option<int>* option, int position) {
			option->add_max(native::get_number_of_ped_drawable_variations(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first) - 1);
		}));

	add_option(number_option<int>(SCROLL, "Clothing Variation")
		.add_translate()
		.add_number(m_vars.m_clothing_variation, "%i", 1).add_min(-1).add_max(0).show_max()
		.add_click([] {
			native::set_ped_component_variation(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first, m_vars.m_clothing_model, m_vars.m_clothing_variation, 0);
		})
		.add_update([](number_option<int>* option, int position) {
			option->add_max(native::get_number_of_ped_texture_variations(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first, m_vars.m_clothing_model));

			if (m_vars.m_clothing_variation > native::get_number_of_ped_texture_variations(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first, m_vars.m_clothing_model)) {
				m_vars.m_clothing_variation = 0;
			}
		})
		.add_requirement([] { return native::get_number_of_ped_drawable_variations(menu::player::get_local_player().m_ped, components[m_vars.m_clothing].m_result.first) > 0; }));

	add_option(scroll_option<std::pair<int, math::vector3_<float>>>(SCROLL, "Accessory")
		.add_translate()
		.add_scroll(m_vars.m_accessory, 0, NUMOF(accessories), accessories)
		.add_click([] {
			m_vars.m_accessory_model = native::get_ped_prop_index(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first);
			m_vars.m_accessory_variation = native::get_ped_prop_texture_index(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first);
		})
		.add_hover([] { change_zoom(2); }));

	add_option(number_option<int>(SCROLL, "Accessory Model")
		.add_translate()
		.add_number(m_vars.m_accessory_model, "%i", 1).add_min(-1).add_max(0).show_max()
		.add_click([] {
			native::set_ped_prop_index(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first, m_vars.m_accessory_model, 0, true);
			m_vars.m_accessory_variation = native::get_ped_prop_texture_index(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first);
		})
		.add_update([](number_option<int>* option, int position) {
			option->add_max(native::get_number_of_ped_prop_drawable_variations(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first));
		}));

	add_option(number_option<int>(SCROLL, "Accessory Variation")
		.add_translate()
		.add_number(m_vars.m_accessory_variation, "%i", 1).add_min(-1).add_max(0).show_max()
		.add_click([] {
			native::set_ped_prop_index(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first, m_vars.m_accessory_model, m_vars.m_accessory_variation, true);
		})
		.add_update([](number_option<int>* option, int position) {
			option->add_max(native::get_number_of_ped_prop_texture_variations(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first, m_vars.m_accessory_variation));

			if (m_vars.m_accessory_variation > native::get_number_of_ped_prop_texture_variations(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first, m_vars.m_accessory_variation)) {
				m_vars.m_clothing_variation = 0;
			}
		})
		.add_requirement([] { return native::get_number_of_ped_prop_texture_variations(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first, m_vars.m_accessory) > 0; }));

	add_option(scroll_option<std::pair<int, math::vector3_<float>>>(SCROLLSELECT, "Clear Accessory")
		.add_translate()
		.add_scroll(m_vars.m_accessory_clear, 0, NUMOF(accessories), accessories)
		.add_click([] {
			native::clear_ped_prop(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first);
			m_vars.m_accessory_model = native::get_ped_prop_index(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first);
			m_vars.m_accessory_variation = native::get_ped_prop_texture_index(menu::player::get_local_player().m_ped, accessories[m_vars.m_accessory].m_result.first);
		})
		.add_hover([] { change_zoom(3); }));
}

void wardrobe_menu::update() {
	if (menu::base::get_current_option() <= 1) {
		change_zoom(1337);
	}
}

void wardrobe_menu::update_once() {
	menu::panels::panel_custom_screen_ped_preview preview;
	preview.m_is_player = false;
	preview.m_ped = global::vars::g_ped_factory->m_local_ped;
	preview.m_screen_offset = { 0.00f, -2.00f, 0.40f };
	menu::panels::set_structure(menu::panels::get_child(menu::panels::get_parent("PANEL_OUTFIT"), "PANEL_OUTFIT_INFO"), (void*)&preview, sizeof(preview));
	menu::panels::toggle_panel_render("PANEL_OUTFIT", true);
}

void wardrobe_menu::feature_update() {
	if (m_vars.m_preview_camera && (menu::submenu::handler::get_current() == this
		|| menu::submenu::handler::get_current() == wardrobe_save_load_menu::get())) {
		if (!native::does_cam_exist(m_vars.m_preview_cam)) {
			m_vars.m_preview_cam = native::create_cam("DEFAULT_SCRIPTED_CAMERA", false);
		}

		native::set_cam_active(m_vars.m_preview_cam, true);
		native::render_script_cams(true, true, 1000, true, 0, 0);
		native::attach_cam_to_ped_bone(m_vars.m_preview_cam, menu::player::get_local_player().m_ped, 0, 0.f, 1.5f, 0.f, true);
		native::point_cam_at_ped_bone(m_vars.m_preview_cam, menu::player::get_local_player().m_ped, 0, 0.f, 0.f, 0.3f, true);
		native::task_stand_still(menu::player::get_local_player().m_ped, 1);
	}
}

wardrobe_menu* g_instance;
wardrobe_menu* wardrobe_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new wardrobe_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}