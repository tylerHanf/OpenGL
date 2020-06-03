#include "Error.h"
#include <iostream>
#include <string>

void Error::reportError(std::string errorString) {
    std::cout << errorString << std::endl;
}