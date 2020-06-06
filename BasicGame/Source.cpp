#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "ObjectData.h"
#include "GL_Context.h"
#include "LoadData.h"
#include "Debug.h"
#include "Window.h"

/**
 * TODO: Add OpenGL Data class to hold and handle OpenGL data
 **/
int main(void) {
    Debug err = Debug();
    std::vector<std::string> filepath; 
    filepath.push_back("Assets/Objects/cube.obj");
    LoadData loadedData = LoadData(&filepath);
    GL_Context glCon = GL_Context(&loadedData);
    err.displayLoadedData(&loadedData);
    ObjectData objData = ObjectData(&loadedData);
    /*Object* player = objData.getObject(0);
    player->move(Position(-2.0f, 0.0f, 0.0f));
    */
    glCon.renderLoop(objData);
    exit(EXIT_SUCCESS);
}