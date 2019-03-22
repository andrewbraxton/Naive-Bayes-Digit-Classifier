#include <fstream>

#include "modelfilemaker.h"

ModelFileMaker::ModelFileMaker(std::string images_filename,
                               std::string labels_filename) {
    imagesfn_ = images_filename;
    labelsfn_ = labels_filename;

    numimages_ = 0;
    numimagesperclass_.resize(kNumClasses);
    for (int i = 0; i < kNumClasses; i++) {
        std::vector<int> tmp (kNumFeatures);
        numblackperclass_.push_back(tmp);
    }
}

void ModelFileMaker::MakeModelFile(std::string output_filename) {
    ReadTrainingData();

    std::ofstream output_file ("../models/" + output_filename);
    OutputPriorProbs(output_file);
    OutputCndtlProbs(output_file);
    output_file.close();
}

void ModelFileMaker::ReadTrainingData() {
    std::ifstream images_file (imagesfn_);
    std::ifstream labels_file (labelsfn_);
    
    std::string line;
    while(std::getline(labels_file, line)) {
        numimages_++;

        int curr_label = std::stoi(line);
        numimagesperclass_[curr_label]++;

        for (int i = 0; i < kNumFeatures; i++) {
            char curr_pixel = images_file.get();
            if (curr_pixel != ' ') {
                numblackperclass_[curr_label][i]++;
            }

            // skip newline characters
            if (i % kSqrtNumFeatures == 0) {
                images_file.get();
            }
        }
    }

    images_file.close();
    labels_file.close();
}

void ModelFileMaker::OutputPriorProbs(std::ofstream& output_file) {
    for (int i = 0; i < kNumClasses; i++) {
        double priorprob = (double)numimagesperclass_[i] / numimages_;
        output_file << priorprob << std::endl;
    }
    output_file << kSeparatingChar << std::endl;
}

void ModelFileMaker::OutputCndtlProbs(std::ofstream& output_file) {
    double smoothingfactor = 0.5;
    for (int i = 0; i < kNumClasses; i++) {
        for (int j = 0; j < kNumFeatures; j++) {
            double smoothed_numer = smoothingfactor + numblackperclass_[i][j];
            double smoothed_denom = 2 * smoothingfactor + numimagesperclass_[i];
            double cndtlprob = smoothed_numer / smoothed_denom;
            output_file << cndtlprob << std::endl;
        }
        output_file << kSeparatingChar << std::endl;
    }
}