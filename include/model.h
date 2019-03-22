#pragma once

#include <string>
#include <vector>
#include <iostream>

class Model {
    public:
        Model();

        void Train(std::string model_filename);

        double GetPriorProbability(int digit) const;
        std::vector<double> GetCndtlProbs(int digit) const;

    private:
        void StorePriorProbs(std::ifstream& model_file);
        void StoreCndtlProbs(std::ifstream& model_file);

        std::vector<double> priorprobs_;
        std::vector<std::vector<double>> cndtlprobs_;
};

std::istream& operator>>(std::istream& stream, Model& model);

