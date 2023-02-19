#include "on_screen_ped.h"
#include "rage/invoker/natives.h"
#include "util/caller.h"

namespace menu::screen::ped {
    struct scene_preset {
        struct scene_preset_element {
            char _0x0000[24];
            math::vector4<float> m_position;
            math::vector4<float> m_position_43;
            math::vector4<float> m_rotation_xyz;
            math::vector4<float> m_bg_rect_xywh;
            math::vector4<float> m_bg_rect_xywh_43;
            uint32_t m_bg_rect_color;
            uint32_t m_blend_color;
            bool m_enabled;
            char _0x0071[15];
        };

        uint32_t m_name;
        char _0x0004[4];
        scene_preset_element m_elements[5];
        char _0x0288[8];
        int32_t m_element_count;
        char _0x0294[12];

        void set_element_rot(uint32_t element, math::vector3<float> rot) {
            if (element >= 0 && element < 5) {
                m_elements[element].m_rotation_xyz.x = rot.x;
                m_elements[element].m_rotation_xyz.y = rot.y;
                m_elements[element].m_rotation_xyz.z = rot.z;
            }
        }

        void set_element_pos(uint32_t element, math::vector2<float> xy, math::vector2<float> wh) {
            if (element >= 0 && element < 5) {
                m_elements[element].m_bg_rect_xywh.z = wh.x; // make fullscreen
                m_elements[element].m_bg_rect_xywh.w = wh.y; // make fullscreen
                m_elements[element].m_bg_rect_xywh.x = xy.x; // convert and set pos
                m_elements[element].m_bg_rect_xywh.y = xy.y; // convert and set pos
                m_elements[element].m_bg_rect_xywh_43.z = wh.x; // make fullscreen
                m_elements[element].m_bg_rect_xywh_43.w = wh.y; // make fullscreen
                m_elements[element].m_bg_rect_xywh_43.x = xy.x; // convert and set pos
                m_elements[element].m_bg_rect_xywh_43.y = xy.y; // convert and set pos
                m_elements[element].m_bg_rect_color = 0x0;
            }
        }
    };

    scene_preset* get_scene_preset(__int64 a1, uint32_t* a2) {
        unsigned int v2; // er8
        __int64 v3; // r9
        __int64 v4; // r10
        __int64 v5; // rcx
        uint32_t v6; // edx
        unsigned int* i; // rax

        v2 = 0;
        v3 = 0;

        v4 = *(uint16_t*)(a1 + 0x810);
        if (!v4)
            return 0;

        v5 = *(uint64_t*)(a1 + 0x808);
        v6 = *a2;

        for (i = (uint32_t*)v5; *i != v6; i += 0xA8) {
            ++v3;
            ++v2;
            if (v3 >= v4)
                return 0;
        }

        return (scene_preset*)(v5 + 0x2A0 * v2);
    }

	void draw_on_screen_ped(rage::types::ped* ped, math::vector2<float> pos, math::vector2<float> scale, math::vector3_<float> position_offset) {
        uint32_t scene_hash = 0x390DCCF5;

        if (!native::is_pause_menu_active()) {
            if (native::ui3dscene_is_available()) {
                uint32_t element = 0;

                uintptr_t ui_3d_draw_manager = *(uint64_t*)(global::vars::g_ui_3d_draw_manager);
                if (ui_3d_draw_manager) {
                    *(uint8_t*)((uint64_t)ped + 0x1163) |= 0x40u;
                    *(uint32_t*)((uint64_t)ped + 0x114C) |= 0xC0u;

                    scene_preset* preset = get_scene_preset(ui_3d_draw_manager, &scene_hash);
                    if (preset) {
                        preset->m_elements[element].m_rotation_xyz.z = 0.0f;
                        preset->set_element_pos(element, pos, scale);
                    }

                    if (caller::call<bool>(global::vars::g_push_scene_preset_to_manager, ui_3d_draw_manager, &scene_hash)) { // push_scene_preset_to_manager
                        if (caller::call<bool>(global::vars::g_add_element_to_scene, ui_3d_draw_manager, &scene_hash, element, ped, position_offset, 1.0f)) { // add_element_to_scene
                            caller::call<bool>(global::vars::g_set_scene_element_lighting, ui_3d_draw_manager, &scene_hash, element, 1.0f); // set_scene_element_lighting
                        }
                    }
                }
            }
        }
	}
}