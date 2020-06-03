#include <vector>
#include <string>

#include "ObjectData.h"
#include "Object.h"
#include "../Utils/Importer.h"


ObjectData::ObjectData(std::vector<std::string> fileList) {
    Importer import;
    for (std::size_t i=0; i<fileList.size(); i++) {
        import.readFile(fileList[i].c_str());
        vertices.push_back(import.getVertices());
        texels.push_back(import.getTexels());
        texturePaths.push_back(import.getTexturePath());
        objects.push_back(new Object(i));
    }
}

void ObjectData::addObjectData(std::string filepath) {
    Importer import;
    import.readFile(filepath.c_str());
    vertices.push_back(import.getVertices());
    texels.push_back(import.getTexels());
    texturePaths.push_back(import.getTexturePath());
    objects.push_back(new Object(vertices.size()));
}

/*
void ObjectData::CreateObject {

}
*/

/*void loadTexture(std::string texturePath) {
    
}*/

std::vector<float> ObjectData::getObjectVertices(std::size_t index) {
    return vertices[index];
}

std::vector<float> ObjectData::getObjectTexels(std::size_t index) {
    return texels[index];
}

std::string ObjectData::getObjectTexPath(std::size_t index) {
    return texturePaths[index];
}

Object* ObjectData::getObject(std::size_t index) {
    return objects[index];
}

std::size_t ObjectData::getNumObjects() {
    return objects.size();
}
