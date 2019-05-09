#ifndef BATIMENT_H
#define BATIMENT_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstdlib>
#include "entity.h"
#include "tower.h"
#include <new>


enum TYPE_INSTALL {
    RADAR,
    USINE_ARMEMENT,
    STOCK_MUNITIONS
};

//classe installation

class Installation : public Entity
{
    private:
    TYPE_INSTALL type;
    int taille;
    int prix;

    public:

    //constructeur
    Installation(int installation_x, int installation_y);

    //surcharge constructeur;
    Installation(int installation_x, int installation_y, TYPE_INSTALL type, int prix);

    //getters (pas de setters, on n'améliore pas les installatoins)
    int get_taille();
    int get_prix();

    //other methods
    void amelioration(TYPE_INSTALL type,Tower tour);


    //PARTIE SDL VISUEL à voir...

};


#endif