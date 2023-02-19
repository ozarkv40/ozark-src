#pragma once
#include "menu/base/submenu.h"

class scripthook_menu : public menu::submenu::submenu {
public:
	static scripthook_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	scripthook_menu()
		: menu::submenu::submenu() {}
};

namespace misc::scripthook::vars {
	struct ScriptHookScript {
		bool m_initialized;
		bool m_loaded;
		HMODULE m_module;

		ScriptHookScript()
			: m_initialized(false), m_loaded(false), m_module(0) {}
	};

	struct variables {
		rage::invoker::native_setup m_context;
		uint64_t m_native_hash = 0;
		std::unordered_map<HMODULE, std::pair<uint64_t, uint64_t>> m_modules;
		std::vector<void(*)(uint32_t, int16_t, uint8_t, int, int, int, int)> m_keyboards;
		std::unordered_map<std::string, ScriptHookScript> m_script_state;
	};

	namespace proxy {
		void script_register(HMODULE mod, void(*callback)());
		void script_register_additional_thread(HMODULE mod, void(*callback)());
		void script_unregister(HMODULE mod);
		void native_init(uint64_t hash);
		void native_push_64(uint64_t val);
		uint64_t* native_call();
		uint64_t* get_global_ptr(int index);
		void script_wait(uint32_t wait_time);
		void keyboard_handler_register(void(*callback)(uint32_t, int16_t, uint8_t, int, int, int, int));
		void keyboard_handler_unregister(void(*callback)(uint32_t, int16_t, uint8_t, int, int, int, int));
		uint8_t* get_script_handle_base_address(int handle);
		void present_callback_register(void(*callback)());
		void present_callback_unregister(void(*callback)());
		int world_get_all_vehicles(int* arr, int arr_size);
		int world_get_all_peds(int* arr, int arr_size);
		int world_get_all_objects(int* arr, int arr_size);
		int world_get_all_pickups(int* arr, int arr_size);
	};

	extern variables m_vars;
}