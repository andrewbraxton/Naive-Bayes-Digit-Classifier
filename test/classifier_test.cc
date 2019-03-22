#include <vector>
#include <iostream>

#include "catch.hpp"
#include "classifier.h"

TEST_CASE("can classify images") {
    Model m;
    m.Train("../models/modeltest.txt");
    Classifier c (m);
    std::vector<int> classifications;
    classifications = c.Classify("../digitdata/testimages");

    REQUIRE(classifications.size() == 1000);
    for (int classification : classifications) {
        REQUIRE(classification >= 0);
        REQUIRE(classification <= 9);
    }
}