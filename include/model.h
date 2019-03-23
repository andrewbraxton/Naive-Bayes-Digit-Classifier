#pragma once

#include <string>
#include <vector>
#include <iostream>

// Class representing a model for use by a Classifier object.
class Model {
    public:
        /* Constructors. */
        // Default constructor.
        Model();
        // Constructor that calls Train().
        // @param model_src the path to a model file
        Model(std::string model_src);

        // Reads a model file and stores the data into this Model.
        // @param model_src the path to a model file
        void Train(std::string model_src);

        /* Getters. */
        // Returns a specified prior probability.
        // @param digit the class to get the prior probability for
        double GetPriorProbability(int digit) const;
        // Returns a specified vector of black pixel conditional probabilities.
        // @param digit the class to get the conditional probabilities for
        std::vector<double> GetBlackCndtlProbs(int digit) const;
        // Returns the size of priorprobs_.
        int GetNumClasses() const;
        // Returns the size of a vector in blackcndtlprobs_.
        int GetImgSize() const;

    private:
        /* Helper functions used by Train(). */
        // Stores prior probabilities from the model file into priorprobs_.
        // @param model_file an opened file stream of the model file
        void StorePriorProbs(std::ifstream& model_file);
        // Stores conditional probabilities of a black pixel from the model file
        // into blackcndtlprobs_.
        // @param model_file an opened file stream of the model file
        void StoreCndtlProbs(std::ifstream& model_file);

        /* Fields. */
        // prior probabilities indexed by class
        std::vector<double> priorprobs_;
        // conditional probabilities for appearance of a black pixel
        // first indexed by class, then indexed by specific pixel
        std::vector<std::vector<double>> blackcndtlprobs_;
};
