#include "vehicle_modifiers_handling_load.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_modifiers_handling.h"
#include "vehicle_modifiers_handling_attr.h"
#include "vehicle_modifiers_handling_boat.h"
#include "vehicle_modifiers_handling_bike.h"
#include "vehicle_modifiers_handling_flying.h"
#include "../../vehicle_multipliers.h"
#include "rage/engine.h"
#include "util/dirs.h"
#include "util/log.h"
#include <fstream>

using namespace vehicle::modifiers::handling::load::vars;

namespace vehicle::modifiers::handling::load::vars {
	variables m_vars;

	rage::types::handling_data* get_data_main() {
		static rage::types::handling_data hd;

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data) {
						return global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data;
					}
				}
			}
		}

		return &hd;
	}

	rage::types::boat_handling_data* get_data_boat() {
		static rage::types::boat_handling_data hd;

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data) {
						if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data) {
							if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data) {
								return &global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data->m_boat_handling_data;
							}
						}
					}
				}
			}
		}

		return &hd;
	}

	rage::types::bike_handling_data* get_data_bike() {
		static rage::types::bike_handling_data hd;

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data) {
						if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data) {
							if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data) {
								return &global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data->m_bike_handling_data;
							}
						}
					}
				}
			}
		}

		return &hd;
	}

	rage::types::flying_handling_data* get_data_flying() {
		static rage::types::flying_handling_data hd;

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data) {
						if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data) {
							if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data) {
								return &global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data->m_flying_handling_data;
							}
						}
					}
				}
			}
		}

		return &hd;
	}

	void load_handling(std::string file) {
		vehicle_modifiers_handling_menu::get()->update_once(); // re-cache model check

		const char* location = util::va::va("%s%s.json", util::dirs::get_path(handling), file.c_str());

		try {
			std::ifstream input(location);
			if (!input.good()) return;

			nlohmann::json object;
			input >> object;

			if ((object["Type"].get<int>() == 1 && !vehicle::modifiers::handling::vars::m_vars.m_in_boat)
				|| (object["Type"].get<int>() == 2 && !vehicle::modifiers::handling::vars::m_vars.m_in_bike)
				|| (object["Type"].get<int>() == 3 && !vehicle::modifiers::handling::vars::m_vars.m_in_flying)) {
				menu::notify::stacked(vehicle_modifiers_handling_load_menu::get()->get_string("Handling"), vehicle_modifiers_handling_load_menu::get()->get_string("You're not in the correct vehicle type"), global::ui::g_error);
				return;
			}

			if (!object["Multipliers"].is_null()) {
				vehicle::multipliers::vars::m_vars.m_rpm = object["Multipliers"]["RPM"].get<float>();
				vehicle::multipliers::vars::m_vars.m_torque = object["Multipliers"]["Torque"].get<float>();
			}

			uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);
			vehicle::modifiers::handling::attr::vars::cache_physical(model);
			vehicle::modifiers::handling::attr::vars::cache_transmission(model);
			vehicle::modifiers::handling::attr::vars::cache_wheel_traction(model);
			vehicle::modifiers::handling::attr::vars::cache_suspension(model);
			vehicle::modifiers::handling::attr::vars::cache_damage(model);
			vehicle::modifiers::handling::attr::vars::cache_misc(model);

			// Main handling
			auto& Main = object["Main"];
			auto& Physical = Main["Physical"];
			auto& Transmission = Main["Transmission"];
			auto& WheelTraction = Main["Wheel Traction"];
			auto& Suspension = Main["Suspension"];
			auto& Damage = Main["Damage"];
			auto& Miscellaneous = Main["Miscellaneous"];

			get_data_main()->m_mass = Physical["Mass"];
			get_data_main()->m_downforce_modifier = Physical["DownforceModifier"];
			get_data_main()->m_percent_submerged = Physical["PercentSubmerged"];
			get_data_main()->m_vec_centre_of_mass_offset.x = Physical["VecCentreOfMassOffset.X"];
			get_data_main()->m_vec_centre_of_mass_offset.y = Physical["VecCentreOfMassOffset.Y"];
			get_data_main()->m_vec_centre_of_mass_offset.z = Physical["VecCentreOfMassOffset.Z"];
			get_data_main()->m_vec_inertia_multiplier.x = Physical["VecInertiaMultiplier.X"];
			get_data_main()->m_vec_inertia_multiplier.y = Physical["VecInertiaMultiplier.Y"];
			get_data_main()->m_vec_inertia_multiplier.z = Physical["VecInertiaMultiplier.Z"];

			get_data_main()->m_drive_bias_front = Transmission["DriveBiasFront"];
			get_data_main()->m_initial_drive_gears = Transmission["InitialDriveGears"];
			get_data_main()->m_initial_drive_force = Transmission["InitialDriveForce"];
			get_data_main()->m_drive_inertia = Transmission["DriveInertia"];
			get_data_main()->m_initial_drive_max_flat_vel = Transmission["InitialDriveMaxFlatVel"];
			get_data_main()->m_clutch_change_rate_scale_up_shift = Transmission["ClutchChangeRateScaleUpShift"];
			get_data_main()->m_clutch_change_rate_scale_down_shift = Transmission["ClutchChangeRateScaleDownShift"];
			get_data_main()->m_brake_force = Transmission["BrakeForce"];
			get_data_main()->m_hand_brake_force = Transmission["HandBrakeForce"];
			get_data_main()->m_steering_lock = Transmission["SteeringLock"];

			get_data_main()->m_traction_curve_max = WheelTraction["TractionCurveMax"];
			get_data_main()->m_traction_spring_delta_max = WheelTraction["TractionSpringDeltaMax"];
			get_data_main()->m_low_speed_traction_loss_mult = WheelTraction["LowSpeedTractionLossMult"];
			get_data_main()->m_camber_stiffness = WheelTraction["CamberStiffnesss"];
			get_data_main()->m_traction_loss_mult = WheelTraction["TractionLossMult"];

			get_data_main()->m_suspension_force = Suspension["SuspensionForce"];
			get_data_main()->m_suspension_comp_damp = Suspension["SuspensionCompDamp"];
			get_data_main()->m_suspension_rebound_damp = Suspension["SuspensionReboundDamp"];
			get_data_main()->m_suspension_upper_limit = Suspension["SuspensionUpperLimit"];
			get_data_main()->m_suspension_lower_limit = Suspension["SuspensionLowerLimit"];
			get_data_main()->m_anti_roll_bar_force = Suspension["AntiRollBarForce"];
			get_data_main()->m_roll_centre_height_front = Suspension["RollCentreHeightFront"];
			get_data_main()->m_roll_centre_height_rear = Suspension["RollCentreHeightRear"];

			get_data_main()->m_collision_damage_mult = Damage["CollisionDamageMult"];
			get_data_main()->m_weapon_damage_mult = Damage["WeaponDamageMult"];
			get_data_main()->m_deformation_damage_mult = Damage["DeformationDamageMult"];
			get_data_main()->m_engine_damage_mult = Damage["EngineDamageMult"];
			get_data_main()->m_petrol_tank_volume = Damage["PetrolTankVolume"];

			get_data_main()->m_oil_volume = Miscellaneous["OilVolume"];
			get_data_main()->m_seat_offset.x = Miscellaneous["SeatOffset.X"];
			get_data_main()->m_seat_offset.y = Miscellaneous["SeatOffset.Y"];
			get_data_main()->m_seat_offset.z = Miscellaneous["SeatOffset.Z"];
			get_data_main()->m_monetary_value = Miscellaneous["MonetaryValue"];

			// Boat
			if (object["Type"].get<int>() == 1) {
				vehicle::modifiers::handling::boat::vars::cache_physical(model);
				vehicle::modifiers::handling::boat::vars::cache_aquaplane(model);
				vehicle::modifiers::handling::boat::vars::cache_rudder(model);
				vehicle::modifiers::handling::boat::vars::cache_resistance(model);
				vehicle::modifiers::handling::boat::vars::cache_misc(model);

				auto& Boat = object["Boat"];
				auto& Physical = Boat["Physical"];
				auto& Aquaplane = Boat["Aquaplane"];
				auto& Rudder = Boat["Rudder"];
				auto& Resistance = Boat["Resistance"];
				auto& Miscellaneous = Boat["Miscellaneous"];

				get_data_boat()->m_box_front_mult = Physical["BoxFrontMult"];
				get_data_boat()->m_box_rear_mult = Physical["BoxRearMult"];
				get_data_boat()->m_box_side_mult = Physical["BoxSideMult"];
				get_data_boat()->m_sample_top = Physical["SampleTop"];
				get_data_boat()->m_sample_bottom = Physical["SampleBottom"];

				get_data_boat()->m_aquaplane_force = Aquaplane["AquaplaneForce"];
				get_data_boat()->m_aquaplane_push_water_mult = Aquaplane["AquaplanePushWaterMult"];
				get_data_boat()->m_aquaplane_push_water_cap = Aquaplane["AquaplanePushWaterCap"];
				get_data_boat()->m_aquaplane_push_water_apply = Aquaplane["AquaplanePushWaterApply"];
				get_data_boat()->m_keel_sphere_size = Aquaplane["KeelSphereSize"];
				get_data_boat()->m_prop_radius = Aquaplane["PropRadius"];
				get_data_boat()->m_impeller_offset = Aquaplane["ImpellerOffset"];
				get_data_boat()->m_impeller_force_mult = Aquaplane["ImpellerForceMult"];
				get_data_boat()->m_prow_raise_mult = Aquaplane["ProwRaiseMult"];

				get_data_boat()->m_rudder_force = Rudder["RudderForce"];
				get_data_boat()->m_rudder_offset_submerge = Rudder["RudderOffsetSubmerge"];
				get_data_boat()->m_rudder_offset_force = Rudder["RudderOffsetForce"];
				get_data_boat()->m_rudder_offset_force_z_mult = Rudder["RudderOffsetForceZMult"];

				get_data_boat()->m_drag_coefficient = Resistance["DragCoefficient"];
				get_data_boat()->m_vec_move_resistance.x = Resistance["VecMoveResistance.X"];
				get_data_boat()->m_vec_move_resistance.y = Resistance["VecMoveResistance.Y"];
				get_data_boat()->m_vec_move_resistance.z = Resistance["VecMoveResistance.Z"];
				get_data_boat()->m_vec_turn_resistance.x = Resistance["VecTurnResistance.X"];
				get_data_boat()->m_vec_turn_resistance.y = Resistance["VecTurnResistance.Y"];
				get_data_boat()->m_vec_turn_resistance.z = Resistance["VecTurnResistance.Z"];

				get_data_boat()->m_wave_audio_mult = Miscellaneous["WaveAudioMult"];
				get_data_boat()->m_look_lr_cam_height = Miscellaneous["Look_L_R_CamHeight"];
				get_data_boat()->m_low_lod_ang_offset = Miscellaneous["LowLodAngOffset"];
				get_data_boat()->m_low_lod_draught_offset = Miscellaneous["LowLodDraughtOffset"];
				get_data_boat()->m_dinghy_sphere_buoy_const = Miscellaneous["DinghySphereBuoyConst"];
			}

			// Bike
			if (object["Type"].get<int>() == 2) {
				vehicle::modifiers::handling::bike::vars::cache_physical(model);
				vehicle::modifiers::handling::bike::vars::cache_balance(model);
				vehicle::modifiers::handling::bike::vars::cache_friction(model);

				auto& Bike = object["Bike"];
				auto& Physical = Bike["Physical"];
				auto& Balance = Bike["Balance"];
				auto& Friction = Bike["Friction"];

				get_data_bike()->m_lean_fwd_com_mult = Physical["LeanFwdCOMMult"];
				get_data_bike()->m_lean_fwd_force_mult = Physical["LeanFwdForceMult"];
				get_data_bike()->m_lean_bak_com_mult = Physical["LeanBakCOMMult"];
				get_data_bike()->m_lean_bak_force_mult = Physical["LeanBakForceMult"];
				get_data_bike()->m_max_bank_angle = Physical["MaxBankAngle"];
				get_data_bike()->m_full_anim_angle = Physical["FullAnimAngle"];
				get_data_bike()->m_des_lean_return_frac = Physical["DesLeanReturnFrac"];
				get_data_bike()->m_stick_lean_mult = Physical["StickLeanMult"];
				get_data_bike()->m_braking_stability_mult = Physical["BrakingStabilityMult"];
				get_data_bike()->m_in_air_steer_mult = Physical["InAirSteerMult"];
				get_data_bike()->m_jump_force = Physical["JumpForce"];

				get_data_bike()->m_bike_on_stand_steer_angle = Balance["BikeOnStandSteerAngle"];
				get_data_bike()->m_bike_on_stand_lean_angle = Balance["BikeOnStandLeanAngle"];
				get_data_bike()->m_front_balance_mult = Balance["FrontBalanceMult"];
				get_data_bike()->m_rear_balance_mult = Balance["RearBalanceMult"];
				get_data_bike()->m_wheelie_balance_point = Balance["WheelieBalancePoint"];
				get_data_bike()->m_stoppie_balance_point = Balance["StoppieBalancePoint"];
				get_data_bike()->m_wheelie_steer_mult = Balance["WheelieSteerMult"];

				get_data_bike()->m_bike_ground_side_friction_mult = Friction["BikeGroundSideFrictionMult"];
				get_data_bike()->m_bike_wheel_ground_side_friction_mult = Friction["BikeWheelGroundSideFrictionMult"];
			}

			// Flying
			if (object["Type"].get<int>() == 3) {
				vehicle::modifiers::handling::flying::vars::cache_thrust(model);
				vehicle::modifiers::handling::flying::vars::cache_movement(model);
				vehicle::modifiers::handling::flying::vars::cache_resistance(model);
				vehicle::modifiers::handling::flying::vars::cache_turbulence(model);
				vehicle::modifiers::handling::flying::vars::cache_gear(model);
				vehicle::modifiers::handling::flying::vars::cache_ground(model);
				vehicle::modifiers::handling::flying::vars::cache_misc(model);

				auto& Flying = object["Flying"];
				auto& Thrust = Flying["Thrust"];
				auto& Movement = Flying["Movement"];
				auto& Resistance = Flying["Resistance"];
				auto& Turbulence = Flying["Turbulence"];
				auto& Gear = Flying["Gear"];
				auto& Ground = Flying["Ground"];
				auto& Miscellaneous = Flying["Miscellaneous"];

				get_data_flying()->m_thrust = Thrust["Thrust"];
				get_data_flying()->m_thrust_fall_off = Thrust["ThrustFallOff"];
				get_data_flying()->m_thrust_vectoring = Thrust["ThrustVectoring"];

				get_data_flying()->m_side_slip_mult = Movement["SideSlipMult"];
				get_data_flying()->m_yaw_mult = Movement["YawMult"];
				get_data_flying()->m_yaw_stabilise = Movement["YawStabilise"];
				get_data_flying()->m_roll_mult = Movement["RollMult"];
				get_data_flying()->m_roll_stabilise = Movement["RollStabilise"];
				get_data_flying()->m_pitch_mult = Movement["PitchMult"];
				get_data_flying()->m_pitch_stabilise = Movement["PitchStabilise"];
				get_data_flying()->m_form_lift_mult = Movement["FormLiftMult"];
				get_data_flying()->m_attack_lift_mult = Movement["AttackLiftMult"];
				get_data_flying()->m_attack_dive_mult = Movement["AttackDiveMult"];
				get_data_flying()->m_engine_off_glide_multi = Movement["EngineOffGlideMulti"];

				get_data_flying()->m_wind_mult = Resistance["WindMult"];
				get_data_flying()->m_move_res = Resistance["MoveRes"];
				get_data_flying()->m_vec_turn_resistance.x = Resistance["VecTurnResistance.X"];
				get_data_flying()->m_vec_turn_resistance.y = Resistance["VecTurnResistance.Y"];
				get_data_flying()->m_vec_turn_resistance.z = Resistance["VecTurnResistance.Z"];
				get_data_flying()->m_vec_speed_resistance.x = Resistance["VecSpeedResistance.X"];
				get_data_flying()->m_vec_speed_resistance.y = Resistance["VecSpeedResistance.Y"];
				get_data_flying()->m_vec_speed_resistance.z = Resistance["VecSpeedResistance.Z"];

				get_data_flying()->m_turublence_magnitude_max = Turbulence["TurublenceMagnitudeMax"];
				get_data_flying()->m_turublence_force_multi = Turbulence["TurublenceForceMulti"];
				get_data_flying()->m_turublence_roll_torque_multi = Turbulence["TurublenceRollTorqueMulti"];
				get_data_flying()->m_turublence_pitch_torque_multi = Turbulence["TurublencePitchTorqueMulti"];

				get_data_flying()->m_gear_down_drag_v = Gear["GearDownDragV"];
				get_data_flying()->m_gear_down_lift_mult = Gear["GearDownLiftMult"];

				get_data_flying()->m_on_ground_yaw_boost_speed_peak = Ground["OnGroundYawBoostSpeedPeak"];
				get_data_flying()->m_on_ground_yaw_boost_speed_cap = Ground["OnGroundYawBoostSpeedCap"];

				get_data_flying()->m_body_damage_control_effect_mult = Miscellaneous["BodyDamageControlEffectMult"];
				get_data_flying()->m_input_sensitivity_for_difficulty = Miscellaneous["InputSensitivityForDifficulty"];
			}

			input.close();
		} catch (std::exception& E) {
			LOG_WARN("[Json] %s", E.what());
		}
	}

	void save_handling(std::string file) {
		vehicle_modifiers_handling_menu::get()->update_once(); // re-cache model check

		const char* location = util::va::va("%s%s.json", util::dirs::get_path(handling), file.c_str());

		try {
			std::ofstream output(location);
			nlohmann::json object;

			object["Multipliers"]["RPM"] = vehicle::multipliers::vars::m_vars.m_rpm;
			object["Multipliers"]["Torque"] = vehicle::multipliers::vars::m_vars.m_torque;

			object["Type"] = 0;
			auto& Main = object["Main"];
			auto& Physical = Main["Physical"];
			auto& Transmission = Main["Transmission"];
			auto& WheelTraction = Main["Wheel Traction"];
			auto& Suspension = Main["Suspension"];
			auto& Damage = Main["Damage"];
			auto& Miscellaneous = Main["Miscellaneous"];

			Physical["Mass"] = get_data_main()->m_mass;
			Physical["DownforceModifier"] = get_data_main()->m_downforce_modifier;
			Physical["PercentSubmerged"] = get_data_main()->m_percent_submerged;
			Physical["VecCentreOfMassOffset.X"] = get_data_main()->m_vec_centre_of_mass_offset.x;
			Physical["VecCentreOfMassOffset.Y"] = get_data_main()->m_vec_centre_of_mass_offset.y;
			Physical["VecCentreOfMassOffset.Z"] = get_data_main()->m_vec_centre_of_mass_offset.z;
			Physical["VecInertiaMultiplier.X"] = get_data_main()->m_vec_inertia_multiplier.x;
			Physical["VecInertiaMultiplier.Y"] = get_data_main()->m_vec_inertia_multiplier.y;
			Physical["VecInertiaMultiplier.Z"] = get_data_main()->m_vec_inertia_multiplier.z;

			Transmission["DriveBiasFront"] = get_data_main()->m_drive_bias_front;
			Transmission["InitialDriveGears"] = get_data_main()->m_initial_drive_gears;
			Transmission["InitialDriveForce"] = get_data_main()->m_initial_drive_force;
			Transmission["DriveInertia"] = get_data_main()->m_drive_inertia;
			Transmission["InitialDriveMaxFlatVel"] = get_data_main()->m_initial_drive_max_flat_vel;
			Transmission["ClutchChangeRateScaleUpShift"] = get_data_main()->m_clutch_change_rate_scale_up_shift;
			Transmission["ClutchChangeRateScaleDownShift"] = get_data_main()->m_clutch_change_rate_scale_down_shift;
			Transmission["BrakeForce"] = get_data_main()->m_brake_force;
			Transmission["HandBrakeForce"] = get_data_main()->m_hand_brake_force;
			Transmission["SteeringLock"] = get_data_main()->m_steering_lock;

			WheelTraction["TractionCurveMax"] = get_data_main()->m_traction_curve_max;
			WheelTraction["TractionSpringDeltaMax"] = get_data_main()->m_traction_spring_delta_max;
			WheelTraction["LowSpeedTractionLossMult"] = get_data_main()->m_low_speed_traction_loss_mult;
			WheelTraction["CamberStiffnesss"] = get_data_main()->m_camber_stiffness;
			WheelTraction["TractionLossMult"] = get_data_main()->m_traction_loss_mult;

			Suspension["SuspensionForce"] = get_data_main()->m_suspension_force;
			Suspension["SuspensionCompDamp"] = get_data_main()->m_suspension_comp_damp;
			Suspension["SuspensionReboundDamp"] = get_data_main()->m_suspension_rebound_damp;
			Suspension["SuspensionUpperLimit"] = get_data_main()->m_suspension_upper_limit;
			Suspension["SuspensionLowerLimit"] = get_data_main()->m_suspension_lower_limit;
			Suspension["AntiRollBarForce"] = get_data_main()->m_anti_roll_bar_force;
			Suspension["RollCentreHeightFront"] = get_data_main()->m_roll_centre_height_front;
			Suspension["RollCentreHeightRear"] = get_data_main()->m_roll_centre_height_rear;

			Damage["CollisionDamageMult"] = get_data_main()->m_collision_damage_mult;
			Damage["WeaponDamageMult"] = get_data_main()->m_weapon_damage_mult;
			Damage["DeformationDamageMult"] = get_data_main()->m_deformation_damage_mult;
			Damage["EngineDamageMult"] = get_data_main()->m_engine_damage_mult;
			Damage["PetrolTankVolume"] = get_data_main()->m_petrol_tank_volume;

			Miscellaneous["OilVolume"] = get_data_main()->m_oil_volume;
			Miscellaneous["SeatOffset.X"] = get_data_main()->m_seat_offset.x;
			Miscellaneous["SeatOffset.Y"] = get_data_main()->m_seat_offset.y;
			Miscellaneous["SeatOffset.Z"] = get_data_main()->m_seat_offset.z;
			Miscellaneous["MonetaryValue"] = get_data_main()->m_monetary_value;

			if (vehicle::modifiers::handling::vars::m_vars.m_in_boat) {
				object["Type"] = 1;
				auto& Boat = object["Boat"];
				auto& Physical = Boat["Physical"];
				auto& Aquaplane = Boat["Aquaplane"];
				auto& Rudder = Boat["Rudder"];
				auto& Resistance = Boat["Resistance"];
				auto& Miscellaneous = Boat["Miscellaneous"];

				Physical["BoxFrontMult"] = get_data_boat()->m_box_front_mult;
				Physical["BoxRearMult"] = get_data_boat()->m_box_rear_mult;
				Physical["BoxSideMult"] = get_data_boat()->m_box_side_mult;
				Physical["SampleTop"] = get_data_boat()->m_sample_top;
				Physical["SampleBottom"] = get_data_boat()->m_sample_bottom;

				Aquaplane["AquaplaneForce"] = get_data_boat()->m_aquaplane_force;
				Aquaplane["AquaplanePushWaterMult"] = get_data_boat()->m_aquaplane_push_water_mult;
				Aquaplane["AquaplanePushWaterCap"] = get_data_boat()->m_aquaplane_push_water_cap;
				Aquaplane["AquaplanePushWaterApply"] = get_data_boat()->m_aquaplane_push_water_apply;
				Aquaplane["KeelSphereSize"] = get_data_boat()->m_keel_sphere_size;
				Aquaplane["PropRadius"] = get_data_boat()->m_prop_radius;
				Aquaplane["ImpellerOffset"] = get_data_boat()->m_impeller_offset;
				Aquaplane["ImpellerForceMult"] = get_data_boat()->m_impeller_force_mult;
				Aquaplane["ProwRaiseMult"] = get_data_boat()->m_prow_raise_mult;

				Rudder["RudderForce"] = get_data_boat()->m_rudder_force;
				Rudder["RudderOffsetSubmerge"] = get_data_boat()->m_rudder_offset_submerge;
				Rudder["RudderOffsetForce"] = get_data_boat()->m_rudder_offset_force;
				Rudder["RudderOffsetForceZMult"] = get_data_boat()->m_rudder_offset_force_z_mult;

				Resistance["DragCoefficient"] = get_data_boat()->m_drag_coefficient;
				Resistance["VecMoveResistance.X"] = get_data_boat()->m_vec_move_resistance.x;
				Resistance["VecMoveResistance.Y"] = get_data_boat()->m_vec_move_resistance.y;
				Resistance["VecMoveResistance.Z"] = get_data_boat()->m_vec_move_resistance.z;
				Resistance["VecTurnResistance.X"] = get_data_boat()->m_vec_turn_resistance.x;
				Resistance["VecTurnResistance.Y"] = get_data_boat()->m_vec_turn_resistance.y;
				Resistance["VecTurnResistance.Z"] = get_data_boat()->m_vec_turn_resistance.z;

				Miscellaneous["WaveAudioMult"] = get_data_boat()->m_wave_audio_mult;
				Miscellaneous["Look_L_R_CamHeight"] = get_data_boat()->m_look_lr_cam_height;
				Miscellaneous["LowLodAngOffset"] = get_data_boat()->m_low_lod_ang_offset;
				Miscellaneous["LowLodDraughtOffset"] = get_data_boat()->m_low_lod_draught_offset;
				Miscellaneous["DinghySphereBuoyConst"] = get_data_boat()->m_dinghy_sphere_buoy_const;
			} else if (vehicle::modifiers::handling::vars::m_vars.m_in_bike) {
				object["Type"] = 2;
				auto& Bike = object["Bike"];
				auto& Physical = Bike["Physical"];
				auto& Balance = Bike["Balance"];
				auto& Friction = Bike["Friction"];

				Physical["LeanFwdCOMMult"] = get_data_bike()->m_lean_fwd_com_mult;
				Physical["LeanFwdForceMult"] = get_data_bike()->m_lean_fwd_force_mult;
				Physical["LeanBakCOMMult"] = get_data_bike()->m_lean_bak_com_mult;
				Physical["LeanBakForceMult"] = get_data_bike()->m_lean_bak_force_mult;
				Physical["MaxBankAngle"] = get_data_bike()->m_max_bank_angle;
				Physical["FullAnimAngle"] = get_data_bike()->m_full_anim_angle;
				Physical["DesLeanReturnFrac"] = get_data_bike()->m_des_lean_return_frac;
				Physical["StickLeanMult"] = get_data_bike()->m_stick_lean_mult;
				Physical["BrakingStabilityMult"] = get_data_bike()->m_braking_stability_mult;
				Physical["InAirSteerMult"] = get_data_bike()->m_in_air_steer_mult;
				Physical["JumpForce"] = get_data_bike()->m_jump_force;

				Balance["BikeOnStandSteerAngle"] = get_data_bike()->m_bike_on_stand_steer_angle;
				Balance["BikeOnStandLeanAngle"] = get_data_bike()->m_bike_on_stand_lean_angle;
				Balance["FrontBalanceMult"] = get_data_bike()->m_front_balance_mult;
				Balance["RearBalanceMult"] = get_data_bike()->m_rear_balance_mult;
				Balance["WheelieBalancePoint"] = get_data_bike()->m_wheelie_balance_point;
				Balance["StoppieBalancePoint"] = get_data_bike()->m_stoppie_balance_point;
				Balance["WheelieSteerMult"] = get_data_bike()->m_wheelie_steer_mult;

				Friction["BikeGroundSideFrictionMult"] = get_data_bike()->m_bike_ground_side_friction_mult;
				Friction["BikeWheelGroundSideFrictionMult"] = get_data_bike()->m_bike_wheel_ground_side_friction_mult;
			} else if (vehicle::modifiers::handling::vars::m_vars.m_in_flying) {
				object["Type"] = 3;
				auto& Flying = object["Flying"];
				auto& Thrust = Flying["Thrust"];
				auto& Movement = Flying["Movement"];
				auto& Resistance = Flying["Resistance"];
				auto& Turbulence = Flying["Turbulence"];
				auto& Gear = Flying["Gear"];
				auto& Ground = Flying["Ground"];
				auto& Miscellaneous = Flying["Miscellaneous"];

				Thrust["Thrust"] = get_data_flying()->m_thrust;
				Thrust["ThrustFallOff"] = get_data_flying()->m_thrust_fall_off;
				Thrust["ThrustVectoring"] = get_data_flying()->m_thrust_vectoring;

				Movement["SideSlipMult"] = get_data_flying()->m_side_slip_mult;
				Movement["YawMult"] = get_data_flying()->m_yaw_mult;
				Movement["YawStabilise"] = get_data_flying()->m_yaw_stabilise;
				Movement["RollMult"] = get_data_flying()->m_roll_mult;
				Movement["RollStabilise"] = get_data_flying()->m_roll_stabilise;
				Movement["PitchMult"] = get_data_flying()->m_pitch_mult;
				Movement["PitchStabilise"] = get_data_flying()->m_pitch_stabilise;
				Movement["FormLiftMult"] = get_data_flying()->m_form_lift_mult;
				Movement["AttackLiftMult"] = get_data_flying()->m_attack_lift_mult;
				Movement["AttackDiveMult"] = get_data_flying()->m_attack_dive_mult;
				Movement["EngineOffGlideMulti"] = get_data_flying()->m_engine_off_glide_multi;

				Resistance["WindMult"] = get_data_flying()->m_wind_mult;
				Resistance["MoveRes"] = get_data_flying()->m_move_res;
				Resistance["VecTurnResistance.X"] = get_data_flying()->m_vec_turn_resistance.x;
				Resistance["VecTurnResistance.Y"] = get_data_flying()->m_vec_turn_resistance.y;
				Resistance["VecTurnResistance.Z"] = get_data_flying()->m_vec_turn_resistance.z;
				Resistance["VecSpeedResistance.X"] = get_data_flying()->m_vec_speed_resistance.x;
				Resistance["VecSpeedResistance.Y"] = get_data_flying()->m_vec_speed_resistance.y;
				Resistance["VecSpeedResistance.Z"] = get_data_flying()->m_vec_speed_resistance.z;

				Turbulence["TurublenceMagnitudeMax"] = get_data_flying()->m_turublence_magnitude_max;
				Turbulence["TurublenceForceMulti"] = get_data_flying()->m_turublence_force_multi;
				Turbulence["TurublenceRollTorqueMulti"] = get_data_flying()->m_turublence_roll_torque_multi;
				Turbulence["TurublencePitchTorqueMulti"] = get_data_flying()->m_turublence_pitch_torque_multi;

				Gear["GearDownDragV"] = get_data_flying()->m_gear_down_drag_v;
				Gear["GearDownLiftMult"] = get_data_flying()->m_gear_down_lift_mult;

				Ground["OnGroundYawBoostSpeedPeak"] = get_data_flying()->m_on_ground_yaw_boost_speed_peak;
				Ground["OnGroundYawBoostSpeedCap"] = get_data_flying()->m_on_ground_yaw_boost_speed_cap;

				Miscellaneous["BodyDamageControlEffectMult"] = get_data_flying()->m_body_damage_control_effect_mult;
				Miscellaneous["InputSensitivityForDifficulty"] = get_data_flying()->m_input_sensitivity_for_difficulty;
			}

			output << object.dump(4);
			output.close();
			vehicle_modifiers_handling_load_menu::get()->update_once();
		} catch (std::exception& E) {
			LOG_WARN("[Json] %s", E.what());
		}
	}
}

void vehicle_modifiers_handling_load_menu::load() {
	set_name("Save and Load");
	set_parent<vehicle_modifiers_handling_menu>();

	add_option(button_option("Save Handling")
		.add_translate()
		.add_keyboard("Enter the handling name!", 30, [](button_option* option, const char* result) { save_handling(result); }));

	add_option(break_option("Handling")
		.add_translate());

	add_string("~m~None");
	add_string("You're not in the correct vehicle type");
	add_string("Handling");
}

void vehicle_modifiers_handling_load_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}
}

void vehicle_modifiers_handling_load_menu::update_once() {
	clear_options(2);

	std::vector<std::string> handling = util::dirs::get_files_in_directory(util::dirs::get_path(handling), ".json");
	if (handling.size()) {
		for (std::string file : handling) {
			add_option(button_option(file)
				.add_click([=] { load_handling(file); }));
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void vehicle_modifiers_handling_load_menu::feature_update() {}

vehicle_modifiers_handling_load_menu* g_instance;
vehicle_modifiers_handling_load_menu* vehicle_modifiers_handling_load_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_modifiers_handling_load_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}