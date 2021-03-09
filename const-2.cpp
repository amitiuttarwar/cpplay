#include <iostream>
using namespace std;

//class X {
//public:
    //int my_int;
    //void f() { my_int = 4; }
//};

//class Y {
//public:
    //X& x;

    //Y() {
        //X x = X();
    //}

    //void g() const {
        //std::cout << "x.my_int: " << x.my_int << std::endl;
        //x.f();
        //std::cout << "x.my_int: " << x.my_int << std::endl;
    //}
//};

class myClass {
public:
    int my_int;
    myClass(int i) : my_int(i) { cout << "myClass constructor, my_int: " << i << endl; }

    void print() const
    {
        cout << "myClass int: " << my_int << endl;
    }

};

class myOtherClass {
public:
    int my_int;
    myOtherClass() : my_int(4) { cout << "myOtherClass constructor, my_int: " << my_int << endl; }
};

int main()
{
    // can change what you point to, but not the value its pointed at.
    const int* my_num;

    // can change what my_num points to:
    // my_num = 3; // error: assigning to 'const int *' from incompatible type 'int'
    my_num = (int*)3;
    my_num = (int*)4;

    cout << "address: " << my_num << endl; // prints the address (bytes) of my_num

    // cannot change the value of m_num pointer
    // *my_num = 3; // error: read-only variable is not assignable

    // seg fault
    // cannot retrieve the value of the m_num pointer.. BUT WHY?
    // auto x = *my_num;

    // can change what msg_type points to
    const char* msg_type;
    msg_type = "abc";
    std::cout << "msg: " << msg_type << std::endl;
    msg_type = "def";
    std::cout << "msg: " << msg_type << std::endl;

    char arr[5] = {'a', 'b', 'c', '\0'};
    char arr2[5] = {'d', 'e', 'f', '\0'};
    const char* p;
    // you can change what p points at
    p = arr;
    cout << "arr:  " << *p << endl;
    p = arr2;
    cout << "arr2: " << *p << endl;
    // but you can't change what value p is pointed at
    // *p = 'd'; // error: read-only variable is not assignable

    int iarr[5] = { 1, 2, 3, 4, 5 };
    const int* ip;
    ip = iarr;
    cout << "int: " << *ip << ", ";
    ip = iarr + 1;
    cout << *ip << endl;
    // *ip = 9; // error: read-only variable is not assignable

    myClass clazz = myClass(3);
    clazz.print();
    clazz.my_int = 4;
    clazz.print();

    const myClass* classy = &clazz;
    classy->print();
    // classy->my_int = 5; // error: cannot assign to variable 'classy' with const-qualified type 'const myClass *'

    return 0;
}



