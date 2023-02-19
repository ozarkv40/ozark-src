#pragma once
#include "menu/base/submenu.h"

class vehicle_modifiers_handling_flying_menu : public menu::submenu::submenu {
public:
	static vehicle_modifiers_handling_flying_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_modifiers_handling_flying_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::modifiers::handling::flying::vars {
	struct ThrustRestore {
		float m_thrust;
		float m_thrust_fall_off;
		float m_thrust_vectoring;
	};

	struct MovementRestore {
		float m_side_slip_mult;
		float m_yaw_mult;
		float m_yaw_stabilise;
		float m_roll_mult;
		float m_roll_stabilise;
		float m_pitch_mult;
		float m_pitch_stabilise;
		float m_form_lift_mult;
		float m_attack_lift_mult;
		float m_attack_dive_mult;
		float m_engine_off_glide_multi;
	};

	struct ResistanceRestore {
		float m_wind_mult;
		float m_move_res;
		math::vector3_<float> m_vec_turn_resistance;
		math::vector3_<float> m_vec_speed_resistance;
	};

	struct TurbulenceRestore {
		float m_turublence_magnitude_max;
		float m_turublence_force_multi;
		float m_turublence_roll_torque_multi;
		float m_turublence_pitch_torque_multi;
	};

	struct GearRestore {
		float m_gear_down_drag_v;
		float m_gear_down_lift_mult;
	};

	struct GroundRestore {
		float m_on_ground_yaw_boost_speed_peak;
		float m_on_ground_yaw_boost_speed_cap;
	};

	struct MiscRestore {
		float m_body_damage_control_effect_mult;
		float m_input_sensitivity_for_difficulty;
	};

	struct variables {
		int m_type;

		std::unordered_map<uint32_t, ThrustRestore> m_ThrustRestore;
		std::unordered_map<uint32_t, MovementRestore> m_MovementRestore;
		std::unordered_map<uint32_t, ResistanceRestore> m_ResistanceRestore;
		std::unordered_map<uint32_t, TurbulenceRestore> m_TurbulenceRestore;
		std::unordered_map<uint32_t, GearRestore> m_GearRestore;
		std::unordered_map<uint32_t, GroundRestore> m_GroundRestore;
		std::unordered_map<uint32_t, MiscRestore> m_MiscRestore;
	};

	void cache_thrust(uint32_t model);
	void cache_movement(uint32_t model);
	void cache_resistance(uint32_t model);
	void cache_turbulence(uint32_t model);
	void cache_gear(uint32_t model);
	void cache_ground(uint32_t model);
	void cache_misc(uint32_t model);
	extern variables m_vars;
}