#include <iostream>
#include <bitset>

enum NetPermissionFlags {
    PF_NONE = 0,
    // Can query bloomfilter even if -peerbloomfilters is false
    PF_BLOOMFILTER = (1U << 1),
    // Relay and accept transactions from this peer, even if -blocksonly is true
    // This peer is also not subject to limits on how many transaction INVs are tracked
    PF_RELAY = (1U << 3),
    // Always relay transactions from this peer, even if already in mempool
    // Keep parameter interaction: forcerelay implies relay
    PF_FORCERELAY = (1U << 2) | PF_RELAY,
    // Allow getheaders during IBD and block-download after maxuploadtarget limit
    PF_DOWNLOAD = (1U << 6),
    // Can't be banned/disconnected/discouraged for misbehavior
    PF_NOBAN = (1U << 4) | PF_DOWNLOAD,
    // Can query the mempool
    PF_MEMPOOL = (1U << 5),
    // Can request addrs without hitting a privacy-preserving cache
    PF_ADDR = (1U << 7),

    // True if the user did not specifically set fine grained permissions
    PF_ISIMPLICIT = (1U << 31),
    PF_ALL = PF_BLOOMFILTER | PF_FORCERELAY | PF_RELAY | PF_NOBAN | PF_MEMPOOL | PF_DOWNLOAD | PF_ADDR,
};


static bool HasFlag(const NetPermissionFlags& flags, NetPermissionFlags f)
{
    std::bitset<8> z(flags);
    std::cout << z << ": flags" << std::endl;

    std::bitset<8> x(f);
    std::cout << x << ": f" << std::endl;

    auto combined = flags & f;
    std::bitset<8> y(combined);
    std::cout << y << ": combined" << std::endl;

    return combined == f;
}

enum ServiceFlags : uint64_t {
    NODE_NONE = 0,
    // NODE_NETWORK means that the node is capable of serving the complete block chain. It is currently
    // set by all Bitcoin Core non pruned nodes, and is unset by SPV clients or other light clients.
    NODE_NETWORK = (1 << 0),
    // NODE_BLOOM means the node is capable and willing to handle bloom-filtered connections.
    // Bitcoin Core nodes used to support this by default, without advertising this bit,
    // but no longer do as of protocol version 70011 (= NO_BLOOM_VERSION)
    NODE_BLOOM = (1 << 2),
    // NODE_WITNESS indicates that a node can be asked for blocks and transactions including
    // witness data.
    NODE_WITNESS = (1 << 3),
    // NODE_COMPACT_FILTERS means the node will service basic block filter requests.
    // See BIP157 and BIP158 for details on how this is implemented.
    NODE_COMPACT_FILTERS = (1 << 6),
    // NODE_NETWORK_LIMITED means the same as NODE_NETWORK with the limitation of only
    // serving the last 288 (2 day) blocks
    // See BIP159 for details on how this is implemented.
    NODE_NETWORK_LIMITED = (1 << 10),
};


int main()
{
    // see how the bitwise operations hits true for a subset of permissions
    //enum NetPermissionFlags forcerelay(PF_FORCERELAY);
    //std::cout << HasFlag(forcerelay, NetPermissionFlags::PF_RELAY) << std::endl;

    // how does & operator work here?
    ServiceFlags nLocalServices = NODE_BLOOM;
    std::bitset<8> z(nLocalServices);
    std::cout << z << ": nLocalServices" << std::endl;

    ServiceFlags bloom = NODE_BLOOM;
    std::bitset<8> x(bloom);
    std::cout << x << ": NODE_BLOOM" << std::endl;

    auto combined = nLocalServices & bloom;
    std::bitset<8> y(combined);
    std::cout << y << ": combined" << std::endl;

    if (!(nLocalServices & NODE_BLOOM)) {
        std::cout << "disconnect" << std::endl;
    }

    return 0;
}

// 00000010, 2:   PF_BLOOMFILTER
// 00001000, 8:   PF_RELAY
// 00001100, 12:  PF_FORCERELAY (ors PF_RELAY)
// 01000000, 64:  PF_DOWNLOAD
// 01010000, 80:  PF_NOBAN (ors PF_DOWNLOAD)
// 00100000, 32:  PF_MEMPOOL
// 10000000, 128: PF_ADDR
// 11111110, 254: PF_ALL

// 00000000, 2147483648: PF_ISIMPLICIT
