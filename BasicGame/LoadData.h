#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <string>
#include "Texture.h"

class LoadData {
    private:
        std::vector<std::vector<float>> *vertices;
        std::vector<std::vector<float>> *texels;
        std::vector<std::string> *texturePaths;
        std::vector<int> *numVertices;
        std::vector<Texture*> *textures;
        std::vector<GLuint> *textIDs;
        std::vector<int> *vertIDs;

        //Both called in constructor
        bool loadObj(std::vector<std::string> *fileList);
        bool loadTextures();

    public:
        LoadData(std::vector<std::string> *filepaths);
        std::vector<std::vector<float>> *getVertices() const;
        std::vector<std::vector<float>> *getTexels() const;
        std::vector<Texture*> *getTextures();
        std::vector<GLuint> *getTextIDs() const;
        std::vector<int> *getVertIDs() const;
        std::vector<std::string> *getTexturePaths() const;
        int getNumVertices(std::size_t index);
};

#endif