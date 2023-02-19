#include "hooks.h"
#include "global/ui_vars.h"
#include "global/vars.h"
#include "rage/invoker/natives.h"
#include "rage/engine.h"
#include "util/dirs.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "util/caller.h"
#include "util/log.h"
#include "util/va.h"
#include "menu/base/renderer.h"
#include "menu/base/submenu_handler.h"
#include "menu/base/base.h"
#include "menu/base/util/input.h"
#include "menu/base/util/menu_input.h"
#include "menu/base/util/player_manager.h"
#include "menu/base/util/hotkeys.h"
#include "menu/base/util/control.h"
#include "menu/base/util/notify.h"
#include "menu/base/util/panels.h"
#include "menu/base/util/stacked_display.h"
#include "menu/base/util/textures.h"
#include "menu/base/util/fonts.h"
#include "menu/init.h"
#include "menu/base/submenus/main/network/network_session_finder.h"
#include <algorithm>
#include <mutex>
#include <filesystem>
#include "menu/base/util/timers.h"

localization t_asset_error("Asset Error", true, true);
localization t_failed_loading("Failed loading", true, true);

void menu::hooks::wait(rage::invoker::native_context* context) {
	menu::control::update();
	native::wait(context->get_argument<int>(0));
}

void menu::hooks::stat_get_int(rage::invoker::native_context* context) {
	static bool call_once_loaded = false;

#ifdef DEV_MODE
	if (menu::input::is_pressed(true, VK_DELETE)) {
		global::vars::g_unloading_queue = true;
	}
#endif

	if (global::vars::g_unloading_queue) {
		global::vars::g_unloading_queue = false;
		menu::init::unload();
		return;
	}

	static int frame_cache = 0;
	static uint32_t this_frame = 0;
	static uint32_t last_frame = 0;

	if (frame_cache < native::get_frame_count()) {
		frame_cache = native::get_frame_count();

		this_frame = timeGetTime();
		global::ui::g_delta = (float)(this_frame - last_frame) / 1000;
		last_frame = this_frame;

		if (!call_once_loaded) {
			try {
				menu::player::update();

				util::fiber::load();
				util::fiber::load_shv();
				util::fiber::pool::load();

				menu::textures::load();
				menu::submenu::handler::load();
				menu::fonts::load();

				util::fiber::add("F_UI", [] {
					menu::notify::update();
					menu::panels::update();
					menu::display::render();
					menu::base::update();
					menu::fonts::update_queue();
				});

				util::fiber::add("F_INPUT", [] {
					menu::hotkey::update();
					menu::input::mi_update();
					menu::input::update();
				});

				util::fiber::add("F_FEATURE", [] {
					menu::submenu::handler::feature_update();
				});

				util::fiber::add("F_BASE", [] {
					menu::player::update();
					menu::control::update();
				});

				util::fiber::add("F_MM", [] {
					if (network::sfinder::vars::m_vars.m_populate) {
						if (menu::submenu::handler::get_current() == network_session_finder_menu::get()) {
							rage::engine::send_matchmaking_request();
						}
					}
				});

				util::fiber::add("F_PIP", [] {
					if (!global::vars::g_player_image_queue.empty()) {
						for (std::size_t i = 0; i < global::vars::g_player_image_queue.size(); i++) {
							menu::textures::load_player_img(global::vars::g_player_image_queue[i].second, global::vars::g_player_image_queue[i].first);
							delete[] global::vars::g_player_image_queue[i].second;
							global::vars::g_player_image_queue.erase(begin(global::vars::g_player_image_queue) + i);
							util::fiber::sleep(100);
						}
					}
				});

				if (!std::filesystem::exists(util::dirs::create_string(util::dirs::get_path(ozark), "OzarkBlips.ytd").c_str()) || rage::engine::register_streaming_file(util::dirs::create_string(util::dirs::get_path(ozark), "OzarkBlips.ytd").c_str(), "OzarkBlips.ytd") == -1) {
					menu::notify::stacked(TRANSLATE(t_asset_error), util::va::va("%s \"%s\"", TRANSLATE(t_failed_loading), util::dirs::create_string(util::dirs::get_path(ozark), "OzarkBlips.ytd").c_str()), global::ui::g_error);
				} else native::request_streamed_texture_dict("OzarkBlips", false);

				native::request_streamed_texture_dict("commonmenu", false);
				native::request_streamed_texture_dict("ozarktextures", false);

				call_once_loaded = true;
			} catch (std::exception& exception) {
				LOG("Exception initializing menu: %s", exception.what());
			}
		}

		if (!global::vars::g_unloading && call_once_loaded) {
			util::fiber::update();
			util::fiber::update_shv();
		}
	}

	context->set_return(0, native::stat_get_int(context->get_argument<uint32_t>(0), context->get_argument<int*>(1), context->get_argument<int>(2)));
}