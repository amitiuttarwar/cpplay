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

int main()
{
    enum NetPermissionFlags forcerelay(PF_FORCERELAY);

    std::cout << HasFlag(forcerelay, NetPermissionFlags::PF_FORCERELAY) << std::endl;

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
