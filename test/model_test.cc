#include <string>
#include <fstream>

#include "catch.hpp"
#include "model.h"

TEST_CASE("can train models from files") {
    Model m;
    m.Train("modeltest.txt");

    SECTION("prior probabilities are stored") {
        for (int i = 0; i <= 9; i++) {
            REQUIRE(m.GetPriorProbability(i) > 0);
        }
    }
    SECTION("conditional probabilities are stored") {
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j < 784; j++) {
                REQUIRE(m.GetCndtlProbs(i)[j] > 0);
            }
        }
    }
}