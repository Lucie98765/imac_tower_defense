#ifndef DEF_TEXTURE_H
#define DEF_TEXTURE_H
#include "../include/headers.h"


GLuint createTexture(char const *image_path);
void free_texture(GLuint texture);

#endif