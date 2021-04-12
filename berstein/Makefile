CFILES = main.cpp
FILELOC=./
SOURCE= ./source/
CFLAGS = -g -Wall -std=c++11
INCLUDES = -I/usr/local -I/usr/include/SOIL -I../common -I./include `pkg-config --cflags glfw3` `pkg-config --cflags opencv` `pkg-config --cflags freetype2`
LIBS = -lm -L/usr/local/lib -lGL -lGLU -lGLEW -lSOIL `pkg-config --static --libs glfw3` `pkg-config --libs opencv` `pkg-config --libs freetype2`
CC = g++

all: main

main:	shaders
	$(CC) $(CFLAGS) $(INCLUDES) $(FILELOC)main.cpp -o main shaders.o $(LIBS)
	
shaders:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCE)shaders.cpp -c -o shaders.o
	
clean:
	rm main