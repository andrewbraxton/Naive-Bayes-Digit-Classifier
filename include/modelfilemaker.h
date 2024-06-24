#pragma once

#include <string>
#include <vector>

// Class for reading training data and generating text files
// representing a model readable by a Model object.
class ModelFileMaker {
   public:
    // non-number char is used to separate probs of different classes
    static const char kSeparatingChar = '$';
    static const char kNewLineChar = '\n';
    static const char kWhitePixel = ' ';

    // Constructor.
    // @param imgs_src the path to the training images
    // @param labels_src the path to the training labels
    // @param img_size the size of each image in total number of pixels
    // @param num_classes the number of classes
    ModelFileMaker(std::string imgs_src, std::string labels_src, int img_size,
                   int num_classes);

    // Generates a text file representing a model.
    // @param output_src the path to output the model file
    void MakeModelFile(std::string output_src);

   private:
    /* Helper functions used by MakeModelFile(). */
    // Records data about the training images into the private fields below.
    void ReadTrainingData();
    // Calculates prior probabilities and prints them to the model file.
    // @param output_file an opened file stream of the output target
    void OutputPriorProbs(std::ofstream& output_file);
    // Calculates conditional probabilities for a black pixel
    // and prints them to the model file.
    // @param output_file an opened file stream of the output target
    void OutputCndtlProbs(std::ofstream& output_file);

    /* Fields used for calculating probabilities. */
    // total number of images in the training data
    int numimages_;
    // number of images in the training data, indexed by class
    std::vector<int> numimagesperclass_;
    // number of times a specific pixel is black
    // first indexed by class, then indexed by pixel number
    std::vector<std::vector<int>> numblackperclass_;

    /* Properties of the training data. See constructor @param tags. */
    std::string imgsrc_;
    std::string labelsrc_;
    int imgsize_;
    int numclasses_;
};