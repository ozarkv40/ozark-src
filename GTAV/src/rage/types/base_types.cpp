#include "base_types.h"
#include "rage/engine.h"
#include "global/vars.h"

void guid_pool::for_each(std::function<void(Entity, void*)> callback) {
    for (uint32_t i = 0; i < m_count; i++) {
        if (get<char>(i)) {
            callback(rage::engine::get_entity_handle((uint64_t)get<char>(i)), get<void>(i));
        }
    }
}

void vehicle_pool::for_each(std::function<void(Entity, void*)> callback) {
    for (uint32_t i = 0; i < m_count; i++) {
        uint64_t address = get(i);
        if (address && is_valid_vtable(*(uint64_t*)address)) {
            callback(rage::engine::get_entity_handle(address), (void*)address);
        }
    }
}