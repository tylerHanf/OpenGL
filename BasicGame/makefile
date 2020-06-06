CC=g++
DEPS=Utils.h
VPATH=../Utils
LIBS=-lGLEW -lSOIL -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
OBJECTS=Source.o ImportedModel.o Utils.o Importer.o ObjectData.o Object.o Position.o GL_Context.o Window.o Debug.o LoadData.o Texture.o Camera.o
EXEC=first.exe

$(EXEC): $(OBJECTS)
	$(CC) -g $(OBJECTS) -o $(EXEC) $(LIBS)

.PHONY : clean
clean : 
	rm first.exe ./*.o
