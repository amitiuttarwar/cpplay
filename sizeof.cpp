#include <iostream>
#include <chrono>

class Thing {
    int i{2};
};

class OtherThing {
    const std::unique_ptr<Thing> m_thing;

    public:
    OtherThing() {
        std::cout << "from inside of OtherThing, size of m_thing: " << sizeof(m_thing) << std::endl; // 8 bytes -> size of the unique ptr
        std::cout << "from inside of OtherThing, size of *m_thing: " << sizeof(*m_thing) << std::endl; // 4 bytes -> size of Thing
    }
};

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

    //std::cout << "malloc usage of int: " << MallocUsage() << std::endl;

    return 0;
}

