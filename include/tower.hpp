#ifndef TOWER_H
#define TOWER_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstdlib>
//#include "monster.hpp"




enum TYPE_TOWER {
    ROCKET,
    LASER,
    MACHINEGUN,
    HYPRBID,
    DISABLED
};

class Tower
{
    private:
    TYPE_tOWER type;
    float puissance;
    float portee:
    float cadence;
    int prix;
    int rayon;
    int tower_x;
    int tower_y;
    GLuint texture;
    Monster cible;


    public:

//construteur
    tower();

//surcharge constructeur
    tower(std::TYPE_TOWER type, float puissance, float portee, float cadence, int tower_x, int tower_y int prix);


//getter
    float get_puissance();
    float get_cadence();
    float get_portee();
    int get_prix();
    int get_rayon();
    float get_position_x();
    float get_position_y();

//setter    
    void set_puissance(float value);
    void set_cadence(float value);
    void set_portee(float value);
    void set_prix(int value);
    void set_position(int value_x, int value_y);

//other method
    void tirer(int puissance, Monster monster);


//PARTIE SDL VISUEL à voir...

};

Tower* create_tower(int coord_x, int coord_y, TYPE_TOWER type);