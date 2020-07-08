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

    LoadData loadedData = LoadData(filepath);
    GL_Context glCon = GL_Context(&loadedData);
    ObjectData objData = ObjectData(&loadedData);
    Object* player = objData.getObject(0);
    player->move(Position(-2.0f, 1.0f, 1.0f));

    float i = 0.0f;
    while (!glCon.windowShouldClose()) {
        player->move(Position(i*glCon.getTime(), 1.0f, 1.0f));
        glCon.runSingleFrame(objData);
        i -= 0.00000001;
    }

    return 0;
}