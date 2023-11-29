CXXFLAGS = -g -std=c++17 -lGL -lGLU -lglut 
CXX      = g++

# These targets don't create any files:
.PHONY: all clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

all: arcade

arcade: arcade.o
	$(CXX) $(CXXFLAGS) -o $@ $+
arcade.o: arcade.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -f arcade *.o
