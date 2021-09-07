#include <iostream>
#include <vector>

/** Understand the use of std::move when passing parameters around.
 *
 *  Observe how many unique memory addresses are used & whether old
 *  variables are emptied out with different combinations of defining
 *  and invoking constructors.
 * */

// explicit CAddrMan(std::vector<bool> asmap) : m_asmap { asmap }
// explicit CAddrMan(std::vector<bool> asmap) : m_asmap { std::move(asmap) }
// both seem to assign 3 memory locations,
// even if caller invokes with std::move

// move constructor:
// explicit CAddrMan(std::vector<bool>&& asmap) : m_asmap{std::move(asmap)}
// caller invokes with std::move
// eg. std::make_unique<CAddrMan>(std::move(asmap));
// only assigns 1 memory location
// to use when caller does not need asmap afterwards

// copy constructor:
// whether or not caller invokes with std::move,
// assigns 2 memory locations
// param has the same address as caller, info gets copied to member in a
// new address
// to use if caller needs asmap afterwards
//explicit CAddrMan(const std::vector<bool>& asmap) : m_asmap{asmap}

class CAddrMan
{
public:
    const std::vector<bool> m_asmap;

    explicit CAddrMan(std::vector<bool> asmap) : m_asmap { std::move(asmap) }
    {
        std::cout << &asmap << " - CAddrMan ctor, param" << std::endl;
        std::cout << &m_asmap << " - CAddrMan ctor, member"  << std::endl;

        std::cout << "asmap = { ";
        for (int n : asmap) {
            std::cout << n << ", ";
        }
        std::cout << "}; \n";

    }
};

int main()
{
    std::vector<bool> asmap = {true, false, true};
    std::cout << &asmap << " - starting main, local var" << std::endl;
    std::make_unique<CAddrMan>(asmap);
    //std::make_unique<CAddrMan>(std::move(asmap));
    std::cout << &asmap << " - back in main, local var" << std::endl;

    return 0;
}

