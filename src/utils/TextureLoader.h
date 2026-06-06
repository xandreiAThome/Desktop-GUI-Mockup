#pragma once
#include <glad/glad.h>
#include <string>

// Loads an image file into an OpenGL texture.
// Returns the texture ID, or 0 on failure.
// outW / outH are filled with the image dimensions.
GLuint loadTexture(const std::string& path, int& outW, int& outH);