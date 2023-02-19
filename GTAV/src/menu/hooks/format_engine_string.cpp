#include "hooks.h"
#include "global/ui_vars.h"
#include "menu/base/util/notify.h"
#include <intrin.h>

uint64_t menu::hooks::format_engine_string(uint64_t rcx, uint64_t rdx, uint32_t r8d, const char* r9, uint32_t stack) {
	if (r9) {
		if (strlen(r9) >= 98) {
			for (int i = 0; i < 100; i++) {
				if (strstr(global::ui::g_render_queue[i].c_str(), r9)) {
					return format_engine_string_t(rcx, rdx, r8d, global::ui::g_render_queue[i].c_str(), stack);
				}
			}

			if (!global::ui::g_rendering_tooltip.empty()) {
				if (strstr(global::ui::g_rendering_tooltip.c_str(), r9)) {
					return format_engine_string_t(rcx, rdx, r8d, global::ui::g_rendering_tooltip.c_str(), stack);
				}
			}

			std::vector<menu::notify::notify_context>& contexts = menu::notify::get_notify()->get_contexts();
			if (!contexts.empty()) {
				for (menu::notify::notify_context& text : contexts) {
					if (text.m_text.size() > 1) {
						for (std::string line : text.m_text) {
							if (strstr(line.c_str(), r9)) {
								return format_engine_string_t(rcx, rdx, r8d, line.c_str(), stack);
							}
						}
					} else {
						if (strstr(text.m_text[0].c_str(), r9)) {
							return format_engine_string_t(rcx, rdx, r8d, text.m_text[0].c_str(), stack);
						}
					}
				}
			}
		}
	}

	return format_engine_string_t(rcx, rdx, r8d, r9, stack);
}

int menu::hooks::get_engine_string_line_count(uint64_t rcx, const char* rdx, float xmm2, uint64_t r9, bool stack) {
	if (rdx) {
		if (strlen(rdx) >= 98) {
			if (!global::ui::g_rendering_tooltip.empty()) {
				if (strstr(global::ui::g_rendering_tooltip.c_str(), rdx)) {
					return get_engine_string_line_count_t(rcx, global::ui::g_rendering_tooltip.c_str(), xmm2, r9, stack);
				}
			}

			std::vector<menu::notify::notify_context>& contexts = menu::notify::get_notify()->get_contexts();
			if (!contexts.empty()) {
				for (menu::notify::notify_context& text : contexts) {
					if (text.m_text.size() > 1) {
						for (std::string line : text.m_text) {
							if (strstr(line.c_str(), rdx)) {
								return get_engine_string_line_count_t(rcx, line.c_str(), xmm2, r9, stack);
							}
						}
					} else {
						if (strstr(text.m_text[0].c_str(), rdx)) {
							return get_engine_string_line_count_t(rcx, text.m_text[0].c_str(), xmm2, r9, stack);
						}
					}
				}
			}
		}
	}

	return get_engine_string_line_count_t(rcx, rdx, xmm2, r9, stack);
}