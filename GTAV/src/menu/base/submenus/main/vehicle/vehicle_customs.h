#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::vars {
	struct vehicle_stats {
		float m_estimated_max_speed;
		float m_acceleration;
		float m_braking;
		float m_traction;
		bool m_success;

		// Mods
		int m_armor;
		int m_brakes;
		int m_front_bumper;
		int m_rear_bumper;
		int m_engine;
		int m_exhaust;
		int m_hood;
		int m_horn;
		int m_lights;
		int m_skirts;
		int m_suspension;
		int m_transmission;
		int m_spoiler;
		int m_grille;
		int m_left_fender;
		int m_right_fender;
		int m_roof;
		int m_chassis;
		int m_turbo;
		int m_window_tint;
		int m_xenon_color;
		int m_plate_index;
		bool m_neon[4] = { false, false, false, false };
		color_rgba m_neon_color = { 0, 0, 0, 0 };

		// Bennys
		int m_bennys_plateholder;
		int m_bennys_vanity_plate;
		int m_bennys_trim_design;
		int m_bennys_ornaments;
		int m_bennys_interior_design;
		int m_bennys_dials;
		int m_bennys_doors;
		int m_bennys_seats;
		int m_bennys_steering_wheel;
		int m_bennys_shifter;
		int m_bennys_plaques;
		int m_bennys_trunk;
		int m_bennys_audio_install;
		int m_bennys_hydraulics;
		int m_bennys_engine_block;
		int m_bennys_air_filters;
		int m_bennys_stunt_brace;
		int m_bennys_arch_covers;
		int m_bennys_aerials;
		int m_bennys_rear_stripe_color;
		int m_bennys_tank;
		int m_bennys_window_mod;
		int m_bennys_livery;
		int m_bennys_special_front_rims;
		int m_bennys_special_rear_rims;

		vehicle_stats()
			: m_estimated_max_speed(0.f),
			m_acceleration(0.f),
			m_braking(0.f),
			m_traction(0.f),
			m_success(false),
			m_window_tint(0),
			m_spoiler(0),
			m_grille(0),
			m_left_fender(0),
			m_right_fender(0),
			m_plate_index(0),
			m_xenon_color(0),
			m_roof(0),
			m_chassis(0),
			m_armor(0),
			m_brakes(0),
			m_front_bumper(0),
			m_rear_bumper(0),
			m_engine(0),
			m_exhaust(0),
			m_hood(0),
			m_horn(0),
			m_lights(0),
			m_skirts(0),
			m_suspension(0),
			m_transmission(0),
			m_turbo(0),

			m_bennys_plateholder(0),
			m_bennys_vanity_plate(0),
			m_bennys_trim_design(0),
			m_bennys_ornaments(0),
			m_bennys_interior_design(0),
			m_bennys_dials(0),
			m_bennys_doors(0),
			m_bennys_seats(0),
			m_bennys_steering_wheel(0),
			m_bennys_shifter(0),
			m_bennys_plaques(0),
			m_bennys_trunk(0),
			m_bennys_audio_install(0),
			m_bennys_hydraulics(0),
			m_bennys_engine_block(0),
			m_bennys_air_filters(0),
			m_bennys_stunt_brace(0),
			m_bennys_arch_covers(0),
			m_bennys_aerials(0),
			m_bennys_rear_stripe_color(0),
			m_bennys_tank(0),
			m_bennys_window_mod(0),
			m_bennys_livery(0),
			m_bennys_special_front_rims(0),
			m_bennys_special_rear_rims(0) {}
	};

	struct variables {
		int m_type = 0;
		int m_global_stats[2] = { 0, 0 };
		float m_values[4][4];
		vehicle_stats m_cached_stats;
		vehicle_stats m_new_stats;
		bool m_update_cache = false;

		std::vector<std::pair<const char*, int>> m_wheel_sport;
		std::vector<std::pair<const char*, int>> m_wheel_muscle;
		std::vector<std::pair<const char*, int>> m_wheel_lowrider;
		std::vector<std::pair<const char*, int>> m_wheel_suv;
		std::vector<std::pair<const char*, int>> m_wheel_offroad;
		std::vector<std::pair<const char*, int>> m_wheel_tuner;
		std::vector<std::pair<const char*, int>> m_wheel_bike;
		std::vector<std::pair<const char*, int>> m_wheel_high_end;
		std::vector<std::pair<const char*, int>> m_wheel_bennys;
		std::vector<std::pair<const char*, int>> m_wheel_bespoke;
		std::vector<std::pair<const char*, int>> m_wheel_open;
		std::vector<std::pair<const char*, int>> m_wheel_street;
		std::vector<std::pair<const char*, int>> m_wheel_track;
	};

	bool can_run_lsc();
	bool can_run_bennys();
	int get_size();
	void update_caches();
	void cache_vehicle_stats();
	std::string get_vehicle_mod_name(eVehicleModTypes type, std::string default);

	namespace scripts {
		void draw_vehicle_stats(Vehicle Veh);
	};

	extern variables m_vars;
}