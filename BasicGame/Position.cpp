#include "Position.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Default constructor
 **/
Position::Position() {
    position = glm::vec3(8.0f, 0.0f, 0.0f);
}

/**
 * Position constructor takes floats to make a glm vec3
 **/
Position::Position(float x, float y, float z) {
    position = glm::vec3(x, y, z);
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
    //position *= glm::translate(glm::mat4(1.0f), moveBy.posToVec3());
}

/**
 * Returns the vec3 value of the position
 **/
glm::vec3 Position::posToVec3() {
    return position;
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