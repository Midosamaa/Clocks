# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Files
SRC = main.cpp
TARGET = supervisor_app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
