# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++17

# SFML Libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source Files
SRC = main.cpp \
      features/Hand.cpp \
      features/Clock.cpp \
      communication/communication.cpp

# Transition Source Files
SRC_TRANSITIONS = $(wildcard transitions/*.cpp)
SRC_TRANSITIONS += type_transitions/type_transitions.cpp

# Combine All
SRC += $(SRC_TRANSITIONS)

# Object Files
OBJ = $(SRC:.cpp=.o)

# Output Executable
TARGET = clock_display

# Include Paths (for supervisor's ClockMotion)
INCLUDES = -I. -I../supervisor

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(SFML_LIBS)

# Compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)
