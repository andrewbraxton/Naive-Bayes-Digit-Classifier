#include <vector>
#include <cmath>
#include <sstream>

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

TEST_CASE("can print accuracy statistics") {
    Model m;
    m.Train("../models/modeltest.txt");
    Classifier c (m);
    c.Classify("../digitdata/testimages");
    c.Evaluate("../digitdata/testlabels");

    std::stringstream stream;
    c.PrintAccuracyStats(stream);
    std::string expected = "\n  Confusion Matrix\n  ---------------------------------------------------\n0 |0.92|0.00|0.01|0.00|0.00|0.02|0.01|0.00|0.02|0.01|\n  ---------------------------------------------------\n1 |0.00|0.84|0.02|0.02|0.00|0.02|0.04|0.05|0.01|0.01|\n  ---------------------------------------------------\n2 |0.01|0.01|0.85|0.00|0.01|0.01|0.04|0.03|0.03|0.00|\n  ---------------------------------------------------\n3 |0.00|0.00|0.04|0.71|0.00|0.11|0.00|0.00|0.12|0.03|\n  ---------------------------------------------------\n4 |0.01|0.00|0.02|0.00|0.77|0.03|0.04|0.03|0.02|0.09|\n  ---------------------------------------------------\n5 |0.06|0.02|0.00|0.03|0.01|0.70|0.07|0.00|0.09|0.02|\n  ---------------------------------------------------\n6 |0.03|0.01|0.08|0.02|0.03|0.01|0.80|0.00|0.00|0.00|\n  ---------------------------------------------------\n7 |0.00|0.00|0.01|0.07|0.01|0.01|0.00|0.87|0.01|0.02|\n  ---------------------------------------------------\n8 |0.05|0.00|0.06|0.02|0.02|0.02|0.02|0.04|0.74|0.01|\n  ---------------------------------------------------\n9 |0.00|0.00|0.00|0.04|0.13|0.04|0.00|0.10|0.08|0.60|\n  ---------------------------------------------------\n     0    1    2    3    4    5    6    7    8    9\n\nOverall accuracy was 0.77.\n";
    REQUIRE(stream.str() == expected);
}