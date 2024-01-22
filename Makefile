# Makefile for main.cpp

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Name of the executable
TARGET = main

# Source files
SOURCES = main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Run options
RUNOPTIONS ?=

# Default target
all: $(TARGET)

# Linking the executable from the object files
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compiling the source files into object files
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET) $(RUNOPTIONS)

# Run the program with Valgrind
vrun: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) $(RUNOPTIONS)

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all run vrun clean
