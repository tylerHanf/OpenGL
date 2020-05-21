CC=g++
DEPS=../Utils/Utils.h
UTILS=../Utils/Utils.o
LIBS=-lGLEW -lSOIL -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor 
first.exe: Source.o Utils.o
	$(CC) Source.o $(UTILS) -o first.exe $(LIBS)

Source.o: Source.cpp $(DEPS)
	$(CC) -c Source.cpp

Utils.o:
	$(MAKE) -C ../Utils
