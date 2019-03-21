#pragma once

#include <string>
#include <vector>
#include <iostream>

class Model {
    public:
        static const int kNumClasses = 10;
        static const int kNumFeatures = 784;
        static const int kSqrtNumFeatures = 28;

        Model();

        void Train(std::string model_filename);

        double GetPriorProbability(int digit) const;
        std::vector<std::vector<double>> GetConditionalProbs(int digit) const;

    private:
        std::vector<double> priorprobs_;
        std::vector<std::vector<double>> cndtlprobs_;
};

std::istream& operator>>(std::istream& stream, Model& model);

void CreateModelFile(std::string images_filename, std::string labels_filename,
                     std::string output_filename);