#include "invoker_types.h"
#include "util/caller.h"
#include "global/vars.h"

namespace rage::invoker {
	uint64_t native_registration::get_handler(uint64_t hash) {
		return caller::call<uint64_t>(global::vars::g_translate_native, global::vars::g_native_registration, hash);
	}
}