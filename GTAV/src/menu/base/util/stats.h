#pragma once
#include "stdafx.h"

template<class T>
class stats {
public:
	static void set(const char* stat_name, T value);
	static T get(const char* stat_name);

	static void set(uint32_t stat_hash, T value);
	static T get(uint32_t stat_hash);
};