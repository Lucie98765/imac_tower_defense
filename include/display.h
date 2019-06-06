#ifndef DEF_DISPLAY_H
#define DEF_DISPLAY_H
#include "../include/headers.h"


void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
void draw_help(GLuint* texture_help);
void open_help(GLuint* texture_wdw);
void draw_tower(GLuint* texture_tower, int x, int y);
void draw_monster(GLuint* texture_monster, int x, int y);
void draw_installation(GLuint* texture_inst, int x, int y);
void write(int x, int y,  char const *string);
void display_welcome(GLuint* texture);
void display_map_texture(GLuint* texture);



#endif