#include <vector>
#include <string>
#include <iostream>

#include "ObjectData.h"
#include "Object.h"
#include "LoadData.h"
#include "../Utils/Importer.h"
#include "Debug.h"


ObjectData::ObjectData(LoadData* loadedData) {
    Debug err = Debug();
    vertIDs = loadedData->getVertIDs();
    textIDs = loadedData->getTextIDs();
    for (int i=0; i<vertIDs.size(); i++) {
        std::cout << "Adding object" << std::endl;
        Object newObject = Object(i, loadedData->getNumVertices(i));
        objects.push_back(newObject);
        err.displayObjectData(&newObject);
    }
    std::cout << "Objects size: " << objects.size() << std::endl;
}

ObjectData::~ObjectData() {
    std::cout << "Deleting object" << std::endl;
}

Object* ObjectData::getObject(std::size_t index) {
    return &(objects[index]);
}

GLuint ObjectData::getTextID(std::size_t index) {
    return textIDs[index];
}

int ObjectData::getNumObjects() {
    return objects.size();
}
