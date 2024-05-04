CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iincludes
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.hpp) $(wildcard src/*.h)
TARGET = main

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@
debug: $(TARGET)
	gdb $<
clean:
	rm -f $(TARGET)