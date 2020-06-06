#ifndef OBJECT_DATA_H
#define OBJECT_DATA_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <string>
#include "LoadData.h"
#include "Object.h"

class ObjectData {

    std::vector<int> vertIDs;
    std::vector<GLuint> textIDs;
    std::vector<Object*> objects;

    public:
        ObjectData(LoadData* loadedData);
        Object* getObject(std::size_t index);
        GLuint getTextID(std::size_t index);
};

#endif