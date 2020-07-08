#include "Object.h"
#include "Position.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Object::Object(Position initPos, std::size_t index, int vertCount) {
    pos = initPos;
    dataIndex = index;
    numVertices = vertCount;
}

Object::Object(std::size_t index, int vertCount) 
{
    pos = Position();
    dataIndex = index;
    numVertices = vertCount;
}

Object::~Object() {
    std::cout << "Deleting object" << std::endl;
}

Object* Object::createObject(std::size_t dataIndex, int vertCount) {
    Object* obj_p = new Object(dataIndex, vertCount);
    return obj_p;
}

void Object::move(Position moveBy) {
    pos.move(moveBy);
}

std::size_t Object::getDataIndex() {
    return dataIndex;
}

glm::vec3 Object::getPosition() {
    return pos.posToVec3();
}

int Object::getNumVertices() {
    return numVertices;
}