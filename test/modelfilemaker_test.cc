#include <fstream>

#include "catch.hpp"
#include "modelfilemaker.h"

TEST_CASE("can make model files") {
    std::string images_src = "../digitdata/testimages";
    std::string labels_src = "../digitdata/testlabels";
    std::string out_src = "../models/makertest.txt";
    ModelFileMaker m (images_src, labels_src);
    m.MakeModelFile("makertest.txt");

    int numlines = 0;
    std::ifstream modelfile (out_src);
    std::string line;
    while (std::getline(modelfile, line)) {
        numlines++;
        if (line != "$") {
            double curr_prob = stod(line);
            REQUIRE(curr_prob > 0);
        }
    }

    int expected_numlines = 7861;
    REQUIRE(numlines == expected_numlines);
}