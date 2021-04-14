MAIN = src/main.cpp
OBJECTS = src/objects/*/*.cpp
LIB = lib/RtMidi.cpp
FLAGS = -D__LINUX_ALSA__ -lasound -lpthread
BINARY = midicmd

build: compile link

compile:
	@ mkdir build -p
	@ printf "Compiling libraries... "
	@ cd build && g++ -c ../$(LIB) $(FLAGS)
	@ echo "\033[1;32mDone\033[1;0m"
	@ printf "Compiling source code... "
	@ cd build && g++ -std=c++17 -c ../$(MAIN) ../$(OBJECTS) $(FLAGS)
	@ echo "\033[1;32mDone\033[1;0m"

link:
	@ printf "Linking..."
	@ g++ ./build/* -o $(BINARY) $(FLAGS)
	@ echo "\033[1;32mDone\033[1;0m"

clean:
	@ printf "Removing build dir..."
	@ rm -rf build
	@ echo "\033[1;32mDone\033[1;0m"
	@ printf "Removing binary..."
	@ rm $(BINARY)
	@ echo "\033[1;32mDone\033[1;0m"

install: build
	@ printf "Copying compiled binary to /usr/local/bin... "
	@ sudo cp ${BINARY} /usr/local/bin/$(BINARY)
	@ echo "\033[1;32mDone\033[1;0m"
	@ echo "\033[1;32m\033[1;1mInstallation complete!\033[1;0m"