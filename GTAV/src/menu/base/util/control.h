#pragma once
#include "stdafx.h"
#include "rage/types/base_types.h"
#include <functional>
#include <queue>

namespace menu::control {
	struct request_control_context {
		Entity m_entity;
		std::vector<std::function<void(Entity)>> m_callbacks;
		std::function<void(Entity, int)> m_callback_with_owner;
		int m_tries;
		bool m_take_owner;

	};

	struct request_model_context {
		uint32_t m_model;
		std::function<void(uint32_t)> m_callback;
		int m_tries;
	};

	struct request_particle_fx_context {
		std::pair<const char*, const char*> m_asset;
		std::function<void(std::pair<const char*, const char*>)> m_callback;
		int m_tries;
	};

	struct request_weapon_asset_context {
		uint32_t m_model;
		std::function<void(uint32_t)> m_callback;
		int m_tries;
	};

	struct request_animation_context {
		std::string m_animation;
		std::function<void()> m_callback;
		int m_tries;
	};

	class control_manager {
	public:
		void update();

		void request_control(Entity entity, std::function<void(Entity)> callback, bool take_owner = false);
		void request_control(Entity entity, std::function<void(Entity, int)> callback, bool take_owner = false);
		void request_model(uint32_t model, std::function<void(uint32_t)> callback);
		void request_animation(std::string animation, std::function<void()> callback);
		void request_particle(std::pair<const char*, const char*> asset, std::function<void(std::pair<const char*, const char*>)> callback);
		void request_weapon(uint32_t weapon, std::function<void(uint32_t)> callback);

		void simple_request_model(uint32_t model);
		void simple_request_control(Entity entity, bool take_owner = false);
		void simple_request_weapon(uint32_t weapon);
		void simple_request_dictionary(std::string dictionary);
	private:
		std::vector<request_control_context> m_control;
		std::queue<request_model_context> m_model;
		std::queue<request_particle_fx_context> m_particle;
		std::queue<request_weapon_asset_context> m_weapon;
		std::queue<request_animation_context> m_animation;
	};

	control_manager* get_control_manager();

	inline void update() {
		get_control_manager()->update();
	}

	inline void request_control(Entity entity, std::function<void(Entity)> callback, bool take_owner = false) {
		get_control_manager()->request_control(entity, callback, take_owner);
	}

	inline void request_control(Entity entity, std::function<void(Entity, int)> callback, bool take_owner = false) {
		get_control_manager()->request_control(entity, callback, take_owner);
	}

	inline void request_model(uint32_t model, std::function<void(uint32_t)> callback) {
		get_control_manager()->request_model(model, callback);
	}

	inline void request_animation(std::string animation, std::function<void()> callback) {
		get_control_manager()->request_animation(animation, callback);
	}

	inline void request_particle(std::pair<const char*, const char*> asset, std::function<void(std::pair<const char*, const char*>)> callback) {
		get_control_manager()->request_particle(asset, callback);
	}

	inline void request_weapon(uint32_t weapon, std::function<void(uint32_t)> callback) {
		get_control_manager()->request_weapon(weapon, callback);
	}

	inline void simple_request_model(uint32_t model) {
		get_control_manager()->simple_request_model(model);
	}

	inline void simple_request_control(Entity entity, bool take_owner = false) {
		get_control_manager()->simple_request_control(entity, take_owner);
	}

	inline void simple_request_weapon(uint32_t weapon) {
		get_control_manager()->simple_request_weapon(weapon);
	}

	inline void simple_request_dictionary(std::string dictionary) {
		get_control_manager()->simple_request_dictionary(dictionary);
	}
}