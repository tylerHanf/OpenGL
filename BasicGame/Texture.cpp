#include "Texture.h"

Texture::Texture() {
    width, height, textureData = 0;
}

Texture::Texture(int w, int h, unsigned char* data) {
    width = w;
    height = h;
    textureData = data;
}