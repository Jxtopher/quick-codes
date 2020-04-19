///
/// @file unitTest_domain.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief 
///

#ifndef UNITTEST_BINARY_SEARCH_TREES_H
#define UNITTEST_BINARY_SEARCH_TREES_H

#include <memory>

#include "binarySearchTrees.hpp"

using namespace CppUnit;

class UnitTest_binarySearchTrees : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UnitTest_binarySearchTrees);
    CPPUNIT_TEST(constructor);
    CPPUNIT_TEST(empty);
    CPPUNIT_TEST(insert);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void constructor(void) {
    }

    void empty(void) {
        BinarySearchTrees<unsigned int, unsigned int> bst;
        CPPUNIT_ASSERT(bst.empty() == true);
    }

    void insert(void) {
        BinarySearchTrees<unsigned int, unsigned int> bst;
        bst.insert(5, 5);
        CPPUNIT_ASSERT(bst.empty() == false);
        bst.insert(6, 5);
        CPPUNIT_ASSERT(bst.empty() == false);
    }


    private:

};

#endif