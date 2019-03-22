#pragma once

#include "model.h"

class Classifier {
    public:
        static const char kNewLineChar = '\n';
        static const char kWhitePixel = ' ';


        Classifier(Model model);

        void Classify(std::string testimgs_src);

        void Evaluate(std::string testlabels_src) const;

        std::vector<int> GetClassifications();


    private:
        std::vector<double> GetLogPriorProbs();
        std::vector<double> AddLogCndtlProbs(std::vector<double> logprobs,
                                             std::ifstream& testimgs);
        int MakePrediction(std::vector<double> logsums);

        Model model_;
        std::vector<int> classifications_;
};