#include "bit_buffer.h"
#include "global/vars.h"
#include "util/caller.h"

namespace rage {
	bit_buffer_sync_instance bit_buffer::create_reader() {
		bit_buffer_sync_instance instance;
		instance.m_VTable = (uint64_t)global::vars::g_sync_data_reader_vtable;
		instance.m_type = 1;
		instance.m_sub_type = 0;
		instance.m_buffer = this;
		return instance;
	}

	void bit_buffer::update_bit(uint32_t LastSize) {
		m_next_bit += LastSize;

		if (m_next_bit > m_current_bit) {
			m_current_bit = m_next_bit;
		}
	}

	bool bit_buffer::read_bool(bool* output) {
		return caller::call<bool>(global::vars::g_read_bool_from_bit_buffer, this, output);
	}

	bool bit_buffer::read_int(int* output, uint32_t bit_offset) {
		return caller::call<bool>(global::vars::g_read_int_from_bit_buffer, this, output, bit_offset);
	}

	bool bit_buffer::read_uint(uint32_t* output, uint32_t bit_offset) {
		return caller::call<bool>(global::vars::g_read_uint_from_bit_buffer, this, output, bit_offset);
	}

	bool bit_buffer::read_ulonglong(uint64_t* output, uint32_t bit_offset) {
		return caller::call<bool>(global::vars::g_read_ulonglong_from_bit_Buffer, this, output, bit_offset);
	}

	bool bit_buffer::read_short(int16_t* output, uint32_t bit_offset) {
		return caller::call<bool>(global::vars::g_read_short_from_bit_buffer, this, output, bit_offset);
	}

	bool bit_buffer::read_ushort(uint16_t* output, uint32_t bit_offset) {
		return caller::call<bool>(global::vars::g_read_short_from_bit_buffer, this, output, bit_offset);
	}

	void bit_buffer::read_vector3(bit_buffer_sync_instance* instance, math::vector3_<float>* output, uint32_t unk, uint32_t bit_offset) {
		caller::call<int>(global::vars::g_read_vector3_from_bit_buffer, instance, output, unk, bit_offset);
	}

	bool bit_buffer::read_array(int* output, uint32_t count, uint32_t Unk) {
		return caller::call<bool>(global::vars::g_read_array_from_bit_buffer, this, output, count, Unk);
	}

	bool bit_buffer::read_msg_header(int* OutID) {
		return caller::call<bool>(global::vars::g_read_msg_header_from_bit_buffer, OutID, this);
	}

	bool bit_buffer::read_string(char* buffer, int size) {
		return caller::call<bool>(global::vars::g_read_string_from_bit_buffer, this, buffer, size);
	}
	
	bool bit_buffer::read_token(uint64_t* out_token) {
		return caller::call<bool>(global::vars::g_read_token_from_bit_buffer, this, out_token);
	}

	void bit_buffer::write_uint(uint32_t input, uint32_t bit_size, uint32_t bit_offset) {
		caller::call<int>(global::vars::g_write_uint_to_bit_buffer, this, input, bit_size, bit_offset);
		update_bit(bit_size);
	}

	bool bit_buffer::read_byte(uint8_t* out, uint32_t bit_offset) {
		return caller::call<bool>(global::vars::g_read_byte_from_bit_buffer, this, out, bit_offset);
	}
}