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
        Camera(Position);
        Position getPosition();
        //Move camera by a given position
        void move(Position);
};

#endif