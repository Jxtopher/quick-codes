///
/// \file main.h
/// \author *
/// \version *
/// \copyright *
/// \date *
/// \brief Hello world for a simple exemple code
/// \details *
///
/// @compilation *
/// @execution *
///

#include <iostream>
#include <cstdlib>

#include "macro.h"

using namespace std;

void version(string name_software, string num_version);

void version(string name_software, string num_version) {
	std::cout<<"*************************************"<<std::endl;
	std::cout<<"[+] *** "<<name_software<<" ***"<<std::endl;
	std::cout<<"[+] Day compilation : "<<__DATE__<<" "<<__TIME__<<std::endl;
	std::cout<<"[+] Version : "<<num_version<<std::endl;
	std::cout<<"*************************************"<<std::endl;
}

//int main(int argc, char **argv) {
int main() {
	DEBUG_TRACE("Start of the program")

	version("Hello World !", "1");
	
	for (int i =  0 ; i < 5 ; i++) {
		DEBUG_VAR(i)
		cout<<"Hello World!"<<endl;
	}

	if (0 == -1) {
		THROW("Error of variable i")
	} 

	DEBUG_TRACE("Stop program")
	return EXIT_SUCCESS;
}