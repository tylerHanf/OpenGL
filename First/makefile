CC=g++
DEPS=Utils.h
LIBS=-lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

first.exe: Source.o Utils.o
	$(CC) Source.o Utils.o -o first.exe $(LIBS)

Source.o: Source.cpp $(DEPS)
	$(CC) -c Source.cpp

Utils.o: Utils.cpp $(DEPS)
	$(CC) -c Utils.cpp
