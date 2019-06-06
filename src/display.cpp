#include "../include/display.h"

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "Imac Tower Defense";

/* Espace fenetre virtuelle */
static const float GL_VIEW_WIDTH = 800.;
static const float GL_VIEW_HEIGHT = 600.;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;



void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{ 
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-GL_VIEW_WIDTH/2, GL_VIEW_WIDTH/2, -GL_VIEW_HEIGHT/2, GL_VIEW_HEIGHT/2);

}

void display_welcome(GLuint* texture){
    if (NULL != texture){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(-400., -300.);
        
            glTexCoord2f(1, 1);
            glVertex2f(400., -300.);
        
            glTexCoord2f(1, 0);
            glVertex2f(400., 300.);
        
            glTexCoord2f(0, 0);
            glVertex2f(-400., 300.);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of welcome image failed\n");
    }

}

void display_map_texture(GLuint* texture){
    if (NULL != texture){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(-400., -300.);
        
            glTexCoord2f(1, 1);
            glVertex2f(400., -300.);
        
            glTexCoord2f(1, 0);
            glVertex2f(400., 300.);
        
            glTexCoord2f(0, 0);
            glVertex2f(-400., 300.);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of map image failed\n");
    }

}

void draw_help(GLuint* texture_help){
    if (NULL != texture_help){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_help);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(-390., -300.);
        
            glTexCoord2f(1, 1);
            glVertex2f(-375., -300.);
        
            glTexCoord2f(1, 0);
            glVertex2f(-375., -270.);
        
            glTexCoord2f(0, 0);
            glVertex2f(-390., -270.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of help button failed\n");
    }

}

void open_help(GLuint* texture_wdw){
    if (NULL != texture_wdw){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_wdw);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(-400., -300.);
        
            glTexCoord2f(1, 1);
            glVertex2f(400., -300.);
        
            glTexCoord2f(1, 0);
            glVertex2f(400., 300.);
        
            glTexCoord2f(0, 0);
            glVertex2f(-400., 300.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of help window failed\n");
    }
}

void draw_tower(GLuint* texture_tower, int x, int y){
    if (NULL != texture_tower){
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_tower);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(x-15, y-32.);
        
            glTexCoord2f(1, 1);
            glVertex2f(x+15., y-32.);
        
            glTexCoord2f(1, 0);
            glVertex2f(x+15., y+31.);
        
            glTexCoord2f(0, 0);
            glVertex2f(x-15., y+31.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of tower failed\n");
    }
}

void draw_monster(GLuint* texture_monster, int x, int y){
    if (NULL != texture_monster){
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_monster);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(x-15, y-18.);
        
            glTexCoord2f(1, 1);
            glVertex2f(x+15., y-18.);
        
            glTexCoord2f(1, 0);
            glVertex2f(x+15., y+18.);
        
            glTexCoord2f(0, 0);
            glVertex2f(x-15., y+18.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of monster failed\n");
    }
}

void draw_installation(GLuint* texture_inst, int x, int y){
    if (NULL != texture_inst){
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_inst);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(x-30, y-15.);
        
            glTexCoord2f(1, 1);
            glVertex2f(x+30., y-15.);
        
            glTexCoord2f(1, 0);
            glVertex2f(x+30., y+15.);
        
            glTexCoord2f(0, 0);
            glVertex2f(x-30., y+15.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of installation failed\n");
    }
}

void write(int x, int y,  char const *string) {
        char const *c;
        glColor3ub(0,0,0);
        // Positionne le premier caractère de la chaîne
        glRasterPos2f(x, y);
        for (c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c); // Affiche chaque caractère de la chaîne

        // Réinitialise la position du premier caractère de la chaîne
        glRasterPos2f(0, 0);
}
