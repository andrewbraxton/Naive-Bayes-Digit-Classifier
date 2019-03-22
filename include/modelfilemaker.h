#pragma once

#include <string>
#include <vector>

class ModelFileMaker {

    public:
        static const char kSeparatingChar = '$';
        static const char kNewLineChar = '\n';
        static const char kWhitePixel = ' ';

        ModelFileMaker(std::string imgs_src, std::string labels_src,
                       int img_size, int num_classes);

        void MakeModelFile(std::string output_filename);

    private:
        void ReadTrainingData();
        void OutputPriorProbs(std::ofstream& output_file);
        void OutputCndtlProbs(std::ofstream& output_file);

        std::string imgsrc_;
        std::string labelsrc_;
        int imgsize_;
        int numclasses_;

        int numimages_;
        std::vector<int> numimagesperclass_;
        std::vector<std::vector<int>> numblackperclass_;
};