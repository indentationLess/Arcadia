CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iincludes
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = src/main.cpp src/game.cpp src/2048.cpp src/pong.cpp src/ball.cpp src/bat.cpp src/aibat.cpp
HEADERS = src/game.hpp src/settings.h src/2048.hpp src/bat.hpp src/pong.hpp src/ball.hpp src/aibat.hpp src/pong.hpp
TARGET = main

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET)
debug: $(TARGET)
	gdb $(TARGET)
clean:
	rm -f $(TARGET)