#include <fstream>

#include "model.h"

Model::Model() {}

void Model::Train(std::string model_filename) {
    std::ifstream model_file ("../models/" + model_filename);

    if (!model_file.is_open()) {
        return;
    }

    StorePriorProbs(model_file);
    StoreCndtlProbs(model_file);
}

 double Model::GetPriorProbability(int digit) const {
     return priorprobs_[digit];
 }

std::vector<double> Model::GetCndtlProbs(int digit) const {
    return cndtlprobs_[digit];
}

void Model::StorePriorProbs(std::ifstream& model_file) {
    std::string line;
    while(std::getline(model_file, line)) {
        double curr_prob;
        try {
            curr_prob = std::stod(line);
            priorprobs_.push_back(curr_prob);
        } catch (std::invalid_argument&) {
            // we've reached a non-number char and are done storing probs
            break;
        }
    }
}

void Model::StoreCndtlProbs(std::ifstream& model_file) {
    do {
        std::vector<double> currclass_probs;
        std::string line;
        while (std::getline(model_file, line)) {
            double curr_prob;
            try {
                curr_prob = std::stod(line);
                currclass_probs.push_back(curr_prob);
            } catch (std::invalid_argument&) {
                // we've reached a non-number char and are done storing probs
                break;
            }
        }
        // condition necessary due to how eof() functions
        if (!currclass_probs.empty()) {
            cndtlprobs_.push_back(currclass_probs);
        }
    } while (!model_file.eof());
}