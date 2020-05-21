CC=g++
DEPS=../Utils/Utils.h
LIBS=-lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lSOIL

first.exe: Source.o Utils.o
	$(CC) Source.o Utils.o -o first.exe $(LIBS)

Source.o: Source.cpp $(DEPS)
	$(CC) -c $^

Utils.o:
	$(MAKE) -C ../Utils
