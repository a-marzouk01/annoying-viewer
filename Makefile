# Define the compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Define the target executable name and source files
TARGET = main
SRC = main.cpp

# Platform detection
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
else ifeq ($(UNAME), Darwin)
    LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit
else ifeq ($(OS), Windows_NT)
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
endif

# Rule to compile and link
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Clean up the build files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean run

