#include <iostream>
#define BOOST_TEST_MODULE MyTests
#include <boost/test/included/unit_test.hpp>
#include "headers/test.hpp"
// #define BOOST_TEST_NO_MAIN

// Function to be tested
int add(int a, int b) {
    return a + b;
}

// Define test cases
BOOST_AUTO_TEST_CASE(testAddition) {
    std::cout << "There" << std::endl;
    std::cout << SOME_VALUE << std::endl;
    // Test case 1
    BOOST_CHECK(add(2, 3) == 5);

    // Test case 2
    BOOST_CHECK(add(-1, 1) == 0);
}

BOOST_AUTO_TEST_CASE(testSubtraction) {
    std::cout << "Here" << std::endl;
    // Test case 3
    BOOST_CHECK(add(5, -3) == 2);

    // Test case 4
    BOOST_CHECK(add(0, 0) == 0);

}