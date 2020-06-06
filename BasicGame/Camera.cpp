#include "Camera.h"
#include "Position.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    pos = Position(0.0f, 0.0f, 0.0f);
}

//Init Camera
Camera::Camera(Position initPos) {
    pos = initPos;
}

glm::vec3 Camera::getPosition() {
    return pos.posToVec3();
}

void Camera::move(Position moveBy) {
    pos.move(moveBy);
}