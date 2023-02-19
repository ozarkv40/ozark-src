#include "animations.h"
#include "menu/base/submenu_handler.h"
#include "../animation.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"

using namespace player::animations::vars;

namespace player::animations::vars {
	variables m_vars;

	scroll_struct<std::pair<const char*, const char*>> sexual[] = {
		{ localization("Doggystyle 1", true), { "rcmpaparazzo_2", "shag_loop_poppy" } },
		{ localization("Doggystyle 2", true), { "rcmpaparazzo_2", "shag_loop_a" } },
		{ localization("Shaking Ass", true), { "switch@trevor@mocks_lapdance", "001443_01_trvs_28_idle_stripper" } },
		{ localization("Slow Humping", true), { "misscarsteal2pimpsex", "shagloop_pimp" } }
	};

	scroll_struct<std::pair<const char*, const char*>> animals[] = {
		{ localization("Monkey", true), { "missfbi5ig_30monkeys", "monkey_b_freakout_loop" } },
		{ localization("Chop Hump", true), { "missfra0_chop_find", "hump_loop_chop" } },
		{ localization("Chop Swim", true), { "creatures@rottweiler@swim@", "swim" } }
	};

	scroll_struct<std::pair<const char*, const char*>> actions[] = {
		{ localization("Air Guitar", true), { "anim@mp_player_intcelebrationfemale@air_guitar", "air_guitar" } },
		{ localization("Blow Kiss", true), { "anim@mp_player_intcelebrationfemale@blow_kiss", "blow_kiss" } },
		{ localization("Bro Hug", true), { "anim@mp_player_intcelebrationpaired@f_m_bro_hug", "bro_hug_right" } },
		{ localization("Challenge", true), { "misscommon@response", "face_palm" } },
		{ localization("Face Palm", true), { "anim@mp_player_intcelebrationmale@face_palm", "" } },
		{ localization("Finger", true), { "anim@mp_player_intcelebrationmale@finger", "finger" } },
		{ localization("Hands Up", true), { "mp_pol_bust_out", "guard_handsup_loop" } },
		{ localization("Hump Air", true), { "anim@mp_player_intcelebrationfemale@air_shagging", "air_shagging" } },
		{ localization("Jazz Hands", true), { "anim@mp_player_intcelebrationmale@jazz_hands", "jazz_hands" } },
		{ localization("Nose Pick", true), { "anim@mp_player_intcelebrationmale@nose_pick", "nose_pick" } },
		{ localization("Photographer", true), { "anim@mp_player_intcelebrationmale@photography", "photography" } },
		{ localization("Salute", true), { "anim@mp_player_intcelebrationmale@salute", "salute" } },
		{ localization("Shush", true), { "anim@mp_player_intcelebrationmale@shush", "shush" } },
		{ localization("Slow Clap", true), { "anim@mp_player_intcelebrationmale@slow_clap", "slow_clap" } },
		{ localization("Smoke", true), { "anim@mp_player_intcelebrationmale@smoke_flick", "smoke_flick" } },
		{ localization("Surrender", true), { "anim@mp_player_intcelebrationmale@surrender", "surrender" } },
		{ localization("Synth", true), { "anim@mp_player_intcelebrationfemale@air_synth", "air_synth" } },
		{ localization("Thumbs Up", true), { "anim@mp_player_intcelebrationmale@thumbs_up", "thumbs_up" } },
		{ localization("Wank", true), { "mp_player_intwank", "mp_player_int_wank" } }
	};

	scroll_struct<std::pair<const char*, const char*>> dance[] = {
		{ localization("Casual", true), { "rcmnigel1bnmt_1b", "dance_loop_tyler" } },
		{ localization("Clown", true), { "rcm_barry2", "clown_idle_6" } },
		{ localization("Pole", true), { "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03" } },
		{ localization("Private", true), { "mini@strip_club@private_dance@part2", "priv_dance_p2" } },
		{ localization("Receive", true), { "mp_am_stripper", "lap_dance_player" } },
		{ localization("Sexual", true), { "mini@strip_club@pole_dance@pole_a_2_stage", "pole_a_2_stage" } },
		{ localization("Yacht", true), { "oddjobs@assassinate@multi@yachttarget@lapdance", "yacht_ld_f" } }
	};

	scroll_struct<std::pair<const char*, const char*>> misc[] = {
		{ localization("Electrocute", true), { "ragdoll@human", "electrocute" } },
		{ localization("Hover", true), { "swimming@base", "dive_idle" } },
		{ localization("Jump", true), { "move_jump", "jump_launch_l_to_skydive" } },
		{ localization("Meditate", true), { "rcmcollect_paperleadinout@", "meditiate_idle" } },
		{ localization("Party", true), { "rcmfanatic1celebrate", "celebrate" } },
		{ localization("Pissing", true), { "misscarsteal2peeing", "peeing_loop" } },
		{ localization("Push Ups", true), { "rcmfanatic3", "ef_3_rcm_loop_maryann" } },
		{ localization("Run", true), { "move_m@alien", "alien_run" } },
		{ localization("Shitting", true), { "missfbi3ig_0", "shit_loop_trev" } },
		{ localization("Showering", true), { "mp_safehouseshower@male@", "male_shower_idle_b" } },
		{ localization("Swim", true), { "swimming@scuba", "dive_idle" } },
		{ localization("Vomit", true), { "missfam5_blackout", "vomit" } },
		{ localization("Wave Forward", true), { "friends@frj@ig_1", "wave_d" } },
		{ localization("Wave Hands High", true), { "random@prisoner_lift", "arms_waving" } },
		{ localization("Wave One Arm", true), { "random@shop_gunstore", "_greeting" } }
	};

	void start_animation(std::pair<const char*, const char*> anim) {
		util::fiber::pool::add([=] {
			int flag = AnimationRepeat;
			if (m_vars.m_controllable) flag |= AnimationEnablePlayerControl | AnimationUpperBody;
			if (m_vars.m_contort) flag |= AnimationCreature;

			while (!native::has_anim_dict_loaded(anim.first)) {
				native::request_anim_dict(anim.first);
				util::fiber::sleep(100);
			}

			native::clear_ped_tasks_immediately(menu::player::get_local_player().m_ped);
			native::task_play_anim(menu::player::get_local_player().m_ped, anim.first, anim.second, 8.f, 8.f, -1, flag, 0.f, false, false, false);
		});
	}
}

void animations_menu::load() {
	set_name("Animations");
	set_parent<animation_menu>();

	add_option(button_option("Stop Animation")
		.add_translate().add_hotkey()
		.add_click([] { native::clear_ped_tasks_immediately(menu::player::get_local_player().m_ped); }));

	add_option(toggle_option("Controllable")
		.add_translate()
		.add_toggle(m_vars.m_controllable).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Contort")
		.add_translate()
		.add_toggle(m_vars.m_contort).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(SCROLL, "Speed")
		.add_translate()
		.add_number(m_vars.m_speed, "%.0f", 1.f).add_min(0.f).add_max(100.f).add_savable(get_submenu_name_stack()));

	add_option(break_option("Animations")
		.add_translate());

	add_option(scroll_option<std::pair<const char*, const char*>>(SCROLLSELECT, "Sexual")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_sexual, 0, NUMOF(sexual), sexual)
		.add_click([] { start_animation(sexual[m_vars.m_sexual].m_result); }));

	add_option(scroll_option<std::pair<const char*, const char*>>(SCROLLSELECT, "Dance")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_dance, 0, NUMOF(dance), dance)
		.add_click([] { start_animation(dance[m_vars.m_dance].m_result); }));

	add_option(scroll_option<std::pair<const char*, const char*>>(SCROLLSELECT, "Actions")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_actions, 0, NUMOF(actions), actions)
		.add_click([] { start_animation(actions[m_vars.m_actions].m_result); }));

	add_option(scroll_option<std::pair<const char*, const char*>>(SCROLLSELECT, "Animals")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_animals, 0, NUMOF(animals), animals)
		.add_click([] { start_animation(animals[m_vars.m_animals].m_result); }));

	add_option(scroll_option<std::pair<const char*, const char*>>(SCROLLSELECT, "Misc")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_misc, 0, NUMOF(misc), misc)
		.add_click([] { start_animation(misc[m_vars.m_misc].m_result); }));
}

void animations_menu::update() {
	bool playing = false;

	for (scroll_struct<std::pair<const char*, const char*>> anim : sexual) {
		if (native::is_entity_playing_anim(menu::player::get_local_player().m_ped, anim.m_result.first, anim.m_result.second, 3)) {
			playing = true;
		}
	}

	for (scroll_struct<std::pair<const char*, const char*>> anim : dance) {
		if (native::is_entity_playing_anim(menu::player::get_local_player().m_ped, anim.m_result.first, anim.m_result.second, 3)) {
			playing = true;
		}
	}

	for (scroll_struct<std::pair<const char*, const char*>> anim : actions) {
		if (native::is_entity_playing_anim(menu::player::get_local_player().m_ped, anim.m_result.first, anim.m_result.second, 3)) {
			playing = true;
		}
	}

	for (scroll_struct<std::pair<const char*, const char*>> anim : animals) {
		if (native::is_entity_playing_anim(menu::player::get_local_player().m_ped, anim.m_result.first, anim.m_result.second, 3)) {
			playing = true;
		}
	}

	for (scroll_struct<std::pair<const char*, const char*>> anim : misc) {
		if (native::is_entity_playing_anim(menu::player::get_local_player().m_ped, anim.m_result.first, anim.m_result.second, 3)) {
			playing = true;
		}
	}

	if (playing) {
		native::set_anim_rate(menu::player::get_local_player().m_ped, m_vars.m_speed, 0.f, 0.f);
	}
}

void animations_menu::update_once() {}

void animations_menu::feature_update() {}

animations_menu* g_instance;
animations_menu* animations_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new animations_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}