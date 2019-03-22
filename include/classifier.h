#pragma once

#include "model.h"

class Classifier {
    public:
        Classifier(Model model);

        std::vector<int> Classify(std::string testimgs_src);

        void Evaluate(std::string testlabels_src) const;


    private:
        Model model_;

};