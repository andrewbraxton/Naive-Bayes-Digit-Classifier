#pragma once

#include "model.h"

class Classifier {
    public:
        static const char kNewLineChar = '\n';
        static const char kWhitePixel = ' ';

        Classifier(Model model);

        void Classify(std::string imgs_src);
        void Evaluate(std::string labels_src);

        void PrintConfusionMatrix(std::ostream& output_src);

        std::vector<int> GetClassifications() const;
        std::vector<std::vector<double>> GetConfusionMatrix() const;

    private:
        std::vector<double> GetLogPriorProbs();
        std::vector<double> AddLogCndtlProbs(std::vector<double> logprobs,
                                             std::ifstream& testimgs);
        int MakePrediction(std::vector<double> logsums);

        std::vector<int> GetLabels(std::ifstream& testlabels);

        void CalcOverallAccuracy(std::vector<int> correctlabels);

        void FillMatrixWithTotals(std::vector<int> correctlabels);
        void ConvertMatrixTotalsToProbs();

        Model model_;
        std::vector<int> classifications_;
        std::vector<std::vector<double>> confusionmatrix_;
        double accuracy_;
};