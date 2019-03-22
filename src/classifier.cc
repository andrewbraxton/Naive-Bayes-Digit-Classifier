#include <fstream>
#include <math.h>

#include "classifier.h"

Classifier::Classifier(Model model) {
    model_ = model;
}

void Classifier::Classify(std::string testimgs_src) {
    std::ifstream testimgs (testimgs_src);
    if (!testimgs.is_open()) {
        return;
    }

    while (!testimgs.eof()) {
        std::vector<double> logsums = GetLogPriorProbs();
        logsums = AddLogCndtlProbs(logsums, testimgs);
        int prediction = MakePrediction(logsums);
        classifications_.push_back(prediction);
    }
    
    // delete the nonsense prediction produced due to how eof() works
    classifications_.pop_back();
    testimgs.close();
}

std::vector<int> Classifier::GetClassifications() {
    return classifications_;
}

std::vector<double> Classifier::GetLogPriorProbs() {
    std::vector<double> logprobs (model_.GetNumClasses());
    for (int k = 0; k < logprobs.size(); k++) {
            logprobs[k] = log(model_.GetPriorProbability(k));
    }

    return logprobs;
}

std::vector<double> Classifier::AddLogCndtlProbs(std::vector<double> logprobs,
                                                 std::ifstream& testimgs) {
    for (int i = 0; i < model_.GetImgSize(); i++) {
        char curr_char = testimgs.get();

        // skip newline characters
        if (curr_char == kNewLineChar) {
            curr_char = testimgs.get();
        }

        // probability for white pixels is (1 - probability for black pixels)
        if (curr_char == kWhitePixel) {
            for (int j = 0; j < model_.GetNumClasses(); j++) {
                logprobs[j] += log(1 - model_.GetBlackCndtlProbs(j)[i]);
            }
        } else {
            for (int j = 0; j < model_.GetNumClasses(); j++) {
                logprobs[j] += log(model_.GetBlackCndtlProbs(j)[i]);
            }
        }
    }

    return logprobs;
}

int Classifier::MakePrediction(std::vector<double> logsums) {
    int prediction = 0;
    int highestprob = logsums[0];
    for (int p = 0; p < logsums.size(); p++) {
        if (logsums[p] > highestprob) {
            highestprob = logsums[p];
            prediction = p;
        }
    }

    return prediction;
}