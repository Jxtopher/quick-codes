//
// @Author: Jxtopher
// @License: GNU General Public License v3.0
// @Date: 2017
// @Version: 1
// 

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

