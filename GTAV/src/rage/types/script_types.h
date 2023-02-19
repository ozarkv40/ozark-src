#pragma once
#include "stdafx.h"
#include "base_types.h"

namespace rage::script {
    struct script_header {
        char _0x0000[0x10];
        unsigned char** m_code_blocks_offset;
        char _0x0018[0x4];
        int m_code_length;
        char _0x0020[0x4];
        int m_local_count;
        char _0x0028[0x4];
        int m_native_count;
        uint64_t* m_local_offset;
        char _0x0038[0x8];
        uint64_t* m_natives;
        char _0x0048[0x10];
        uint32_t m_name_hash;
        char _0x005C[0x4];
        const char* m_name;
        char** m_strings_offset;
        int m_string_size;
        char _0x0074[0xC];
    };

    struct script_table_item {
        script_header* m_header;
        char _0x0008[0x4];
        uint32_t m_script_hash;
    };

    struct script_table {
        script_table_item* m_table;
        char _0x0008[0x10];
        int m_count;

        script_table_item* find(uint32_t script_hash) {
            if (m_table == nullptr) {
                return nullptr;
            }

            for (int i = 0; i < m_count; i++) {
                if (m_table[i].m_script_hash == script_hash) {
                    return &m_table[i];
                }
            }

            return nullptr;
        }
    };

    struct game_script_handler;
    struct game_script_handler_network_component;

    struct script_thread_context {
        uint32_t m_thread_id;
        uint32_t m_script_hash;
        eThreadState m_state;
        uint32_t m_instruction_pointer;
        uint32_t m_frame_pointer;
        uint32_t m_stack_pointer;
        float m_timer_a;
        float m_timer_b;
        float m_timer_c;
        char _0x0024[0x2C];
        uint32_t m_stack_size;
        char _0x0054[0x54];
    };

    struct script_thread {
        uint64_t m_vtable;
        script_thread_context m_context;
        void* m_stack;
        char _0x00B8[0x10];
        const char* m_exit_message;
        char m_name[0x40];
        game_script_handler* m_handler;
        game_script_handler_network_component* m_net_component;
    };

    struct gta_thread : script_thread {
        uint32_t m_script_hash;
        char _0x0124[0x14];
        uint32_t m_instance_id;
        char _0x013C[0x4];
        uint8_t m_flag;
        bool m_safe_for_network;
        char _0x0142[0x2];
        bool m_is_minigame;
        bool m_is_paused;
        char _0x0146[0x1];
        bool m_can_be_paused;
        bool m_can_remove_blips;
        char _0x0149[0xF];
    };

    struct game_script_id {
        char _0x0000[0x8];
        uint32_t m_hash;
        char m_name[0x20];
        char _0x002C[0x4];
        uint32_t m_timestamp;
        uint32_t m_script_id;
        uint32_t m_instance_id;
        uint32_t m_instance_hash;
        char _0x0040[0x10];
    };

    struct game_script_handler_network_component {
        uint64_t m_vtable;
        game_script_handler* m_component;
        int m_state;
        int m_pending_player_join_bitset;
    };

    struct game_script_handler {
        char _0x0000[0x18];
        gta_thread* m_thread;
        char _0x0020[0x28];
        game_script_handler_network_component* m_net_component;
        char _0x0050[0x10];
        game_script_id m_script_id;
    };
}