CXX = g++
CXXFLAGS = -std=c++17 -c -g -O0 -Wall -Wextra -Werror -pedantic -I include

LD = g++
LDFLAGS = -std=c++17

tests : build/tests_main.o
	$(LD) $(LDFLAGS) $? -o build/$@

# delete everything in build/ except compiled Catch file
clean :
	find build/* -not -name "tests_main.o" -delete