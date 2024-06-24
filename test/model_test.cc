#include "model.h"

#include <fstream>
#include <string>

#include "catch.hpp"

TEST_CASE("can train models from files") {
    Model m;
    m.Train("../models/modeltest.txt");

    SECTION("prior probabilities are stored") {
        for (int i = 0; i <= 9; i++) {
            REQUIRE(m.GetPriorProbability(i) > 0);
        }
    }
    SECTION("conditional probabilities are stored") {
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j < 784; j++) {
                REQUIRE(m.GetBlackCndtlProbs(i)[j] > 0);
            }
        }
    }
}