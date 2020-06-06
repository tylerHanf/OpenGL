/**
 * Holds camera position data and operations for the camera movement
 **/

#ifndef CAMERA_H
#define CAMERA_H

#include "Position.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    Position pos;

    public:
        Camera();
        Camera(Position);
        glm::vec3 getPosition();
        //Move camera by a given position
        void move(Position);
};

#endif