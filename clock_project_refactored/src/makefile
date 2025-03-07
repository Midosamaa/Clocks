# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# SFML Libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files and output
SRC = main.cpp ClockApplication.cpp TimeDisplay.cpp DigitClock.cpp AnimationController.cpp Clock.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = clock_app

# Default rule: compile the program
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(SFML_LIBS)

# Rule to compile individual .cpp files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: all
	./$(TARGET)
