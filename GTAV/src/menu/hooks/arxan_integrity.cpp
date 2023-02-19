#include "hooks.h"

void menu::hooks::arxan_integrity_start1(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[0] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][0], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][0], 25);
	return arxan_integrity_start1_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_end1(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[1] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][1], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][1], 25);
	return arxan_integrity_end1_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_start2(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[2] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][0], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][0], 25);
	return arxan_integrity_start2_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_end2(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[3] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][1], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][1], 25);
	return arxan_integrity_end2_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_start3(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[4] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][0], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][0], 25);
	return arxan_integrity_start3_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_end3(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[5] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][1], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][1], 25);
	return arxan_integrity_end3_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_start4(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[6] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][0], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][0], 25);
	return arxan_integrity_start4_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_end4(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[7] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][1], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][1], 25);
	return arxan_integrity_end4_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_start5(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[8] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][0], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][0], 25);
	return arxan_integrity_start5_t(rcx, rdx, r8, r9);
}

void menu::hooks::arxan_integrity_end5(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9) {
	global::vars::g_arxan_called[9] = true;
	memcpy((void*)global::vars::g_arxan_restore_addresses[0], global::vars::g_arxan_restore_bytes[0][1], 25);
	memcpy((void*)global::vars::g_arxan_restore_addresses[1], global::vars::g_arxan_restore_bytes[1][1], 25);
	return arxan_integrity_end5_t(rcx, rdx, r8, r9);
}