#include <iostream>
using namespace std;

void simple_example()
{
    // in the printf call that accesses b[3], it accesses an index past the end
    // of the array, so b[3] returns the value of a.

    char a = 10;
    char b[3] = {20,21,22};
    char c = 30;

    printf("address of    a=%p, value of    a=%hhd\n", &a, a);
    printf("address of b[3]=%p, value of b[3]=%hhd\n", &b[3], b[3]);
    printf("address of b[2]=%p, value of b[2]=%hhd\n", &b[2], b[2]);
    printf("address of b[1]=%p, value of b[1]=%hhd\n", &b[1], b[1]);
    printf("address of b[0]=%p, value of b[0]=%hhd\n", &b[0], b[0]);
    printf("address of    c=%p, value of    c=%hhd\n", &c, c);

    // note: stack memory starts high, allocates in order, decrementing.
}

enum class Color {
    RED,
    BLUE,
};

void func(Color c) {
    switch(c) {
        case Color::RED:
            printf("switch: hit RED\n");
            return;
        case Color::BLUE:
            printf("switch: hit BLUE\n");
            return;
    }

    std::cout << "oooo got past the switch!" << std::endl;
}

int main()
{
    simple_example();

    // manually initialize enum by casting number
    // -> gets past switch statement
    //Color c = Color(8);
    //func(c);

    // properly initialize the enum, but then have a buffer overflow corrupt
    // the memory, reassigning the value of the enum type
    //enum Color c = Color::RED;
    //char v[3] = {10, 20, 30};
    //v[3] = 5;
    //func(c);

    return 0;
}
