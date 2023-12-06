CXXFLAGS = -g -std=c++17  
LIBS = -lGL -lGLU -lglut
CXX      = g++

# These targets don't create any files:
.PHONY: all clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

all: arcade

arcade: arcade.o npc.o player.o blob.o
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIBS)
arcade.o: arcade.cpp npc.h player.h
	$(CXX) $(CXXFLAGS) -c $<
player.o: player.cpp player.h blob.h
	$(CXX) $(CXXFLAGS) -c $<
npc.o: npc.cpp npc.h blob.h
	$(CXX) $(CXXFLAGS) -c $<
blob.o: blob.cpp blob.h
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -f arcade *.o
