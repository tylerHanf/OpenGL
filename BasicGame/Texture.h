#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {

    public:
        int width;
        int height;
        unsigned char* textureData;
        Texture();
        Texture(int w, int h, unsigned char* data);
};

#endif