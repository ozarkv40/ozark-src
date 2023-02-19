#include "generic_types.h"
#include "rage/engine.h"
#include "util/caller.h"
#include "global/vars.h"
#include "util/log.h"

namespace rage::types {
    void replay_interface_camera::for_each(std::function<void(Entity, void*)> callback) {
        for (int i = 0; i < m_count; i++) {
            if (m_camera_list[i].m_entity) {
                callback(rage::engine::get_entity_handle((uint64_t)m_camera_list[i].m_entity), m_camera_list[i].m_entity);
            }
        }
    }

    void replay_interface_veh::for_each(std::function<void(Entity, vehicle*)> callback) {
        for (int i = 0; i < m_count; i++) {
            if (m_veh_list[i].m_entity) {
                callback(rage::engine::get_entity_handle((uint64_t)m_veh_list[i].m_entity), m_veh_list[i].m_entity);
            }
        }
    }

    void replay_interface_ped::for_each(std::function<void(Entity, ped*)> callback) {
        for (int i = 0; i < m_count; i++) {
            if (m_ped_list[i].m_entity) {
                callback(rage::engine::get_entity_handle((uint64_t)m_ped_list[i].m_entity), m_ped_list[i].m_entity);
            }
        }
    }
    
    void replay_interface_pickup::for_each(std::function<void(Entity, void*)> callback) {
        for (int i = 0; i < m_count; i++) {
            if (m_pickup_list[i].m_entity) {
                callback(rage::engine::get_entity_handle((uint64_t)m_pickup_list[i].m_entity), m_pickup_list[i].m_entity);
            }
        }
    }

    void replay_interface_object::for_each(std::function<void(Entity, object*)> callback) {
        for (int i = 0; i < m_count; i++) {
            if (m_object_list[i].m_entity) {
                callback(rage::engine::get_entity_handle((uint64_t)m_object_list[i].m_entity), m_object_list[i].m_entity);
            }
        }
    }
}