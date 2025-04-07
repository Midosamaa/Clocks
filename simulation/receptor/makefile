# Nom de l'exécutable
TARGET = receptor

# Répertoires
SRC_DIR = .
COMM_DIR = ../simulator/communication

# Fichiers source
SRCS = $(SRC_DIR)/main.cpp $(COMM_DIR)/communication.cpp

# Compilateur
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Règle principale
all: $(TARGET)

# Lier les fichiers sources
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Nettoyage
clean:
	rm -f $(TARGET)

.PHONY: all clean
