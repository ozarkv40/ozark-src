#pragma once
#include "stdafx.h"
#include "util/math.h"
#include "global/vars.h"

namespace rage::invoker {
	namespace crossmap {
		uint64_t search_crossmap(uint64_t hash);
		uint64_t search_crossmap_mapped(uint64_t hash);
		void foreach(void(*func)(uint64_t));
	}

	class native_context {
	protected:
		void* m_return_data;
		uint32_t m_argument_count;
		void* m_argument_data;
		uint32_t m_data_count;
		math::vector3<float>* m_script_vectors[4];
		math::vector4<float> m_result_vectors[4];
	public:
		void reset() {
			m_argument_count = 0;
			m_data_count = 0;
		}

		template<typename T>
		T get_argument(int index) {
			uint64_t* _ = (uint64_t*)m_argument_data;
			return *(T*)&_[index];
		}

		template<typename T>
		void set_argument(int index, T value) {
			uint64_t* _ = (uint64_t*)m_argument_data;
			*(T*)&_[index] = value;
		}

		template<typename T>
		T get_return_result(int index) {
			uint64_t* _ = (uint64_t*)m_return_data;
			return *(T*)&_[index];
		}

		template<typename T>
		void set_return(int index, T value) {
			uint64_t* _ = (uint64_t*)m_return_data;
			*(T*)&_[index] = value;
		}

		void* get_return_data() {
			return m_return_data;
		}

		static void update_result_vectors(native_context* p) {
			for (uint32_t i = 0; i < p->m_data_count; i++) {
				p->m_script_vectors[i]->x = p->m_result_vectors[i].x;
				p->m_script_vectors[i]->y = p->m_result_vectors[i].y;
				p->m_script_vectors[i]->z = p->m_result_vectors[i].z;
			}

			p->m_data_count = 0;
		}
	};

	class native_setup : public native_context {
	private:
		uint8_t m_temp_buffer[256];
	public:
		inline native_setup() {
			m_argument_data = &m_temp_buffer;
			m_return_data = &m_temp_buffer;

			m_argument_count = 0;
			m_data_count = 0;

			memset(m_temp_buffer, 0x0, sizeof(m_temp_buffer));
		}

		uint32_t get_argument_count() {
			return m_argument_count;
		}

		template<typename T>
		void push(T value) {
			memset(&m_temp_buffer[8 * m_argument_count], 0, 8);
			*(T*)&m_temp_buffer[8 * m_argument_count] = value;
			m_argument_count++;
		}

		template<typename T>
		T get_return() {
			return *(T*)m_temp_buffer;
		}

		uint64_t* get_result_pointer() {
			return (uint64_t*)m_temp_buffer;
		}
	};

	typedef void(*native_handler)(native_context*);

	native_handler get_native_handler(uint64_t hash);
	void call_native(uint64_t hash, native_setup* setup);

	struct pass {
		template<typename ...type> pass(type...) {}
	};

	template<typename R, typename... meme>
	R invoke(uint64_t hash, meme&&... args) {
		native_setup setup;

		pass{([&]() {
			setup.push(args);
		}(), 1)... };

		call_native(hash, &setup);
		native_context::update_result_vectors(&setup);
		return setup.get_return<R>();
	}
}