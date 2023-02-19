#pragma once
#include "stdafx.h"
#include "util/math.h"
#include "base_types.h"
#include "bit_buffer.h"

#pragma pack(push)
#pragma pack(1)
namespace rage::network {
    struct player_info;
    struct camera_manager_angles;
    struct camera_angles;
    struct player_angles;
    struct net_object;

    struct read_stats_by_gamer {
        uint32_t m_bank_balance;
        uint32_t m_wallet_balance;
        uint32_t m_rank;
        int m_kills;
        int m_deaths;
    };

    struct stat_response_item {
        int m_padding;
        uint8_t m_type; // 0 = int, 3 = float

        union {
            int m_int;
            uint32_t m_uint;
            float m_float;
        } value;
    };

    struct stat_response {
        stat_response_item* m_stats;
    };

    struct attach_data_node {
        char _0x0000[0xC0];
        bool m_attached;
        bool m_unk;
        uint16_t m_network_id;
    };

    struct transaction {
        int m_id;
        int m_variation;
        int m_price;
        int m_multiplier;
        int m_value;
    };

    struct net_shop_transaction_basket {
        char _0x0000[0x8];
        int m_transaction_id;
        char _0x000C[0xC];
        int m_category;
        char _0x001C[0x8];
        int m_action;
        int m_target; // 4 = bank etc
        char _0x002C[0xB4];
        transaction m_transactions[71];
        int m_transaction_count;
    };

    struct transaction_node {
        char _0x0000[0x8];
        net_shop_transaction_basket* m_transaction;
        transaction_node* m_next;
    };

    struct metric {
        virtual ~metric();
        virtual int get_type();
        virtual int get_sub_type();
        virtual const char* get_name();
        virtual bool create_json(uint64_t Json);
        virtual int get_size();
        virtual uint32_t get_hashed_name();
    };

    struct net_shop_queue {
        char _0x0000[32];
        void* m_first;
        void* m_last;
        char _0x0030[9];
        bool m_is_busy1;
        char _0x003A[14];
        bool m_is_busy2;
        char _0x0049[7];
        bool m_is_busy3;
    };

    struct rockstar_identifier {
        uint64_t m_rockstar_id;
        uint32_t m_type;
        uint32_t m_sub_type;
    };

    struct gs_session {
        uint64_t m_peer_token;
        uint64_t m_peer_token2;
        uint64_t m_peer_token3;
        rockstar_identifier m_rockstar_id;
        char _0x0028[0x48];

        uint32_t get_local_ip() {
            return *(uint32_t*)((uint64_t)this + 0x64);
        }
    };

    struct join_request {
        uint32_t m_flags;
        char _0x0004[0x4];
        uint64_t m_net_game_player_data_msg;
        uint32_t m_game_version; // 0x10
        char _0x0014[0x4];
        int m_ros_flags; // 0x18
        char m_nigger[0x300];
    };

    struct player_gamer_data_node {
        char _0x0000[0xC8];
        int m_crew_id;
        char _0x00cc[0x12];
        char m_crew_name[0x19];
        char m_crew_abbr[0x5];
        char m_crew_motto[0x4C];
        char m_crew_rank[0x18];
    };

    struct global_msg_context {
        char m_message[0x100];
        uint64_t m_sender_chat_token;
        bool m_flag0_is_neg1;
    };

    struct player_peer {
        uint8_t get_bitset() {
            return *(uint8_t*)((uint64_t)this + 0x28);
        }

        uint8_t get_flag() {
            return *(uint8_t*)((uint64_t)this + 0x18);
        }

        int get_player_key() {
            return *(int*)((uint64_t)this);
        }

        int get_secondary_key() {
			return *(int*)((uint64_t)this + 0x4);
        }

        uint32_t get_ip() {
			return *(uint32_t*)((uint64_t)this + 0xC);
        }
    };

    struct global_chat_raw {
        char _0x0000[0x180];
        int m_flag0;
        char _0x0184[0x1D24];
        player_peer* m_player_peers[0x20];
        int m_player_count;
        char _0x1fac[0xC];
        uint64_t m_manager_ptr;
        int m_flag1;
        int m_flag2;
        char _0x1fc8[0x30];
        uint8_t m_bitset;
    };

    struct rs_info {
        char m_scs_ticket[0x100];
        char _0x0100[0x100];
        char m_session_ticket[0x90];
        uint64_t m_peer;
        char _0x0298[0xA7];
        char m_email[0x50];
        char _0x038f[0x20];
        char m_name[0x20];
        char _0x03cf[0x29];
        uint32_t m_rockstar_id;
        char _0x03FC[0x1DC];
        uint8_t m_session_key[0x10];
    };

    struct network_handle {
        int m_handle;
        char _0x0[48];
    };

    struct net_msg_identifier {
        uint64_t m_rockstar_id;
        uint8_t m_type;
        char _0x0009[0xB];
    };

    struct net_msg_text_message {
        char m_message[0x100];
        net_msg_identifier m_sender;
    };

    struct network_gamer_cmd {
        char _0x0000[0x10];
        uint64_t m_rockstar_id; // 0x10
        char _0x0018[0x3C];
        uint32_t m_ip; // 0x54
        char _0x0058[0x10];
        uint64_t m_host_token; // 0x68
        uint64_t m_chat_token; // 0x70
        net_msg_identifier m_identifier; // 0x78
        char m_name[0x14]; // 0x8C
        char _0x00A0[0x8];
        uint32_t m_msg_ip; // 0xA8

        void set_ip(int index, uint8_t ip) {
            uint8_t* val = (uint8_t*)&m_ip;
            val[index] = ip;

            val = (uint8_t*)&m_msg_ip;
            val[index] = ip;
        }
    };

    struct game_camera_angles {
        camera_manager_angles* m_camera_manager_angles;
        char _0x0008[56];
    };

    struct camera_manager_angles {
        camera_angles* m_camera_angles;
    };

    struct camera_angles {
        char _0x0000[0x3C0];
        player_angles* m_fps_player_angles;
        char _0x03C8[0x10];
        uint64_t m_ped;
    };

    struct player_angles {
        char _0x0000[0x40];
        math::vector3_<float> m_view_angles;
        char _0x0004C[0x14];
        math::vector3_<float> m_crosshair_location;
    };

    struct player_info {
        char _0x0000[0x20];
        uint64_t m_host_token2;
        uint64_t m_rockstar_id;
        char _0x0030[0x3C];
        uint32_t m_external_ip;
        uint32_t m_external_port;
        uint32_t m_internal_ip;
        uint32_t m_internal_port;
        char _0x007C[0x4];
        uint64_t m_host_token;
        uint64_t m_chat_token;
        net_msg_identifier m_identifier;
        char m_name[0x14]; // A4
        char _0x00B8[0xB4];
        float m_swim_speed; // 16C
        float m_run_speed; // 170
        char _0x0174[0xA4];
        uint32_t m_frame_flags; // 218
        char _0x021C[0xDD4];
        char _new_padding[0x10];
        uint32_t m_aim_flag; // FF0

        bool is_free_aiming() {
            return m_aim_flag >> 6 & 1;
        }

        void set_ip(int Index, uint8_t IP) {
            uint8_t* Val = (uint8_t*)&m_external_ip;
            Val[Index] = IP;
        }

        void set_run_speed(float Speed) {
            *(float*)((uint64_t)this + 0xCF0) = Speed;
        }
    };

    struct net_game_player {
        char _0x0000[0x21];
        int8_t m_id;
        char _0x0022[0x7E];
        player_info* m_player_info;
        char _0x00b8[0xF1];
        bool m_is_rockstar_developer; // 1A9
        bool m_is_rockstar_qa; // 1AA
        bool m_is_cheater; // 1AB
        char _0x01AB[0x94];
        uint8_t m_report_bits; // 240
        char _0x0241[0x3];
        int* m_report_reasons; // 244
        char _0x024C[0x48];
        int m_max_report_reasons; // 294

        const char* get_crew_motto() {
            return (const char*)((uint64_t)this + 0x104);
        }

        const char* get_crew_name() {
            return (const char*)((uint64_t)this + 0xE6);
        }

        const char* get_crew_tag() {
            return (const char*)((uint64_t)this + 0xFF);
        }

        const char* get_crew_rank() {
            return (const char*)((uint64_t)this + 0x150);
        }

        int get_crew_id() {
            return *(int*)((uint64_t)this + 0x148);
        }
    };

    struct net_object {
        uint64_t m_vtable;
        eNetObjectTypes m_type;
        int16_t m_network_id;
        char _0x000C[0x14];
        int8_t m_player_sync_intervals[0x20];
        char _0x0040[0x9];
        uint8_t m_owner; // 0x49
        char _0x004A[0x6];
        uint64_t m_entity;
        char _0x0058[0x4C0];
        int16_t m_spectating_network_id;
    };

    struct data_node_common_operations {
        virtual ~data_node_common_operations();

        uint64_t m_data;
    };

    struct data_node {
        virtual ~data_node() = 0;
        virtual bool is_data_node() = 0;
        virtual bool is_parent_node() = 0;

        data_node* m_next; //0x0008
        data_node* m_previous; //0x0010
        uint64_t m_sync_tree; //0x0018
        data_node* m_parent; //0x0020
        uint32_t m_flag; //0x0028
        uint32_t m_flag2; //0x002C
        uint32_t m_flag3; //0x0030
        char _0x0034[0x4]; //0x0034
        data_node* m_first_child; //0x0038
        data_node* m_last_child; //0x0040
        uint64_t m_unk_data; //0x0048
        uint32_t m_child_count; //0x0050
        char _0x0054[0x54];
        data_node_common_operations* m_data_node_common_operations; // 0xA8

        bool is_writing() {
            return *(bool*)((uint64_t)this + 0x40);
        }
    };

    struct friends {
        char _0x0000[128]; //0x0000
        char m_name[32]; //0x0080
        char _0x00A0[24]; //0x00A0
        uint64_t m_rockstar_id; //0x00B8
        char _0x00C0[4]; //0x00C0
        int m_state; //0x00C4
        char _0x00C8[312]; //0x00C8
    };

    struct event_added_gamer {
        char _0x0000[0x6C];
        uint32_t m_external_ip;		// 0x006C
        char _0x0070[0x20];			// 0x0070
        uint64_t m_rockstar_id;		// 0x0090
        char _0x00098[0xC];			// 0x0098
        char m_name[0x14];			// 0x00A4
    };

    struct blacklisted_player {
        net_msg_identifier m_player;
        uint32_t m_timestamp;
        blacklisted_player* m_next;
        blacklisted_player* m_last;
    };

    struct network_base_config {
        char _0x0000[0x20];
		uint64_t m_unk_ptr;
		uint64_t m_unk_ptr2;
        char _0x0030[0x198F8];
        net_msg_identifier m_last_blacklisted; // 0x19928
        uint32_t m_last_blacklisted_timestamp;
        char _0x184b0[0x280];
        blacklisted_player* m_first_blacklisted_player; 
        blacklisted_player* m_last_blacklisted_player;

        void set_network_session_was_invited(bool invited);

        gs_session* get_gs_session() {
            return (gs_session*)((uint64_t)this + 0x178);
        }

        uint64_t get_net_msg_manager() {
            return *(uint64_t*)((uint64_t)this + 0x48);
        }
    };

    struct kick_peer {
        uint64_t m_peer;
        char _0x0008[5];
        bool m_kicked;
        char _0x000E[2];
    };

    struct list_kick_peers {
        kick_peer m_peers[0x20];
    };

    struct sync_tree {
        void* m_vtable;
        net_object* m_object;
        data_node* m_parent_node;
        char _0x0018[0x8];
        int m_data_node_count;
        char _0x0024[0xC];
        data_node** m_nodes;
    };

    struct game_invite {
        char _0x0000[8]; //0x0000
        gs_session gssession_start; //0x0008
        uint64_t h; //0x0058
        uint64_t h2; //0x0060
        char s[125]; //0x0068
        char n[17]; //0x00B5
        char _0x00C6[2]; //0x00C6
        uint32_t gm; //0x00C8
        char c[23]; //0x00CC
        char _0x00E3[5]; //0x00E3
        uint64_t cc; //0x00E8
        uint64_t cc2;
        char mid[30]; //0x00F8
        char _0x0116[2]; //0x0116
        uint32_t if_; //0x0118
        uint32_t it; //0x011C
        uint32_t l; //0x0120
        uint32_t p; //0x0124
        uint32_t f; //0x0128
        uint32_t cr; //0x012C
        uint32_t u; //0x0130
        uint32_t d; //0x0134
        uint32_t jq; //0x0138
    };

    struct chat_config {
        char _0x0000[0x10];
        uint32_t m_override_gxt; // only works when it's a team message
        char _0x0014[0x134];
        uint32_t m_chat_color;
        bool m_using_chat_color;
    };
}
#pragma pack(pop)