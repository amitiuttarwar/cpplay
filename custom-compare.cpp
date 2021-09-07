#include <iostream>
#include <unordered_map>

/** Define a custom comparison function to evaluate if two user-defined classes
 *  are equivalent to one another.
 *
 *  Two methods:
 *  1. overloading the == operator on the class
 *  2. designating a non-member function as a friend so it can access private members
 * */

class CAddrMan
{
    int nIdCount{0};
    std::unordered_map<int, int> mapInfo;

public:
    CAddrMan(int count, int num_in_map)
        : nIdCount(count)
    {
        for (int i = 0; i < num_in_map; i++ ) {
            mapInfo[i] = 3;
        }
    }

    // Method 1
    bool operator==(const CAddrMan& other)
    {
        if (other.nIdCount != nIdCount) return false;
        if (other.mapInfo.size() != mapInfo.size()) return false;
        return true;
    }

// Method 2: class declares function as a friend
friend bool CompareTwoAddrMans(const CAddrMan& one, const CAddrMan& two);
};

// Method 2: define the function
bool CompareTwoAddrMans(const CAddrMan& one, const CAddrMan& two)
{
    if (one.nIdCount != two.nIdCount) return false;
    if (one.mapInfo.size() != two.mapInfo.size()) return false;
    return true;
}

int main()
{
    std::cout << "hello world!" << std::endl;
    CAddrMan one = CAddrMan{2, 3};
    CAddrMan two = CAddrMan{2, 3};

    // Method 1
    if (one == two) {
        std::cout << "Method 1 says: samesies" <<  std::endl;
    }

    // Method 2
    if (CompareTwoAddrMans(one, two)) {
        std::cout << "Method 2 says: samesies" <<  std::endl;
    }

    return 0;
}
