///
/// @file main.cpp
/// @author *
/// @version *
/// @copyright *
/// @date *
/// @brief Hello world for a simple exemple code
/// @details *
///
/// -compilation *
/// -execution *
///

#include <cstdlib>
#include <iostream>
#include <string>

#include "macro.h"

void version(const std::string& name_software, const std::string& num_version);

void version(const std::string& name_software, const std::string& num_version) {
	std::cout << "*************************************" << std::endl;
	std::cout << "[+] *** " << name_software << " ***" << std::endl;
	std::cout << "[+] Day compilation : " << __DATE__ << " " << __TIME__ << std::endl;
	std::cout << "[+] Version : " << num_version << std::endl;
	std::cout << "*************************************" << std::endl;
}

// int main(int argc, char **argv) {
int main() {
	DEBUG_TRACE("Start of the program")

	version("Hello World !", "1");

	for(int i = 0; i < 5; i++) {
		DEBUG_VAR(i)
		std::cout << "Hello World!" <<std::endl;
	}

	if(0 == -1) { THROW("Error of variable i") }

	DEBUG_TRACE("Stop program")
	return EXIT_SUCCESS;
}
