#include <fstream>
#include <math.h>

#include "classifier.h"


Classifier::Classifier(Model model) {
    model_ = model;
}

std::vector<int> Classifier::Classify(std::string testimgs_src) {
    std::vector<int> classifications;

    std::ifstream testimgs (testimgs_src);
    if (!testimgs.is_open()) {
        return classifications;
    }

    while (!testimgs.eof()) {
        std::vector<double> logsums (model_.GetNumClasses());
        for (int k = 0; k < logsums.size(); k++) {
                logsums[k] = log(model_.GetPriorProbability(k));
        }

        for (int i = 0; i < model_.GetImgSize(); i++) {
            char curr_char = testimgs.get();
            if (curr_char == '\n') {
                curr_char = testimgs.get();
            }

            if (curr_char != ' ') {
                for (int j = 0; j < model_.GetNumClasses(); j++) {
                    logsums[j] += log(model_.GetCndtlProbs(j)[i]);
                }
            } else {
                for (int j = 0; j < model_.GetNumClasses(); j++) {
                    logsums[j] += log(1 - model_.GetCndtlProbs(j)[i]);
                }
            }
        }

        int prediction = 0;
        int highestprob = logsums[0];
        for (int p = 0; p < logsums.size(); p++) {
            if (logsums[p] > highestprob) {
                highestprob = logsums[p];
                prediction = p;
            }
        }
        classifications.push_back(prediction);
    }
    
    // delete the nonsense prediction produced due to how eof() works
    classifications.pop_back();
    testimgs.close();
    return classifications;
}

