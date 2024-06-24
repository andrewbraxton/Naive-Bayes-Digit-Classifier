## BUILD ENVIRONMENT ##

CXX := clang++
CXXFLAGS = -std=c++17 -c -O0 -Wall -Wextra -pedantic -I include/

LD := clang++
LDFLAGS :=

## VARIABLES ##

OBJ := obj
BIN := bin
SRCS := $(wildcard */*.cc)

TEST_DEPS := $(notdir $(filter-out %main.cc,$(SRCS)))
TEST_DEPS := $(patsubst %.cc,$(OBJ)/%.o,$(TEST_DEPS))

MODELMAKER := $(BIN)/modelmaker
CLASSIFY := $(BIN)/classify
TEST := $(BIN)/test

## TARGETS ##

all: classify modelmaker
clean:
	@rm -rf $(OBJ) $(BIN)
	@echo 'Removed obj/ and bin/'
.PHONY: all clean

format:
	@clang-format -i $(shell find . -name '*.h' -o -name '*.cc')
tidy:
	@clang-tidy --fix $(shell find . -name '*.h' -o -name '*.cc')
.PHONY: format tidy

classify: $(CLASSIFY)
modelmaker: $(MODELMAKER)
test: $(TEST)
.PHONY: classify modelmaker test

## BUILD RULES ##

$(OBJ) $(BIN):
	@mkdir $@

$(OBJ)/%.o: | $(OBJ)
	@echo 'Building $@...'
	@$(CXX) $(CXXFLAGS) $(filter %/$*.cc,$(SRCS)) -o $@

$(CLASSIFY): $(OBJ)/model.o $(OBJ)/classifier.o $(OBJ)/classify_main.o | $(BIN)
	@echo 'Building $@...'
	@$(LD) $(LDFLAGS) $^ -o $@
	@echo 'Done building classify!'

$(MODELMAKER): $(OBJ)/modelfilemaker.o $(OBJ)/modelmaker_main.o | $(BIN)
	@echo 'Building $@...'
	@$(LD) $(LDFLAGS) $^ -o $@
	@echo 'Done building modelmaker!'

$(TEST): $(OBJ)/tests_main.o $(TEST_DEPS) | $(BIN)
	@echo 'Building $@...'
	@$(LD) $(LDFLAGS) $^ -o $@
	@echo 'Done building tests!'
