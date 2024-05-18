CXX = g++
CXXFLAGS = -Wall -Iincludes -J 
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SOURCES = $(wildcard src/*.cpp) $(wildcard src/pong/*.cpp) $(wildcard src/TwentyFourtyEight/*.cpp)
HEADERS = $(wildcard src/*.hpp) $(wildcard src/*.h)  $(wildcard src/pong/*.hpp) $(wildcard src/TwentyFourtyEight/*.hpp)
TARGET = main

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@
debug: $(TARGET)
	gdb $<
clean:
	rm -f $(TARGET)
	.