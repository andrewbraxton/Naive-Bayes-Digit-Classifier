#include <string>
#include <fstream>

#include "catch.hpp"
#include "model.h"

// TEST_CASE("can train a model from file data") {
    
// }

TEST_CASE("can create model files") {
    std::string images_filename ("../digitdata/trainingimages");
    std::string labels_filename ("../digitdata/traininglabels");
    CreateModelFile(images_filename, labels_filename, "modeltest.txt");

    std::ifstream model_file ("../models/modeltest.txt");
    int numlines = 0;
    std::string line;
    while (std::getline(model_file, line)) {
        numlines++;
    }

    int expected_numlines = 7850;
    REQUIRE(numlines == expected_numlines);
}

// TEST_CASE("can get prior probability") {

// }

// TEST_CASE("can get conditional probabilities") {

// }