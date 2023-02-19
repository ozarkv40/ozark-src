#include "spawner_vehicle_modded.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"
#include "util/dirs.h"
#include "util/xml/pugixml.h"
#include "menu/base/util/notify.h"
#include "menu/base/util/control.h"
#include "rage/engine.h"
#include "util/fiber.h"

using namespace spawner::vehicle::modded::vars;

namespace spawner::vehicle::modded::vars {
	variables m_vars;

	struct xml_attachment {
		struct attachment {
			bool m_is_attached;
			int m_attached_to;
			int m_bone_index;
			math::vector3<float> m_position;
			math::vector3<float> m_rotation;
		} attachment;

		struct placement {
			math::vector3<float> m_position;
			math::vector3<float> m_rotation;
		} placement;

		int m_initial_handle;
		int m_handle;
		int m_type;
		uint32_t m_model_hash;
		bool m_dynamic;
		bool m_frozen_position;
		int m_opacity_level;
		int m_lod_distance;
		bool m_is_visible;
		int m_max_health;
		int m_health;
		bool m_has_gravity;
		bool m_is_on_fire;
		bool m_is_invincible;
		bool m_is_bullet_proof;
		bool m_is_collision_proof;
		bool m_is_explosion_proof;
		bool m_is_fire_proof;
		bool m_is_melee_proof;
		bool m_is_only_damaged_by_player;
	};

	xml_attachment create_entity(pugi::xml_node node) {
		xml_attachment attachment;
		attachment.m_type = node.child("Type").text().as_int();
		attachment.m_frozen_position = node.child("FrozenPos").text().as_bool();
		attachment.m_model_hash = node.child("ModelHash").text().as_uint();
		attachment.m_dynamic = node.child("Dynamic").text().as_bool();
		attachment.m_initial_handle = node.child("InitialHandle").text().as_int();
		attachment.m_opacity_level = node.child("OpacityLevel").text().as_int();
		attachment.m_lod_distance = node.child("LodDistance").text().as_int();
		attachment.m_is_visible = node.child("IsVisible").text().as_bool();
		attachment.m_health = node.child("Health").text().as_int();
		attachment.m_max_health = node.child("MaxHealth").text().as_int();
		attachment.m_is_on_fire = node.child("IsOnFire").text().as_bool();
		attachment.m_is_invincible = node.child("IsInvincible").text().as_bool();
		attachment.m_is_bullet_proof = node.child("IsBulletProof").text().as_bool();
		attachment.m_is_collision_proof = node.child("IsCollisionProof").text().as_bool();
		attachment.m_is_explosion_proof = node.child("IsExplosionProof").text().as_bool();
		attachment.m_is_fire_proof = node.child("IsFireProof").text().as_bool();
		attachment.m_is_melee_proof = node.child("IsMeleeProof").text().as_bool();
		attachment.m_is_only_damaged_by_player = node.child("IsOnlyDamagedByPlayer").text().as_bool();
		attachment.m_has_gravity = node.child("HasGravity").text().as_bool(true);
		
		attachment.placement.m_position = math::vector3<float>(node.child("PositionRotation").child("X").text().as_float(), node.child("PositionRotation").child("Y").text().as_float(), node.child("PositionRotation").child("Z").text().as_float());
		attachment.placement.m_rotation = math::vector3<float>(node.child("PositionRotation").child("Pitch").text().as_float(), node.child("PositionRotation").child("Roll").text().as_float(), node.child("PositionRotation").child("Yaw").text().as_float());

		attachment.attachment.m_is_attached = node.child("Attachment").attribute("isAttached").as_bool();
		attachment.attachment.m_bone_index = node.child("Attachment").child("BoneIndex").text().as_int();
		attachment.attachment.m_position = math::vector3<float>(node.child("Attachment").child("X").text().as_float(), node.child("Attachment").child("Y").text().as_float(), node.child("Attachment").child("Z").text().as_float());
		attachment.attachment.m_rotation = math::vector3<float>(node.child("Attachment").child("Pitch").text().as_float(), node.child("Attachment").child("Roll").text().as_float(), node.child("Attachment").child("Yaw").text().as_float());

		if (node.child("Attachment").child("AttachedTo").text().as_string() == "VEHICLE") {
			attachment.attachment.m_attached_to = m_vars.m_vehicle_handle;
		} else if (node.child("Attachment").child("AttachedTo").text().as_string() == "PLAYER") {
			attachment.attachment.m_attached_to = menu::player::get_local_player().m_ped;
		} else {
			attachment.attachment.m_attached_to = node.child("Attachment").child("AttachedTo").text().as_int();
		}

		menu::control::simple_request_model(attachment.m_model_hash);

		switch (attachment.m_type) {
			case 1: { // ped
				attachment.m_handle = native::create_ped(21, attachment.m_model_hash, attachment.placement.m_position.x, attachment.placement.m_position.y, attachment.placement.m_position.z, 0.f, true, true);
				if (native::does_entity_exist(attachment.m_handle)) {
					native::freeze_entity_position(attachment.m_handle, attachment.m_frozen_position);

					native::set_ped_can_be_knocked_off_vehicle(attachment.m_handle, false);
					native::set_ped_can_switch_weapon(attachment.m_handle, false);

					native::set_ped_flee_attributes(attachment.m_handle, 0, 0);
					native::set_ped_combat_attributes(attachment.m_handle, 17, 1);

					if (attachment.m_opacity_level < 255) native::set_entity_alpha(attachment.m_handle, attachment.m_opacity_level, 0);
					native::set_entity_lod_dist(attachment.m_handle, attachment.m_lod_distance);
					native::set_entity_visible(attachment.m_handle, attachment.m_is_visible, true);

					if (attachment.m_max_health) native::set_entity_max_health(attachment.m_handle, attachment.m_max_health);
					if (attachment.m_health) native::set_entity_health(attachment.m_handle, attachment.m_health);

					if (attachment.m_is_on_fire) {
						native::start_entity_fire(attachment.m_handle);
					}

					native::set_entity_invincible(attachment.m_handle, attachment.m_is_invincible);
					native::set_entity_proofs(attachment.m_handle, attachment.m_is_bullet_proof, attachment.m_is_fire_proof, attachment.m_is_explosion_proof, attachment.m_is_collision_proof, attachment.m_is_melee_proof, 1, 1, 1);
					native::set_entity_only_damaged_by_player(attachment.m_handle, attachment.m_is_only_damaged_by_player);

					pugi::xml_node ped_properties = node.child("PedProperties");

					if (ped_properties.child("IsStill").text().as_bool()) {
						native::task_stand_still(attachment.m_handle, -1);
					}

					if (ped_properties.child("CanRagdoll")) native::set_ped_can_ragdoll(attachment.m_handle, ped_properties.child("CanRagdoll").text().as_bool());

					native::set_ped_armour(attachment.m_handle, ped_properties.child("Armour").text().as_int());

					if (ped_properties.child("CurrentWeapon")) {
						native::give_delayed_weapon_to_ped(attachment.m_handle, ped_properties.child("CurrentWeapon").text().as_uint(), 9999, 1);
					}

					if (ped_properties.child("PedComps")) {
						for (pugi::xml_node node_components = ped_properties.child("PedComps").first_child(); node_components; node_components = node_components.next_sibling()) {
							int mod_type = std::stoi(std::string(node_components.name()).substr(1));
							std::string mod_value_str = node_components.text().as_string();
							if (mod_value_str.find(",") != std::string::npos) {
								native::set_ped_component_variation(attachment.m_handle, mod_type, std::stoi(mod_value_str.substr(0, mod_value_str.find(","))), std::stoi(mod_value_str.substr(mod_value_str.find(",") + 1)), 0);
							}
						}
					}

					if (ped_properties.child("RelationshipGroupAltered").text().as_bool()) {
						native::set_ped_relationship_group_default_hash(attachment.m_handle, ped_properties.child("RelationshipGroup").text().as_uint());
					}

					if (ped_properties.child("ScenarioActive").text().as_bool()) {
						native::task_start_scenario_in_place(attachment.m_handle, (char*)ped_properties.child("ScenarioName").text().as_string(), 0, 1);
					}

					if (ped_properties.child("AnimActive").text().as_bool()) {
						char* anim_dict = (char*)ped_properties.child("AnimDict").text().as_string();
						char* anim_name = (char*)ped_properties.child("AnimName").text().as_string();

						native::request_anim_dict(anim_dict);
						native::task_play_anim(attachment.m_handle, anim_dict, anim_name, 8, 0, -1, 9, 0, 0, 0, 0);
					}
				}

				break;
			}

			case 2: { // vehicle
				attachment.m_handle = native::create_vehicle(attachment.m_model_hash, attachment.placement.m_position.x, attachment.placement.m_position.y, attachment.placement.m_position.z, menu::player::get_local_player().m_heading, true, true, false);
				if (native::does_entity_exist(attachment.m_handle)) {
					native::freeze_entity_position(attachment.m_handle, attachment.m_frozen_position);

					native::decor_set_int(attachment.m_handle, "MPBitset", (1 << 10));
					native::set_vehicle_is_stolen(attachment.m_handle, false);

					native::set_vehicle_mod_kit(attachment.m_handle, 0);
					native::set_entity_visible(attachment.m_handle, node.child("IsVisible").text().as_bool(), true);
					native::set_entity_visible(menu::player::get_local_player().m_ped, node.child("IsDriverVisible").text().as_bool(), false);

					int opacity_level = node.child("OpacityLevel").text().as_int();
					if (opacity_level < 255) native::set_entity_alpha(attachment.m_handle, opacity_level, 0);
					native::set_entity_lod_dist(attachment.m_handle, node.child("LodDistance").text().as_int());

					if (attachment.m_max_health) native::set_entity_max_health(attachment.m_handle, attachment.m_max_health);
					if (attachment.m_health) native::set_entity_health(attachment.m_handle, attachment.m_health);

					native::set_vehicle_gravity(attachment.m_handle, attachment.m_has_gravity);

					if (attachment.m_is_on_fire) {
						native::start_entity_fire(attachment.m_handle);
					}

					native::set_entity_invincible(attachment.m_handle, node.child("IsInvincible").text().as_bool());
					native::set_entity_proofs(attachment.m_handle, node.child("IsBulletProof").text().as_bool(), node.child("IsFireProof").text().as_bool(), node.child("IsExplosionProof").text().as_bool(), node.child("IsCollisionProof").text().as_bool(), node.child("IsMeleeProof").text().as_bool(), 1, 1, 1);
					native::set_entity_only_damaged_by_player(attachment.m_handle, node.child("IsOnlyDamagedByPlayer").text().as_bool());

					pugi::xml_node vehicle_properties = node.child("VehicleProperties");
					native::set_vehicle_livery(attachment.m_handle, vehicle_properties.child("Livery").text().as_int());

					pugi::xml_node vehicle_colors = vehicle_properties.child("Colours");

					int current_primary_color, current_secondary_color;
					native::get_vehicle_colours(attachment.m_handle, &current_primary_color, &current_secondary_color);
					native::set_vehicle_colours(attachment.m_handle, vehicle_colors.child("Primary").text().as_int(), current_secondary_color);
					native::get_vehicle_colours(attachment.m_handle, &current_primary_color, &current_secondary_color);
					native::set_vehicle_colours(attachment.m_handle, current_primary_color, vehicle_colors.child("Secondary").text().as_int());

					int current_pearlescent_color, current_wheel_color;
					native::get_vehicle_extra_colours(attachment.m_handle, &current_pearlescent_color, &current_wheel_color);
					native::set_vehicle_extra_colours(attachment.m_handle, vehicle_colors.child("Pearl").text().as_int(), current_wheel_color);
					native::get_vehicle_extra_colours(attachment.m_handle, &current_pearlescent_color, &current_wheel_color);
					native::set_vehicle_extra_colours(attachment.m_handle, current_pearlescent_color, vehicle_colors.child("Rim").text().as_int());

					bool is_primary_color_custom = vehicle_colors.child("IsPrimaryColourCustom").text().as_bool();
					bool is_secondary_color_custom = vehicle_colors.child("IsSecondaryColourCustom").text().as_bool();

					color_rgba vehicle_color;

					if (is_primary_color_custom) {
						vehicle_color.r = vehicle_colors.child("Cust1_R").text().as_int();
						vehicle_color.g = vehicle_colors.child("Cust1_G").text().as_int();
						vehicle_color.b = vehicle_colors.child("Cust1_B").text().as_int();
						native::set_vehicle_custom_primary_colour(attachment.m_handle, vehicle_color.r, vehicle_color.g, vehicle_color.b);
					}

					if (is_secondary_color_custom) {
						vehicle_color.r = vehicle_colors.child("Cust2_R").text().as_int();
						vehicle_color.g = vehicle_colors.child("Cust2_G").text().as_int();
						vehicle_color.b = vehicle_colors.child("Cust2_B").text().as_int();
						native::set_vehicle_custom_secondary_colour(attachment.m_handle, vehicle_color.r, vehicle_color.g, vehicle_color.b);
					}

					vehicle_color.r = vehicle_colors.child("tyreSmoke_R").text().as_int();
					vehicle_color.g = vehicle_colors.child("tyreSmoke_G").text().as_int();
					vehicle_color.b = vehicle_colors.child("tyreSmoke_B").text().as_int();
					native::set_vehicle_tyre_smoke_color(attachment.m_handle, vehicle_color.r, vehicle_color.g, vehicle_color.b);

					int mod1a = vehicle_colors.child("Mod1_a").text().as_int();
					int mod1b = vehicle_colors.child("Mod1_b").text().as_int();
					int mod1c = vehicle_colors.child("Mod1_c").text().as_int();
					native::set_vehicle_mod_color1(attachment.m_handle, mod1a, mod1b, mod1c);

					int mod2a = vehicle_colors.child("Mod2_a").text().as_int();
					int mod2b = vehicle_colors.child("Mod2_b").text().as_int();
					native::set_vehicle_mod_color2(attachment.m_handle, mod2a, mod2b);

					native::set_vehicle_number_plate_text(attachment.m_handle, (char*)vehicle_properties.child("NumberPlateText").text().as_string());
					native::set_vehicle_number_plate_text_index(attachment.m_handle, vehicle_properties.child("NumberPlateIndex").text().as_int());
					native::set_vehicle_wheel_type(attachment.m_handle, vehicle_properties.child("WheelType").text().as_int());

					native::set_vehicle_window_tint(attachment.m_handle, vehicle_properties.child("WindowTint").text().as_int());
					native::set_vehicle_tyres_can_burst(attachment.m_handle, !vehicle_properties.child("BulletProofTyres").text().as_bool());
					native::set_vehicle_dirt_level(attachment.m_handle, vehicle_properties.child("DirtLevel").text().as_float());
					native::set_vehicle_enveff_scale(attachment.m_handle, vehicle_properties.child("PaintFade").text().as_float());

					switch (vehicle_properties.child("RoofState").text().as_int()) {
						case 0:
						case 3:
							native::raise_convertible_roof(attachment.m_handle, false);
							break;
						case 2:
						case 1:
							native::lower_convertible_roof(attachment.m_handle, false);
							break;
					}

					native::set_vehicle_siren(attachment.m_handle, vehicle_properties.child("SirenActive").text().as_bool());

					if (vehicle_properties.child("EngineOn")) native::set_vehicle_engine_on(attachment.m_handle, vehicle_properties.child("EngineOn").text().as_bool(), true, 0);
					if (vehicle_properties.child("EngineHealth")) native::set_vehicle_engine_health(attachment.m_handle, vehicle_properties.child("EngineHealth").text().as_float());

					if (vehicle_properties.child("LightsOn")) native::set_vehicle_lights(attachment.m_handle, vehicle_properties.child("LightsOn").text().as_bool() ? 3 : 4);
					if (vehicle_properties.child("IsRadioLoud").text().as_int(0)) {
						native::set_vehicle_radio_loud(attachment.m_handle, vehicle_properties.child("IsRadioLoud").text().as_bool());
						native::set_vehicle_radio_enabled(attachment.m_handle, true);
					}

					native::set_vehicle_doors_locked(attachment.m_handle, vehicle_properties.child("LockStatus").text().as_bool());

					pugi::xml_node vehicle_neons = vehicle_properties.child("Neons");
					native::set_vehicle_neon_light_enabled(attachment.m_handle, 0, vehicle_neons.child("Left").text().as_bool());
					native::set_vehicle_neon_light_enabled(attachment.m_handle, 1, vehicle_neons.child("Right").text().as_bool());
					native::set_vehicle_neon_light_enabled(attachment.m_handle, 2, vehicle_neons.child("Front").text().as_bool());
					native::set_vehicle_neon_light_enabled(attachment.m_handle, 3, vehicle_neons.child("Back").text().as_bool());
					native::set_vehicle_neon_lights_colour(attachment.m_handle, vehicle_neons.child("R").text().as_int(), vehicle_neons.child("G").text().as_int(), vehicle_neons.child("B").text().as_int());

					for (pugi::xml_node node_vehicle_mod_extras_object = vehicle_properties.child("ModExtras").first_child(); node_vehicle_mod_extras_object; node_vehicle_mod_extras_object = node_vehicle_mod_extras_object.next_sibling()) {
						native::set_vehicle_extra(attachment.m_handle, std::stoi(std::string(node_vehicle_mod_extras_object.name()).substr(1)), !node_vehicle_mod_extras_object.text().as_bool());
					}

					for (pugi::xml_node node_vehicle_mods_object = vehicle_properties.child("Mods").first_child(); node_vehicle_mods_object; node_vehicle_mods_object = node_vehicle_mods_object.next_sibling()) {
						int mod_type = std::stoi(std::string(node_vehicle_mods_object.name()).substr(1));
						std::string mod_value_str = node_vehicle_mods_object.text().as_string();
						if (mod_value_str.find(",") == std::string::npos) {
							native::toggle_vehicle_mod(attachment.m_handle, mod_type, node_vehicle_mods_object.text().as_bool());
						} else {
							native::set_vehicle_mod(attachment.m_handle, mod_type, stoi(mod_value_str.substr(0, mod_value_str.find(","))), stoi(mod_value_str.substr(mod_value_str.find(",") + 1)) ? true : false);
						}
					}

					pugi::xml_node vehicle_doors_open = vehicle_properties.child("DoorsOpen");

					if (vehicle_doors_open) {
						if (vehicle_doors_open.child("BackLeftDoor").text().as_bool()) {
							native::set_vehicle_door_open(attachment.m_handle, 2, false, true);
							native::play_vehicle_door_open_sound(attachment.m_handle, 1);
						} else {
							native::set_vehicle_door_shut(attachment.m_handle, 2, true);
							native::play_vehicle_door_close_sound(attachment.m_handle, 1);
						}

						if (vehicle_doors_open.child("BackRightDoor").text().as_bool()) {
							native::set_vehicle_door_open(attachment.m_handle, 3, false, true);
							native::play_vehicle_door_open_sound(attachment.m_handle, 1);
						} else {
							native::set_vehicle_door_shut(attachment.m_handle, 3, true);
							native::play_vehicle_door_close_sound(attachment.m_handle, 1);
						}

						if (vehicle_doors_open.child("FrontLeftDoor").text().as_bool()) {
							native::set_vehicle_door_open(attachment.m_handle, 0, false, true);
							native::play_vehicle_door_open_sound(attachment.m_handle, 1);
						} else {
							native::set_vehicle_door_shut(attachment.m_handle, 0, true);
							native::play_vehicle_door_close_sound(attachment.m_handle, 1);
						}

						if (vehicle_doors_open.child("FrontRightDoor").text().as_bool()) {
							native::set_vehicle_door_open(attachment.m_handle, 1, false, true);
							native::play_vehicle_door_open_sound(attachment.m_handle, 1);
						} else {
							native::set_vehicle_door_shut(attachment.m_handle, 1, true);
							native::play_vehicle_door_close_sound(attachment.m_handle, 1);
						}

						if (vehicle_doors_open.child("Hood").text().as_bool()) {
							native::set_vehicle_door_open(attachment.m_handle, 4, false, true);
							native::play_vehicle_door_open_sound(attachment.m_handle, 1);
						} else {
							native::set_vehicle_door_shut(attachment.m_handle, 4, true);
							native::play_vehicle_door_close_sound(attachment.m_handle, 1);
						}

						if (vehicle_doors_open.child("Trunk").text().as_bool()) {
							native::set_vehicle_door_open(attachment.m_handle, 5, false, true);
							native::play_vehicle_door_open_sound(attachment.m_handle, 1);
						} else {
							native::set_vehicle_door_shut(attachment.m_handle, 5, true);
							native::play_vehicle_door_close_sound(attachment.m_handle, 1);
						}

						if (vehicle_doors_open.child("Trunk2").text().as_bool()) {
							native::set_vehicle_door_open(attachment.m_handle, 6, false, true);
							native::play_vehicle_door_open_sound(attachment.m_handle, 1);
						} else {
							native::set_vehicle_door_shut(attachment.m_handle, 6, true);
							native::play_vehicle_door_close_sound(attachment.m_handle, 1);
						}
					}

					pugi::xml_node vehicle_doors_broken = vehicle_properties.child("DoorsBroken");

					if (vehicle_doors_broken) {
						if (vehicle_doors_broken.child("BackLeftDoor").text().as_bool()) {
							native::set_vehicle_door_broken(attachment.m_handle, 2, true);
						}

						if (vehicle_doors_broken.child("BackRightDoor").text().as_bool()) {
							native::set_vehicle_door_broken(attachment.m_handle, 3, true);
						}

						if (vehicle_doors_broken.child("FrontLeftDoor").text().as_bool()) {
							native::set_vehicle_door_broken(attachment.m_handle, 0, true);
						}

						if (vehicle_doors_broken.child("FrontRightDoor").text().as_bool()) {
							native::set_vehicle_door_broken(attachment.m_handle, 1, true);
						}

						if (vehicle_doors_broken.child("Hood").text().as_bool()) {
							native::set_vehicle_door_broken(attachment.m_handle, 4, true);
						}

						if (vehicle_doors_broken.child("Trunk").text().as_bool()) {
							native::set_vehicle_door_broken(attachment.m_handle, 5, true);
						}

						if (vehicle_doors_broken.child("Trunk2").text().as_bool()) {
							native::set_vehicle_door_broken(attachment.m_handle, 6, true);
						}
					}

					pugi::xml_node vehicle_tyres_bursted = vehicle_properties.child("TyresBursted");

					if (vehicle_tyres_bursted) {
						if (vehicle_tyres_bursted.child("FrontLeft").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 0, 1, 1000.f);
						}

						if (vehicle_tyres_bursted.child("FrontRight").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 1, 1, 1000.f);
						}

						if (vehicle_tyres_bursted.child("_2").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 2, 1, 1000.f);
						}

						if (vehicle_tyres_bursted.child("_3").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 3, 1, 1000.f);
						}

						if (vehicle_tyres_bursted.child("BackLeft").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 4, 1, 1000.f);
						}

						if (vehicle_tyres_bursted.child("BackRight").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 5, 1, 1000.f);
						}

						if (vehicle_tyres_bursted.child("_6").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 6, 1, 1000.f);
						}

						if (vehicle_tyres_bursted.child("_7").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 7, 1, 1000.f);
						}

						if (vehicle_tyres_bursted.child("_8").text().as_bool()) {
							if (!native::get_vehicle_tyres_can_burst(attachment.m_handle)) native::set_vehicle_tyres_can_burst(attachment.m_handle, true);
							native::set_vehicle_tyre_burst(attachment.m_handle, 8, 1, 1000.f);
						}
					}

					pugi::xml_node vehicle_rpm_multiplier = vehicle_properties.child("RpmMultiplier");
					pugi::xml_node vehicle_torque_multiplier = vehicle_properties.child("TorqueMultiplier");
					pugi::xml_node vehicle_max_speed = vehicle_properties.child("MaxSpeed");
					pugi::xml_node vehicle_headlight_intensity = vehicle_properties.child("HeadlightIntensity");

					if (vehicle_rpm_multiplier) {
						native::set_vehicle_engine_power_multiplier(attachment.m_handle, vehicle_rpm_multiplier.text().as_float());
					}

					if (vehicle_torque_multiplier) {
						uint64_t address = rage::engine::get_entity_address(attachment.m_handle);
						if (address) {
							*(float*)(address + 0x1360) = vehicle_torque_multiplier.text().as_float();
						}
					}

					if (vehicle_max_speed) {
						native::set_entity_max_speed(attachment.m_handle, vehicle_max_speed.text().as_float());
					}

					if (vehicle_headlight_intensity) {
						native::set_vehicle_light_multiplier(attachment.m_handle, vehicle_headlight_intensity.text().as_float());
					}
				}

				break;
			}

			case 3: { // object
				attachment.m_handle = native::create_object(attachment.m_model_hash, attachment.placement.m_position.x, attachment.placement.m_position.y, attachment.placement.m_position.z, true, true, attachment.m_dynamic);
				if (native::does_entity_exist(attachment.m_handle)) {
					native::freeze_entity_position(attachment.m_handle, attachment.m_frozen_position);

					if (attachment.m_opacity_level < 255) native::set_entity_alpha(attachment.m_handle, attachment.m_opacity_level, 0);
					native::set_entity_lod_dist(attachment.m_handle, attachment.m_lod_distance);
					native::set_entity_visible(attachment.m_handle, attachment.m_is_visible, true);

					if (attachment.m_max_health) native::set_entity_max_health(attachment.m_handle, attachment.m_max_health);
					if (attachment.m_health) native::set_entity_health(attachment.m_handle, attachment.m_health);

					if (attachment.m_is_on_fire) {
						native::start_entity_fire(attachment.m_handle);
					}

					native::set_entity_invincible(attachment.m_handle, attachment.m_is_invincible);
					native::set_entity_proofs(attachment.m_handle, attachment.m_is_bullet_proof, attachment.m_is_fire_proof, attachment.m_is_explosion_proof, attachment.m_is_collision_proof, attachment.m_is_melee_proof, 1, 1, 1);
					native::set_entity_only_damaged_by_player(attachment.m_handle, attachment.m_is_only_damaged_by_player);
				}
				
				break;
			}
		}

		if (native::does_entity_exist(attachment.m_handle)) {
			native::network_register_entity_as_networked(attachment.m_handle);
		}

		m_vars.m_spawned_attachments.push_back(attachment.m_handle);
		return attachment;
	}

	void load_xml(std::string file) {
		spawner_vehicle_modded_menu* _this = spawner_vehicle_modded_menu::get();

		native::set_entity_visible(menu::player::get_local_player().m_ped, true, true);

		if (m_vars.m_delete_current) {
			for (Entity entity : m_vars.m_spawned_vehicles) {
				native::set_entity_as_mission_entity(entity, true, true);
				native::delete_entity(&entity);
			}

			for (Entity entity : m_vars.m_spawned_attachments) {
				native::set_entity_as_mission_entity(entity, true, true);
				native::delete_entity(&entity);
			}
		}

		m_vars.m_initial_handle = 0;
		m_vars.m_vehicle_handle = 0;

		pugi::xml_document doc;
		if (doc.load_file(util::va::va("%s%s.xml", util::dirs::get_path(modded_vehicles), file.c_str())).status != pugi::status_ok) {
			menu::notify::stacked(_this->get_name().get(), _this->get_string("Failed to load XML file!"));
			return;
		}

		pugi::xml_node root = doc.child("Vehicle");
		if (root) {
			uint32_t vehicle_hash = root.child("ModelHash").text().as_uint();
			m_vars.m_initial_handle = root.child("InitialHandle").text().as_int();
			menu::control::simple_request_model(vehicle_hash);

			math::vector3<float> forward = menu::player::get_local_player().m_coords + (native::get_entity_forward_vector(menu::player::get_local_player().m_entity) * 5.f);
			
			m_vars.m_vehicle_handle = native::create_vehicle(vehicle_hash, forward.x, forward.y, forward.z, menu::player::get_local_player().m_heading, true, true, false);
			if (!native::does_entity_exist(m_vars.m_vehicle_handle)) {
				menu::notify::stacked(_this->get_name().get(), _this->get_string("Failed to create XML vehicle!"));
				return;
			}

			m_vars.m_spawned_vehicles.push_back(m_vars.m_vehicle_handle);

			native::decor_set_int(m_vars.m_vehicle_handle, "MPBitset", (1 << 10));
			native::set_vehicle_is_stolen(m_vars.m_vehicle_handle, false);

			if (menu::player::get_local_player().m_in_vehicle) {
				native::set_entity_as_mission_entity(menu::player::get_local_player().m_vehicle, true, true);
				native::delete_entity(&menu::player::get_local_player().m_vehicle);
			}

			native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, m_vars.m_vehicle_handle, -1);
			native::set_vehicle_mod_kit(m_vars.m_vehicle_handle, 0);

			native::set_entity_visible(m_vars.m_vehicle_handle, root.child("IsVisible").text().as_bool(), true);
			native::set_entity_visible(menu::player::get_local_player().m_ped, root.child("IsDriverVisible").text().as_bool(), false);

			int opacity_level = root.child("OpacityLevel").text().as_int();
			if (opacity_level < 255) native::set_entity_alpha(m_vars.m_vehicle_handle, opacity_level, 0);
			native::set_entity_lod_dist(m_vars.m_vehicle_handle, root.child("LodDistance").text().as_int());

			if (root.child("MaxHealth")) native::set_entity_max_health(m_vars.m_vehicle_handle, root.child("MaxHealth").text().as_int());
			if (root.child("Health")) native::set_entity_health(m_vars.m_vehicle_handle, root.child("Health").text().as_int());

			native::set_vehicle_gravity(m_vars.m_vehicle_handle, root.child("HasGravity").text().as_bool(true));

			if (root.child("IsOnFire").text().as_bool()) {
				native::start_entity_fire(m_vars.m_vehicle_handle);
			}

			native::set_entity_invincible(m_vars.m_vehicle_handle, root.child("IsInvincible").text().as_bool());
			native::set_entity_proofs(m_vars.m_vehicle_handle, root.child("IsBulletProof").text().as_bool(), root.child("IsFireProof").text().as_bool(), root.child("IsExplosionProof").text().as_bool(), root.child("IsCollisionProof").text().as_bool(), root.child("IsMeleeProof").text().as_bool(), 1, 1, 1);
			native::set_entity_only_damaged_by_player(m_vars.m_vehicle_handle, root.child("IsOnlyDamagedByPlayer").text().as_bool());

			pugi::xml_node vehicle_properties = root.child("VehicleProperties");
			native::set_vehicle_livery(m_vars.m_vehicle_handle, vehicle_properties.child("Livery").text().as_int());

			pugi::xml_node vehicle_colors = vehicle_properties.child("Colours");

			int current_primary_color, current_secondary_color;
			native::get_vehicle_colours(m_vars.m_vehicle_handle, &current_primary_color, &current_secondary_color);
			native::set_vehicle_colours(m_vars.m_vehicle_handle, vehicle_colors.child("Primary").text().as_int(), current_secondary_color);
			native::get_vehicle_colours(m_vars.m_vehicle_handle, &current_primary_color, &current_secondary_color);
			native::set_vehicle_colours(m_vars.m_vehicle_handle, current_primary_color, vehicle_colors.child("Secondary").text().as_int());

			int current_pearlescent_color, current_wheel_color;
			native::get_vehicle_extra_colours(m_vars.m_vehicle_handle, &current_pearlescent_color, &current_wheel_color);
			native::set_vehicle_extra_colours(m_vars.m_vehicle_handle, vehicle_colors.child("Pearl").text().as_int(), current_wheel_color);
			native::get_vehicle_extra_colours(m_vars.m_vehicle_handle, &current_pearlescent_color, &current_wheel_color);
			native::set_vehicle_extra_colours(m_vars.m_vehicle_handle, current_pearlescent_color, vehicle_colors.child("Rim").text().as_int());

			bool is_primary_color_custom = vehicle_colors.child("IsPrimaryColourCustom").text().as_bool();
			bool is_secondary_color_custom = vehicle_colors.child("IsSecondaryColourCustom").text().as_bool();

			color_rgba vehicle_color;

			if (is_primary_color_custom) {
				vehicle_color.r = vehicle_colors.child("Cust1_R").text().as_int();
				vehicle_color.g = vehicle_colors.child("Cust1_G").text().as_int();
				vehicle_color.b = vehicle_colors.child("Cust1_B").text().as_int();
				native::set_vehicle_custom_primary_colour(m_vars.m_vehicle_handle, vehicle_color.r, vehicle_color.g, vehicle_color.b);
			}

			if (is_secondary_color_custom) {
				vehicle_color.r = vehicle_colors.child("Cust2_R").text().as_int();
				vehicle_color.g = vehicle_colors.child("Cust2_G").text().as_int();
				vehicle_color.b = vehicle_colors.child("Cust2_B").text().as_int();
				native::set_vehicle_custom_secondary_colour(m_vars.m_vehicle_handle, vehicle_color.r, vehicle_color.g, vehicle_color.b);
			}

			vehicle_color.r = vehicle_colors.child("tyreSmoke_R").text().as_int();
			vehicle_color.g = vehicle_colors.child("tyreSmoke_G").text().as_int();
			vehicle_color.b = vehicle_colors.child("tyreSmoke_B").text().as_int();
			native::set_vehicle_tyre_smoke_color(m_vars.m_vehicle_handle, vehicle_color.r, vehicle_color.g, vehicle_color.b);

			int mod1a = vehicle_colors.child("Mod1_a").text().as_int();
			int mod1b = vehicle_colors.child("Mod1_b").text().as_int();
			int mod1c = vehicle_colors.child("Mod1_c").text().as_int();
			native::set_vehicle_mod_color1(m_vars.m_vehicle_handle, mod1a, mod1b, mod1c);

			int mod2a = vehicle_colors.child("Mod2_a").text().as_int();
			int mod2b = vehicle_colors.child("Mod2_b").text().as_int();
			native::set_vehicle_mod_color2(m_vars.m_vehicle_handle, mod2a, mod2b);

			native::set_vehicle_number_plate_text(m_vars.m_vehicle_handle, (char*)vehicle_properties.child("NumberPlateText").text().as_string());
			native::set_vehicle_number_plate_text_index(m_vars.m_vehicle_handle, vehicle_properties.child("NumberPlateIndex").text().as_int());
			native::set_vehicle_wheel_type(m_vars.m_vehicle_handle, vehicle_properties.child("WheelType").text().as_int());

			native::set_vehicle_window_tint(m_vars.m_vehicle_handle, vehicle_properties.child("WindowTint").text().as_int());
			native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, !vehicle_properties.child("BulletProofTyres").text().as_bool());
			native::set_vehicle_dirt_level(m_vars.m_vehicle_handle, vehicle_properties.child("DirtLevel").text().as_float());
			native::set_vehicle_enveff_scale(m_vars.m_vehicle_handle, vehicle_properties.child("PaintFade").text().as_float());

			switch (vehicle_properties.child("RoofState").text().as_int()) {
				case 0:
				case 3:
					native::raise_convertible_roof(m_vars.m_vehicle_handle, false);
					break;
				case 2:
				case 1:
					native::lower_convertible_roof(m_vars.m_vehicle_handle, false);
					break;
			}

			native::set_vehicle_siren(m_vars.m_vehicle_handle, vehicle_properties.child("SirenActive").text().as_bool());

			if (vehicle_properties.child("EngineOn")) native::set_vehicle_engine_on(m_vars.m_vehicle_handle, vehicle_properties.child("EngineOn").text().as_bool(), true, 0);
			if (vehicle_properties.child("EngineHealth")) native::set_vehicle_engine_health(m_vars.m_vehicle_handle, vehicle_properties.child("EngineHealth").text().as_float());

			if (vehicle_properties.child("LightsOn")) native::set_vehicle_lights(m_vars.m_vehicle_handle, vehicle_properties.child("LightsOn").text().as_bool() ? 3 : 4);
			if (vehicle_properties.child("IsRadioLoud").text().as_int(0)) {
				native::set_vehicle_radio_loud(m_vars.m_vehicle_handle, vehicle_properties.child("IsRadioLoud").text().as_bool());
				native::set_vehicle_radio_enabled(m_vars.m_vehicle_handle, true);
			}

			native::set_vehicle_doors_locked(m_vars.m_vehicle_handle, vehicle_properties.child("LockStatus").text().as_bool());

			pugi::xml_node vehicle_neons = vehicle_properties.child("Neons");
			native::set_vehicle_neon_light_enabled(m_vars.m_vehicle_handle, 0, vehicle_neons.child("Left").text().as_bool());
			native::set_vehicle_neon_light_enabled(m_vars.m_vehicle_handle, 1, vehicle_neons.child("Right").text().as_bool());
			native::set_vehicle_neon_light_enabled(m_vars.m_vehicle_handle, 2, vehicle_neons.child("Front").text().as_bool());
			native::set_vehicle_neon_light_enabled(m_vars.m_vehicle_handle, 3, vehicle_neons.child("Back").text().as_bool());
			native::set_vehicle_neon_lights_colour(m_vars.m_vehicle_handle, vehicle_neons.child("R").text().as_int(), vehicle_neons.child("G").text().as_int(), vehicle_neons.child("B").text().as_int());

			for (pugi::xml_node node_vehicle_mod_extras_object = vehicle_properties.child("ModExtras").first_child(); node_vehicle_mod_extras_object; node_vehicle_mod_extras_object = node_vehicle_mod_extras_object.next_sibling()) {
				native::set_vehicle_extra(m_vars.m_vehicle_handle, std::stoi(std::string(node_vehicle_mod_extras_object.name()).substr(1)), !node_vehicle_mod_extras_object.text().as_bool());
			}

			for (pugi::xml_node node_vehicle_mods_object = vehicle_properties.child("Mods").first_child(); node_vehicle_mods_object; node_vehicle_mods_object = node_vehicle_mods_object.next_sibling()) {
				int mod_type = std::stoi(std::string(node_vehicle_mods_object.name()).substr(1));
				std::string mod_value_str = node_vehicle_mods_object.text().as_string();
				if (mod_value_str.find(",") == std::string::npos) {
					native::toggle_vehicle_mod(m_vars.m_vehicle_handle, mod_type, node_vehicle_mods_object.text().as_bool());
				} else {
					native::set_vehicle_mod(m_vars.m_vehicle_handle, mod_type, stoi(mod_value_str.substr(0, mod_value_str.find(","))), stoi(mod_value_str.substr(mod_value_str.find(",") + 1)) ? true : false);
				}
			}

			pugi::xml_node vehicle_doors_open = vehicle_properties.child("DoorsOpen");

			if (vehicle_doors_open) {
				if (vehicle_doors_open.child("BackLeftDoor").text().as_bool()) {
					native::set_vehicle_door_open(m_vars.m_vehicle_handle, 2, false, true);
					native::play_vehicle_door_open_sound(m_vars.m_vehicle_handle, 1);
				} else {
					native::set_vehicle_door_shut(m_vars.m_vehicle_handle, 2, true);
					native::play_vehicle_door_close_sound(m_vars.m_vehicle_handle, 1);
				}

				if (vehicle_doors_open.child("BackRightDoor").text().as_bool()) {
					native::set_vehicle_door_open(m_vars.m_vehicle_handle, 3, false, true);
					native::play_vehicle_door_open_sound(m_vars.m_vehicle_handle, 1);
				} else {
					native::set_vehicle_door_shut(m_vars.m_vehicle_handle, 3, true);
					native::play_vehicle_door_close_sound(m_vars.m_vehicle_handle, 1);
				}

				if (vehicle_doors_open.child("FrontLeftDoor").text().as_bool()) {
					native::set_vehicle_door_open(m_vars.m_vehicle_handle, 0, false, true);
					native::play_vehicle_door_open_sound(m_vars.m_vehicle_handle, 1);
				} else {
					native::set_vehicle_door_shut(m_vars.m_vehicle_handle, 0, true);
					native::play_vehicle_door_close_sound(m_vars.m_vehicle_handle, 1);
				}

				if (vehicle_doors_open.child("FrontRightDoor").text().as_bool()) {
					native::set_vehicle_door_open(m_vars.m_vehicle_handle, 1, false, true);
					native::play_vehicle_door_open_sound(m_vars.m_vehicle_handle, 1);
				} else {
					native::set_vehicle_door_shut(m_vars.m_vehicle_handle, 1, true);
					native::play_vehicle_door_close_sound(m_vars.m_vehicle_handle, 1);
				}

				if (vehicle_doors_open.child("Hood").text().as_bool()) {
					native::set_vehicle_door_open(m_vars.m_vehicle_handle, 4, false, true);
					native::play_vehicle_door_open_sound(m_vars.m_vehicle_handle, 1);
				} else {
					native::set_vehicle_door_shut(m_vars.m_vehicle_handle, 4, true);
					native::play_vehicle_door_close_sound(m_vars.m_vehicle_handle, 1);
				}

				if (vehicle_doors_open.child("Trunk").text().as_bool()) {
					native::set_vehicle_door_open(m_vars.m_vehicle_handle, 5, false, true);
					native::play_vehicle_door_open_sound(m_vars.m_vehicle_handle, 1);
				} else {
					native::set_vehicle_door_shut(m_vars.m_vehicle_handle, 5, true);
					native::play_vehicle_door_close_sound(m_vars.m_vehicle_handle, 1);
				}

				if (vehicle_doors_open.child("Trunk2").text().as_bool()) {
					native::set_vehicle_door_open(m_vars.m_vehicle_handle, 6, false, true);
					native::play_vehicle_door_open_sound(m_vars.m_vehicle_handle, 1);
				} else {
					native::set_vehicle_door_shut(m_vars.m_vehicle_handle, 6, true);
					native::play_vehicle_door_close_sound(m_vars.m_vehicle_handle, 1);
				}
			}

			pugi::xml_node vehicle_doors_broken = vehicle_properties.child("DoorsBroken");

			if (vehicle_doors_broken) {
				if (vehicle_doors_broken.child("BackLeftDoor").text().as_bool()) {
					native::set_vehicle_door_broken(m_vars.m_vehicle_handle, 2, true);
				}

				if (vehicle_doors_broken.child("BackRightDoor").text().as_bool()) {
					native::set_vehicle_door_broken(m_vars.m_vehicle_handle, 3, true);
				}

				if (vehicle_doors_broken.child("FrontLeftDoor").text().as_bool()) {
					native::set_vehicle_door_broken(m_vars.m_vehicle_handle, 0, true);
				}

				if (vehicle_doors_broken.child("FrontRightDoor").text().as_bool()) {
					native::set_vehicle_door_broken(m_vars.m_vehicle_handle, 1, true);
				}

				if (vehicle_doors_broken.child("Hood").text().as_bool()) {
					native::set_vehicle_door_broken(m_vars.m_vehicle_handle, 4, true);
				}

				if (vehicle_doors_broken.child("Trunk").text().as_bool()) {
					native::set_vehicle_door_broken(m_vars.m_vehicle_handle, 5, true);
				}

				if (vehicle_doors_broken.child("Trunk2").text().as_bool()) {
					native::set_vehicle_door_broken(m_vars.m_vehicle_handle, 6, true);
				}
			}

			pugi::xml_node vehicle_tyres_bursted = vehicle_properties.child("TyresBursted");

			if (vehicle_tyres_bursted) {
				if (vehicle_tyres_bursted.child("FrontLeft").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 0, 1, 1000.f);
				}

				if (vehicle_tyres_bursted.child("FrontRight").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 1, 1, 1000.f);
				}

				if (vehicle_tyres_bursted.child("_2").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 2, 1, 1000.f);
				}

				if (vehicle_tyres_bursted.child("_3").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 3, 1, 1000.f);
				}

				if (vehicle_tyres_bursted.child("BackLeft").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 4, 1, 1000.f);
				}

				if (vehicle_tyres_bursted.child("BackRight").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 5, 1, 1000.f);
				}

				if (vehicle_tyres_bursted.child("_6").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 6, 1, 1000.f);
				}

				if (vehicle_tyres_bursted.child("_7").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 7, 1, 1000.f);
				}

				if (vehicle_tyres_bursted.child("_8").text().as_bool()) {
					if (!native::get_vehicle_tyres_can_burst(m_vars.m_vehicle_handle)) native::set_vehicle_tyres_can_burst(m_vars.m_vehicle_handle, true);
					native::set_vehicle_tyre_burst(m_vars.m_vehicle_handle, 8, 1, 1000.f);
				}
			}

			pugi::xml_node vehicle_rpm_multiplier = vehicle_properties.child("RpmMultiplier");
			pugi::xml_node vehicle_torque_multiplier = vehicle_properties.child("TorqueMultiplier");
			pugi::xml_node vehicle_max_speed = vehicle_properties.child("MaxSpeed");
			pugi::xml_node vehicle_headlight_intensity = vehicle_properties.child("HeadlightIntensity");

			if (vehicle_rpm_multiplier) {
				native::set_vehicle_engine_power_multiplier(m_vars.m_vehicle_handle, vehicle_rpm_multiplier.text().as_float());
			}

			if (vehicle_torque_multiplier) {
				uint64_t address = rage::engine::get_entity_address(m_vars.m_vehicle_handle);
				if (address) {
					*(float*)(address + 0x1360) = vehicle_torque_multiplier.text().as_float();
				}
			}

			if (vehicle_max_speed) {
				native::set_entity_max_speed(m_vars.m_vehicle_handle, vehicle_max_speed.text().as_float());
			}

			if (vehicle_headlight_intensity) {
				native::set_vehicle_light_multiplier(m_vars.m_vehicle_handle, vehicle_headlight_intensity.text().as_float());
			}
		} else {
			menu::notify::stacked(_this->get_name().get(), _this->get_string("Failed to load XML file! Invalid formatting!"));
			return;
		}

		util::fiber::sleep(100);

		pugi::xml_node attachments = root.child("SpoonerAttachments");
		if (attachments) {
			std::vector<uint32_t> used_models;
			std::vector<xml_attachment> attachment_list;

			for (pugi::xml_node node_attachment = attachments.first_child(); node_attachment; node_attachment = node_attachment.next_sibling()) {
				menu::control::simple_request_model(node_attachment.child("ModelHash").text().as_uint());
				if (node_attachment.child("Type").text().as_int() == 1) { // ped
					if (node_attachment.child("PedProperties").child("AnimActive").text().as_bool()) {
						native::request_anim_dict((char*)node_attachment.child("PedProperties").child("AnimDict").text().as_string());
					}
				}

				used_models.push_back(node_attachment.child("ModelHash").text().as_uint());
			}

			for (pugi::xml_node node_attachment = attachments.first_child(); node_attachment; node_attachment = node_attachment.next_sibling()) {
				util::fiber::sleep(10);
				attachment_list.push_back(create_entity(node_attachment));
			}

			if (!m_vars.m_initial_handle) {
				for (xml_attachment e : attachment_list) {
					native::attach_entity_to_entity(e.m_handle, m_vars.m_vehicle_handle, e.attachment.m_bone_index, e.attachment.m_position.x, e.attachment.m_position.y, e.attachment.m_position.z, e.attachment.m_rotation.x, e.attachment.m_rotation.y, e.attachment.m_rotation.z, 1, 0, m_vars.m_use_collision, 1, 2, 1);
				}
			} else {
				xml_attachment temp;
				temp.m_handle = m_vars.m_vehicle_handle;
				temp.m_initial_handle = m_vars.m_initial_handle;
				attachment_list.push_back(temp);

				for (xml_attachment e : attachment_list) {
					if (e.attachment.m_is_attached) {
						for (xml_attachment b : attachment_list) {
							if (e.m_handle != b.m_handle && e.attachment.m_attached_to == b.m_initial_handle) {
								native::attach_entity_to_entity(e.m_handle, b.m_handle, e.attachment.m_bone_index, e.attachment.m_position.x, e.attachment.m_position.y, e.attachment.m_position.z, e.attachment.m_rotation.x, e.attachment.m_rotation.y, e.attachment.m_rotation.z, 1, 0, m_vars.m_use_collision, 1, 2, 1);
								break;
							}
						}
					}
				}
			}

			for (uint32_t e : used_models) {
				native::set_model_as_no_longer_needed(e);
			}

			for (xml_attachment e : attachment_list) {
				native::set_entity_as_no_longer_needed(&e.m_handle);
			}
		}


	}
}

void spawner_vehicle_modded_menu::load() {
	set_name("Modded Vehicles");
	set_parent<spawner_menu>();

	add_option(toggle_option("Delete Current")
		.add_translate()
		.add_toggle(m_vars.m_delete_current));

	add_option(toggle_option("Use Collision")
		.add_translate()
		.add_toggle(m_vars.m_use_collision));

	add_option(break_option("Vehicles")
		.add_translate());

	add_string("Failed to load XML file!");
	add_string("Failed to create XML vehicle!");
	add_string("Failed to load XML file! Invalid formatting!");
}

void spawner_vehicle_modded_menu::update() {}

void spawner_vehicle_modded_menu::update_once() {
	clear_options(3);

	for (std::string file : util::dirs::get_files_in_directory(util::dirs::get_path(modded_vehicles), ".xml")) {
		add_option(button_option(file)
			.add_click([=] { load_xml(file); }));
	}
}

void spawner_vehicle_modded_menu::feature_update() {}

spawner_vehicle_modded_menu* g_instance;
spawner_vehicle_modded_menu* spawner_vehicle_modded_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_vehicle_modded_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}