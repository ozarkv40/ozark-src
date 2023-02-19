#include "control.h"
#include "rage/invoker/natives.h"
#include "menu/base/util/player_manager.h"
#include "util/fiber.h"
#include "util/log.h"
#include "rage/engine.h"

namespace menu::control {
	void control_manager::update() {
		if (m_control.size()) {
			request_control_context& request = m_control.front();

			int old_owner = 0;
			bool exists = native::does_entity_exist(request.m_entity);

			int network_id = 0;
			if (exists) {
				rage::types::ped* ptr = (rage::types::ped*)rage::engine::get_entity_address(request.m_entity);
				if (ptr) {
					if (ptr->get_net_obj()) {
						network_id = ptr->get_net_obj()->m_network_id;
					}
				}

				if (network_id) {
					if (request.m_take_owner) {
						if (rage::engine::get_network_object_owner(request.m_entity) != menu::player::get_local_player().m_id) {
							old_owner = rage::engine::get_network_object_owner(request.m_entity);

							uint64_t manager = *(uint64_t*)global::vars::g_network_object_manager;
							if (manager) {
								if (*(uint64_t*)(manager + 0x2710) > 0xFFFFFFFF) {
									if (!native::is_ped_a_player(request.m_entity)) {
										rage::engine::update_network_object_owner(request.m_entity, menu::player::get_local_player().m_id);
									}
								}
							}
						}
					}
				}

				if ((native::network_has_control_of_entity(request.m_entity) || (network_id > 0 && native::network_has_control_of_network_id(network_id))) || request.m_tries > 50) {
					if (request.m_tries < 50) {
						if (!request.m_callbacks.empty()) {
							for (auto c : request.m_callbacks) {
								if (c) {
									c(request.m_entity);
								}
							}
						}

						if (request.m_callback_with_owner) request.m_callback_with_owner(request.m_entity, old_owner);
					}

					m_control.erase(m_control.begin());
				} else {
					request.m_tries++;
					native::network_request_control_of_entity(request.m_entity);

					if (network_id) {
						native::set_network_id_can_migrate(network_id, true);
						native::network_request_control_of_network_id(network_id);
					}
				}
			} else {
				m_control.erase(m_control.begin());
			}
		}

		if (m_model.size()) {
			request_model_context& request = m_model.front();
			if (native::has_model_loaded(request.m_model) || request.m_tries > 30) {
				if (request.m_tries < 30) {
					request.m_callback(request.m_model);
				}

				m_model.pop();
			} else {
				request.m_tries++;
				native::request_model(request.m_model);
			}
		}

		if (m_particle.size()) {
			request_particle_fx_context& request = m_particle.front();
			if (native::has_named_ptfx_asset_loaded(request.m_asset.first) || request.m_tries > 30) {
				if (request.m_tries < 30) {
					request.m_callback(request.m_asset);
				}

				m_particle.pop();
			} else {
				request.m_tries++;
				native::request_named_ptfx_asset(request.m_asset.first);
			}
		}

		if (m_weapon.size()) {
			request_weapon_asset_context& request = m_weapon.front();
			if (native::has_weapon_asset_loaded(request.m_model) || request.m_tries > 30) {
				if (request.m_tries < 30) {
					request.m_callback(request.m_model);
				}

				m_weapon.pop();
			} else {
				request.m_tries++;
				native::request_weapon_asset(request.m_model, 31, 0);
			}
		}

		if (m_animation.size()) {
			request_animation_context& request = m_animation.front();
			if (native::has_anim_dict_loaded(request.m_animation.c_str()) || request.m_tries > 30) {
				if (request.m_tries < 30) {
					request.m_callback();
				}

				m_animation.pop();
			} else {
				request.m_tries++;
				native::request_anim_dict(request.m_animation.c_str());
			}
		}
	}

	void control_manager::request_control(Entity entity, std::function<void(Entity)> callback, bool take_owner) {
		if (!native::network_is_in_session()) {
			callback(entity);
		} else {
			auto vit = std::find_if(begin(m_control), end(m_control), [=] (request_control_context& c) { return c.m_entity == entity; });

			if (vit == end(m_control)) {
				m_control.push_back({ entity, { callback }, nullptr, 0, take_owner });
			} else {
				bool exists = false;
				for (auto c : vit->m_callbacks) {
					if ((uint64_t)&c == (uint64_t)&callback) {
						exists = true;
						break;
					}
				}

				if (!exists) {
					vit->m_callbacks.push_back(callback);
				}
			}
		}
	}

	void control_manager::request_control(Entity entity, std::function<void(Entity, int)> callback, bool take_owner) {
		m_control.push_back({ entity, { nullptr }, callback, 0, take_owner });
	}

	void control_manager::request_model(uint32_t model, std::function<void(uint32_t)> callback) {
		m_model.push({ model, callback, 0 });
	}

	void control_manager::request_animation(std::string animation, std::function<void()> callback) {
		m_animation.push({ animation, callback, 0 });
	}

	void control_manager::request_particle(std::pair<const char*, const char*> asset, std::function<void(std::pair<const char*, const char*>)> callback) {
		m_particle.push({ asset, callback, 0 });
	}

	void control_manager::request_weapon(uint32_t model, std::function<void(uint32_t)> callback) {
		m_weapon.push({ model, callback, 0 });
	}

	void control_manager::simple_request_model(uint32_t model) {
		int tries = 0;
		while (!native::has_model_loaded(model) && tries < 25) {
			native::request_model(model);
			tries++;
			util::fiber::go_to_main();
		}
	}

	void control_manager::simple_request_control(Entity entity, bool take_owner) {
		int tries = 0;
		while (native::does_entity_exist(entity) && !native::network_has_control_of_entity(entity) && tries < 30 && native::network_is_session_active()) {
			native::network_request_control_of_entity(entity);

			uint16_t network_id = 0;
			rage::types::ped* ptr = (rage::types::ped*)rage::engine::get_entity_address(entity);
			if (ptr) {
				if (ptr->get_net_obj()) {
					network_id = ptr->get_net_obj()->m_network_id;
				}
			}

			if (network_id) {
				native::set_network_id_can_migrate(network_id, 1);

				if (take_owner) {
					if (rage::engine::get_network_object_owner(entity) != menu::player::get_local_player().m_id) {
						uint64_t manager = *(uint64_t*)global::vars::g_network_object_manager;
						if (manager) {
							if (*(uint64_t*)(manager + 0x2710) > 0xFFFFFFFF) {
								if (!native::is_ped_a_player(entity)) {
									rage::engine::update_network_object_owner(entity, menu::player::get_local_player().m_id);
								}
							}
						}
					}
				}
			}

			util::fiber::go_to_main();
			tries++;
		}
	}

	void control_manager::simple_request_weapon(uint32_t model) {
		int tries = 0;
		while (!native::has_weapon_asset_loaded(model) && tries < 30) {
			native::request_weapon_asset(model, 31, 0);
			tries++;
			util::fiber::go_to_main();
		}
	}

	void control_manager::simple_request_dictionary(std::string dictionary) {
		int tries = 0;
		while (!native::has_streamed_texture_dict_loaded(dictionary.c_str()) && tries < 30) {
			native::request_streamed_texture_dict(dictionary.c_str(), false);
			tries++;
			util::fiber::go_to_main();
		}
	}

	control_manager* get_control_manager() {
		static control_manager instance;
		return &instance;
	}
}