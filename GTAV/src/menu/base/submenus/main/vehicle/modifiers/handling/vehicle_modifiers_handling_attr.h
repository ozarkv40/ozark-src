#pragma once
#include "menu/base/submenu.h"

class vehicle_modifiers_handling_attr_menu : public menu::submenu::submenu {
public:
	static vehicle_modifiers_handling_attr_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_modifiers_handling_attr_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::modifiers::handling::attr::vars {
	struct physical_restore {
		float m_mass;
		float m_downforce_modifier;
		float m_percent_submerged;
		math::vector3_<float> m_vec_centre_of_mass_offset;
		math::vector3_<float> m_vec_inertia_multiplier;
	};

	struct transmission_restore {
		float m_drive_bias_front;
		uint8_t m_initial_drive_gears;
		float m_initial_drive_force;
		float m_drive_inertia;
		float m_initial_drive_max_flat_vel;
		float m_clutch_change_rate_scale_up_shift;
		float m_clutch_change_rate_scale_down_shift;
		float m_brake_force;
		float m_hand_brake_force;
		float m_steering_lock;
	};

	struct wheel_traction_restore {
		float m_traction_curve_max;
		float m_traction_spring_delta_max;
		float m_low_speed_traction_loss_mult;
		float m_camber_stiffness;
		float m_traction_loss_mult;
	};

	struct suspension_restore {
		float m_suspension_force;
		float m_suspension_comp_damp;
		float m_suspension_rebound_damp;
		float m_suspension_upper_limit;
		float m_suspension_lower_limit;
		float m_anti_roll_bar_force;
		float m_roll_centre_height_front;
		float m_roll_centre_height_rear;
	};

	struct damage_restore {
		float m_collision_damage_mult;
		float m_weapon_damage_mult;
		float m_deformation_damage_mult;
		float m_engine_damage_mult;
		float m_petrol_tank_volume;
		float m_oil_volume;
	};

	struct misc_restore {
		float m_oil_volume;
		math::vector3_<float> m_seat_offset;
		int m_monetary_value;
	};

	struct variables {
		int m_type;
		int m_drive_bias_front;

		std::unordered_map<uint32_t, physical_restore> m_physical_restore;
		std::unordered_map<uint32_t, transmission_restore> m_transmission_restore;
		std::unordered_map<uint32_t, wheel_traction_restore> m_wheel_traction_restore;
		std::unordered_map<uint32_t, suspension_restore> m_suspension_restore;
		std::unordered_map<uint32_t, damage_restore> m_damage_restore;
		std::unordered_map<uint32_t, misc_restore> m_misc_restore;
	};

	void cache_physical(uint32_t model);
	void cache_transmission(uint32_t model);
	void cache_wheel_traction(uint32_t model);
	void cache_suspension(uint32_t model);
	void cache_damage(uint32_t model);
	void cache_misc(uint32_t model);
	extern variables m_vars;
}