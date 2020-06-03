#ifndef OBJECT_DATA_H
#define OBJECT_DATA_H

#include <vector>
#include <string>

#include "Object.h"

class ObjectData {
    std::vector<std::vector<float>> vertices;
    std::vector<std::vector<float>> texels;
    std::vector<const unsigned char*> textures;
    std::vector<std::string> texturePaths;
    std::vector<Object*> objects;

    void loadTexture(std::string texturePath);
    void loadObjectData(Importer, std::string filepath);

    public:
        ObjectData(std::vector<std::string>);
        std::vector<float> getObjectVertices(std::size_t index);
        std::vector<float> getObjectTexels(std::size_t index);
        std::string getObjectTexPath(std::size_t index);
        Object* getObject(std::size_t index);
        void addObjectData(std::string filepath);
        std::size_t getNumObjects();
};

#endif