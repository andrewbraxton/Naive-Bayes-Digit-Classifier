CXX = g++
CXXFLAGS = -std=c++17 -c -g -O0 -Wall -Wextra -pedantic -I ../include

LD = g++
LDFLAGS = -std=c++17

BUILDDIR = ../build

all : modelmaker classify

modelmaker : $(BUILDDIR)/modelmaker

classify : $(BUILDDIR)/classify

$(BUILDDIR)/modelmaker : $(BUILDDIR)/modelmaker_main $(BUILDDIR)/modelfilemaker.o
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/classify : $(BUILDDIR)/classify_main $(BUILDDIR)/classifier.o $(BUILDDIR)/model.o
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/model.o : model.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/modelfilemaker.o : modelfilemaker.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/classifier.o : classifier.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/modelmaker_main : modelmaker_main.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/classify_main : classify_main.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

clean :
	find $(BUILDDIR)/* -not -name "tests_main.o" -delete