#pragma once
#include "stdafx.h"
#include "global/ui_vars.h"
#include <vector>
#include <stack>

namespace util::config {
	class config {
	public:
		std::string read_string(std::stack<std::string> name_stack, std::string key, std::string default_string = "", std::vector<std::string> additional_stacks = {});
		int read_int(std::stack<std::string> name_stack, std::string key, int default_int = 0, std::vector<std::string> additional_stacks = {});
		uint64_t read_uint64(std::stack<std::string> name_stack, std::string key, uint64_t default_int = 0, std::vector<std::string> additional_stacks = {});
		float read_float(std::stack<std::string> name_stack, std::string key, float default_float = 0.f, std::vector<std::string> additional_stacks = {});
		bool read_bool(std::stack<std::string> name_stack, std::string key, bool default_bool = false, std::vector<std::string> additional_stacks = {});
		bool read_color(std::stack<std::string> name_stack, std::string key, color_rgba* color, std::vector<std::string> additional_stacks = {});
		bool read_vector(std::stack<std::string> name_stack, std::string key, math::vector3_<float>* vec, std::vector<std::string> additional_stacks = {});
	
		void write_string(std::stack<std::string> name_stack, std::string key, std::string value, std::vector<std::string> additional_stacks = {});
		void write_int(std::stack<std::string> name_stack, std::string key, int value, std::vector<std::string> additional_stacks = {});
		void write_uint64(std::stack<std::string> name_stack, std::string key, uint64_t value, std::vector<std::string> additional_stacks = {});
		void write_float(std::stack<std::string> name_stack, std::string key, float value, std::vector<std::string> additional_stacks = {});
		void write_bool(std::stack<std::string> name_stack, std::string key, bool value, std::vector<std::string> additional_stacks = {});
		void write_color(std::stack<std::string> name_stack, std::string key, color_rgba value, std::vector<std::string> additional_stacks = {});
		void write_vector(std::stack<std::string> name_stack, std::string key, math::vector3_<float> value, std::vector<std::string> additional_stacks = {});
	};

	config* get_config();

	inline std::string read_string(std::stack<std::string> name_stack, std::string key, std::string default_string = "", std::vector<std::string> additional_stacks = {}) {
		return get_config()->read_string(name_stack, key, default_string, additional_stacks);
	}

	inline int read_int(std::stack<std::string> name_stack, std::string key, int default_int = 0, std::vector<std::string> additional_stacks = {}) {
		return get_config()->read_int(name_stack, key, default_int, additional_stacks);
	}

	inline uint64_t read_uint64(std::stack<std::string> name_stack, std::string key, uint64_t default_int = 0, std::vector<std::string> additional_stacks = {}) {
		return get_config()->read_uint64(name_stack, key, default_int, additional_stacks);
	}

	inline float read_float(std::stack<std::string> name_stack, std::string key, float default_float = 0.f, std::vector<std::string> additional_stacks = {}) {
		return get_config()->read_float(name_stack, key, default_float, additional_stacks);
	}

	inline bool read_bool(std::stack<std::string> name_stack, std::string key, bool default_bool = false, std::vector<std::string> additional_stacks = {}) {
		return get_config()->read_bool(name_stack, key, default_bool, additional_stacks);
	}

	inline bool read_color(std::stack<std::string> name_stack, std::string key, color_rgba* color, std::vector<std::string> additional_stacks = {}) {
		return get_config()->read_color(name_stack, key, color, additional_stacks);
	}

	inline bool read_vector(std::stack<std::string> name_stack, std::string key, math::vector3_<float>* vec, std::vector<std::string> additional_stacks = {}) {
		return get_config()->read_vector(name_stack, key, vec, additional_stacks);
	}

	inline void write_string(std::stack<std::string> name_stack, std::string key, std::string value, std::vector<std::string> additional_stacks = {}) {
		return get_config()->write_string(name_stack, key, value, additional_stacks);
	}

	inline void write_int(std::stack<std::string> name_stack, std::string key, int value, std::vector<std::string> additional_stacks = {}) {
		return get_config()->write_int(name_stack, key, value, additional_stacks);
	}

	inline void write_uint64(std::stack<std::string> name_stack, std::string key, uint64_t value, std::vector<std::string> additional_stacks = {}) {
		return get_config()->write_uint64(name_stack, key, value, additional_stacks);
	}

	inline void write_float(std::stack<std::string> name_stack, std::string key, float value, std::vector<std::string> additional_stacks = {}) {
		return get_config()->write_float(name_stack, key, value, additional_stacks);
	}

	inline void write_bool(std::stack<std::string> name_stack, std::string key, bool value, std::vector<std::string> additional_stacks = {}) {
		return get_config()->write_bool(name_stack, key, value, additional_stacks);
	}

	inline void write_color(std::stack<std::string> name_stack, std::string key, color_rgba value, std::vector<std::string> additional_stacks = {}) {
		return get_config()->write_color(name_stack, key, value, additional_stacks);
	}

	inline void write_vector(std::stack<std::string> name_stack, std::string key, math::vector3_<float> value, std::vector<std::string> additional_stacks = {}) {
		return get_config()->write_vector(name_stack, key, value, additional_stacks);
	}
}