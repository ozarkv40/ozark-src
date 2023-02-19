#include "weather_fx.h"
#include "menu/base/submenu_handler.h"
#include "../../world_weather.h"
#include "menu/base/submenus/main/helper/helper_color.h"
#include "menu/base/util/textures.h"

using namespace world::weather::fx::vars;

namespace world::weather::fx::vars {
	variables m_vars;

    scroll_struct<int> scroll_names[20];

    std::pair<uint32_t, std::string> names[] = {
        { 0xE947723D, "Rainstorm Drop" },
        { 0xF4698119, "Thunder Drop" },
        { 0xB13E1842, "Snow Light Drop" },
        { 0x7F84E74E, "Snow Heavy Drop" },
        { 0xFA37E4E2, "Blizzard Drop" },
        { 0xC11D1EC6, "Underwater Drop" },
        { 0x69163FA7, "Lake Fog Drop" },
        { 0x91C32C69, "Woodland Pollen Drop" },
        { 0x8DE5FE6A, "Woodland Firefly Drop" },
        { 0x36196668, "Wetland Flies Drop" },
    };

    std::string get_shader_name(uint32_t name_hash) {
        auto vit = std::find_if(begin(names), end(names), [=] (std::pair<uint32_t, std::string> e) { return e.first == name_hash; });
        if (vit != end(names)) {
            return vit->second;
        }

        return "Unknown";
    }
}

void weather_fx_menu::load() {
	set_name("Weather FX");
	set_parent<weather_menu>();

    for (std::pair<uint32_t, std::string> str : names) {
        add_string(str.second);
    }

    add_option(scroll_option<int>(SCROLL, "Weather Type")
        .add_translate()
        .add_scroll(m_vars.m_scroll, 0, 1, scroll_names)
        .add_update([] (scroll_option<int>* option, int pos) {
            option->add_scroll(m_vars.m_scroll, 0, (int)m_vars.m_shaders.size(), scroll_names);
        })
        .add_click([this] {
            update_once();
        }));

    add_option(button_option("Reset to Default")
        .add_translate().add_hotkey()
        .add_sprite({ "ozarktextures", "spinner.png" })
        .add_sprite_scale({ 0.01232f, 0.02184f })
        .add_sprite_rotation()
        .add_click([] {
            uint32_t hash = m_vars.m_shaders[m_vars.m_scroll].m_drop->m_name_hash;
            auto vit = std::find_if(begin(m_vars.m_originals), end(m_vars.m_originals), [=] (rage::types::drop_shader e) { return e.m_name_hash == hash; });
            if (vit != end(m_vars.m_originals)) {
                memcpy(m_vars.m_shaders[m_vars.m_scroll].m_drop, &(*(vit)), sizeof(rage::types::drop_shader));
            }
        }));
}

void weather_fx_menu::update() {}

void weather_fx_menu::update_once() {
    clear_options(2);
    m_vars.m_shaders.clear();

    uint32_t drop_shader_count = *(uint32_t*)(global::vars::g_drop_shader_count);
    rage::types::drop_shader* drop_shader_list = (rage::types::drop_shader*)(global::vars::g_drop_shaders);

    for (uint32_t i = 0; i < drop_shader_count; i++) {
        rage::types::drop_shader* current = &drop_shader_list[i];
        if (!get_shader_name(current->m_name_hash).empty()) {
            color_rgba internal_color;
            float luminance = 1.f;
            
            internal_color.r = (int)(current->m_color.x * 255.f);
            internal_color.g = (int)(current->m_color.y * 255.f);
            internal_color.b = (int)(current->m_color.z * 255.f);
            internal_color.a = (int)(current->m_color.w * 255.f);

            if (current->m_color.x > 1.f) {
                luminance = current->m_color.x / 1.f;
                internal_color.r /= (int)luminance;
            }

            if (current->m_color.y > 1.f) {
                luminance = current->m_color.y / 1.f;
                internal_color.g /= (int)luminance;
            }

            if (current->m_color.z > 1.f) {
                luminance = current->m_color.z / 1.f;
                internal_color.b /= (int)luminance;
            }

            if (internal_color.r < 0) internal_color.r = 0;
            if (internal_color.g < 0) internal_color.g = 0;
            if (internal_color.b < 0) internal_color.b = 0;

            m_vars.m_shaders.push_back({ current, internal_color, luminance });
            scroll_names[i].m_name.set(get_string(get_shader_name(current->m_name_hash)));
            scroll_names[i].m_result = 123;

            auto vit = std::find_if(begin(m_vars.m_originals), end(m_vars.m_originals), [=] (rage::types::drop_shader e) { return e.m_name_hash == current->m_name_hash; });
            if (vit == end(m_vars.m_originals)) {
                rage::types::drop_shader shader;
                memcpy(&shader, current, sizeof(shader));
                m_vars.m_originals.push_back(shader);
            }
        }
    }

    if (!m_vars.m_shaders.empty()) {
        add_option(submenu_option("Edit Color")
            .add_submenu<helper_color_menu>()
            .add_click([=] {
                helper_color_menu::get()->set_name(get_name().get(), false, false);
                helper_color_menu::get()->set_parent<weather_fx_menu>();
                helper::color::vars::m_vars.m_color = &m_vars.m_shaders[m_vars.m_scroll].m_internal_color;

                helper::color::vars::m_vars.m_callback = [] {
                    m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.x = m_vars.m_shaders[m_vars.m_scroll].m_internal_color.r / 255.f;
                    m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.y = m_vars.m_shaders[m_vars.m_scroll].m_internal_color.g / 255.f;
                    m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.z = m_vars.m_shaders[m_vars.m_scroll].m_internal_color.b / 255.f;
                    m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.w = m_vars.m_shaders[m_vars.m_scroll].m_internal_color.a / 255.f;
                };
            })
            .add_update([] (submenu_option* option, int pos) {
                option->add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, &m_vars.m_shaders[m_vars.m_scroll].m_internal_color);
            }));

        add_option(number_option<float>(SCROLL, "Luminance")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_luminance, "%.1f", 0.1f).add_min(0.1f).add_max(100.f)
            .add_click([] {
                m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.x = (m_vars.m_shaders[m_vars.m_scroll].m_internal_color.r / 255.f) * m_vars.m_shaders[m_vars.m_scroll].m_luminance;
                m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.y = (m_vars.m_shaders[m_vars.m_scroll].m_internal_color.g / 255.f) * m_vars.m_shaders[m_vars.m_scroll].m_luminance;
                m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.z = (m_vars.m_shaders[m_vars.m_scroll].m_internal_color.b / 255.f) * m_vars.m_shaders[m_vars.m_scroll].m_luminance;
                m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.w = (m_vars.m_shaders[m_vars.m_scroll].m_internal_color.a / 255.f) * m_vars.m_shaders[m_vars.m_scroll].m_luminance;
            }));

        add_option(number_option<float>(SCROLL, "Gravity")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_gravity, "%.1f", 0.1f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Box Centre Offset - X")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_centre_offset.x, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Box Centre Offset - Y")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_centre_offset.y, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Box Centre Offset - Z")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_centre_offset.z, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Box Size - X")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_size.x, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Box Size - Y")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_size.y, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Box Size - Z")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_size.z, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Life Minimum")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_life_min_max.x, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Life Maximum")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_life_min_max.y, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Velocity Minimum - X")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_min.x, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Velocity Minimum - Y")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_min.y, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Velocity Minimum - Z")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_min.z, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Velocity Maximum - X")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_max.x, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Velocity Maximum - Y")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_max.y, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Velocity Maximum - Z")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_max.z, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Size Minimum - X")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_size_min_max.x, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Size Minimum - Y")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_size_min_max.y, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Size Maximum - X")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_size_min_max.z, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Size Maximum - Y")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_size_min_max.w, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Fade In")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_fade_in_out.x, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Fade Out")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_fade_in_out.y, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Fade Near")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_fade_near_far.x, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Fade Far")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_fade_near_far.y, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Edge Softness")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_edge_softness, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Particle Color Percentage")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_particle_color_percentage, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Background Distortion Visibility Percentage")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_background_distortion_visibility_percentage, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Background Distortion Alpha Booster")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_background_distortion_alpha_booster, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Background Distortion Amount")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_background_distortion_amount, "%.2f", 0.01f).set_scroll_speed(10));

        add_option(number_option<float>(SCROLL, "Local Lights Multiplier")
            .add_number(m_vars.m_shaders[m_vars.m_scroll].m_drop->m_local_lights_multiplier, "%.2f", 0.01f).set_scroll_speed(10));
    }
}

void weather_fx_menu::feature_update() {}

weather_fx_menu* g_instance;
weather_fx_menu* weather_fx_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new weather_fx_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}