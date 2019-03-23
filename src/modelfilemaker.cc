#include <fstream>

#include "modelfilemaker.h"

ModelFileMaker::ModelFileMaker(std::string imgs_src, std::string labels_src,
                               int img_size, int num_classes) {
    imgsrc_ = imgs_src;
    labelsrc_ = labels_src;
    imgsize_ = img_size;
    numclasses_ = num_classes;

    // need to initialize the 2D vector in this way
    // to be able to set elements through [][] notation
    numimagesperclass_.resize(numclasses_);
    for (int i = 0; i < numclasses_; i++) {
        std::vector<int> tmp (imgsize_);
        numblackperclass_.push_back(tmp);
    }
}

void ModelFileMaker::MakeModelFile(std::string output_src) {
    ReadTrainingData();

    std::ofstream output_file (output_src);
    OutputPriorProbs(output_file);
    OutputCndtlProbs(output_file);
    output_file.close();
}

void ModelFileMaker::ReadTrainingData() {
    std::ifstream images_file (imgsrc_);
    std::ifstream labels_file (labelsrc_);
    
    std::string line;
    while(std::getline(labels_file, line)) {
        numimages_++;
        int curr_label = std::stoi(line);
        numimagesperclass_[curr_label]++;

        for (int i = 0; i < imgsize_; i++) {
            char curr_pixel = images_file.get();
            if (curr_pixel == kNewLineChar) {
                curr_pixel = images_file.get();
            }
            if (curr_pixel != kWhitePixel) {
                numblackperclass_[curr_label][i]++;
            }
        }
    }
    images_file.close();
    labels_file.close();
}

void ModelFileMaker::OutputPriorProbs(std::ofstream& output_file) {
    for (int i = 0; i < numclasses_; i++) {
        double priorprob = (double)numimagesperclass_[i] / numimages_;
        output_file << priorprob << std::endl;
    }
    output_file << kSeparatingChar << std::endl;
}

void ModelFileMaker::OutputCndtlProbs(std::ofstream& output_file) {
    // can play around with Laplace smoothing factor and test resulting accuracy
    double smoothingfactor = 0.5;
    for (int i = 0; i < numclasses_; i++) {
        for (int j = 0; j < imgsize_; j++) {
            double smoothed_numer = smoothingfactor + numblackperclass_[i][j];
            double smoothed_denom = 2 * smoothingfactor + numimagesperclass_[i];
            double cndtlprob = smoothed_numer / smoothed_denom;
            output_file << cndtlprob << std::endl;
        }
        output_file << kSeparatingChar << std::endl;
    }
}
