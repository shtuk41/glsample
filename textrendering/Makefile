CFILES = main.cpp
FILELOC=./
CFLAGS = -g -Wall 
INCLUDES = -I/usr/local -I/usr/include/SOIL -I../common `pkg-config --cflags glfw3` `pkg-config --cflags opencv` `pkg-config --cflags freetype2`
LIBS = -lm -L/usr/local/lib -lGL -lGLU -lGLEW -lSOIL `pkg-config --static --libs glfw3` `pkg-config --libs opencv` `pkg-config --libs freetype2`
CC = g++

all: main

main:	
	$(CC) $(CFLAGS) $(INCLUDES) $(FILELOC)main.cpp $(FILELOC)shader.cpp $(FILELOC)texture.cpp $(FILELOC)controls.cpp -o main $(LIBS)

clean:
	rm main