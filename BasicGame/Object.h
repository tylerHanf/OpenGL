/**
 * Handles object position and includes index value
 *      for object vertices and texture within ObjectData class
 **/
#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "../Utils/ImportedModel.h"
#include "Position.h"
#include "../Utils/Importer.h"

class Object {
    Position pos;
    std::size_t dataIndex; 


    public:
        Object(Position initPos, std::size_t dataIndex);
        Object(std::size_t dataIndex);
        Object* createObject(std::size_t dataIndex);
        void move(Position);
        std::size_t getDataIndex();
};

#endif