///
/// @file wordGenerator.h
/// @author Jxtopher
/// @version 1
/// @date 2019
/// @brief Generating a list of words from a set of characters.
///

#ifndef JXTOPHER_WORDGENERATOR_H
#define JXTOPHER_WORDGENERATOR_H

#include <cstdio>
#include <cstdlib>
#include <cstdbool>

namespace jxtopher {

class WordGenerator {
	public:

	void operator()(const unsigned char *c, unsigned int len_word, void (*f)(unsigned char *, unsigned int)) {
		unsigned int lenC = 0;
		unsigned int *word = new unsigned int[len_word];
		unsigned char *string = new unsigned char[len_word + 1];
		bool overflow = false;
		unsigned int i, j;

		// Nomber of length c
		while (c[lenC] != 0) lenC++;

		for (i = 0 ; i < len_word; i++) {
			word[i] = 0;
			string[i] = c[0];
		}
		string[len_word] = '\0';

		i = len_word - 1;
		while (!overflow) {
			if ((lenC - 1) <= word[i]) {
				do {
					word[i] = 0;

					if (i > 0) {
						i--;
					} else {
						overflow = true;
						break;
					}

					word[i]++;
				} while (lenC <= word[i]);

				i = len_word - 1;
			} else
				word[i]++;

			for (j = 0 ; j < len_word; j++)
				string[j] = c[word[j]];

			f(string, len_word);
		}

		delete [] word;
		delete [] string;
	}

	static void f(unsigned char *string, unsigned int size) {
		printf("%s\n", string);
	}

	const unsigned char alphabet_tiny_uppercase_numeric[64] = 
		{'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z', 
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'0','1','2','3','4','5','6','7','8','9','0',0};
	const unsigned char alphabet_tiny_uppercase[53] = 
		{'a','b','c','d','e','f','g','h','i','j','k','l', 'm',
		'n','o','p','q','r','s','t','u','v','w','x','y','z', 
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P', 'Q','R','S','T','U','V','W','X','Y','Z',0};
	const unsigned char alphabet_tiny[27] = 
		{'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z', 0};

	const unsigned char alphabet_uppercase[27] = 
		{'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z', 0};

	const unsigned char binary[3] = {'0', '1', 0};
};

}

#endif

