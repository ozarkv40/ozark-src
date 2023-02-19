#pragma once
#include "stdafx.h"
#include "util/math.h"
#include "network_types.h"
#include <functional>

namespace rage::types {
    struct ped;
    struct ammo_info;
    struct aiming_info;
    struct weapon_info;
    struct base_model_info;
    struct vehicle_model_info;
    struct replay_interface_camera;
    struct replay_interface_veh;
    struct replay_interface_ped;
    struct replay_interface_pickup;
    struct replay_interface_object;

    struct ped_model_info {};
    struct ped_draw_handler {};
    struct ped_inventory {};

    struct memory_heap_pt {
        virtual ~memory_heap_pt();
        virtual void _0x1();
        virtual void _0x2();
        virtual void _0x3();
        virtual void _0x4();
        virtual void _0x5();
        virtual void _0x6();
        virtual void _0x7();
        virtual void _0x8();
        virtual void _0x9();
        virtual uint64_t allocate(uint32_t size);
    };

#pragma pack(push)
#pragma pack(1)
    struct marker_table {
        char _0x0000[0x70];
        bool m_in_use;
        char _0x0071[0x5F];
    };
#pragma pack(pop)

    struct store_entry {
        uint32_t m_handle;
        uint32_t m_flag;
    };

    struct store_module {
        char _0x0000[0x8];
        uint32_t m_base_index;
        char _0x000C[0x2C];
        guid_pool m_pool;
    };

    struct store_module_manager {};

    struct store_manager {
        store_entry* m_entries;
        char _0x0008[0x1B0];
        store_module_manager m_module;
    };

    struct xml_node {
        const char* m_name;
        char _0x0008[0x20];
        xml_node* m_next;
    };

    struct waypoint_data {
        math::vector4<float>* m_points;
        char _0x0008[0x3C];
        uint32_t m_count;
    };

    struct grc_texture_dx11 { // grcTexture
        char _0x0000[0x28];
        char* m_name;
        char _0x0030[0x8];
        void* m_texture; // ID3D11Resource
        char _0x0040[0x10];
        uint16_t m_width;
        uint16_t m_height;
        uint16_t m_depth;
        char _0x0056[0xA];
        grc_texture_dx11* m_previous;
        grc_texture_dx11* m_next;
        char _0x0070[0x8];
        void* m_shader; // ID3D11ShaderResourceView
        char _0x0080[0x20];
    };

    struct dictionary { // 0x40-
        char _0x0000[0x28];
        short m_count;
        char _0x002A[0x6];
        grc_texture_dx11** m_items;
    };

    struct dictionary_pool {
        dictionary* m_pool;
        char _0x0008[0x4];
        uint32_t m_dictionary_hash;
        char _0x0010[0x8];
    };

    struct texture_store {
        char _0x0000[0x38];
        dictionary_pool* m_pool;
        uint8_t* m_mask;
        uint32_t m_count;
        uint32_t m_size;
    };

    struct ui_element_vector {
        int m_index;
        char _0x0004[0xC];
        math::vector4<float> m_value;
    };

    struct ui_element_vector_constant {
        math::vector4<float> m_value;
        char _0x0004[0xC];
        int m_index;
    };

    struct ui_index {
        int m_index;
    };

    struct ui_element_integer {
        ui_index m_index;
        int m_value;
    };

    struct ui_element_shader {
        uint64_t m_raw_element;
        grc_texture_dx11* m_shader;
    };

    struct ui_visual_settings {
        char _0x0000[0x2874];
        float m_rim_light;
        float m_global_environment_reflection;
        float m_gamma;
        float m_mid_blur;
        float m_far_blur;
        float m_sky_multiplier;
        float m_desaturation;
    };

    struct ui_weather {
        char _0x0000[0x10];
        ui_element_vector m_azimuth_east_color;
        char _0x0030[0x10];
        ui_element_vector m_azimuth_west_color;
        char _0x0060[0x10];
        ui_element_vector m_azimuth_transition_color;
        char _0x0090[0x4];
        ui_element_integer m_azimuth_transition_position;
        char _0x009c[0x4];
        ui_element_vector m_zenith_color;
        char _0x00c0[0x10];
        ui_element_vector m_zenith_transition_color;
        char _0x00f0[0x4];
        ui_element_vector_constant m_zenith_constants;
        char _0x0114[0x1C];
        ui_element_vector m_sky_plane_color;
        char _0x0150[0x10];
        ui_index m_sky_plane_params;
        char _0x0164[0x34];
        ui_index m_sun_direction;
        ui_index m_sun_position;
        char _0x01a0[0x10];
        ui_element_vector m_sun_color;
        ui_element_vector m_sun_color_hdr;
        char _0x01f0[0x10];
        ui_element_vector m_sun_disc_color_hdr;
        char _0x0220[0x20];
        ui_element_vector m_sun_constants;
        ui_element_shader m_high_detail_noise;
        ui_element_vector_constant m_cloud_constant1;
        char _0x0290[0x10];
        ui_element_vector_constant m_cloud_constant2;
        char _0x02c0[0x10];
        ui_element_vector_constant m_cloud_constant3;
        char _0x02f0[0x10];
        ui_element_vector_constant m_cloud_detail_constants;
        char _0x0320[0x30];
        ui_element_vector m_cloud_base_minus_mid_colour;
        ui_element_vector m_cloud_mid_color;
        ui_element_vector m_cloud_shadow_minus_base_colour_times_shadow_strength;
        ui_element_vector_constant m_small_cloud_constants;
        char _0x03d0[0x20];
        ui_element_vector m_small_cloud_color_hdr;
        char _0x0410[0x10];
        ui_index m_cloudgen_frequency;
        char _0x0424[0x1C];
        ui_element_vector m_noise_phase;
        char _0x0460[0x20];
        ui_index m_speed_constants;
        char _0x0484[0x1C];
        ui_element_integer m_horizon_level;
        char _0x04a8[0x10];
        ui_element_shader m_dither;
        char _0x04c8[0x18];
        ui_element_shader m_star_field;
        ui_element_integer m_starfield_intensity;
        ui_element_shader m_moon;
        char _0x0508[0x28];
        ui_element_integer m_moon_intensity;
        char _0x0538[0x8];
        ui_element_vector m_moon_color;
        char _0x0560[0x10];
        ui_index m_lunar_cycle;
        char _0x0574[0x1C];
        ui_index m_moon_direction;
        ui_index m_moon_position;
        char _0x0598[0x18];
        ui_element_integer m_noise_frequency;
        ui_element_integer m_noise_scale;
        ui_element_integer m_noise_threshold;
        ui_element_integer m_noise_softness;
        ui_element_integer m_noise_density_offset;
        ui_element_shader m_noise;

        void set_sky(bool enabled) {
            *(bool*)((uint64_t)this - 0x60) = enabled;
        }
    };

    struct ui_puddle_ripple {
        char _0x0000[0xF50];
        float m_ripple_max_size;
        float m_ripple_min_size;
        float m_ripple_min_duration;
        float m_ripple_max_duration;
        float m_ripple_speed;
        float m_ripple_drop_factor;
        float m_ripple_wind_strength;
        char _0x0f6c[0x4];
        float m_ripple_strength;
        char _0x0f74[0x14];
        float m_ripple_player_map_size;
        float m_ripple_player_speed;
        char _0x0f90[0x4];
        float m_ripple_wind_damping;
    };

    struct ui_puddle {
        char _0x0000[0x70];
        float m_scale;
        float m_range;
        float m_depth;
        float m_depth_test;
        float m_reflectivity;
        char _0x0084[0x2C];
        ui_puddle_ripple* m_ripples;
    };

    struct ui_element_color_struct {
        float m_intensity;
        float m_radius;
        float m_falloff_exp;
        float m_inner_cone_angle;
        float m_outer_cone_angle;
        float m_corona_hdr;
        float m_corona_size;
        float m_shadow_blur;
        float m_capsule_length;
        char _0x0024[0xC];
        math::vector3_<float> m_color;
        char _0x003C[0x4];
        uint32_t m_flags; // 0x200 = using sun, 0x140 = using dynamic shadows
    };

    struct vehicle_stream_render {
        char _0x0000[0x8];
        float m_tire_size;
        char _0x000C[0xB94];
        float m_tire_width;
    };

    struct custom_shader_effect_vehicle {
        char _0x0000[0xE0];
        grc_texture_dx11* m_unk_texture;
        char _0x00E8[0x38];
        grc_texture_dx11* m_plate_texture;
        grc_texture_dx11* m_plate_texture2;
    };

    struct vehicle_draw_handler {
        char _0x0000[0x20];
        custom_shader_effect_vehicle* m_damage_shader_effect;
        char _0x0028[0x8];
        custom_shader_effect_vehicle* m_shader_effect;
        char _0x0038[0x338]; //0x0000
        vehicle_stream_render* m_vehicle_stream_render; //0x0370
        char _0x0378[0x8B0]; //0x0378
    };

    struct flying_handling_data {
        char _0x0000[0x8]; //0x0000
        float m_thrust; //0x0008
        float m_thrust_fall_off; //0x000C
        float m_thrust_vectoring; //0x0010
        char _0x0014[0x8]; //0x0014
        float m_yaw_mult; //0x001C
        float m_yaw_stabilise; //0x0020
        float m_side_slip_mult; //0x0024
        char _0x0028[0x4]; //0x0028
        float m_roll_mult; //0x002C
        float m_roll_stabilise; //0x0030
        float N000026D3; //0x0034
        float m_pitch_mult; //0x0038
        float m_pitch_stabilise; //0x003C
        char _0x0040[0x4]; //0x0040
        float m_form_lift_mult; //0x0044
        float m_attack_lift_mult; //0x0048
        float m_attack_dive_mult; //0x004C
        float m_gear_down_drag_v; //0x0050
        float m_gear_down_lift_mult; //0x0054
        float m_wind_mult; //0x0058
        float m_move_res; //0x005C
        math::vector3_<float> m_vec_turn_resistance; //0x0060
        char _0x006C[0x4]; //0x006C
        math::vector3_<float> m_vec_speed_resistance; //0x0070
        char _0x007C[0x4]; //0x007C
        float m_gear_door_front_open; //0x0080
        float m_gear_door_rear_open; //0x0084
        float m_gear_door_rear_open2; //0x0088
        float m_gear_door_rear_m_open; //0x008C
        float m_turublence_magnitude_max; //0x0090
        float m_turublence_force_multi; //0x0094
        float m_turublence_roll_torque_multi; //0x0098
        float m_turublence_pitch_torque_multi; //0x009C
        float m_body_damage_control_effect_mult; //0x00A0
        float m_input_sensitivity_for_difficulty; //0x00A4
        float m_on_ground_yaw_boost_speed_peak; //0x00A8
        float m_on_ground_yaw_boost_speed_cap; //0x00AC
        float m_engine_off_glide_multi; //0x00B0
    }; //Size=0x00B4

    struct boat_handling_data {
        char _0x0000[0x8]; //0x0000
        float m_box_front_mult; //0x0008
        float m_box_rear_mult; //0x000C
        float m_box_side_mult; //0x0010
        float m_sample_top; //0x0014
        float m_sample_bottom; //0x0018
        float N000028C4; //0x001C
        float m_aquaplane_force; //0x0020
        float m_aquaplane_push_water_mult; //0x0024
        float m_aquaplane_push_water_cap; //0x0028
        float m_aquaplane_push_water_apply; //0x002C
        float m_rudder_force; //0x0030
        float m_rudder_offset_submerge; //0x0034
        float m_rudder_offset_force; //0x0038
        float m_rudder_offset_force_z_mult; //0x003C
        float m_wave_audio_mult; //0x0040
        float N000028CE; //0x0044
        float N0000283E; //0x0048
        float N000028D0; //0x004C
        math::vector3_<float> m_vec_move_resistance; //0x0050
        float N000028D4; //0x005C
        math::vector3_<float> m_vec_turn_resistance; //0x0060
        float N000028D8; //0x006C
        float m_look_lr_cam_height; //0x0070
        float m_drag_coefficient; //0x0074
        float m_keel_sphere_size; //0x0078
        float m_prop_radius; //0x007C
        float m_low_lod_ang_offset; //0x0080
        float m_low_lod_draught_offset; //0x0084
        float m_impeller_offset; //0x0088
        float m_impeller_force_mult; //0x008C
        float m_dinghy_sphere_buoy_const; //0x0090
        float m_prow_raise_mult; //0x0094
    }; //Size=0x0098

    struct bike_handling_data {
        char _0x0000[0x8]; //0x0000
        float m_lean_fwd_com_mult; //0x0008
        float m_lean_fwd_force_mult; //0x000C
        float m_lean_bak_com_mult; //0x0010
        float m_lean_bak_force_mult; //0x0014
        float m_max_bank_angle; //0x0018
        char _0x001C[0x4]; //0x001C
        float m_full_anim_angle; //0x0020
        float m_des_lean_return_frac; //0x0024
        float m_stick_lean_mult; //0x0028
        float m_braking_stability_mult; //0x002C
        float m_in_air_steer_mult; //0x0030
        float m_wheelie_balance_point; //0x0034
        float m_stoppie_balance_point; //0x0038
        float m_wheelie_steer_mult; //0x003C
        float m_rear_balance_mult; //0x0040
        float m_front_balance_mult; //0x0044
        float m_bike_ground_side_friction_mult; //0x0048
        float m_bike_wheel_ground_side_friction_mult; //0x004C
        float m_bike_on_stand_lean_angle; //0x0050 c
        float m_bike_on_stand_steer_angle; //0x0054
        float m_jump_force; //0x0058
    }; //Size=0x005C

    typedef union {
        flying_handling_data m_flying_handling_data;
        bike_handling_data m_bike_handling_data;
        boat_handling_data m_boat_handling_data;
    } sub_handling_data_type;

    struct SubHandlingData {
        sub_handling_data_type* m_sub_handling_data; //0x0000
        void* m_vehicle_weapon_handling_data; //0x0008
        char _0x0010[0x8]; //0x0010
    };

    struct handling_data {
        char _0x0000[0x8]; //0x0000
        int m_hash; //0x0008
        float m_mass; //0x000C
        char _0x0010[0x4]; //0x0010
        float m_downforce_modifier; //0x0014
        char _0x0018[0x8]; //0x0018
        math::vector3_<float> m_vec_centre_of_mass_offset; //0x0020
        char _0x002C[0x4]; //0x002C
        math::vector3_<float> m_vec_inertia_multiplier; //0x0030
        char _0x003C[0x4]; //0x003C
        float m_percent_submerged; //0x0040
        char _0x0044[0x8]; //0x0044
        float m_drive_bias_front; //0x004C
        unsigned char m_initial_drive_gears; //0x0050
        char _0x0051[0x3]; //0x0051
        float m_drive_inertia; //0x0054
        float m_clutch_change_rate_scale_up_shift; //0x0058
        float m_clutch_change_rate_scale_down_shift; //0x005C
        float m_initial_drive_force; //0x0060
        char _0x0064[0x8]; //0x0064
        float m_brake_force; //0x006C
        char _0x0070[0x4]; //0x0070
        float m_initial_drive_max_flat_vel; //0x0074
        char _0x0078[0x4]; //0x0078
        float m_hand_brake_force; //0x007C
        float m_steering_lock; //0x0080
        char _0x0084[0x4]; //0x0084
        float m_traction_curve_max; //0x0088
        char _0x008C[0x14]; //0x008C
        float m_traction_spring_delta_max; //0x00A0
        char _0x00A4[0x4]; //0x00A4
        float m_low_speed_traction_loss_mult; //0x00A8
        float m_camber_stiffness; //0x00AC
        char _0x00B0[0x8]; //0x00B0
        float m_traction_loss_mult; //0x00B8
        float m_suspension_force; //0x00BC
        float m_suspension_comp_damp; //0x00C0
        float m_suspension_rebound_damp; //0x00C4
        float m_suspension_upper_limit; //0x00C8
        float m_suspension_lower_limit; //0x00CC
        char _0x00D0[0xC]; //0x00D0
        float m_anti_roll_bar_force; //0x00DC
        char _0x00E0[0x8]; //0x00E0
        float m_roll_centre_height_front; //0x00E8
        float m_roll_centre_height_rear; //0x00EC
        float m_collision_damage_mult; //0x00F0
        float m_weapon_damage_mult; //0x00F4
        float m_deformation_damage_mult; //0x00F8
        float m_engine_damage_mult; //0x00FC
        float m_petrol_tank_volume; //0x0100
        float m_oil_volume; //0x0104
        char _0x0108[0x4]; //0x0108
        math::vector3_<float> m_seat_offset; //0x010C
        int m_monetary_value; //0x0118
        char _0x011C[0x30]; //0x011C
        unsigned char N00002337; //0x014C
        unsigned char N0000239F; //0x014D
        char _0x014E[0x2]; //0x014E
        void* m_a_i_handling_info; //0x0150
        SubHandlingData* m_sub_handling_data; //0x0158
    }; //Size=0x0160

    struct vehicle {
        char _0x0000[0x20]; //0x0000
        vehicle_model_info* m_model_info;
        char _0x0028[0x8];
        void* m_frag_inst; //0x0030
        char _0x0038[0x10]; //0x0038
        vehicle_draw_handler* m_vehicle_draw_handler; //0x0048
        char _0x0050[0x230]; //0x0050
        float m_health; //0x0280
        char _0x0284[0x1C]; //0x0284
        float m_max_health; //0x02A0
        char _0x02A4[0x77]; //0x02A4
        unsigned char m_rocket_state; //0x031B
        char _0x031C[0x1]; //0x031C
        unsigned char m_rocket_energy; //0x031D
        char _0x031E[0x5FA + 0x20]; //0x031E
        handling_data* m_handling_data; //0x0918 - NOW 0x938
        char _0x0920[0x48]; //0x0920
        vehicle* m_vehicle; //0x0968
        char _0x0970[0x8]; //0x0970
        void* m_vehicle_deformation; //0x0978
        char _0x0980[0x101C]; //0x0980
        float m_visual_suspension; //0x199C
        char _0x19A0[0x240]; //0x19A0

        math::matrix<float>* get_matrix() {
            return (math::matrix<float>*)((uint64_t)this + 0x60);
        }

        rage::network::net_object* get_net_obj() {
            return *(rage::network::net_object**)((uint64_t)this + 0xD0);
        }
    };

    struct object {
        char _0x0000[0x20];
        base_model_info* m_model_info;
        char _0x0028[0x20];
        void* m_object_draw_handler;
        char _0x0050[0x10];
        math::matrix<float> m_matrix;

        // m_up[3] = width
        // m_forward[3] = height
    };

    struct ped_weapon_manager {
        char _0x0000[0x20]; //0x0000
        rage::types::weapon_info* m_weapon_info; //0x0020
        char _0x0028[0x178]; //0x0028
        math::vector3_<float> m_last_aimed_position; //0x01A0
        char _0x01AC[0x4]; //0x01AC
        math::vector3_<float> m_impact_position; //0x01B0
        char _0x01BC[0x2E4]; //0x01BC

        weapon_info* get_vehicle_weapon() {
            return *(weapon_info**)(this + 0x70);
        }
    };

    struct navigation {
        char _0x0000[0x20];
        float m_last_heading;
        float m_heading;
        char _0x0028[0x8];
        math::vector3_<float> m_rotation;
        char _0x003C[0x14];
        math::vector3_<float> m_position;
    };

    struct ped {
        char _0x0000[0x10];
        uint64_t m_decor_info;
        char _0x0018[0x8];
        ped_model_info* m_ped_model_info;
        char _0x0028[0x8];
        navigation* m_navigation;
        char _0x0038[0x10];
        ped_draw_handler* m_ped_draw_handler; // 0x48
        char _0x0050[0x10];
        math::matrix<float> m_transform;
        char _0x00A0[0x1E0];
        float m_health;
        char _0x0284[0x1C];
        float m_max_health;
        char _0x02A4[0xA8C]; // 0xA8C
        vehicle* m_vehicle;
        char _0x0D30[0x390];
        rage::network::player_info* m_player_info; // 0x10C8
        ped_inventory* m_ped_inventory;
        ped_weapon_manager* m_ped_weapon_manager;

        rage::network::net_object* get_net_obj() {
            return *(rage::network::net_object**)((uint64_t)this + 0xD0);
        }

        void set_flag(uint32_t flag) {
            *(uint32_t*)((uint64_t)this + 0x141C) = flag;
        }
    };

    struct ped_factory {
        char _0x0000[8];
        ped* m_local_ped;
    };

    struct ammo_info {
        char _0x0008[0x10]; //0x0008
        uint32_t m_ammo_hash; //0x0010
        uint32_t m_name; //0x0014
        uint32_t m_model; //0x0018
        uint32_t m_slot; //0x001C
        unsigned char m_ammo_max; //0x0020
        char _0x0021[0x3]; //0x0021
        unsigned char m_ammo_max50; //0x0024
        char _0x0025[0x3]; //0x0025
        unsigned char m_ammo_max100; //0x0028
        char _0x0029[0x3]; //0x0029
        unsigned char m_ammo_max_m_p; //0x002C
        char _0x002D[0x3]; //0x002D
        unsigned char m_ammo_max50_m_p; //0x0030
        char _0x0031[0x3]; //0x0031
        unsigned char m_ammo_max100_m_p; //0x0034
        char _0x0035[0xB]; //0x0035
        float m_damage; //0x0040
        float m_life_time; //0x0044
        float m_from_vehicle_life_time; //0x0048
        float m_life_time_after_impact; //0x004C
        float m_life_time_after_explosion; //0x0050
        float m_explosion_time; //0x0054
        float m_launch_speed; //0x0058
        float m_separation_time; //0x005C
        float m_time_to_reach_target; //0x0060
        float m_damping; //0x0064
        float m_gravity_factor; //0x0068
        float m_ricochet_tolerance; //0x006C
        float m_ped_ricochet_tolerance; //0x0070
        float m_vehicle_ricochet_tolerance; //0x0074
        float m_friction_multiplier; //0x0078
        char _0x007C[0x64]; //0x007C
        math::vector3_<float> m_light_color; //0x00E0
        char _0x00EC[0x4]; //0x00EC
        float m_light_intensity; //0x00F0
        float m_light_range; //0x00F4
        float m_light_falloff_exp; //0x00F8
        float m_light_frequency; //0x00FC
        float m_light_power; //0x0100
        float m_corona_size; //0x0104
        float m_corona_intensity; //0x0108
        float m_corona_z_bias; //0x010C
        char _0x0110[0x40]; //0x0110
        unsigned char m_ammo_max_m_p_bonus; //0x0150
        char _0x0151[0x7]; //0x0151
    };

    struct aiming_info {
        int m_hash; //0x0000
        float m_heading_limit; //0x0004
        float m_sweep_pitch_min; //0x0008
        float m_sweep_pitch_max; //0x000C
    };

    struct weapon_info {
        uint64_t m_vmt; //0x0000
        char _0x0008[8]; //0x0008
        uint32_t m_name_hash; //0x0010
        uint32_t m_model_hash; //0x0014
        uint32_t m_audio; //0x0018
        uint32_t m_slot; //0x001C
        int m_damage_type; //0x0020
        uint32_t m_explosion_default; //0x0024
        uint32_t m_explosion_hit_car; //0x0028
        uint32_t m_explosion_hit_truck; //0x002C
        uint32_t m_explosion_hit_bike; //0x0030
        uint32_t m_explosion_hit_boat; //0x0034
        uint32_t m_explosion_hit_plane; //0x0038
        char _0x003C[24]; //0x003C
        int m_fire_type; //0x0054
        int m_wheel_slot; //0x0058
        uint32_t m_group_hash; //0x005C
        rage::types::ammo_info* m_ammo_info; //0x0060
        rage::types::aiming_info* m_aiming_info; //0x0068
        uint32_t m_clip_size; //0x0070
        float m_accuracy_spread; //0x0074
        float m_accurate_mode_accuracy_modifier; //0x0078
        float m_run_and_gun_accuracy_modifier; //0x007C
        float m_run_and_gun_accuracy_max_modifier; //0x0080
        float m_recoil_accuracy_max; //0x0084
        float m_recoil_error_time; //0x0088
        float m_recoil_recovery_rate; //0x008C
        float m_recoil_accuracy_to_allow_head_shot_a_i; //0x0090
        float m_min_head_shot_distance_a_i; //0x0094
        float m_max_head_shot_distance_a_i; //0x0098
        float m_head_shot_damage_modifier_a_i; //0x009C
        float m_recoil_accuracy_to_allow_head_shot_player; //0x00A0
        float m_min_head_shot_distance_player; //0x00A4
        float m_max_head_shot_distance_player; //0x00A8
        float m_head_shot_damage_modifier_player; //0x00AC
        float m_damage; //0x00B0
        float m_damage_time; //0x00B4
        float m_damage_time_in_vehicle; //0x00B8
        float m_damage_time_in_vehicle_head_shot; //0x00BC
        char _0x00C0[8]; //0x00C0
        float m_hit_limbs_damage_modifier; //0x00C8
        float m_network_hit_limbs_damage_modifier; //0x00CC
        float m_lightly_armoured_damage_modifier; //0x00D0
        float m_vehicle_damage_modifier; //0x00D4
        float m_force; //0x00D8
        float m_force_hit_ped; //0x00DC
        float m_force_hit_vehicle; //0x00E0
        float m_force_hit_flying_heli; //0x00E4
        uint64_t m_override_forces; //0x00E8
        int16_t m_override_forces_count; //0x00F0
        int16_t m_override_forces_capacity; //0x00F2
        char _0x00F4[4]; //0x00F4
        float m_force_max_strength_mult; //0x00F8
        float m_force_falloff_range_start; //0x00FC
        float m_force_falloff_range_end; //0x0100
        float m_force_falloff_min; //0x0104
        float m_projectile_force; //0x0108
        float m_frag_impulse; //0x010C
        float m_penetration; //0x0110
        float m_vertical_launch_adjustment; //0x0114
        float m_drop_forward_velocity; //0x0118
        float m_speed; //0x011C
        int m_bullets_in_batch; //0x0120
        float m_batch_spread; //0x0124
        float m_reload_time_m_p; //0x0128
        float m_reload_time_s_p; //0x012C
        float m_vehicle_reload_time; //0x0130
        float m_anim_reload_rate; //0x0134
        int m_bullets_per_anim_loop; //0x0138
        float m_time_between_shots; //0x013C
        float m_time_left_between_shots_where_should_fire_is_cached; //0x0140
        float m_spin_up_time; //0x0144
        float m_spin_time; //0x0148
        float m_spin_down_time; //0x014C
        float m_alternate_wait_time; //0x0150
        float m_bullet_bending_near_radius; //0x0154
        float m_bullet_bending_far_radius; //0x0158
        float m_bullet_bending_zoomed_radius; //0x015C
        float m_first_person_bullet_bending_near_radius; //0x0160
        float m_first_person_bullet_bending_far_radius; //0x0164
        float m_first_person_bullet_bending_zoomed_radius; //0x0168
        char _0x016C[4]; //0x016C
        int m_effect_group; //0x0170
        uint32_t m_flash_fx; //0x0174
        uint32_t m_flash_fx_alt; //0x0178
        uint32_t m_flash_fx_fp; //0x017C
        uint32_t m_flash_fx_alt_fp; //0x0180
        uint32_t m_muzzle_smoke_fx; //0x0184
        uint32_t m_muzzle_smoke_fx_fp; //0x0188
        float m_muzzle_smoke_fx_min_level; //0x018C
        float m_muzzle_smoke_fx_inc_per_shot; //0x0190
        float m_muzzle_smoke_fx_dec_per_sec; //0x0194
        char _0x0198[28]; //0x0198
        uint32_t m_shell_fx; //0x01B4
        uint32_t m_shell_fx_fp; //0x01B8
        uint32_t m_tracer_fx; //0x01BC
        uint32_t m_ped_damage_hash; //0x01C0
        float m_tracer_fx_chance_sp; //0x01C4
        float m_tracer_fx_chance_mp; //0x01C8
        char _0x01CC[4]; //0x01CC
        float m_flash_fx_chance_sp; //0x01D0
        float m_flash_fx_chance_mp; //0x01D4
        float m_flash_fx_alt_chance; //0x01D8
        float m_flash_fx_scale; //0x01DC
        char _0x01E0[76]; //0x01E0
        float m_ground_disturb_fx_dist; //0x022C
        char _0x0230[32]; //0x0230
        int m_initial_rumble_duration; //0x0250
        float m_initial_rumble_intensity; //0x0254
        float m_initial_rumble_intensity_trigger; //0x0258
        int m_rumble_duration; //0x025C
        float m_rumble_intensity; //0x0260
        float m_rumble_intensity_trigger; //0x0264
        float m_rumble_damage_intensity; //0x0268
        int m_initial_rumble_duration_fps; //0x026C
        float m_initial_rumble_intensity_fps; //0x0270
        int m_rumble_duration_fps; //0x0274
        float m_rumble_intensity_fps; //0x0278
        float m_network_player_damage_modifier; //0x027C
        float m_network_ped_damage_modifier; //0x0280
        float m_network_head_shot_player_damage_modifier; //0x0284
        float m_lock_on_range; //0x0288
        float weapon_range; //0x028C
        float m_ai_sound_range; //0x0290
        float m_ai_potential_blast_event_range; //0x0294
        float m_damage_fall_off_range_min; //0x0298
        float m_damage_fall_off_range_max; //0x029C
        char _0x02A0[8]; //0x02A0
        float m_damage_fall_off_modifier; //0x02A8
        char _0x02AC[4]; //0x02AC
        float m_damage_fall_off_modifier1; //0x02B0
        char _0x02B4[60]; //0x02B4
        int m_min_time_between_recoil_shakes; //0x02F0
        float m_recoil_shake_amptitude; //0x02F4
        float m_explosion_shake_amplitude; //0x02F8
        float m_camera_fov; //0x02FC
        char _0x0300[8]; //0x0300
        float m_first_person_scope_fov; //0x0308
        float m_first_person_scope_attachment_fov; //0x030C
        char _0x0310[736]; //0x0310
        char* m_label_text; //0x05F0
        char _0x05F8[872]; //0x05F8
    };

    struct weapon {
        char _0x0000[0x40];
        weapon_info* m_weapon_info;
    };

    struct explosion_data {
        const char* m_explosion_name;
        int m_unk1;
        int m_unk2;
        float m_damage_at_centre;
        float m_damage_at_edge;
        float m_network_player_modifier;
        float m_network_ped_modifier;
        float m_end_radius;
        float m_init_speed;
        float m_decay_factor;
        float m_force_factor;
        float m_ragdoll_force_modifier;
        float m_self_force_modifier;
        float m_directed_width;
        float m_directed_lifetime;
        float m_cam_shake;
        float m_cam_shake_roll_off_scaling;
        float m_shocking_event_visual_range_override;
        float m_shocking_event_audio_range_override;
        float m_frag_damage;
        bool m_minor_explosion;
        bool m_applies_continuous_damage;
        bool m_post_process_collisions_with_no_force;
        bool m_damage_vehicles;
        bool m_damage_objects;
        bool m_only_affects_live_peds;
        bool m_ignore_exploding_entity;
        bool m_no_occlusion;
        bool m_explode_attach_entity_when_finished;
        bool m_can_set_ped_on_fire;
        bool m_can_set_player_on_fire;
        bool m_suppress_crime;
        bool m_use_distance_damage_calc;
        bool m_prevent_water_explosion_vfx;
        bool m_ignore_ratio_check_for_fire;
        bool m_allow_underwater_explosion;
        int m_unk3;
        float m_unk4;
        float m_unk5;
        char m_unk6[12];
        int m_cam_shake_name_hash;
        int m_vfx_tag_name_hash;
        int m_unk_size;
    };

    struct explosion_fx {
        uint32_t m_name_hash;
        char Unk[0x20];
        float m_scale;
        char Unk2[0x38];
    };

    struct blip {
        char _0x0000[0x4];
        int m_handle;
        char _0x0008[0x8];
        math::vector3_<float> m_coords;
        char _0x001C[0x24];
        int m_sprite;
        char _0x0044[0x4];
        int m_color;
        int m_color2;
        math::vector2<float> m_scale;
        float m_rotation;

        bool is_visible() {
            return *(bool*)((uint64_t)this + 0x10);
        }
    };

    struct blip_list {
        blip* m_blips[1500];
    };

    struct ocean_wave_quad {
        math::vector2<short> m_min;
        math::vector2<short> m_max;
        short m_amplitude;
        math::vector2<uint8_t> m_direction;
    };

    struct ocean_calming_quad {
        math::vector2<short> m_min;
        math::vector2<short> m_max;
        float m_dampening;
    };

    struct ocean_quad {
        math::vector2<short> m_min;
        math::vector2<short> m_max;
        uint32_t m_alpha;
        char _0x000C[0x8];
        float m_height;
        char _0x0024[0x4];
    };

    struct ocean_quad_info {
        uint64_t m_quad_pool;
        short m_quad_count;
    };

    struct ocean_quads {
        ocean_quad_info* m_ocean;
        ocean_quad_info* m_wave;
        ocean_quad_info* m_calming;
    };

    struct water_tune {
        int m_water_color;
        float m_ripple_scale;
        float m_ocean_foam_scale;
        float m_specular_falloff;
        float m_fog_pierce_intensity;
        float m_refraction_blend;
        float m_refraction_exponent;
        float m_water_cycle_depth;
        float m_water_cycle_fade;
        float m_water_lightning_depth;
        float m_water_lightning_fade;
        float m_deep_water_mod_depth;
        float m_deep_water_mod_fade;
        float m_god_rays_lerp_start;
        float m_god_rays_lerp_end;
        float m_disturb_foam_scale;
        math::vector2<float> m_fog_min;
        math::vector2<float> m_fog_max;
    };

    struct base_model_info {
        char _0x0000[24];
        uint32_t m_model;
    };

    struct building {
        char _0x0000[32];
        base_model_info* m_model_info;
        uint8_t m_type; // 1
        char _0x0029[55];
        math::matrix<float> m_matrix;
        char _0x00A0[16];
        int m_lod;
    };

    struct vfx_liquid {
        float m_duration_foot;
        float m_duration_wheel_in;
        float m_life_foot;
        float m_life_wheel;
        char _0x0010[0x48];
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        char _0x005C[0x4];
    };

    struct vfx_wheel {
        float m_slip_min; //0x0004
        float m_slip_max; //0x0008
        float m_pressure_min; //0x000C
        float m_pressure_max; //0x0010
        int m_type1; //0x0014
        BOOL m_unk1; //0x0018
        int m_type2; //0x001c
        BOOL m_unk2; //0x0010
        int m_type3; //0x0024
        BOOL m_unk3; //0x0028
        int m_type4; //0x002c
        BOOL m_unk4; //0x0030
        uint8_t m_r; //0x0034
        uint8_t m_g; //0x0035
        uint8_t m_b; //0x0036
        char _0x0037[1]; //0x0037
        float m_friction_thresh_min; //0x0038
        float m_friction_thresh_max; //0x003C
        uint32_t m_friction_fx1; //0x0040
        uint32_t m_friction_fx2; //0x0044
        uint32_t m_friction_fx3; //0x0048
        float m_disp_thresh_min; //0x004C
        float m_disp_thresh_max; //0x0050
        uint32_t m_displacement_fx1; //0x0054
        uint32_t m_displacement_fx2; //0x0058
        uint32_t m_displacement_fx3; //0x005C
        uint32_t m_displacement_fx_lod; //0x0060
        float m_burn_friction_evo_min; //0x0064
        float m_burn_friction_evo_max; //0x0068
        float m_burn_temp_evo_min; //0x006C
        float m_burn_temp_evo_max; //0x0070
        uint32_t m_burnout_fx1; //0x0074
        uint32_t m_burnout_fx2; //0x0078
        uint32_t m_burnout_fx3; //0x007C
        bool m_lights_on; //0x0080
        uint8_t m_lights_col_min_r; //0x0081
        uint8_t m_lights_col_min_g; //0x0082
        uint8_t m_lights_col_min_b; //0x0083
        uint8_t m_lights_col_max_r; //0x0084
        uint8_t m_lights_col_max_g; //0x0085
        uint8_t m_lights_col_max_b; //0x0086
        char _0x0087[1]; //0x0087
        float m_lights_intensity_min; //0x0088
        float m_lights_intensity_max; //0x008C
        float m_lights_range_min; //0x0090
        float m_lights_range_max; //0x0094
        float m_lights_falloff_min; //0x0098
        float m_lights_falloff_max; //0x009C
    };

    struct vehicle_model_info {
        char _0x0000[0x298];
        char m_model_name[0xC];
        char m_manufacturer_name[0xC];
        uint16_t* m_mod_kits;
        uint16_t m_mod_kit_count;
    };

    template<typename T>
    struct replay_interface_list {
        T* m_entity;
        char _0x000C[0x8];
    };

    struct replay_interface {
        void* m_game;
        replay_interface_camera* m_camera;
        replay_interface_veh* m_veh;
        replay_interface_ped* m_ped;
        replay_interface_pickup* m_pickup;
        replay_interface_object* m_object;
    };

    struct replay_interface_camera {
        char _0x0000[256];
        replay_interface_list<void>* m_camera_list;
        int m_max;
        char _0x010C[4];
        int m_count;

        void for_each(std::function<void(Entity, void*)> callback);
    };

    struct replay_interface_veh {
        char _0x0000[384];
        replay_interface_list<vehicle>* m_veh_list;
        int m_max;
        char _0x018C[4];
        int m_count;

        void for_each(std::function<void(Entity, vehicle*)> callback);
    };

    struct replay_interface_ped {
        char _0x0000[256];
        replay_interface_list<ped>* m_ped_list;
        int m_max;
        char _0x010C[4];
        int m_count;

        void for_each(std::function<void(Entity, ped*)> callback);
    };

    struct replay_interface_pickup {
        char _0x0000[256];
        replay_interface_list<void>* m_pickup_list;
        int m_max;
        char _0x010C[4];
        int m_count;

        void for_each(std::function<void(Entity, void*)> callback);
    };

    struct replay_interface_object {
        char _0x0000[344];
        replay_interface_list<object>* m_object_list;
        int m_max;
        char _0x0164[4];
        int m_count;

        void for_each(std::function<void(Entity, object*)> callback);
    };

    struct drop_shader {
        uint32_t m_name_hash;
        char _1[4];
        float m_velocity;
        float m_gravity;
        char _2[16];
        math::vector4<float> m_box_centre_offset;
        math::vector4<float> m_box_size;
        math::vector4<float> m_life_min_max;
        math::vector4<float> m_velocity_min;
        math::vector4<float> m_velocity_max;
        char _3[32];
        grc_texture_dx11* m_texture_1;
        grc_texture_dx11* m_texture_2;
        math::vector4<float> m_texture_rows_cols_start_end;
        math::vector4<float> m_texture_anim_rate_scale_over_life_start_2_end_2;
        math::vector4<float> m_size_min_max;
        math::vector4<float> m_color;
        math::vector2<float> m_fade_in_out;
        math::vector2<float> m_fade_near_far;
        math::vector4<float> m_fade_grd_off_lo_hi;
        math::vector4<float> m_rot_speed_min_max;
        math::vector4<float> m_directional_z_offset_min_max;
        math::vector4<float> m_dir_vel_add_cam_speed_min_max_mult;
        float m_edge_softness;
        char _4[8];
        float m_particle_color_percentage;
        float m_background_distortion_visibility_percentage;
        float m_background_distortion_alpha_booster;
        float m_background_distortion_amount;
        uint32_t m_background_distortion_blur_level;
        float m_local_lights_multiplier;
        char _5[12];
    };
}