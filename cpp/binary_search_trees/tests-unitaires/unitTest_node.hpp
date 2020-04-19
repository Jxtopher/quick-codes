///
/// @file unitTest_domain.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief 
///

#ifndef UNITTEST_NODE_H
#define UNITTEST_NODE_H

#include <memory>

#include "node.hpp"

using namespace CppUnit;

class UnitTest_node : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UnitTest_node);
    CPPUNIT_TEST(constructor);
    CPPUNIT_TEST(key);
    CPPUNIT_TEST(value);
    CPPUNIT_TEST(left);
    CPPUNIT_TEST(right);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void constructor(void) {
        Node<unsigned int, double> n;
    }

    void key() {
        Node<unsigned int, double> n;
        n.key(5);
        CPPUNIT_ASSERT(n.key() == 5);
    }

    void value() {
        Node<unsigned int, unsigned int> n;
        n.value(5);
        CPPUNIT_ASSERT(n.value() == 5);
    }

    void left() {
        Node<unsigned int, unsigned int> n;
        CPPUNIT_ASSERT(n.left() == nullptr);
    }

    void right() {
        Node<unsigned int, unsigned int> n;
        CPPUNIT_ASSERT(n.right() == nullptr);
    }

    private:

};

#endif