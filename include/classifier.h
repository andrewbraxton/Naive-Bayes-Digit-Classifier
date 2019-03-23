#pragma once

#include "model.h"

// Class for classifying images.
class Classifier {
    public:
        static const char kNewLineChar = '\n';
        static const char kWhitePixel = ' ';

        // Constructor.
        // @param model the Model this classifier will use
        Classifier(Model model);

        // Classifies provided images using this Classifier's model.
        // Classifications can be retrieved through GetClassifications().
        // @param imgs_src the path to the test images
        void Classify(std::string imgs_src);
        // Evaluates the accuracy of this Classifier's classifications.
        // Should be used after Classify() is used.
        // @param labels_src the path to the test labels
        void Evaluate(std::string labels_src);

        // Outputs the confusion matrix as well as overall accuracy.
        // Should be used after Evaluate() is used.
        // @param output_src the destination to output the stats to
        void PrintAccuracyStats(std::ostream& output_src);

        /* Getters. */
        std::vector<int> GetClassifications() const;
        std::vector<std::vector<double>> GetConfusionMatrix() const;

    private:
        /* Helper functions used by Classify(). */ 
        // Returns a vector of log'd prior probabilities from the Model.
        std::vector<double> GetLogPriorProbs();
        // Returns a vector with log'd conditional probabilities
        // added to the values in the given vector.
        // @param logprobs a vector of log'd probabilities
        // @param testimgs an opened file stream of test images
        std::vector<double> AddLogCndtlProbs(std::vector<double> logprobs,
                                             std::ifstream& testimgs);
        // Returns the prediction that should be made for this test image
        // by finding the index of the max value of the provided vector.
        // @param logsums a vector of log'd probabilities indexed by class
        int MakePrediction(std::vector<double> logsums);

        /* Helper functions used by Evaluate(). */
        // Reads the labels file and returns a vector of the correct labels.
        // @param testlabels an opened file stream of the test labels
        std::vector<int> GetLabels(std::ifstream& testlabels);
        // Stores overall accuracy of the classifier into accuracy_.
        // @param correctlabels the correct classifications
        void CalcOverallAccuracy(std::vector<int> correctlabels);
        // Populates confusionmatrix_ with the total number of times
        // that a class was classified as each other class.
        // @param correctlabels the correct classifications
        void FillMatrixWithTotals(std::vector<int> correctlabels);
        // Divides each element of confusionmatrix_ by the sum of its row.
        // i.e. converts totals to probabilities.
        void ConvertMatrixTotalsToProbs();

        /* Fields. */
        Model model_;
        std::vector<int> classifications_;
        std::vector<std::vector<double>> confusionmatrix_;
        double accuracy_;
};