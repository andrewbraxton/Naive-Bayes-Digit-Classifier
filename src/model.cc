#include <fstream>

#include "model.h"

Model::Model() {
    priorprobs_ = std::vector<double>(kNumClasses);
    cndtlprobs_ = std::vector<std::vector<double>>(kNumClasses);
}

void Model::Train(std::string model_filename) {
    std::ifstream model_file ("../models/" + model_filename);

    if (!model_file.is_open()) {
        CreateModelFile("../digitdata/trainingimages",
                        "../digitdata/traininglabels", "default_model.txt");
        model_file = std::ifstream ("../models/default_model.txt");
    }

    for (int i = 0; i < kNumClasses; i++) {
        double curr_priorprob;
        model_file >> curr_priorprob;
        priorprobs_.push_back(curr_priorprob);

        for (int j = 0; j < kNumFeatures; j++) {
            double curr_cndtlprob;
            model_file >> curr_cndtlprob;
            cndtlprobs_[i].push_back(curr_cndtlprob);
        }
    }
}

void CreateModelFile(std::string images_filename, std::string labels_filename,
                     std::string output_filename) {
    std::ifstream images_file (images_filename);
    std::ifstream labels_file (labels_filename);
    std::ofstream output_file ("../models/" + output_filename);

    // total number of training images
    int num_images = 0;
    // number of training images of each class
    std::vector<int> num_images_perclass (Model::kNumClasses);
    // number of times a specific pixel was black for each class
    std::vector<std::vector<int>> num_black_perclass (Model::kNumClasses);
    for (int i = 0; i < num_black_perclass.size(); i++) {
        std::vector<int> vec (Model::kNumFeatures);
        num_black_perclass[i] = vec;
    }

    std::string line;
    while(std::getline(labels_file, line)) {
        num_images++;

        int curr_label = std::stoi(line);
        num_images_perclass[curr_label]++;

        for (int i = 0; i < Model::kNumFeatures; i++) {
            char curr_pixel = images_file.get();
            if (curr_pixel != ' ') {
                num_black_perclass[curr_label][i]++;
            }

            // skip newline characters
            if (i % Model::kSqrtNumFeatures == 0) {
                images_file.get();
            }
        }
    }

    for (int i = 0; i < Model::kNumClasses; i++) {
        double priorprob = (double)num_images_perclass[i] / num_images;
        output_file << priorprob << std::endl;

        for (int j = 0; j < Model::kNumFeatures; j++) {
            double smoothing_factor = 0.5;
            double smoothed_numer = smoothing_factor + num_black_perclass[i][j];
            double smoothed_denom = 2 * smoothing_factor + num_images_perclass[i];

            double cndtlprob = smoothed_numer / smoothed_denom;
            output_file << cndtlprob << std::endl;
        }
    }

    images_file.close();
    labels_file.close();
    output_file.close();
}