#include <iostream>

// Create the vector {8, 8, 8, 8}
std::vector<int> v1(4, 8);

// Create another vector {8, 8, 8, 8}
std::vector<int> v2(std::begin(v1), std::end(v1));

// Create the vector {1, 2, 3, 4}
int arr[] = {1, 2, 3, 4, 5, 6, 7};
std::vector<int> v3(arr, arr + 4);