#include <iostream>
#include <string>

#include "modelfilemaker.h"

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cout << "Please provide the needed arguments";
        return -1;
    }

    std::string imgs_src = argv[1];
    std::string labels_src = argv[2];
    int img_size = std::stoi(std::string(argv[3]));
    int num_classes = std::stoi(std::string(argv[4]));
    std::string output_src = argv[5];

    ModelFileMaker modelmaker (imgs_src, labels_src, img_size, num_classes);
    modelmaker.MakeModelFile(output_src);
    
    std::cout << "Model file has been created";
    return 0;
}