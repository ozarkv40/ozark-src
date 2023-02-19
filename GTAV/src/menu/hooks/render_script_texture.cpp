#include "hooks.h"
#include "util/caller.h"
#include "menu/base/util/player_manager.h"
#include "global/vars.h"
#include "global/ui_vars.h"
#include "rage/invoker/natives.h"
#include "rage/engine.h"

bool menu::hooks::render_script_textures(uint64_t table, uint32_t edx, uint32_t r8d) {
	uint32_t count = *(uint32_t*)(table + 0x9C40);
	if (count) {
		for (uint32_t i = 0; i < (count < 500 ? count : 500); i++) {
			caller::call<int>(global::vars::g_render_script_texture, table + (i * 0x50), edx, r8d);
		}

		if (count >= 500) {
			for (uint32_t i = 500; i < count; i++) {
				caller::call<int>(global::vars::g_render_script_texture, global::vars::g_texture_bypass + ((i - 500) * 0x50), edx, r8d);
			}
		}
	}

	if (global::ui::m_line_2d) {
		struct vertex {
			math::vector3_<float> m_position;
			math::vector2<float> m_uv;
			uint32_t m_color;
		};

		for (int i = 0; i < global::ui::g_line_2d_index; i++) {
			line_2d line = global::ui::m_line_2d[i];
			vertex vertices[2];
			memset(vertices, 0, sizeof(vertices));

			vertices[0].m_position = { line.m_from.x, line.m_from.y, 0.f };
			vertices[0].m_uv = { 0.f, 0.f };
			vertices[0].m_color = line.m_color.to_argb(); // argb

			vertices[1].m_position = { line.m_to.x, line.m_to.y, 0.f };
			vertices[1].m_uv = { 0.f, 0.f };
			vertices[1].m_color = line.m_color.to_argb(); // argb

			rage::engine::vertex_begin(2, 2);

			for (int i = 0; i < 2; i++) {
				rage::engine::vertex_add(vertices[i].m_position.x, vertices[i].m_position.y, vertices[i].m_position.z, 0.f, 0.f, 0.f, vertices[i].m_color, vertices[i].m_uv.x, vertices[i].m_uv.y);
			}

			rage::engine::vertex_end();
		}
	}

	return true;
}

void menu::hooks::reset_script_render_params() {
	if (*(uint32_t*)global::vars::g_reset_script_render_params[0] != *(uint32_t*)global::vars::g_reset_script_render_params[1]) {
		global::ui::g_line_2d_index = 0;
	}

	reset_script_render_params_t();
}

uint64_t menu::hooks::get_next_grc_texture(uint64_t table) {
	uint32_t count = *(uint32_t*)(table + 0x9C40);
	if (count >= 500 && count < 5000) {
		*(uint32_t*)(table + 0x9C40) = count + 1;
		return global::vars::g_texture_bypass + ((count - 500) * 0x50);
	}

	return get_next_grc_texture_t(table);
}

void menu::hooks::translate_marker_to_screen(rage::types::marker_table* table) {
	bool bypass = true;

	for (int i = 0; i < 128; i++) {
		if (!table[i].m_in_use) {
			bypass = false;
		}
	}

	if (bypass) {
		int block_size = sizeof(rage::types::marker_table) * 128;
		for (int i = 0; i < 10; i++) {
			// we setup 10 blocks extra, render one by one, if there isn't anything to render it wont do shit
			translate_marker_to_screen_t((rage::types::marker_table*)(global::vars::g_marker_bypass + (block_size * i)));
		}
	}

	translate_marker_to_screen_t(table);
}

void menu::hooks::render_markers_to_screen(rage::types::marker_table* table) {
	bool bypass = true;

	for (int i = 0; i < 128; i++) {
		if (!table[i].m_in_use) {
			bypass = false;
		}
	}

	if (bypass) {
		int block_size = sizeof(rage::types::marker_table) * 128;
		for (int i = 0; i < 10; i++) {
			// we setup 10 blocks extra, render one by one, if there isn't anything to render it wont do shit
			render_markers_to_screen_t((rage::types::marker_table*)(global::vars::g_marker_bypass + (block_size * i)));
		}
	}

	render_markers_to_screen_t(table);
}

int menu::hooks::get_next_marker_texture_index(rage::types::marker_table* table) {
	if (table == (rage::types::marker_table*)global::vars::g_marker_bypass) {
		for (int i = 0; i < 1280; i++) {
			rage::types::marker_table* marker = (rage::types::marker_table*)(global::vars::g_marker_bypass + (i * sizeof(rage::types::marker_table)));
			if (!marker->m_in_use) {
				return i;
			}
		}

		return -1;
	}

	return get_next_marker_texture_index_t(table);
}

int menu::hooks::add_marker_to_table(rage::types::marker_table* table, uint64_t marker) {
	for (int i = 0; i < 128; i++) {
		if (!table[i].m_in_use) {
			return add_marker_to_table_t(table, marker);
		}
	}

	for (int i = 0; i < 1280; i++) {
		rage::types::marker_table* marker_ptr = (rage::types::marker_table*)(global::vars::g_marker_bypass + (i * sizeof(rage::types::marker_table)));
		if (!marker_ptr->m_in_use) {
			return add_marker_to_table_t((rage::types::marker_table*)global::vars::g_marker_bypass, marker);
		}
	}

	return add_marker_to_table_t(table, marker);
}