#include <vector>
#include <string>

#include "ObjectData.h"
#include "Object.h"
#include "LoadData.h"
#include "../Utils/Importer.h"
#include "Debug.h"


ObjectData::ObjectData(LoadData* loadedData) {
    Debug err = Debug();
    vertIDs = *(loadedData->getVertIDs());
    textIDs = *(loadedData->getTextIDs());
    for (int i=0; i<vertIDs.size(); i++) {
        Object* newObject = new Object(i, loadedData->getNumVertices(i));
        objects.push_back(newObject);
        err.displayObjectData(newObject);
    }
}

Object* ObjectData::getObject(std::size_t index) {
    return objects[index];
}

GLuint ObjectData::getTextID(std::size_t index) {
    return textIDs[index];
}
