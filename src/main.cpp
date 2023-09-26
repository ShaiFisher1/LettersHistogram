#define BOOST_TEST_MODULE Tests
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "simplehistogram.cpp"
#include "parallelhistogram.cpp"


BOOST_AUTO_TEST_CASE(testrandomwords) {
        std::array<int, NUM_LETTERS> expected = { 367426, 81974, 182327, 153198, 477143, 54387, 105639, 119019, 375383, 7801, 38866, 249255, 126768, 310535, 307788, 134722, 8096, 305957, 306060, 281205, 157478, 42894, 36767, 12373, 83264, 17676 };
        std::array<int, NUM_LETTERS> simpleHistogramResult = simpleHistogram::histogram("tests/words.txt");
        std::array<int, NUM_LETTERS> parallelHistogramResult = parallelHistogram::histogram("tests/words.txt");
        bool isSimpleEqual = true;
        bool isParallelEqual = true;
        for (int i = 0; i < NUM_LETTERS; ++i) {
            if (simpleHistogramResult[i] != expected[i]) {
                isSimpleEqual = false;
            }
            if (parallelHistogramResult[i] != expected[i]) {
                isParallelEqual = false;
            }
        }
        BOOST_CHECK(isSimpleEqual);
        BOOST_CHECK(isParallelEqual);
}


BOOST_AUTO_TEST_CASE(testcountries) {
        std::array<int,NUM_LETTERS> expected = { 189, 34, 25, 30, 73, 3, 35, 18, 97, 6, 13, 48, 44, 91, 54, 12, 3, 64, 45, 44, 45, 9, 9, 2, 19, 11};
        std::array<int, NUM_LETTERS> simpleHistogramResult = simpleHistogram::histogram("tests/countries.txt");
        std::array<int, NUM_LETTERS> parallelHistogramResult = parallelHistogram::histogram("tests/countries.txt");
        bool isSimpleEqual = true;
        bool isParallelEqual = true;
        for (int i = 0; i < NUM_LETTERS; ++i) {
            if (simpleHistogramResult[i] != expected[i]) {
                isSimpleEqual = false;
            }
            if (parallelHistogramResult[i] != expected[i]) {
                isParallelEqual = false;
            }
        }
        BOOST_CHECK(isSimpleEqual);
        BOOST_CHECK(isParallelEqual);
}
