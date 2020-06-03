#include "Camera.h"
#include "Position.h"

//Init Camera
Camera::Camera(Position initPos) {
    pos = initPos;
}

Position Camera::getPosition() {
    return pos;
}

void Camera::move(Position moveBy) {
    pos.move(moveBy);
}