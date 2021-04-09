
all: build execute clean

build: compile link

compile:
	@ mkdir build -p
	@ cd build && g++ -std=c++17 -c ../src/main.cpp ../src/objects/*/*.cpp ../lib/RtMidi.cpp -D__LINUX_ALSA__ -lasound -lpthread

link:
	@ g++ ./build/* -o midicmd

execute:
	@ ./midicmd help

clean:
	@ rm -rf build
	@ rm midicmd
