//
// @Author: Jxtopher
// @Date: 2018
// @Version: 1
// @Purpose: factorelle
// @description: https://oeis.org/A000142
//

#include <iostream>

#define CRASH_TEST_START	std::cout<<"*** START Crash test ***"<<std::endl;
#define CRASH_TEST_END		std::cout<<"*** END Crash test ***"<<std::endl;
#define CRASH_TEST(test) 					\
if (test) {							\
	std::cout<<"[+] "; 						\
} else { 							\
	std::cout<<"[!] "; 						\
} 								\
std::cout<<__LINE__<<":"<<__FUNCTION__<<":"<<__FILE__<<std::endl;


namespace jxtopher {



class Factorial {
	public:
	// Recursion non terminale et fonction non-void
	static unsigned int tail_recursive(unsigned int n) {
		return 1 < n ? n * tail_recursive(n - 1): 1;
	}

	// Recursion non terminale et fonction void
	static void tail_recursive(unsigned int n, unsigned int & r) {
		if (1 < n) {
			unsigned int new_r;		// sans valeur
			tail_recursive(n - 1, new_r);
			r = n * new_r;
		} else {
			r = 1;
		}
	}

	// Fonction itérative
	static unsigned int iterative(unsigned int n) {
		unsigned int r = n;

		if (n == 0) return 1;
		
		for (unsigned int i = n - 1 ; 0 < i ; i--)
				r = r * i;

		return r;
	}

	void crash_test() {
		CRASH_TEST_START
		CRASH_TEST(tail_recursive(0) == 1);
		CRASH_TEST(tail_recursive(1) == 1);
		CRASH_TEST(tail_recursive(5) == 120);

		unsigned int r;
		tail_recursive(0, r); CRASH_TEST(r == 1);
		tail_recursive(1, r); CRASH_TEST(r == 1);
		tail_recursive(5, r); CRASH_TEST(r == 120);

		CRASH_TEST(iterative(0) == 1);
		CRASH_TEST(iterative(1) == 1);
		CRASH_TEST(iterative(5) == 120);
		CRASH_TEST_END
	}
};

}
