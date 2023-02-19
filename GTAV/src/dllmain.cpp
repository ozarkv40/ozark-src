#include "stdafx.h"
#include "global/vars.h"
#include "util/threads.h"
#include "menu/init.h"
#include "global/auth_vars.h"
#include "security/security.h"

#include <Psapi.h>
#pragma comment(lib, "Winmm.lib")

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            global::vars::g_module_handle = handle;

            if (handle) {
                MODULEINFO module_info;
                GetModuleInformation(GetCurrentProcess(), handle, &module_info, sizeof(module_info));
                global::vars::g_cheat_address = { (uint64_t)module_info.lpBaseOfDll, module_info.SizeOfImage };
            }

            util::threads::add_job(menu::init::entry, handle);
            break;

        case DLL_PROCESS_DETACH:
            global::vars::g_unloading = true;
            break;
    }

    return TRUE;
}