# NaiveBayes
Simple Naive Bayes digit classifier.

## Usage instructions
Compile the two executable files by running `make`.

### modelmaker
This executable is used to read training data and generate a text file representing a model readable by a `Model` object. It works with any number of classes and training images of any size, as long as each image is the same size, images are encoded as black and white with a single whitespace character representing white, and images are laid out vertically with no space between them.

It requires five additional arguments, supplied correctly and in order, to run properly: the path to the image file, the path to the label file, the size of each image in total number of features, the number of classes, and desired output location.

Using the training data supplied by CS 126 staff, the execute command should look something like this:

`./modelmaker ../digitdata/trainingimages ../digitdata/traininglabels 784 10 ../models/mymodel.txt`

### classify
This executable is used to classify test data and evaluate the accuracy of the classifier. It works with any model file in the format produced by a `ModelFileMaker` object and with test data that corresponds to the model.

It requires three additional arguments, supplied correctly and in order, to run properly: the path to the model file, the path to the test images, and the path to the test labels.

Using the test data supplied by CS 126 staff, the execute command should look something like this:

`./classify ../models/mymodel.txt ../digitdata/testimages ../digitdata/testlabels`

The resulting confusion matrix and overall accuracy will be printed to standard output.
