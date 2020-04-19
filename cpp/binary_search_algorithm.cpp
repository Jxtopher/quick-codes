/// 
/// @file binary_search_algorithm.cpp
/// @author Jxtopher
/// @brief https://en.wikipedia.org/wiki/Binary_search_algorithm
/// @version 0.1
/// @date 2019-11-27
/// 
/// @copyright Copyright (c) 2019
/// 
///
#include <algorithm>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>


/// 
/// @brief Search value in the array
/// 
/// @param array 
/// @param target_value 
/// @return the position of the target_value or if failure search std::numeric_limits<unsigned int>::max()
///
template<typename T>
unsigned int binary_search(std::vector<T> array, T target_value) {
    unsigned int left = 0, right = array.size() - 1;

    while (left <= right) {
        unsigned int m = static_cast<unsigned int>(std::floor(static_cast<float>(left + right) / 2));
        if (array[m] < target_value)
            left = m + 1;
        else if (array[m] > target_value)
            right = m - 1;
        else
            return m;
    }
    return std::numeric_limits<unsigned int>::max();
}

int main() {
    std::mt19937 mt_rand;
    mt_rand.seed(0);
    std::uniform_int_distribution<unsigned int> rid(0, 1000);

    
    unsigned int n = 50;
    std::vector<unsigned int> array;
    for (unsigned int i = 0 ; i < n ; i++) array.push_back(rid(mt_rand));
    
    for (unsigned int value : array) std::cout<<value<<" ";
    std::cout<<std::endl;

    std::sort(array.begin(), array.end());

    for (unsigned int value : array) std::cout<<value<<" ";
    std::cout<<std::endl;

    std::cout<<binary_search<unsigned int>(array, 60)<<std::endl;
    return EXIT_SUCCESS;
}
