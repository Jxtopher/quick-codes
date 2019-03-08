///
/// \file wordGenerator.cpp
/// \author Jxtopher
/// \version 1
/// \date 2017
/// \copyright GNU General Public License v3.0
/// \brief *
///

#include "wordGenerator.h"

//int main(int argc, char **argv, char *envp[]) {
int main() {
	jxtopher::WordGenerator wordGenerator;

	// c: The characters composing the word
	// len_word: Word size
	// f: Function applying word processing
	wordGenerator(wordGenerator.alphabet_tiny_uppercase_numeric, 5, jxtopher::WordGenerator::f);

	return EXIT_SUCCESS;
}

