#include <vector>
#include <iostream>
#include "../../vector.hpp"

int main()
{
    ft::vector<char> ftv(5,'a');
    std::vector<char> v(5,'a');

    std::cout << v.max_size() << std::endl;
    std::cout << ftv.max_size() << std::endl;
    // std::cout << v.capacity() << std::endl;
    for (int i = 0; i < 5; i++)
    {
        std::cout << ftv.back() << std::endl;
    }

    // std::cout << ftv[1] << std::endl;
    return (0);
}
