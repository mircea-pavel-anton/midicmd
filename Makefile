MAIN = src/main.cpp
OBJECTS = src/objects/*/*.cpp
LIB = lib/RtMidi.cpp
FLAGS = -D__LINUX_ALSA__ -lasound -lpthread
BINARY = midicmd.out

all: build execute clean

build: compile link

compile:
	@ mkdir build -p
	@ printf "Compiling libraries... "
	@ cd build && g++ -c ../$(LIB) $(FLAGS)
	@ echo "Done"
	@ printf "Compiling source code..."
	@ cd build && g++ -std=c++17 -c ../$(MAIN) ../$(OBJECTS) $(FLAGS)
	@ echo "Done"

link:
	@ printf "Linking..."
	@ g++ ./build/* -o $(BINARY) $(FLAGS)
	@ echo "Done"

execute:
	@ $(BINARY) help

clean:
	@ printf "Removing build dir..."
	@ rm -rf build
	@ echo "Done"
	@ printf "Removing binary..."
	@ rm $(BINARY)
	@ echo "Done"
