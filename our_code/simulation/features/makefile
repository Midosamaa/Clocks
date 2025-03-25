# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++17

# SFML Libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source Files
SRC = main_features.cpp Hand.cpp Clock.cpp Digit.cpp WholeSystem.cpp

# Object Files
OBJ = $(SRC:.cpp=.o)

# Output Executable
TARGET = clock_display

# Default target: Build the program
all: $(TARGET)

# Compile the executable
$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(SFML_LIBS)

# Compile each .cpp file into an .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
