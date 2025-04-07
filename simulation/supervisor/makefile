CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = supervisor

all: $(TARGET)

supervisor: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean
