#pragma once

#include <string>
#include <vector>
#include <iostream>

class Model {
    public:
        Model();
        Model(std::string model_src);

        void Train(std::string model_src);

        double GetPriorProbability(int digit) const;
        std::vector<double> GetBlackCndtlProbs(int digit) const;

        int GetNumClasses() const;
        int GetImgSize() const;

    private:
        void StorePriorProbs(std::ifstream& model_file);
        void StoreCndtlProbs(std::ifstream& model_file);

        std::vector<double> priorprobs_;
        std::vector<std::vector<double>> blackcndtlprobs_;
};
