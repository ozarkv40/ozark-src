#include "stats.h"
#include "rage/invoker/natives.h"
#include "menu/base/submenus/main/network/network_account.h"

template<class T>
void stats<T>::set(const char* stat_name, T value) {
	bool use_character = strstr(stat_name, "MPPLY") == NULL && strstr(stat_name, "MP_PLAYING_TIM") == NULL;

	char stat[100];
	sprintf_s(stat, "%s%s", use_character ? ("MP" + std::to_string(network::account::vars::m_vars.m_selected_character) + "_").c_str() : "", stat_name);

	if (std::is_same<T, int>::value) {
		native::stat_set_int(native::get_hash_key(stat), (int)value, true);
	} else if (std::is_same<T, float>::value) {
		native::stat_set_float(native::get_hash_key(stat), (float)value, true);
	} else if (std::is_same<T, bool>::value) {
		native::stat_set_bool(native::get_hash_key(stat), (bool)value, true);
	}
}

template<class T>
T stats<T>::get(const char* stat_name) {
	T _return;
	bool use_character = strstr(stat_name, "MPPLY") == NULL && strstr(stat_name, "MP_PLAYING_TIM") == NULL;

	char stat[100];
	sprintf_s(stat, "%s%s", use_character ? ("MP" + std::to_string(network::account::vars::m_vars.m_selected_character) + "_").c_str() : "", stat_name);

	if (std::is_same<T, int>::value) {
		native::stat_get_int(native::get_hash_key(stat), (int*)&_return, true);
	} else if (std::is_same<T, float>::value) {
		native::stat_get_float(native::get_hash_key(stat), (float*)&_return, true);
	} else if (std::is_same<T, bool>::value) {
		native::stat_get_bool(native::get_hash_key(stat), (bool*)&_return, true);
	}

	return _return;
}

template<class T>
void stats<T>::set(uint32_t stat_hash, T value) {
	if (std::is_same<T, int>::value) {
		native::stat_set_int(stat_hash, (int)value, true);
	} else if (std::is_same<T, float>::value) {
		native::stat_set_float(stat_hash, (float)value, true);
	} else if (std::is_same<T, bool>::value) {
		native::stat_set_bool(stat_hash, (bool)value, true);
	}
}

template<class T>
T stats<T>::get(uint32_t stat_hash) {
	T _return;

	if (std::is_same<T, int>::value) {
		native::stat_get_int(stat_hash, (int*)&_return, true);
	} else if (std::is_same<T, float>::value) {
		native::stat_get_float(stat_hash, (float*)&_return, true);
	} else if (std::is_same<T, bool>::value) {
		native::stat_get_bool(stat_hash, (bool*)&_return, true);
	}

	return _return;
}

template class stats<int>;
template class stats<float>;
template class stats<bool>;
