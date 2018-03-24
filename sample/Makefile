CFILES = main.cpp
CFLAGS = -g -Wall
INCLUDES = -I/usr/local -I/usr/include/SOIL -I../common `pkg-config --cflags glfw3` `pkg-config --cflags opencv`
LIBS = -lm -L/usr/local/lib -lGL -lGLU -lGLEW -lSOIL `pkg-config --static --libs glfw3` `pkg-config --libs opencv`
CC = g++

all: main

main:	
	$(CC) $(CFLAGS) $(INCLUDES) main.cpp shader.cpp -o main $(LIBS)

clean:
	rm main