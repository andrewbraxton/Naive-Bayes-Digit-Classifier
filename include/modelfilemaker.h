#pragma once

#include <string>
#include <vector>

class ModelFileMaker {

    public:
        static const int kNumClasses = 10;
        static const int kNumFeatures = 784;
        static const int kSqrtNumFeatures = 28;
        static const char kSeparatingChar = '$';

        ModelFileMaker(std::string images_filename,
                       std::string labels_filename);

        void MakeModelFile(std::string output_filename);

    private:
        void ReadTrainingData();
        void OutputPriorProbs(std::ofstream& output_file);
        void OutputCndtlProbs(std::ofstream& output_file);

        std::string imagesfn_;
        std::string labelsfn_;

        int numimages_;
        std::vector<int> numimagesperclass_;
        std::vector<std::vector<int>> numblackperclass_;
};