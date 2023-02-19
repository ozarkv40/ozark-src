#include "config.h"
#include "json.h"
#include "dirs.h"
#include <fstream>
#include <filesystem>

namespace util::config {
	nlohmann::json read_config_contents() {
		nlohmann::json json;

		if (std::filesystem::exists(dirs::get_path(config))) {
			std::ifstream input(dirs::get_path(config));
			if (input.good()) {
				input >> json;
				input.close();
			}
		}

		return json;
	}

	void write_config_contents(nlohmann::json json) {
		std::ofstream Output(dirs::get_path(config));
		if (Output.good()) {
			Output << json.dump(4);
			Output.close();
		}
	}

	template<typename T>
	void build_stack(nlohmann::json& contents, std::stack<std::string> menu_stack, std::string key, T value) {
		std::vector<std::string> names;
		while (!menu_stack.empty()) {
			names.push_back(menu_stack.top());
			menu_stack.pop();
		}

		switch (names.size()) {
			case 1:
				contents[names.at(0)][key] = value;
				break;
			case 2:
				contents[names.at(0)][names.at(1)][key] = value;
				break;
			case 3:
				contents[names.at(0)][names.at(1)][names.at(2)][key] = value;
				break;
			case 4:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][key] = value;
				break;
			case 5:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][key] = value;
				break;
			case 6:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][key] = value;
				break;
			case 7:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][key] = value;
				break;
			case 8:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][key] = value;
				break;
			case 9:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][key] = value;
				break;
			case 10:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][key] = value;
				break;
			case 11:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][key] = value;
				break;
			case 12:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][names.at(11)][key] = value;
				break;
			case 13:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][names.at(11)][names.at(12)][key] = value;
				break;
			case 14:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][names.at(11)][names.at(12)][names.at(13)][key] = value;
				break;
			case 15:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][names.at(11)][names.at(12)][names.at(13)][names.at(14)][key] = value;
				break;
			case 16:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][names.at(11)][names.at(12)][names.at(13)][names.at(14)][names.at(15)][key] = value;
				break;
			case 17:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][names.at(11)][names.at(12)][names.at(13)][names.at(14)][names.at(15)][names.at(16)][key] = value;
				break;
			case 18:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][names.at(11)][names.at(12)][names.at(13)][names.at(14)][names.at(15)][names.at(16)][names.at(17)][key] = value;
				break;
			case 19:
				contents[names.at(0)][names.at(1)][names.at(2)][names.at(3)][names.at(4)][names.at(5)][names.at(6)][names.at(7)][names.at(8)][names.at(9)][names.at(10)][names.at(11)][names.at(12)][names.at(13)][names.at(14)][names.at(15)][names.at(16)][names.at(17)][names.at(18)][key] = value;
				break;
		}
	}

	nlohmann::json get_stack_value(std::stack<std::string> menu_stack, std::string key) {
		nlohmann::json contents = read_config_contents();
		if (!contents.empty()) {
			bool error = false;
			while (!menu_stack.empty()) {
				contents = contents[menu_stack.top()];
				if (contents.is_null()) {
					error = true;
					break;
				}

				menu_stack.pop();
			}

			if (error) return nlohmann::json();

			if (!contents[key].is_null()) {
				return contents[key];
			}
		}

		return nlohmann::json();
	}

	std::stack<std::string> increase_stack(std::stack<std::string> menu_stack, std::vector<std::string> Stacks) {
		std::vector<std::string> tmp;
		while (!menu_stack.empty()) {
			tmp.push_back(menu_stack.top());
			menu_stack.pop();
		}

		for (std::string stack : Stacks) tmp.push_back(stack);

		std::reverse(tmp.begin(), tmp.end());

		std::stack<std::string> return_;
		for (std::string stack : tmp) return_.push(stack);
		return return_;
	}

	std::string config::read_string(std::stack<std::string> name_stack, std::string key, std::string default_string, std::vector<std::string> additional_stacks) {
		if (!std::filesystem::exists(dirs::get_path(config))) return default_string;
		
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json json = get_stack_value(name_stack, key);
		if (json.is_null() || !json.is_string()) return default_string;
		return json.get<std::string>();
	}

	int config::read_int(std::stack<std::string> name_stack, std::string key, int default_int, std::vector<std::string> additional_stacks) {
		if (!std::filesystem::exists(dirs::get_path(config))) return default_int;
		
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json json = get_stack_value(name_stack, key);
		if (json.is_null() || !json.is_number_integer()) return default_int;
		return json.get<int>();
	}

	uint64_t config::read_uint64(std::stack<std::string> name_stack, std::string key, uint64_t default_int, std::vector<std::string> additional_stacks) {
		if (!std::filesystem::exists(dirs::get_path(config))) return default_int;
		
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json json = get_stack_value(name_stack, key);
		if (json.is_null() || !json.is_number_integer()) return default_int;
		return json.get<uint64_t>();
	}

	float config::read_float(std::stack<std::string> name_stack, std::string key, float default_float, std::vector<std::string> additional_stacks) {
		if (!std::filesystem::exists(dirs::get_path(config))) return default_float;

		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json json = get_stack_value(name_stack, key);
		if (json.is_null() || !json.is_number_float()) return default_float;
		return json.get<float>();
	}

	bool config::read_bool(std::stack<std::string> name_stack, std::string key, bool default_bool, std::vector<std::string> additional_stacks) {
		if (!std::filesystem::exists(dirs::get_path(config))) return default_bool;
		
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json json = get_stack_value(name_stack, key);
		if (json.is_null() || !json.is_boolean()) return default_bool;
		return json.get<bool>();
	}

	bool config::read_color(std::stack<std::string> name_stack, std::string key, color_rgba* color, std::vector<std::string> additional_stacks) {
		if (!std::filesystem::exists(dirs::get_path(config))) return false;
		
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json json = get_stack_value(name_stack, key);
		if (json.is_null() || !json.is_array() || json.size() != 4) return false;

		color->r = json[0].get<int>();
		color->g = json[1].get<int>();
		color->b = json[2].get<int>();
		color->a = json[3].get<int>();
		return true;
	}

	bool config::read_vector(std::stack<std::string> name_stack, std::string key, math::vector3_<float>* vec, std::vector<std::string> additional_stacks) {
		if (!std::filesystem::exists(dirs::get_path(config))) return false; 
		
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json json = get_stack_value(name_stack, key);
		if (json.is_null() || !json.is_array() || json.size() != 3) return false;

		vec->x = json[0].get<float>();
		vec->y = json[1].get<float>();
		vec->z = json[2].get<float>();
		return true;
	}

	void config::write_string(std::stack<std::string> name_stack, std::string key, std::string value, std::vector<std::string> additional_stacks) {
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json contents = read_config_contents();
		build_stack(contents, name_stack, key, value);
		write_config_contents(contents);
	}

	void config::write_int(std::stack<std::string> name_stack, std::string key, int value, std::vector<std::string> additional_stacks) {
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json contents = read_config_contents();
		build_stack(contents, name_stack, key, value);
		write_config_contents(contents);
	}

	void config::write_uint64(std::stack<std::string> name_stack, std::string key, uint64_t value, std::vector<std::string> additional_stacks) {
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json contents = read_config_contents();
		build_stack(contents, name_stack, key, value);
		write_config_contents(contents);
	}

	void config::write_float(std::stack<std::string> name_stack, std::string key, float value, std::vector<std::string> additional_stacks) {
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json contents = read_config_contents();
		build_stack(contents, name_stack, key, value);
		write_config_contents(contents);
	}

	void config::write_bool(std::stack<std::string> name_stack, std::string key, bool value, std::vector<std::string> additional_stacks) {
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json contents = read_config_contents();
		build_stack(contents, name_stack, key, value);
		write_config_contents(contents);
	}

	void config::write_color(std::stack<std::string> name_stack, std::string key, color_rgba value, std::vector<std::string> additional_stacks) {
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json contents = read_config_contents();
		build_stack(contents, name_stack, key, nlohmann::json::array({ value.r, value.g, value.b, value.a }));
		write_config_contents(contents);
	}

	void config::write_vector(std::stack<std::string> name_stack, std::string key, math::vector3_<float> value, std::vector<std::string> additional_stacks) {
		if (additional_stacks.size()) {
			name_stack = increase_stack(name_stack, additional_stacks);
		}

		nlohmann::json contents = read_config_contents();
		build_stack(contents, name_stack, key, nlohmann::json::array({ value.x, value.y, value.z }));
		write_config_contents(contents);
	}

	config* get_config() {
		static config instance;
		return &instance;
	}
}