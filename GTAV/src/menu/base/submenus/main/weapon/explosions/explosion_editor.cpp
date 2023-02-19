#include "explosion_editor.h"
#include "menu/base/submenu_handler.h"
#include "../weapon_mods.h"

using namespace weapon::explosion::editor::vars;

namespace weapon::explosion::editor::vars {
	variables m_vars;

	scroll_struct<int> explosion_names[83];

	scroll_struct<uint32_t> explosion_fx_list[] = {
		{ localization("GRENADE", true), 0x8CBD7381 },
		{ localization("GRENADELAUNCHER", true), 0x8CBD7381 },
		{ localization("STICKYBOMB", true), 0x6818372E },
		{ localization("MOLOTOV", true), 0x289C84AB },
		{ localization("ROCKET", true), 0xC18A7083 },
		{ localization("TANKSHELL", true), 0xC6109DA9 },
		{ localization("HI_OCTANE", true), 0xC18A7083 },
		{ localization("CAR", true), 0x1FDD8CC7 },
		{ localization("PLANE", true), 0x174DDF67 },
		{ localization("PETROL_PUMP", true), 0x5C685140 },
		{ localization("BIKE", true), 0x2E89B6C6 },
		{ localization("DIR_STEAM", true), 0xB096860 },
		{ localization("DIR_FLAME", true), 0x61BEF304 },
		{ localization("DIR_WATER_HYDRANT", true), 0xC9E6266C },
		{ localization("DIR_GAS_CANISTER", true), 0xDCD1237B },
		{ localization("BOAT", true), 0x9AE5CE85 },
		{ localization("SHIP_DESTROY", true), 0xC18A7083 },
		{ localization("TRUCK", true), 0x272C2A1C },
		{ localization("BULLET", true), 0x4A602D1B },
		{ localization("SMOKEGRENADELAUNCHER", true), 0x1B171B0A },
		{ localization("SMOKEGRENADE", true), 0xC36F9FF4 },
		{ localization("BZGAS", true), 0xC36F9FF4 },
		{ localization("FLARE", true), 0x4DFE55EF },
		{ localization("GAS_CANISTER", true), 0x531AE6D7 },
		{ localization("EXTINGUISHER", true), 0x3C212E68 },
		{ localization("PROGRAMMABLEAR", true), 0x4A602D1B },
		{ localization("TRAIN", true), 0x7DF5D791 },
		{ localization("BARREL", true), 0x26A49BC },
		{ localization("PROPANE", true), 0x2A8D8114 },
		{ localization("BLIMP", true), 0xBA683EF5 },
		{ localization("DIR_FLAME_EXPLODE", true), 0x61BEF304 },
		{ localization("TANKER", true), 0x6136E279 },
		{ localization("PLANE_ROCKET", true), 0x549AE743 },
		{ localization("VEHICLE_BULLET", true), 0x4A602D1B },
		{ localization("GAS_TANK", true), 0x2A8D8114 },
		{ localization("BIRD_CRAP", true), 0x8B716982 },
		{ localization("RAILGUN", true), 0x4A602D1B },
		{ localization("BLIMP2", true), 0x9077376B },
		{ localization("FIREWORK", true), 0x1499FEF9 },
		{ localization("SNOWBALL", true), 0x4B0245BA },
		{ localization("PROXMINE", true), 0x6818372E },
		{ localization("VALKYRIE_CANNON", true), 0x8CBD7381 },
		{ localization("AIR_DEFENCE", true), 0x3C84F30B },
		{ localization("PIPEBOMB", true), 0x2E3BC2D6 },
		{ localization("VEHICLEMINE", true), 0x8CBD7381 },
		{ localization("EXPLOSIVEAMMO", true), 0x4A602D1B },
		{ localization("APCSHELL", true), 0xC6109DA9 },
		{ localization("BOMB_CLUSTER", true), 0x7007891E },
		{ localization("BOMB_GAS", true), 0xAD0A7E5D },
		{ localization("BOMB_INCENDIARY", true), 0x62F8744D },
		{ localization("BOMB_STANDARD", true), 0x30A5254A },
		{ localization("TORPEDO", true), 0xC18A7083 },
		{ localization("TORPEDO_UNDERWATER", true), 0x8D16EE2E },
		{ localization("BOMBUSHKA_CANNON", true), 0x8CBD7381 },
		{ localization("BOMB_CLUSTER_SECONDARY", true), 0x8CBD7381 },
		{ localization("HUNTER_BARRAGE", true), 0x549AE743 },
		{ localization("HUNTER_CANNON", true), 0x8CBD7381 },
		{ localization("ROGUE_CANNON", true), 0x2E3BC2D6 },
		{ localization("MINE_UNDERWATER", true), 0x4F7CD2DC },
		{ localization("ORBITAL_CANNON", true), 0x0 },
		{ localization("BOMB_STANDARD_WIDE", true), 0x30A5254A },
		{ localization("EXPLOSIVEAMMO_SHOTGUN", true), 0x4A602D1B },
		{ localization("OPPRESSOR2_CANNON", true), 0x3C4CCAAB },
		{ localization("MORTAR_KINETIC", true), 0x996D8865 },
		{ localization("VEHICLEMINE_KINETIC", true), 0xD0CB2C03 },
		{ localization("VEHICLEMINE_EMP", true), 0xEEC9E329 },
		{ localization("VEHICLEMINE_SPIKE", true), 0xD1C5557C },
		{ localization("VEHICLEMINE_SLICK", true), 0x98BC33A3 },
		{ localization("VEHICLEMINE_TAR", true), 0x1325B17C },
		{ localization("SCRIPT_DRONE", true), 0x8CBD7381 },
		{ localization("RAYGUN", true), 0x86AD156C },
		{ localization("BURIEDMINE", true), 0x25A8CEBF },
		{ localization("SCRIPT_MISSILE", true), 0xC18A7083 },
		{ localization("RCTANK_ROCKET", true), 0x26CB9D76 },
		{ localization("BOMB_WATER", true), 0xC612E8E3 },
		{ localization("BOMB_WATER_SECONDARY", true), 0xC612E8E3 },
		{ localization("EXTINGUISHER", true), 0x3C212E68 },
		{ localization("EXTINGUISHER", true), 0x3C212E68 },
		{ localization("EXTINGUISHER", true), 0x3C212E68 },
		{ localization("EXTINGUISHER", true), 0x3C212E68 },
		{ localization("EXTINGUISHER", true), 0x3C212E68 },
		{ localization("SCRIPT_MISSILE_LARGE", true), 0xC18A7083 },
		{ localization("SUBMARINE_BIG", true), 0x32775176 },
	};

	rage::types::explosion_data* get_explosion(uint32_t explosion_hash) {
		for (std::size_t i = 0; i < 83; i++) {
			rage::types::explosion_data* explosion = &global::vars::g_explosion_data[i];
			if (native::get_hash_key(explosion->m_explosion_name) == explosion_hash) {
				return explosion;
			}
		}

		return nullptr;
	}

	rage::types::explosion_fx* get_explosion_fx(uint32_t hash) {
		for (std::size_t i = 0; i < 53; i++) {
			rage::types::explosion_fx* fx = &global::vars::g_explosion_fx[i];
			if (fx->m_name_hash == hash) {
				return fx;
			}
		}

		return nullptr;
	}

	std::size_t get_explosion_fx_entry(uint32_t hash) {
		for (std::size_t i = 0; i < NUMOF(explosion_fx_list); i++) {
			if (explosion_fx_list[i].m_result == hash) {
				return i;
			}
		}

		return 0;
	}

	void update_editor() {
		if (explosion_names[0].m_result != 1337) {
			for (std::size_t i = 0; i < NUMOF(explosion_names); i++) {
				rage::types::explosion_data* explosion = &global::vars::g_explosion_data[i];
				explosion_names[i].m_name.set(native::get_text_substring_slice(explosion->m_explosion_name, 8, (int)strlen(explosion->m_explosion_name)));
				explosion_names[i].m_result = 1337;
			}
		}

		m_vars.m_explosion_data_ptr = &global::vars::g_explosion_data[m_vars.m_selected_explosion];
		memcpy(&m_vars.m_explosion_data, m_vars.m_explosion_data_ptr, sizeof(rage::types::explosion_data));

		m_vars.m_selected_fx = (int)get_explosion_fx_entry(m_vars.m_explosion_data_ptr->m_vfx_tag_name_hash);

		m_vars.m_explosion_fx_ptr = get_explosion_fx(m_vars.m_explosion_data_ptr->m_vfx_tag_name_hash);
		if (m_vars.m_explosion_fx_ptr) {
			memcpy(&m_vars.m_explosion_fx, m_vars.m_explosion_fx_ptr, sizeof(rage::types::explosion_fx));
		}
	}
}

void explosion_editor_menu::load() {
	set_name("Explosion Editor");
	set_parent<weapon_mods_menu>();

	add_option(scroll_option<int>(SCROLL, "Explosion")
		.add_translate()
		.add_scroll(m_vars.m_selected_explosion, 0, NUMOF(explosion_names), explosion_names)
		.add_click(update_editor));

	add_option(scroll_option<uint32_t>(SCROLL, "FX")
		.add_translate()
		.add_scroll(m_vars.m_selected_fx, 0, NUMOF(explosion_fx_list), explosion_fx_list)
		.add_click([] { m_vars.m_explosion_data_ptr->m_vfx_tag_name_hash = explosion_fx_list[m_vars.m_selected_fx].m_result; }));

	add_option(number_option<float>(SCROLL, "FX Scale")
		.add_translate()
		.add_number(m_vars.m_explosion_fx.m_scale, "%.1f", 0.1f).add_min(-1.f).add_max(100.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_fx_ptr->m_scale = m_vars.m_explosion_fx.m_scale; })
		.add_requirement([] { return m_vars.m_explosion_fx_ptr != nullptr; }));

	add_option(number_option<float>(SCROLL, "Center Damage")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_damage_at_centre, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_damage_at_centre = m_vars.m_explosion_data.m_damage_at_centre; }));

	add_option(number_option<float>(SCROLL, "Edge Damage")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_damage_at_edge, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_damage_at_edge = m_vars.m_explosion_data.m_damage_at_edge; }));

	add_option(number_option<float>(SCROLL, "Network Player Modifier")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_network_player_modifier, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_network_player_modifier = m_vars.m_explosion_data.m_network_player_modifier; }));

	add_option(number_option<float>(SCROLL, "Network Ped Modifier")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_network_ped_modifier, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_network_ped_modifier = m_vars.m_explosion_data.m_network_ped_modifier; }));

	add_option(number_option<float>(SCROLL, "End Radius")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_end_radius, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_end_radius = m_vars.m_explosion_data.m_end_radius; }));

	add_option(number_option<float>(SCROLL, "Init Speed")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_init_speed, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_init_speed = m_vars.m_explosion_data.m_init_speed; }));

	add_option(number_option<float>(SCROLL, "Decay Factor")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_decay_factor, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_decay_factor = m_vars.m_explosion_data.m_decay_factor; }));

	add_option(number_option<float>(SCROLL, "Force Factor")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_force_factor, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_force_factor = m_vars.m_explosion_data.m_force_factor; }));

	add_option(number_option<float>(SCROLL, "Ragdoll Force Modifier")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_ragdoll_force_modifier, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_ragdoll_force_modifier = m_vars.m_explosion_data.m_ragdoll_force_modifier; }));

	add_option(number_option<float>(SCROLL, "Self Force Modifier")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_self_force_modifier, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_self_force_modifier = m_vars.m_explosion_data.m_self_force_modifier; }));

	add_option(number_option<float>(SCROLL, "Directed Width")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_directed_width, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_directed_width = m_vars.m_explosion_data.m_directed_width; }));

	add_option(number_option<float>(SCROLL, "Directed Lifetime")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_directed_lifetime, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_directed_lifetime = m_vars.m_explosion_data.m_directed_lifetime; }));

	add_option(number_option<float>(SCROLL, "Cam Shake")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_cam_shake, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_cam_shake = m_vars.m_explosion_data.m_cam_shake; }));

	add_option(number_option<float>(SCROLL, "Cam Shake Rolloff Scaling")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_cam_shake_roll_off_scaling, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_cam_shake_roll_off_scaling = m_vars.m_explosion_data.m_cam_shake_roll_off_scaling; }));

	add_option(number_option<float>(SCROLL, "Shocking Event Visual Range")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_shocking_event_visual_range_override, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_shocking_event_visual_range_override = m_vars.m_explosion_data.m_shocking_event_visual_range_override; }));

	add_option(number_option<float>(SCROLL, "Shocking Event Audio Range")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_shocking_event_audio_range_override, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_shocking_event_audio_range_override = m_vars.m_explosion_data.m_shocking_event_audio_range_override; }));

	add_option(number_option<float>(SCROLL, "Frag Damage")
		.add_translate()
		.add_number(m_vars.m_explosion_data.m_frag_damage, "%.1f", 0.1f).add_min(-1.f).add_max(10000.f).set_scroll_speed(10)
		.add_click([] { m_vars.m_explosion_data_ptr->m_frag_damage = m_vars.m_explosion_data.m_frag_damage; }));

	add_option(toggle_option("Minor Explosion")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_minor_explosion)
		.add_click([] { m_vars.m_explosion_data_ptr->m_minor_explosion = m_vars.m_explosion_data.m_minor_explosion; }));

	add_option(toggle_option("Applies Continuous Damage")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_applies_continuous_damage)
		.add_click([] { m_vars.m_explosion_data_ptr->m_applies_continuous_damage = m_vars.m_explosion_data.m_applies_continuous_damage; }));

	add_option(toggle_option("Post Process Collisions")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_post_process_collisions_with_no_force)
		.add_click([] { m_vars.m_explosion_data_ptr->m_post_process_collisions_with_no_force = m_vars.m_explosion_data.m_post_process_collisions_with_no_force; }));

	add_option(toggle_option("Damage Vehicles")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_damage_vehicles)
		.add_click([] { m_vars.m_explosion_data_ptr->m_damage_vehicles = m_vars.m_explosion_data.m_damage_vehicles; }));

	add_option(toggle_option("Damage Objects")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_damage_objects)
		.add_click([] { m_vars.m_explosion_data_ptr->m_damage_objects = m_vars.m_explosion_data.m_damage_objects; }));

	add_option(toggle_option("Only Affect Living Peds")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_only_affects_live_peds)
		.add_click([] { m_vars.m_explosion_data_ptr->m_only_affects_live_peds = m_vars.m_explosion_data.m_only_affects_live_peds; }));

	add_option(toggle_option("Ignore Exploding Entity")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_ignore_exploding_entity)
		.add_click([] { m_vars.m_explosion_data_ptr->m_ignore_exploding_entity = m_vars.m_explosion_data.m_ignore_exploding_entity; }));

	add_option(toggle_option("No Occlusion")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_no_occlusion)
		.add_click([] { m_vars.m_explosion_data_ptr->m_no_occlusion = m_vars.m_explosion_data.m_no_occlusion; }));

	add_option(toggle_option("Explode Attach When Finished")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_explode_attach_entity_when_finished)
		.add_click([] { m_vars.m_explosion_data_ptr->m_explode_attach_entity_when_finished = m_vars.m_explosion_data.m_explode_attach_entity_when_finished; }));

	add_option(toggle_option("Can Set Ped On Fire")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_can_set_ped_on_fire)
		.add_click([] { m_vars.m_explosion_data_ptr->m_can_set_ped_on_fire = m_vars.m_explosion_data.m_can_set_ped_on_fire; }));

	add_option(toggle_option("Can Set Player On Fire")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_can_set_player_on_fire)
		.add_click([] { m_vars.m_explosion_data_ptr->m_can_set_player_on_fire = m_vars.m_explosion_data.m_can_set_player_on_fire; }));

	add_option(toggle_option("Supress Crime")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_suppress_crime)
		.add_click([] { m_vars.m_explosion_data_ptr->m_suppress_crime = m_vars.m_explosion_data.m_suppress_crime; }));

	add_option(toggle_option("Use Distance Damage Calculation")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_use_distance_damage_calc)
		.add_click([] { m_vars.m_explosion_data_ptr->m_use_distance_damage_calc = m_vars.m_explosion_data.m_use_distance_damage_calc; }));

	add_option(toggle_option("Prevent Water Explosion VFX")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_prevent_water_explosion_vfx)
		.add_click([] { m_vars.m_explosion_data_ptr->m_prevent_water_explosion_vfx = m_vars.m_explosion_data.m_prevent_water_explosion_vfx; }));

	add_option(toggle_option("Ignore Fire Ratio Check")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_ignore_ratio_check_for_fire)
		.add_click([] { m_vars.m_explosion_data_ptr->m_ignore_ratio_check_for_fire = m_vars.m_explosion_data.m_ignore_ratio_check_for_fire; }));

	add_option(toggle_option("Allow Underwater Explosion")
		.add_translate()
		.add_toggle(m_vars.m_explosion_data.m_allow_underwater_explosion)
		.add_click([] { m_vars.m_explosion_data_ptr->m_allow_underwater_explosion = m_vars.m_explosion_data.m_allow_underwater_explosion; }));

	for (std::size_t i = 0; i < NUMOF(explosion_names); i++) {
		explosion_names[i].m_name.set("");
		explosion_names[i].m_result = 0;
	}
}

void explosion_editor_menu::update() {}

void explosion_editor_menu::update_once() {
	update_editor();
}

void explosion_editor_menu::feature_update() {}

explosion_editor_menu* g_instance;
explosion_editor_menu* explosion_editor_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new explosion_editor_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
