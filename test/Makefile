CXX = g++
CXXFLAGS = -std=c++17 -c -g -O0 -Wall -Wextra -pedantic -I ../include

LD = g++
LDFLAGS = -std=c++17

BUILDDIR = ../build
SRCDIR = ../src

tests : $(BUILDDIR)/tests

filemakertest : $(BUILDDIR)/filemakertest

modeltest : $(BUILDDIR)/modeltest

classifiertest : $(BUILDDIR)/classifiertest

$(BUILDDIR)/tests : $(BUILDDIR)/tests_main.o $(BUILDDIR)/model_test.o $(BUILDDIR)/model.o $(BUILDDIR)/modelfilemaker_test.o $(BUILDDIR)/modelfilemaker.o $(BUILDDIR)/classifier_test.o $(BUILDDIR)/classifier.o
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/filemakertest : $(BUILDDIR)/tests_main.o $(BUILDDIR)/modelfilemaker_test.o $(BUILDDIR)/modelfilemaker.o
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/modeltest : $(BUILDDIR)/tests_main.o $(BUILDDIR)/model_test.o $(BUILDDIR)/model.o
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/classifiertest : $(BUILDDIR)/tests_main.o $(BUILDDIR)/classifier_test.o $(BUILDDIR)/classifier.o $(BUILDDIR)/model.o
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/tests_main.o : tests_main.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/model_test.o : model_test.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/model.o : $(SRCDIR)/model.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/modelfilemaker_test.o : modelfilemaker_test.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/modelfilemaker.o : $(SRCDIR)/modelfilemaker.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/classifier_test.o : classifier_test.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/classifier.o : $(SRCDIR)/classifier.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

# delete everything in build/ except compiled Catch file
clean :
	find $(BUILDDIR)/* -not -name "tests_main.o" -delete