#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include "LoadData.h"
#include "Object.h"
#include "Position.h"
#include "ObjectData.h"

class Debug {
    public:
        void reportError(std::string errorString);
        void displayLoadedData(LoadData &ld);
        void displayTextIDs(LoadData &ld);
        void displayObjectData(Object* obj);
        void displayPosition(Position pos);
        void displayPosition(glm::vec3 pos);
        void displayNumObjects(ObjectData& objData);
};

#endif