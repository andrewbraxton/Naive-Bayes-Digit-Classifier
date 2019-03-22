#include <vector>
#include <cmath>

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

TEST_CASE("can evaluate classifications") {
    Model m;
    m.Train("../models/modeltest.txt");
    Classifier c (m);
    c.Classify("../digitdata/testimages");
    c.Evaluate("../digitdata/testlabels");
    std::vector<std::vector<double>> confusionmatrix = c.GetConfusionMatrix();

    double epsilon = .0001; // yay for floating point calculations
    double sum = 0;
    for (size_t i = 0; i < confusionmatrix.size(); i++) {
        sum = 0;
        for (size_t j = 0; j < confusionmatrix[i].size(); j++) {
            sum += confusionmatrix[i][j];
        }
        REQUIRE(abs(sum - 1) < epsilon);
    }
}