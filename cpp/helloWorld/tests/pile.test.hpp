///
/// @file UnitTest_pile.h
/// @author *
/// @version *
/// @date *
/// @brief Unit testing
///

#ifndef JXTOPHER_UNITTEST_PILE_H
#define JXTOPHER_UNITTEST_PILE_H

#include <iostream>
#include <list>
#include <string>

#include "pile.hpp"

///
/// \class Pile
///
class UnitTest_pile : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_pile);
	CPPUNIT_TEST(test_push);
	CPPUNIT_TEST(test_operatoreqeq);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		p = new jxtopher::Pile<unsigned int>;
	}
	void tearDown(void) {
		delete p;
	}

  protected:
	void test_push(void) {
		unsigned int a = 5;
		p->push(a);
		CPPUNIT_ASSERT(p->isEmpty() == false);

		unsigned int b = p->pop();
		CPPUNIT_ASSERT(b == a);
	}
	void test_operatoreqeq(void) {
		jxtopher::Pile<unsigned int> p1;

		for(unsigned int i = 0; i < 100; i++) p1.push(i);

		jxtopher::Pile<unsigned int> p2(p1);
		CPPUNIT_ASSERT(p2 == p1);
		for(unsigned int i = 100; 0 < i; i--) CPPUNIT_ASSERT(p1.pop() == p2.pop());
	}

  private:
	jxtopher::Pile<unsigned int>* p;
};

#endif