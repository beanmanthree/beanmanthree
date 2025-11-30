# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
DEBUGFLAGS = -g -O0
RELEASEFLAGS = -O2

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Project files
TARGET = beanmanthree
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target (release build)
all: release

# Release build
release: CXXFLAGS += $(RELEASEFLAGS)
release: $(TARGET)

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: release
	./$(TARGET)

# Run with debugging
gdb: debug
	gdb ./$(TARGET)

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all release debug run gdb clean rebuild
