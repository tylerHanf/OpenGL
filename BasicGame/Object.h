/**
 * Handles object position and includes index value
 *      for object vertices and texture within ObjectData class
 **/
#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "../Utils/ImportedModel.h"
#include "Position.h"
#include "../Utils/Importer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object {
    Position pos;
    std::size_t dataIndex; 
    int numVertices;

    public:
        Object(Position initPos, std::size_t dataIndex, int vertCount);
        Object(std::size_t dataIndex, int vertCount);
        Object* createObject(std::size_t dataIndex, int vertCount);
        void move(Position);
        std::size_t getDataIndex();
        glm::vec3 getPosition();
        int getNumVertices();
};

#endif