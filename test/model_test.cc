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




// TEST_CASE("can train a model from file data") {
//     std::string images_filename ("../digitdata/trainingimages");
//     std::string labels_filename ("../digitdata/traininglabels");
//     std::string model_filename ("modeltest.txt");
//     CreateModelFile(images_filename, labels_filename, model_filename);

//     Model m;
//     m.Train(model_filename);

//     for (int i = 0; i < Model::kNumClasses; i++) {
//         REQUIRE(m.GetPriorProbability(i) > 0);
        
//         for (int j = 0; j < Model::kNumFeatures; j++) {
//             REQUIRE(m.GetCndtlProbs(i)[j] > 0);
//         }
//     }
// }

// TEST_CASE("can create model files") {
//     std::string images_filename ("../digitdata/trainingimages");
//     std::string labels_filename ("../digitdata/traininglabels");
//     CreateModelFile(images_filename, labels_filename, "modeltest.txt");

//     std::ifstream model_file ("../models/modeltest.txt");
//     int numlines = 0;
//     std::string line;
//     while (std::getline(model_file, line)) {
//         numlines++;
//     }

//     int expected_numlines = 7850;
//     REQUIRE(numlines == expected_numlines);
// }