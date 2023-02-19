#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"

class helper_esp_menu : public menu::submenu::submenu {
public:
	static helper_esp_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	helper_esp_menu()
		: menu::submenu::submenu() {}
};

namespace helper::esp::vars {
	struct esp_rainbow {
		menu::rainbow m_rainbow;
		bool m_rainbow_toggle;
	};

	struct esp_context {
		bool m_ped; // enables skeleton>weapon

		bool m_name;
		bool m_snapline;
		bool m_2d_box;
		bool m_2d_corners;
		bool m_3d_box;
		bool m_3d_axis;
		bool m_skeleton_bones;
		bool m_skeleton_joints;
		bool m_weapon;

		int m_name_type;

		color_rgba m_name_text_color = color_rgba(255, 255, 255, 255);
		color_rgba m_name_bg_color = color_rgba(0, 0, 0, 180);
		color_rgba m_snapline_color = color_rgba(255, 0, 255, 255);
		color_rgba m_2d_box_color = color_rgba(255, 0, 255, 255);
		color_rgba m_2d_corners_color = color_rgba(255, 0, 255, 255);
		color_rgba m_3d_box_color = color_rgba(255, 0, 255, 255);
		color_rgba m_skeleton_bones_color = color_rgba(255, 0, 255, 255);
		color_rgba m_skeleton_joints_color = color_rgba(255, 0, 255, 255);
		color_rgba m_weapon_color = color_rgba(255, 255, 255, 255);

		esp_rainbow m_name_text_rainbow;
		esp_rainbow m_name_bg_rainbow;
		esp_rainbow m_snapline_rainbow;
		esp_rainbow m_2d_box_rainbow;
		esp_rainbow m_2d_corners_rainbow;
		esp_rainbow m_3d_box_rainbow;
		esp_rainbow m_skeleton_bones_rainbow;
		esp_rainbow m_skeleton_joints_rainbow;
		esp_rainbow m_weapon_rainbow;
	};

	struct variables {
		esp_context* m_current;
	};

	void name_esp(esp_context context, Entity entity, std::string name_override = "");
	void snapline_esp(esp_context context, Entity entity);
	void _2d_esp(esp_context context, Entity entity, int type);
	void _3d_esp(esp_context context, Entity entity, int type);
	void skeleton_esp(esp_context context, Entity entity, int type);
	extern variables m_vars;
}