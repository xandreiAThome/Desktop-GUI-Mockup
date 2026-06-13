#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "TextureLoader.h"
#include <cstdio>

GLuint loadTexture(const std::string& path, int& outW, int& outH) {
    int channels;
    // flip so the image is right-side-up in OpenGL coords
    stbi_set_flip_vertically_on_load(false);

    // load pixel data + load dimensions and color channels into outw, outh, channels
    unsigned char* data = stbi_load(path.c_str(), &outW, &outH, &channels, 4);

    // check if data loaded properly
    if (!data) {
        fprintf(stderr, "Failed to load texture: %s\n", path.c_str());
        return 0;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    // smoothing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // load to gpu memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, outW, outH, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return texID;
}