#pragma once
#include "menu/base/submenu.h"

class vehicle_modifiers_handling_bike_menu : public menu::submenu::submenu {
public:
	static vehicle_modifiers_handling_bike_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_modifiers_handling_bike_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::modifiers::handling::bike::vars {
	struct PhysicalRestore {
		float m_lean_fwd_com_mult;
		float m_lean_fwd_force_mult;
		float m_lean_bak_com_mult;
		float m_lean_bak_force_mult;
		float m_max_bank_angle;
		float m_full_anim_angle;
		float m_des_lean_return_frac;
		float m_stick_lean_mult;
		float m_braking_stability_mult;
		float m_in_air_steer_mult;
		float m_jump_force;
	};

	struct BalanceRestore {
		float m_bike_on_stand_steer_angle;
		float m_bike_on_stand_lean_angle;
		float m_front_balance_mult;
		float m_rear_balance_mult;
		float m_wheelie_balance_point;
		float m_stoppie_balance_point;
		float m_wheelie_steer_mult;
	};

	struct FrictionRestore {
		float m_bike_ground_side_friction_mult;
		float m_bike_wheel_ground_side_friction_mult;
	};

	struct variables {
		int m_type;

		std::unordered_map<uint32_t, PhysicalRestore> m_physical_restore;
		std::unordered_map<uint32_t, BalanceRestore> m_balance_restore;
		std::unordered_map<uint32_t, FrictionRestore> m_friction_restore;
	};

	void cache_physical(uint32_t model);
	void cache_balance(uint32_t model);
	void cache_friction(uint32_t model);
	extern variables m_vars;
}