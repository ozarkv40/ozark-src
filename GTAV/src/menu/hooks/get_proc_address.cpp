#include "hooks.h"
#include "menu/base/submenus/main/misc/scripthook.h"
#include "util/log.h"

FARPROC menu::hooks::get_proc_address(HMODULE mod, LPCSTR name) {
	if (mod == (HMODULE)0x63686970) {
		if (!strcmp(name, "scriptRegister")) {
			return (FARPROC)&misc::scripthook::vars::proxy::script_register;
		}

		if (!strcmp(name, "scriptRegisterAdditionalThread")) {
			return (FARPROC)&misc::scripthook::vars::proxy::script_register_additional_thread;
		}

		if (!strcmp(name, "scriptUnregister")) {
			return (FARPROC)&misc::scripthook::vars::proxy::script_unregister;
		}

		if (!strcmp(name, "nativeInit")) {
			return (FARPROC)&misc::scripthook::vars::proxy::native_init;
		}

		if (!strcmp(name, "nativePush64")) {
			return (FARPROC)&misc::scripthook::vars::proxy::native_push_64;
		}

		if (!strcmp(name, "nativeCall")) {
			return (FARPROC)&misc::scripthook::vars::proxy::native_call;
		}

		if (!strcmp(name, "getGlobalPtr")) {
			return (FARPROC)&misc::scripthook::vars::proxy::get_global_ptr;
		}

		if (!strcmp(name, "scriptWait")) {
			return (FARPROC)&misc::scripthook::vars::proxy::script_wait;
		}

		if (!strcmp(name, "keyboardHandlerRegister")) {
			return (FARPROC)&misc::scripthook::vars::proxy::keyboard_handler_register;
		}

		if (!strcmp(name, "keyboardHandlerUnregister")) {
			return (FARPROC)&misc::scripthook::vars::proxy::keyboard_handler_unregister;
		}

		if (!strcmp(name, "getScriptHandleBaseAddress")) {
			return (FARPROC)&misc::scripthook::vars::proxy::get_script_handle_base_address;
		}

		if (!strcmp(name, "presentCallbackRegister")) {
			return (FARPROC)&misc::scripthook::vars::proxy::present_callback_register;
		}

		if (!strcmp(name, "presentCallbackUnregister")) {
			return (FARPROC)&misc::scripthook::vars::proxy::present_callback_unregister;
		}

		if (!strcmp(name, "worldGetAllVehicles")) {
			return (FARPROC)&misc::scripthook::vars::proxy::world_get_all_vehicles;
		}

		if (!strcmp(name, "worldGetAllPeds")) {
			return (FARPROC)&misc::scripthook::vars::proxy::world_get_all_peds;
		}

		if (!strcmp(name, "worldGetAllObjects")) {
			return (FARPROC)&misc::scripthook::vars::proxy::world_get_all_objects;
		}

		if (!strcmp(name, "worldGetAllPickups")) {
			return (FARPROC)&misc::scripthook::vars::proxy::world_get_all_pickups;
		}

		LOG_CUSTOM_WARN("ScriptHook", "Failed to verify %s", name);
	}

	return get_proc_address_t(mod, name);
}