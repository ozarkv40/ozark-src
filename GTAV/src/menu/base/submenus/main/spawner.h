#pragma once
#include "menu/base/submenu.h"
#include <array>

class spawner_menu : public menu::submenu::submenu {
public:
	static spawner_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::vars {
	enum eSpawnerFlag {
		SPAWNER_SELF,
		SPAWNER_PLAYER,
		SPAWNER_SESSION
	};

	struct variables {
		int m_type;
		std::array<std::vector<uint32_t>, 23> m_vehicle_hashes;

		int m_popular;
		int m_story;
		int m_animals;
		int m_emergency;
		int m_role;
		int m_ambient;
		int m_misc;

		eSpawnerFlag m_flag;
	};

	void spawn_vehicle(uint32_t hash, std::function<void(Entity)> callback = [](Entity) {}, bool garage = false);
	void spawn_object(uint32_t model, std::string esp_name, std::function<void(Entity)> callback = [](Entity) {});
	void spawn_ped(uint32_t model, std::string esp_name, std::function<void(Entity)> callback = [](Entity) {});
	const char* get_class_name(int class_id);
	extern variables m_vars;
}