#include <fstream>
#include <iomanip>
#include <math.h>

#include "classifier.h"

Classifier::Classifier(Model model) {
    model_ = model;
    for (int i = 0; i < model_.GetNumClasses(); i++) {
        std::vector<double> tmp (model_.GetNumClasses());
        confusionmatrix_.push_back(tmp);
    }
}

void Classifier::Classify(std::string imgs_src) {
    std::ifstream testimgs (imgs_src);
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

void Classifier::Evaluate(std::string labels_src) {
    std::ifstream testlabels (labels_src);
    if (!testlabels.is_open()) {
        return;
    }

    std::vector<int> correctlabels = GetLabels(testlabels);

    CalcOverallAccuracy(correctlabels);
    FillMatrixWithTotals(correctlabels);
    ConvertMatrixTotalsToProbs(); 
    testlabels.close();
}

void Classifier::PrintConfusionMatrix(std::ostream& output_src) {
    std::string header = "\nConfusion Matrix";
    std::string horiz_divider = "  ---------------------------------------------------";
    std::string vert_divider = "|";

    output_src << header << std::endl << horiz_divider << std::endl;
    
    for (size_t i = 0; i < confusionmatrix_.size(); i++) {
        output_src << i << ' ' << vert_divider;
        for (size_t j = 0; j < confusionmatrix_[i].size(); j++) {
            output_src << std::setprecision(2) << std::fixed;
            output_src << confusionmatrix_[i][j] << vert_divider;
        }
        output_src << std::endl << horiz_divider << std::endl;
    }

    output_src << " ";
    for (int i = 0; i < model_.GetNumClasses(); i++) {
        output_src << "    " << i;
    }
    output_src << std::endl << std::endl;
    output_src << "Overall accuracy was " << accuracy_ << '.' << std::endl;
}

std::vector<int> Classifier::GetClassifications() const {
    return classifications_;
}

std::vector<std::vector<double>> Classifier::GetConfusionMatrix() const {
    return confusionmatrix_;
}

std::vector<double> Classifier::GetLogPriorProbs() {
    std::vector<double> logprobs (model_.GetNumClasses());
    for (size_t i = 0; i < logprobs.size(); i++) {
            logprobs[i] = log(model_.GetPriorProbability(i));
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
    for (size_t i = 0; i < logsums.size(); i++) {
        if (logsums[i] > highestprob) {
            highestprob = logsums[i];
            prediction = i;
        }
    }

    return prediction;
}

std::vector<int> Classifier::GetLabels(std::ifstream& testlabels) {
    std::vector<int> labels;
    std::string line;
    while (std::getline(testlabels, line)) {
        labels.push_back(std::stoi(line));
    }
    return labels;
}

void Classifier::CalcOverallAccuracy(std::vector<int> correctlabels) {
    int numcorrect = 0;
    for (size_t i = 0; i < correctlabels.size(); i++) {
        if (classifications_[i] == correctlabels[i]) {
            numcorrect++;
        }
    }
    accuracy_ = (double)numcorrect / correctlabels.size();
}

void Classifier::FillMatrixWithTotals(std::vector<int> correctlabels) {
    for (size_t i = 0; i < correctlabels.size(); i++)  {
        int prediction = classifications_[i];
        int actual = correctlabels[i];
        confusionmatrix_[prediction][actual]++;
    }
}

void Classifier::ConvertMatrixTotalsToProbs() {
    // calculating sums of each row in matrix
    std::vector<int> rowsums (model_.GetNumClasses());
    for (size_t i = 0; i < confusionmatrix_.size(); i++) {
        int sum = 0;
        for (size_t j = 0; j < confusionmatrix_[i].size(); j++) {
            sum += confusionmatrix_[i][j];
        }
        rowsums[i] = sum;
    }

    // dividing each matrix element by its corresponding sum
    for (size_t i = 0; i < confusionmatrix_.size(); i++) {
        for (size_t j = 0; j < confusionmatrix_[i].size(); j++) {
            confusionmatrix_[i][j] /= (double)rowsums[i];
        }
    }
}