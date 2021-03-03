#include <iostream>
#include <bitset>

int MY_BIT_NUMBER = (1U << 5) | (1U << 2);
unsigned char FULL_BITS = 255;

int main() {
    std::bitset<8> bitnum(MY_BIT_NUMBER);
    std::cout << bitnum << ": original number" << std::endl;

    std::bitset<8> fullbits(FULL_BITS);
    std::cout << fullbits << ": full bits" << std::endl;

    // xor with all bits flipped on
    std::bitset<8> xored(MY_BIT_NUMBER ^ FULL_BITS);
    std::cout << xored << ": xor number with full bits" << std::endl;

    // xor with itself once
    std::bitset<8> self_xored(MY_BIT_NUMBER ^ MY_BIT_NUMBER);
    std::cout << self_xored << ": xor number with itself once" << std::endl;

    // xor with itself twice
    std::bitset<8> xored_again(MY_BIT_NUMBER ^ MY_BIT_NUMBER ^ MY_BIT_NUMBER);
    std::cout << xored_again << ": xor number with itself twice" << std::endl;
	return 0;
}
