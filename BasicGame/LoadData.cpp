#include "LoadData.h"
#include "../Utils/Importer.h"
#include "../Utils/Utils.h"
#include "Texture.h"
#include <SOIL2/SOIL2.h>
#include <vector>
#include <string>

LoadData::LoadData(const std::vector<std::string> &filepaths) {
    vertices = std::vector<std::vector<float>>();
    texels = std::vector<std::vector<float>>();
    texturePaths = std::vector<std::string>();
    numVertices = std::vector<int>();
    textures = std::vector<Texture>();
    vertIDs = std::vector<int>();
    loadObj(filepaths);
    textIDs = std::vector<GLuint>(texturePaths.size());
    loadTextures();
}

/**
 * TODO: Use folder name as object type identifier
 **/
bool LoadData::loadObj(const std::vector<std::string> &fileList) {
    Importer import;
    for (const auto& file: fileList ) {
        import.readFile(file.c_str());
        std::vector<float> verts = import.getVertices();
        numVertices.push_back(verts.size()/3);
        vertices.push_back(verts);
        texels.push_back(import.getTexels());
        texturePaths.push_back(import.getTexturePath());
        
    }
    return true;
}

bool LoadData::loadTextures() {
    for (int i=0; i<texturePaths.size(); i++) {
        Texture *newTexture = new Texture();
        getPNGDim(texturePaths.at(i), &newTexture->width, &newTexture->height);
        newTexture->textureData = SOIL_load_image(texturePaths.at(i).c_str(), &newTexture->width, &newTexture->height, 0, SOIL_LOAD_RGB);
        textures.push_back(*newTexture);
    }
    return true;
}

std::vector<std::vector<float>> &LoadData::getVertices() {
    return vertices;
}

std::vector<std::vector<float>> &LoadData::getTexels() {
    return texels;
}

std::vector<Texture> &LoadData::getTextures() {
    return textures;
}

std::vector<GLuint> &LoadData::getTextIDs() {
    return textIDs;
}

std::vector<int> &LoadData::getVertIDs() {
    return vertIDs;
}

std::vector<std::string> &LoadData::getTexturePaths() {
    return texturePaths;
}

int LoadData::getNumVertices(std::size_t index) {
    return numVertices[index];
}
