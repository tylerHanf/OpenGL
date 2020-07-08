#include "Position.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Default constructor
 **/
Position::Position() {
    position = glm::vec4(8.0f, 1.0f, 1.0f, 1.0f);
}

/**
 * Position constructor takes floats to make a glm vec3
 **/
Position::Position(float x, float y, float z) {
    position = glm::vec4(x, y, z, 1.0f);
}

/**
 * Copy constructor
 **/
Position::Position(const Position& otherPos) {
    position = otherPos.position;
}

/**
 * Uses glm::translate to move position
 **/
void Position::move(Position moveBy) {
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), moveBy.posToVec3());
    position = translate * position;
}

/**
 * Returns the vec3 value of the position
 **/
glm::vec4 Position::posToVec4() {
    return position;
}

glm::vec3 Position::posToVec3() {
    glm::vec3 vec3 = glm::vec3(position.x, position.y, position.z);
    return vec3;
}
/**
 * Fix assignment operator
 **/
Position& Position::operator= (const Position& otherPos) {
    if (this == &otherPos) {
        return *this;
    }

    position = otherPos.position;
    return *this;
}