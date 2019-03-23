#include <iostream>
#include <string>

#include "classifier.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Please provide the needed arguments";
        return -1;
    }

    std::string modelfile = argv[1];
    std::string imgs_src = argv[2];
    std::string labels_src = argv[3];

    Model model (modelfile);
    Classifier classifier (model);
    classifier.Classify(imgs_src);
    classifier.Evaluate(labels_src);
    classifier.PrintConfusionMatrix(std::cout);
    return 0;
}