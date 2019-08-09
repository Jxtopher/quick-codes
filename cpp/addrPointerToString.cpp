///
/// \file addrPointerToString.cpp
/// \author htonivi
/// \date Mar 10, 2009 at 3:35am
/// \brief http://www.cplusplus.com/forum/general/8597/
///
/// @compilation g++ -std=c++1z -Wall -Os  main.cpp -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
///

#include <iostream>
#include <sstream>
#include <string>

template <typename T>
std::string convertPointerToStringAddress(const T* obj) {
    long long int address(reinterpret_cast<long long int>(obj));
    std::stringstream ss;
    ss << address;
    return ss.str();
}

template <typename T>
T* convertAddressStringToPointer(const std::string& address) {
    std::stringstream ss;
    ss << address;
    long long int tmp(0);
    if (!(ss >> tmp)) throw std::runtime_error("Failed - invalid address!");
    return reinterpret_cast<T*>(tmp);
}

int main() {
    int val(0);
    int* ptr = &val;

    std::cout << ptr << std::endl;

    std::string address = convertPointerToStringAddress(ptr);
    int* ptr2 = convertAddressStringToPointer<int>(address);

    if (ptr == ptr2) {
        std::cout << "The pointers are the same!" << std::endl;
    } else {
        std::cout << "The pointers are different! : " << std::endl;
    }

    system("PAUSE");
}