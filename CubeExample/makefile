CC=g++
DEPS=../Utils/Utils.h
UTILS=../Utils/Utils.o
LIBS=-lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

first.exe: Cube.o Utils.o
	$(CC) Cube.o $(UTILS) -o first.exe $(LIBS)

Cube.o: Cube.cpp $(DEPS)
	$(CC) -c Cube.cpp

Utils.o:
	$(MAKE) -C ../Utils
