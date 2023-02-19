#include "hooks.h"
#include "global/vars.h"
#include "util/log.h"
#include "util/util.h"
#include "menu/base/submenus/main/network/players/network_players_removals.h"
#include <intrin.h>

using namespace network::players::removals::vars;

bool menu::hooks::read_unsigned_int_from_buffer(rage::bit_buffer_sync_instance* _this, uint32_t* output, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_unsigned_int_from_buffer_t(_this, output, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	uint64_t return_address = (uint64_t)_ReturnAddress();
	for (auto& [address, count] : global::vars::g_return_address_node_iterations) {
		if (return_address == address) {
			if (*output > (uint32_t)count) {
				for (auto& [name, alignment] : global::vars::g_alignment_tests) {
					if (alignment.m_monitor) {
						if (alignment.m_thread_id == GetCurrentThreadId()) {
							alignment.m_block = true;
						}
					}
				}

				*output = 0;
				// LOG_DEV("[%s] iteration failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
				_this->m_buffer->m_unk1 = 1234;
				return false;
			}
		}
	}

	return _return;
}

bool menu::hooks::read_unsigned_short_from_buffer(rage::bit_buffer_sync_instance* _this, uint16_t* output, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_unsigned_short_from_buffer_t(_this, output, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_unsigned_char_from_buffer(rage::bit_buffer_sync_instance* _this, uint8_t* output, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_unsigned_char_from_buffer_t(_this, output, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_int_from_buffer(rage::bit_buffer_sync_instance* _this, int* output, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_int_from_buffer_t(_this, output, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_short_from_buffer(rage::bit_buffer_sync_instance* _this, short* output, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_short_from_buffer_t(_this, output, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_char_from_buffer(rage::bit_buffer_sync_instance* _this, char* output, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_char_from_buffer_t(_this, output, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_bool_from_buffer(rage::bit_buffer_sync_instance* _this, bool* output) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_bool_from_buffer_t(_this, output);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_long_long_from_buffer(rage::bit_buffer_sync_instance* _this, long long* output, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_long_long_from_buffer_t(_this, output, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_unsigned_long_long_from_buffer(rage::bit_buffer_sync_instance* _this, uint64_t* output, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_unsigned_long_long_from_buffer_t(_this, output, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_float_from_buffer(rage::bit_buffer_sync_instance* _this, float* output, float mod, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_float_from_buffer_t(_this, output, mod, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_unsigned_float_from_buffer(rage::bit_buffer_sync_instance* _this, float* output, float mod, int count) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_unsigned_float_from_buffer_t(_this, output, mod, count);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_network_id_from_buffer(rage::bit_buffer_sync_instance* _this, short* output) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_network_id_from_buffer_t(_this, output);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_array_from_buffer(rage::bit_buffer_sync_instance* _this, int* output, int count, int unk) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_array_from_buffer_t(_this, output, count, unk);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

bool menu::hooks::read_string_from_buffer(rage::bit_buffer_sync_instance* _this, char* output, int length) {
	if (_this->m_buffer->m_unk1 == 1234) return false;

	bool _return = read_string_from_buffer_t(_this, output, length);
	if (!_return) {
		for (auto& [name, alignment] : global::vars::g_alignment_tests) {
			if (alignment.m_monitor) {
				if (alignment.m_thread_id == GetCurrentThreadId()) {
					alignment.m_block = true;
				}
			}
		}

		// LOG_DEV("[%s] failed! %s", __FUNCTION__, util::get_stack_trace().c_str());
		_this->m_buffer->m_unk1 = 1234;
		return false;
	}

	return _return;
}

uint64_t menu::hooks::construct_in_frame(uint64_t in_frame, uint64_t rdx, uint64_t r8, uint64_t r9d, uint64_t s_rbp, uint64_t s_rsi, uint16_t s_r15w, uint64_t s_rax) {
	uint64_t _return = construct_in_frame_t(in_frame, rdx, r8, r9d, s_rbp, s_rsi, s_r15w, s_rax);
	uint64_t raw_buffer = *(uint64_t*)(in_frame + 0x80);
	uint32_t raw_size = *(uint32_t*)(in_frame + 0x78);

	global::vars::g_raw_buffer_translations[raw_buffer] = { *(uint32_t*)(in_frame + 0x40), raw_size };

	return _return;
}

uint64_t menu::hooks::destruct_in_frame(uint64_t in_frame, uint8_t dl) {
	uint64_t raw_buffer = *(uint64_t*)(in_frame + 0x80);
	global::vars::g_raw_buffer_translations.erase(raw_buffer);

	return destruct_in_frame_t(in_frame, dl);
}

bool menu::hooks::write_unsigned_int_from_buffer(rage::bit_buffer_sync_instance* _this, uint32_t* output, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			uint64_t return_address = (uint64_t)_ReturnAddress();
			for (auto& [address, count] : global::vars::g_return_address_node_iterations) {
				if (return_address == address) {
					uint32_t NicholasDavidChant = 0xFFFFFFFF;
					return write_unsigned_int_from_buffer_t(_this, &NicholasDavidChant, count);
				}
			}

			if (GetTickCount() % 2 == 0) {
				uint32_t NicholasDavidChant = 0;
				return write_unsigned_int_from_buffer_t(_this, &NicholasDavidChant, count);
			}
		}
	}

	return write_unsigned_int_from_buffer_t(_this, output, count);
}

bool menu::hooks::write_unsigned_short_from_buffer(rage::bit_buffer_sync_instance* _this, uint16_t* output, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_unsigned_short_from_buffer_t(_this, output, count);
}

bool menu::hooks::write_unsigned_char_from_buffer(rage::bit_buffer_sync_instance* _this, uint8_t* output, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_unsigned_char_from_buffer_t(_this, output, count);
}

bool menu::hooks::write_int_from_buffer(rage::bit_buffer_sync_instance* _this, int* output, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_int_from_buffer_t(_this, output, count);
}

bool menu::hooks::write_short_from_buffer(rage::bit_buffer_sync_instance* _this, short* output, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_short_from_buffer_t(_this, output, count);
}

bool menu::hooks::write_char_from_buffer(rage::bit_buffer_sync_instance* _this, char* output, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_char_from_buffer_t(_this, output, count);
}

bool menu::hooks::write_bool_from_buffer(rage::bit_buffer_sync_instance* _this, bool* output) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_bool_from_buffer_t(_this, output);
}

bool menu::hooks::write_long_long_from_buffer(rage::bit_buffer_sync_instance* _this, long long* output, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_long_long_from_buffer_t(_this, output, count);
}

bool menu::hooks::write_unsigned_long_long_from_buffer(rage::bit_buffer_sync_instance* _this, uint64_t* output, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_unsigned_long_long_from_buffer_t(_this, output, count);
}

bool menu::hooks::write_float_from_buffer(rage::bit_buffer_sync_instance* _this, float* output, float mod, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_float_from_buffer_t(_this, output, mod, count);
}

bool menu::hooks::write_unsigned_float_from_buffer(rage::bit_buffer_sync_instance* _this, float* output, float mod, int count) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_unsigned_float_from_buffer_t(_this, output, mod, count);
}

bool menu::hooks::write_network_id_from_buffer(rage::bit_buffer_sync_instance* _this, short* output) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_network_id_from_buffer_t(_this, output);
}

bool menu::hooks::write_array_from_buffer(rage::bit_buffer_sync_instance* _this, int* output, int count, int unk) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) {
					return true;
				}
			}
		}
	}

	return write_array_from_buffer_t(_this, output, count, unk);
}

bool menu::hooks::write_string_from_buffer(rage::bit_buffer_sync_instance* _this, char* output, int length) {
	if (m_vars.m_break_nodes || m_vars.m_session_crash) {
		if (m_vars.m_break_node_threads[0] == GetCurrentThreadId() || m_vars.m_break_node_threads[1] == GetCurrentThreadId()) {
			if (m_vars.m_crash_type == 2) {
				if (GetTickCount() % 2 == 0) return true;
			}
		}
	}

	return write_string_from_buffer_t(_this, output, length);
}