CC=g++
DEPS=Utils.h
VPATH=../Utils
LIBS=-lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
OBJECTS=Source.o ImportedModel.o Utils.o Importer.o
EXEC=first.exe

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LIBS)

.PHONY : clean
clean : 
	rm first.exe ./*.o
