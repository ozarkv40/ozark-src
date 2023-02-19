#include "init.h"
#include "global/vars.h"
#include "util/dirs.h"
#include "util/log.h"
#include "util/threads.h"
#include "util/va.h"
#include "util/wmi.h"
#include "util/util.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "util/hooking/hooking.h"
#include "menu/auth.h"
#include "menu/hooks/hooks.h"
#include "menu/base/util/input.h"
#include "menu/base/submenu_handler.h"
#include "rage/api/api.h"
#include "rage/ros.h"
#include "menu/base/util/textures.h"
#include "auth/http/curl.h"
#include "security/security.h"
#include "global/auth_vars.h"
#include <Psapi.h>
#include <fstream>
#include <filesystem>

namespace menu::init {
	LONG WINAPI exception_filter(struct _EXCEPTION_POINTERS* ExceptionInfoPtr) {
#undef exception_code
#undef exception_info

		DWORD exception_code = ExceptionInfoPtr->ExceptionRecord->ExceptionCode;
		ULONG_PTR exception_info = ExceptionInfoPtr->ExceptionRecord->ExceptionInformation[0];
		ULONG_PTR exception_info1 = ExceptionInfoPtr->ExceptionRecord->ExceptionInformation[1];
		ULONG_PTR exception_info2 = ExceptionInfoPtr->ExceptionRecord->ExceptionInformation[2];

		uint64_t exception_address = (uint64_t)ExceptionInfoPtr->ExceptionRecord->ExceptionAddress;

		LOG_CUSTOM_ERROR("Crash", "Game crashed with code 0x%X", exception_code);
		LOG_CUSTOM_ERROR("Crash", "Crashed @ 0x%llx (game=%llx cheat=%llx)", exception_address, global::vars::g_game_address.first, global::vars::g_module_handle);
		// LOG_DEV("Game Script: %s", *(const char**)(global::vars::g_game_address.first + 0x2D59018));

		switch (exception_code) {
			case EXCEPTION_ACCESS_VIOLATION:
				LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_ACCESS_VIOLATION");
				if (exception_info == 0) {
					LOG_CUSTOM_ERROR("Crash", "Attempted to read from: 0x%llx", exception_info1);
				} else if (exception_info == 1) {
					LOG_CUSTOM_ERROR("Crash", "Attempted to write to: 0x%llx", exception_info1);
				} else if (exception_info == 8) {
					LOG_CUSTOM_ERROR("Crash", "Data Execution Prevention (DEP) at: 0x%llx", exception_info1);
				} else {
					LOG_CUSTOM_ERROR("Crash", "Unknown access violation at: 0x%llx", exception_info1);
				}
				break;

			case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_ARRAY_BOUNDS_EXCEEDED"); break;
			case EXCEPTION_BREAKPOINT: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_BREAKPOINT"); break;
			case EXCEPTION_DATATYPE_MISALIGNMENT: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_DATATYPE_MISALIGNMENT"); break;
			case EXCEPTION_FLT_DENORMAL_OPERAND: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_FLT_DENORMAL_OPERAND"); break;
			case EXCEPTION_FLT_DIVIDE_BY_ZERO: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_FLT_DIVIDE_BY_ZERO"); break;
			case EXCEPTION_FLT_INEXACT_RESULT: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_FLT_INEXACT_RESULT"); break;
			case EXCEPTION_FLT_INVALID_OPERATION: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_FLT_INVALID_OPERATION"); break;
			case EXCEPTION_FLT_OVERFLOW: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_FLT_OVERFLOW"); break;
			case EXCEPTION_FLT_STACK_CHECK: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_FLT_STACK_CHECK"); break;
			case EXCEPTION_FLT_UNDERFLOW: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_FLT_UNDERFLOW"); break;
			case EXCEPTION_ILLEGAL_INSTRUCTION: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_ILLEGAL_INSTRUCTION"); break;
			case EXCEPTION_IN_PAGE_ERROR:
				LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_IN_PAGE_ERROR");
				if (exception_info == 0) {
					LOG_CUSTOM_ERROR("Crash", "Attempted to read from: 0x%llx", exception_info1);
				} else if (exception_info == 1) {
					LOG_CUSTOM_ERROR("Crash", "Attempted to write to: 0x%llx", exception_info1);
				} else if (exception_info == 8) {
					LOG_CUSTOM_ERROR("Crash", "Data Execution Prevention (DEP) at: 0x%llx", exception_info1);
				} else {
					LOG_CUSTOM_ERROR("Crash", "Unknown access violation at: 0x%llx", exception_info1);
				}

				LOG_CUSTOM_ERROR("Crash", "NTSTATUS: 0x%llx", exception_info2);
				break;

			case EXCEPTION_INT_DIVIDE_BY_ZERO: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_INT_DIVIDE_BY_ZERO"); break;
			case EXCEPTION_INT_OVERFLOW: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_INT_OVERFLOW"); break;
			case EXCEPTION_INVALID_DISPOSITION: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_INVALID_DISPOSITION"); break;
			case EXCEPTION_NONCONTINUABLE_EXCEPTION: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_NONCONTINUABLE_EXCEPTION"); break;
			case EXCEPTION_PRIV_INSTRUCTION: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_PRIV_INSTRUCTION"); break;
			case EXCEPTION_SINGLE_STEP: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_SINGLE_STEP"); break;
			case EXCEPTION_STACK_OVERFLOW: LOG_CUSTOM_ERROR("Crash", "Cause: EXCEPTION_STACK_OVERFLOW"); break;
			case DBG_CONTROL_C: LOG_CUSTOM_ERROR("Crash", "Cause: DBG_CONTROL_C"); break;
			default: LOG_CUSTOM_ERROR("Crash", "Cause: 0x%08x", exception_code);
		}

		LOG_CUSTOM_ERROR("Crash", "Dumping ASM registers:");
		LOG_CUSTOM_ERROR("Crash", "RAX: 0x%llx || RSI: 0x%llx", ExceptionInfoPtr->ContextRecord->Rax, ExceptionInfoPtr->ContextRecord->Rsi);
		LOG_CUSTOM_ERROR("Crash", "RBX: 0x%llx || RDI: 0x%llx", ExceptionInfoPtr->ContextRecord->Rbx, ExceptionInfoPtr->ContextRecord->Rdi);
		LOG_CUSTOM_ERROR("Crash", "RCX: 0x%llx || RBP: 0x%llx", ExceptionInfoPtr->ContextRecord->Rcx, ExceptionInfoPtr->ContextRecord->Rbp);
		LOG_CUSTOM_ERROR("Crash", "RDX: 0x%llx || RSP: 0x%llx", ExceptionInfoPtr->ContextRecord->Rdx, ExceptionInfoPtr->ContextRecord->Rsp);
		LOG_CUSTOM_ERROR("Crash", "R8: 0x%llx || R9: 0x%llx", ExceptionInfoPtr->ContextRecord->R8, ExceptionInfoPtr->ContextRecord->R9);
		LOG_CUSTOM_ERROR("Crash", "R10: 0x%llx || R11: 0x%llx", ExceptionInfoPtr->ContextRecord->R10, ExceptionInfoPtr->ContextRecord->R11);
		LOG_CUSTOM_ERROR("Crash", "R12: 0x%llx || R13: 0x%llx", ExceptionInfoPtr->ContextRecord->R12, ExceptionInfoPtr->ContextRecord->R13);
		LOG_CUSTOM_ERROR("Crash", "R14: 0x%llx || R15: 0x%llx", ExceptionInfoPtr->ContextRecord->R14, ExceptionInfoPtr->ContextRecord->R15);
		LOG_CUSTOM_ERROR("Crash", util::get_stack_trace().c_str());

		return EXCEPTION_CONTINUE_SEARCH;
	}

	void unload() {
		if (!global::vars::g_unloading) {
			global::vars::g_unloading = true;
			
			util::threads::add_job([](void*) {
#ifndef DEV_MODE
				security::relink((HMODULE)global::vars::g_module_handle);
#endif

				for (patches& patch : global::vars::g_patches) {
					memory::write_vector(patch.m_address, patch.m_bytes);
				}

				for (auto& hack_patch : global::vars::g_hack_patches) {
					memory::write_vector(hack_patch.second.m_address, hack_patch.second.m_bytes);
				}

				hooking::cleanup();
				util::threads::cleanup();
				util::fiber::cleanup();
				menu::input::cleanup();
				menu::submenu::handler::cleanup();
				util::va::cleanup();
				util::log::cleanup();

				free((void*)global::vars::g_texture_bypass);
				free((void*)global::vars::g_marker_bypass);
				free((void*)global::ui::m_line_2d);

				PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
				FreeConsole();

#ifdef DEV_MODE
				Sleep(2000);
				FreeLibraryAndExitThread(global::vars::g_module_handle, 0);
#endif
			});
		}
	}

	void entry(void* handle) {
		SetUnhandledExceptionFilter(exception_filter);
		srand(GetTickCount());

		MODULEINFO module_info;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(0), &module_info, sizeof(module_info));

		global::vars::g_steam = (uint64_t)GetModuleHandleA(XOR("steam_api64.dll")) > 0;
		global::vars::g_game_address = { (uint64_t)module_info.lpBaseOfDll, module_info.SizeOfImage };

		std::copy((uint8_t*)handle, (uint8_t*)((uint64_t)handle + 0x1000), std::back_inserter(global::auth::g_pe_header));

#ifndef DEV_MODE
		security::unlink((HMODULE)handle);
#endif

		if (!util::dirs::load()) {
			unload();
			return;
		}

		util::log::load();

		LOG_DEV("Base: %llx", handle);

		LOG(XOR("Welcome to Ozark! Version V%i"), VERSION);

		if (!security::load()) {
			unload();
			return;
		}

		if (!(global::vars::g_window = FindWindowA(XOR("grcWindow"), NULL))) {
			int timeout = 0;
			while (!global::vars::g_window && !global::vars::g_unloading) {
				if (timeout >= 20) {
					LOG_ERROR(XOR("Failed to find window!"));
					unload();
					return;
				}

				global::vars::g_window = FindWindowA(XOR("grcWindow"), NULL);

				timeout++;
				Sleep(1000);
			}
		}

		if (!menu::hooks::bypass()) {
			unload();
			return;
		}

		if (!auth::run()) {
			unload();
			return;
		}

		global::vars::g_texture_bypass = (uint64_t)malloc(5000 * 0x50);
		global::vars::g_marker_bypass = (uint64_t)malloc(1280 * sizeof(rage::types::marker_table));
		global::ui::m_line_2d = (line_2d*)malloc(5000 * sizeof(line_2d));

		memset((void*)global::vars::g_texture_bypass, 0, 5000 * 0x50);
		memset((void*)global::vars::g_marker_bypass, 0, 1280 * sizeof(rage::types::marker_table));
		memset((void*)global::ui::m_line_2d, 0, 5000 * sizeof(line_2d));

		util::threads::add_thread(XOR("T_HB"), [](void*) {
			if (!auth::run_heartbeat()) {
				unload();
				return;
			}

			// 5 minutes
			Sleep(300000);
		});

		if (!menu::hooks::globals()) {
			unload();
			return;
		}

		if (!menu::hooks::hooks()) {
			unload();
			return;
		}

		menu::hooks::spoofing();

		while (*global::vars::g_game_state != GameStatePlaying) Sleep(500);

		if (!menu::hooks::globals_in_game()) {
			unload();
			return;
		}

		hooking::script(XOR("SGI"), XOR("main_persistent"), 0x767FBC2AC802EF3D, hooks::stat_get_int);

		util::threads::add_thread(XOR("T_SH"), [](void*) {
			Sleep(1500);

			hooking::script(XOR("SCPW_P"), XOR("am_mp_property_int"), 0xADF692B254977C0C, &hooks::set_current_ped_weapon);
			hooking::script(XOR("DCA_P"), XOR("am_mp_property_int"), 0xFE99B66D079CF6BC, &hooks::disable_control_action);

			hooking::script(XOR("SCPW_C"), XOR("am_mp_smpl_interior_int"), 0xADF692B254977C0C, &hooks::set_current_ped_weapon);
			hooking::script(XOR("DCA_C"), XOR("am_mp_smpl_interior_int"), 0xFE99B66D079CF6BC, &hooks::disable_control_action);

			hooking::script(XOR("SCPW_F"), XOR("freemode"), 0xADF692B254977C0C, &hooks::set_current_ped_weapon);
			hooking::script(XOR("DCA_F"), XOR("freemode"), 0xFE99B66D079CF6BC, &hooks::disable_control_action);
			hooking::script(XOR("TTT"), XOR("freemode"), 0x1090044AD1DA76FA, &hooks::terminate_this_thread);
			// hooking::script(XOR("WAIT"), XOR("freemode"), 0x4EDE34FBADD967A6, &hooks::wait);

			hooking::script(XOR("SWM2"), XOR("shop_controller"), 0xDC38CC1E35B6A5D7, &hooks::set_warning_message_2);
		});

		util::threads::add_thread(XOR("T_SC"), [](void*) {
			rage::api::update();
		});

		util::threads::add_thread(XOR("T_GEO"), [](void*) {
			Sleep(1000);

			if (!global::vars::g_geo_queue.empty()) {
				if (!native::network_is_session_active()) {
					global::vars::g_geo_queue.pop();
					return;
				}

				uint32_t item = global::vars::g_geo_queue.front();

				if (global::vars::g_geo.find(item) == global::vars::g_geo.end()) {
					char str[16];
					sprintf_s(str, "%i.%i.%i.%i", ((item & 0xFF000000) >> 24), ((item & 0xFF0000) >> 16), ((item & 0xFF00) >> 8), item & 0xFF);
					LOG_CUSTOM(XOR("Geo"), XOR("Sending request for %s"), str);

					curl::request_state context(nullptr, 0);
					curl::setup_context(&context);
					curl::set_url(&context, XOR("https://ozarkengine.cc/geo.php?ip=") + std::string(str));

					CURLcode code = curl::send(&context);
					if (code == CURLE_OK) {
						try {
							nlohmann::json json = nlohmann::json::parse(context.m_write_chunk);
							if (!json.empty()) {
								if (!json["status"].is_null()) {
									if (json["status"].get<std::string>() == "success") {
										geo_ip ip;
										ip.m_country = json["country"].get<std::string>();
										ip.m_country_code = json["countryCode"].get<std::string>();
										ip.m_region_name = json["regionName"].get<std::string>();
										ip.m_city = json["city"].get<std::string>();
										ip.m_zip = json["zip"].get<std::string>();
										ip.m_timezone = json["timezone"].get<std::string>();
										ip.m_isp = json["isp"].get<std::string>();
										ip.m_org = json["org"].get<std::string>();
										global::vars::g_geo[item] = ip;
									}
								}
							}

						} catch (std::exception& e) {
							LOG_WARN("[Json] %s", e.what());
						}
					} else {
						LOG_DEV("CURL Error: %i", code);
					}
				}

				global::vars::g_geo_queue.pop();
			}
		});
	}
}