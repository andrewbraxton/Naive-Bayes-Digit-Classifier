#include <fstream>

#include "model.h"

Model::Model() {};

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
    double curr_prob;
    model_file >> curr_prob;
    
    while (curr_prob != 0) {
        priorprobs_.push_back(curr_prob);
        model_file >> curr_prob;
    }
}

void Model::StoreCndtlProbs(std::ifstream& model_file) {

}