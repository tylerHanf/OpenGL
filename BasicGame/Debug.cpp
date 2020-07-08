#include "Debug.h"
#include <iostream>
#include <string>
#include "LoadData.h"
#include "Object.h"
#include "Position.h"

void Debug::reportError(std::string errorString) {
    std::cout << errorString << std::endl;
}

void Debug::displayLoadedData(LoadData &ld) {
    std::vector<std::vector<float>> verts = ld.getVertices();
    std::vector<std::vector<float>> texels = ld.getTexels();
    std::vector<GLuint> textIDs = ld.getTextIDs();
    std::vector<int> vertIDs = ld.getVertIDs();
    std::vector<std::string> texturePaths = ld.getTexturePaths();

    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$    LOADED DATA    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Displaying Loaded Vertices" << std::endl;
    for (int i=0; i<verts.size(); i++) {
        for (int j=0; j<verts.at(i).size()-3; j+=3) {
            std::cout << verts.at(i).at(j) << " ";
            std::cout << verts.at(i).at(j+1) << " ";
            std::cout << verts.at(i).at(j+2) << std::endl;;
        }
    }

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Displaying texels" << std::endl;
    for (int i=0; i<texels.size(); i++) {
        for (int j=0; j<texels.at(i).size()-2; j+=2) {
            std::cout << texels.at(i).at(j) << " ";
            std::cout << texels.at(i).at(j+1) << std::endl;
        }
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Displaying numVertices" << std::endl;
    for (int i=0; i<verts.size(); i++) {
        std::cout << "Vert " << i << " size: " << ld.getNumVertices(i) << std::endl; 
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Displaying textIDs" << std::endl;
    for (int i=0; i<textIDs.size(); i++) {
        std::cout << "Texture ID " << i << ": " << textIDs.at(i) << std::endl;
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Displaying vert IDs" << std::endl;
    for (int i=0; i<vertIDs.size(); i++) {
        std::cout << "Vert ID " << i << ": " << vertIDs.at(i) << std::endl;
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Displaying texture paths" << std::endl;
    for (int i=0; i<texturePaths.size(); i++) {
        std::cout << "File: " << texturePaths.at(i) << std::endl;
    }
}

void Debug::displayObjectData(Object* obj) {
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ OBJECT DATA $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Displaying Object Data" << std::endl;
    std::cout << obj->getDataIndex() << std::endl;
    displayPosition(obj->getPosition());
}

void Debug::displayPosition(Position pos) {
    std::cout << "pos(" << pos.posToVec4().x << "," << pos.posToVec4().y << "," << pos.posToVec4().z << ")" << std::endl;
}

void Debug::displayPosition(glm::vec3 pos) {
    std::cout << "pos(" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
}

void Debug::displayNumObjects(ObjectData& objData) {
    std::cout << "Number of Objects Made: " << objData.getNumObjects() << std::endl;
}