/**
 * Holds position data and contains movement functionality
 **/
#ifndef POSITION_H
#define POSITION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Position {
    glm::vec3 position;

    public:
        Position();
        Position(float x, float y, float z);
        Position(const Position& otherPos);
        void move(Position);
        //Returns vec3 version of position
        glm::vec3 posToVec3();
        //Handle assignment operator
        Position& operator= (const Position& otherPos);
};

#endif 