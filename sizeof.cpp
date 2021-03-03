#include <iostream>
#include <chrono>

// sizeof returns number of bytes allocated for objects
int main()
{
    int i(32);
    std::cout << "size of int: " << sizeof(i) << std::endl;

    std::chrono::seconds time(i);
    std::cout << "size of chrono: " << sizeof(time) << std::endl;

    return 0;
}

