#include <iostream>
#include <chrono>
#include <vector>

class Thing {
    int i{2};
    std::vector<int> is{1, 2, 3};
};

class OtherThing {
    const std::unique_ptr<Thing> m_thing;

    public:
    OtherThing() {
        std::cout << "from inside of OtherThing, size of m_thing: " << sizeof(m_thing) << std::endl; // 8 bytes -> size of the unique ptr
        std::cout << "from inside of OtherThing, size of *m_thing: " << sizeof(*m_thing) << std::endl; // 4 bytes -> size of Thing
    }
};

class NestedThing {
    Thing my_thing;
    OtherThing my_other_thing;
};

class ReallyNestedThing {
    NestedThing my_nested_thing;
};

// taken from:
// https://github.com/bitcoin/bitcoin/blob/master/src/memusage.h#L51
static inline size_t MallocUsage(size_t alloc)
{
    // Measured on libc6 2.19 on Linux.
    if (alloc == 0) {
        return 0;
    } else if (sizeof(void*) == 8) {
        return ((alloc + 31) >> 4) << 4;
    } else if (sizeof(void*) == 4) {
        return ((alloc + 15) >> 3) << 3;
    } else {
        assert(0);
    }
}

template<typename X>
static inline size_t DynamicUsage(const std::vector<X>& v)
{
    return MallocUsage(v.capacity() * sizeof(X));
}

class Transport {
public:
    virtual ~Transport() {}
};

class V1Transport final : public Transport
{
public:
    int m_magic_bytes;
    int m_node_id;
    bool in_data;
};

class CNode {
public:
    std::unique_ptr<Transport> m_transport;

    CNode() {
        m_transport = std::make_unique<V1Transport>();
    }

};

template<typename X>
static inline size_t DynamicUsage(const std::unique_ptr<X>& p)
{
    std::cout << "size of X: " << sizeof(X) << " -> ";
    return p ? MallocUsage(sizeof(X)) : 0;
}

// sizeof returns number of bytes allocated for objects
// its a compile time function, so doesn't handle any dynamically allocated memory
// can add members to `Thing` and see which values scale
int main()
{
    int i(32);
    std::cout << "size of int: " << sizeof(i) << std::endl; // 4 bytes

    Thing my_thing;
    OtherThing my_other_thing;
    std::unique_ptr<Thing> my_thing_ptr = std::make_unique<Thing>();
    std::unique_ptr<Thing> empty_ptr;

    std::cout << "size of my_thing: " << sizeof(my_thing) << std::endl; // 4 bytes -> sizeof Thing object, class is just one int
    std::cout << "size of my_other_thing: " << sizeof(my_other_thing) << std::endl; // 8 bytes -> class is a unique ptr
    std::cout << "size of my_thing_ptr: " << sizeof(my_thing_ptr) << std::endl; // 8 bytes -> size of unique ptr
    std::cout << "size of empty_ptr: " << sizeof(empty_ptr) << std::endl; // 8 bytes
    std::cout << "size of *my_thing_ptr: " << sizeof(*my_thing_ptr) << std::endl; // 4 bytes -> size of Thing

    // the sizeof a vector returns a fixed value based on internal overhead: 24
    std::vector<int> int_vector = {};
    std::vector<int> int_vector_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<Thing> thing_vector = {my_thing};
    std::cout << "size of int_vector: " << sizeof(int_vector) << std::endl;
    std::cout << "size of int_vector_2: " << sizeof(int_vector_2) << std::endl;
    std::cout << "size of thing_vector: " << sizeof(thing_vector) << std::endl;
    std::cout << "DynamicUsage of empty vector: " << DynamicUsage(int_vector) << std::endl;
    std::cout << "DynamicUsage of int_vector_2: " << DynamicUsage(int_vector_2) << " capacity: " << int_vector_2.capacity() << std::endl;

    ReallyNestedThing t;
    std::cout << "sizeof ReallyNestedThing: " << sizeof(t) << std::endl;

    // CNode has a unique ptr to a virtual class
    V1Transport transport;
    std::cout << "size of V1Transport class: " << sizeof(transport) << std::endl;
    CNode node;
    std::cout << "size of node's unique ptr to transport class: " << sizeof(node.m_transport) << std::endl;

    // this shows that DynamicUsage(m_transport) doesn't work properly.
    // sizeof(X) prints 8 bytes instead of the 24 bytes that would represent
    // the class, because sizeof is calculated at compile time and Transport is
    // a virtual class until its instantiated
    std::cout << "size of DynamicUsage(transport): " << DynamicUsage(node.m_transport) << std::endl;

    return 0;
}

