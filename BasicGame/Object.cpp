#include "Object.h"
#include "Position.h"

Object::Object(Position initPos, std::size_t index) {
    pos = initPos;
    dataIndex = index;
}

Object::Object(std::size_t index) 
{
    pos = Position();
    dataIndex = index;
}

Object* Object::createObject(std::size_t dataIndex) {
    Object* obj_p = new Object(dataIndex);
    return obj_p;
}

void Object::move(Position moveBy) {
    pos.move(moveBy);
}

std::size_t Object::getDataIndex() {
    return dataIndex;
}