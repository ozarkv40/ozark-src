#include "hooks.h"
#include "menu/base/submenus/main/misc/misc_disables.h"

enum eProfanity {
	PROFANITY_CHAT_CLEAN = -1,
	PROFANITY_CLEAN,
	PROFANITY_DIRTY,
	PROFANITY_UNK,
	PROFANITY_ERROR
};

int menu::hooks::check_chat_profanity(uint64_t rcx, uint64_t rdx, uint64_t r8) {
	if (misc::disables::vars::m_vars.m_disable_profanity_filter) {
		return PROFANITY_CHAT_CLEAN;
	}

	return check_chat_profanity_t(rcx, rdx, r8);
}

int menu::hooks::check_string_profanity(uint64_t rcx, uint64_t rdx, uint64_t r8) {
	if (misc::disables::vars::m_vars.m_disable_profanity_filter) {
		return PROFANITY_CLEAN;
	}

	return check_string_profanity_t(rcx, rdx, r8);
}