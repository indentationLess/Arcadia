CXX=g++
RM=rm -f
CXXFLAGS=-std=c++11 -g -DSFML_STATIC -I$(PATH_TO_SFML_INCLUDE) -L$(PATH_TO_SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lfreetype
TARGET=main

.PHONY: all clean

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o $(TARGET)

clean:
	$(RM) $(TARGET)

run:
	./$(TARGET)