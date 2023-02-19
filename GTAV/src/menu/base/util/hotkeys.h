#pragma once
#include "stdafx.h"
#include "menu/base/options/option.h"

namespace menu::hotkey {
	struct hotkey_context {
		int m_key;
		base_option* m_parent;
		int m_type = 0; // 0 = release, 1 = press, 2 = hold
	};

	class hotkey {
	public:
		void update();
		void read_hotkey(base_option* parent);
		void register_hotkey(int key, base_option* parent);
		void unregister_hotkey(base_option* parent);
		void change_type(int new_type, base_option* parent);

		std::vector<hotkey_context>& get_hotkeys() { return m_registered_hotkeys; }
	private:
		std::vector<hotkey_context> m_registered_hotkeys;
	};

	hotkey* get_hotkey();

	inline void update() {
		get_hotkey()->update();
	}

	inline void read_hotkey(base_option* parent) {
		get_hotkey()->read_hotkey(parent);
	}

	inline void register_hotkey(int key, base_option* parent) {
		get_hotkey()->register_hotkey(key, parent);
	}

	inline void unregister_hotkey(base_option* parent) {
		get_hotkey()->unregister_hotkey(parent);
	}

	inline std::vector<hotkey_context>& get_hotkeys() {
		return get_hotkey()->get_hotkeys();
	}

	inline void change_type(int new_type, base_option* parent) {
		get_hotkey()->change_type(new_type, parent);
	}
}