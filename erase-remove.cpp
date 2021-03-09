#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    auto is_greater_than_three = [](int i){ if(i>3) return true; return false; };
    auto is_true= [](int i){ return true; };

    std::vector<int> my_ints{1, 2, 3, 4, 5};
    my_ints.erase(std::remove_if(my_ints.begin(), my_ints.end(), is_greater_than_three), my_ints.end());

    for (int i : my_ints){
        std::cout << i << std::endl;
    }

    std::cout << "======" << std::endl;

    std::vector<int> my_other_ints{1, 2, 3, 4, 5};
    my_other_ints.erase(std::remove_if(my_other_ints.begin(), my_other_ints.end(), is_true), my_other_ints.end());

    for (int i : my_other_ints){
        std::cout << i << std:: endl;
    }

    return 0;
}