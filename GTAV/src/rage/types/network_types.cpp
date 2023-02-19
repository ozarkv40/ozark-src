#include "network_types.h"
#include "global/vars.h"

namespace rage::network {
    void network_base_config::set_network_session_was_invited(bool invited) {
        *(bool*)((uint64_t)this + 0x86A5) = invited; // updated
    }
}