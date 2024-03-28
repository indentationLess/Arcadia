CXX=g++
RM=rm -f
CXXFLAGS = -I/path/to/SFML/include -L/path/to/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
TARGET=main

.PHONY: all clean

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o $(TARGET)

clean:
	$(RM) $(TARGET)

run:
	./$(TARGET)