#pragma once
#include "menu/base/submenu.h"

class vehicle_modifiers_handling_boat_menu : public menu::submenu::submenu {
public:
	static vehicle_modifiers_handling_boat_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_modifiers_handling_boat_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::modifiers::handling::boat::vars {
	struct physical_restore {
		float m_box_front_mult;
		float m_box_rear_mult;
		float m_box_side_mult;
		float m_sample_top;
		float m_sample_bottom;
	};

	struct aquaplane_restore {
		float m_aquaplane_force;
		float m_aquaplane_push_water_mult;
		float m_aquaplane_push_water_cap;
		float m_aquaplane_push_water_apply;
		float m_keel_sphere_size;
		float m_prop_radius;
		float m_impeller_offset;
		float m_impeller_force_mult;
		float m_prow_raise_mult;
	};

	struct rudder_restore {
		float m_rudder_force;
		float m_rudder_offset_submerge;
		float m_rudder_offset_force;
		float m_rudder_offset_force_z_mult;
	};

	struct resistance_restore {
		float m_drag_coefficient;
		math::vector3_<float> m_vec_move_resistance;
		math::vector3_<float> m_vec_turn_resistance;
	};

	struct misc_restore {
		float m_wave_audio_mult;
		float m_look_lr_cam_height;
		float m_low_lod_ang_offset;
		float m_low_lod_draught_offset;
		float m_dinghy_sphere_buoy_const;
	};

	struct variables {
		int m_type;

		std::unordered_map<uint32_t, physical_restore> m_physical_restore;
		std::unordered_map<uint32_t, aquaplane_restore> m_aquaplane_restore;
		std::unordered_map<uint32_t, rudder_restore> m_rudder_restore;
		std::unordered_map<uint32_t, resistance_restore> m_resistance_restore;
		std::unordered_map<uint32_t, misc_restore> m_misc_restore;
	};

	void cache_physical(uint32_t model);
	void cache_aquaplane(uint32_t model);
	void cache_rudder(uint32_t model);
	void cache_resistance(uint32_t model);
	void cache_misc(uint32_t model);
	extern variables m_vars;
}