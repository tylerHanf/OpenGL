#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <string>
#include "Texture.h"

class LoadData {
    private:
        std::vector<std::vector<float>> vertices;
        std::vector<std::vector<float>> texels;
        std::vector<std::string> texturePaths;
        std::vector<int> numVertices;
        std::vector<Texture> textures;
        std::vector<GLuint> textIDs;
        std::vector<int> vertIDs;

        //Both called in constructor
        bool loadObj(const std::vector<std::string> &fileList);
        bool loadTextures();

    public:
        LoadData(const std::vector<std::string> &filepaths);
        std::vector<std::vector<float>> &getVertices();
        std::vector<std::vector<float>> &getTexels();
        std::vector<Texture> &getTextures();
        std::vector<GLuint> &getTextIDs();
        std::vector<int> &getVertIDs();
        std::vector<std::string> &getTexturePaths();
        int getNumVertices(std::size_t index);
};

#endif