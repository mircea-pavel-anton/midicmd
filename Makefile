build:
	g++ -std=c++17 src/main.cpp src/objects/*/*.cpp lib/RtMidi.cpp -o midicmd.out -D__LINUX_ALSA__ -lasound -lpthread