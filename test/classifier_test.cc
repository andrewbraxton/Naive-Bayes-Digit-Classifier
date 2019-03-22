#include <vector>

#include "catch.hpp"
#include "classifier.h"

TEST_CASE("can classify images") {
    Model m;
    m.Train("../models/modeltest.txt");
    Classifier c (m);
    c.Classify("../digitdata/testimages");
    std::vector<int> classifications = c.GetClassifications();

    REQUIRE(classifications.size() == 1000);
    for (int classification : classifications) {
        REQUIRE(classification >= 0);
        REQUIRE(classification <= 9);
    }
}