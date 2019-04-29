#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstdlib>
#include "tower.hpp"


enum TYPE_INSTALL {
    RADAR,
    UNSINE_ARMEMENT,
    STOCK_MUNITIONS,
    DISABLED
};

//classe installation

class Installation
{
    private:
    TYPE_INSTALL type;
    int taille;
    int prix;
    int installation_x;
    int installation_y;

    public:

    //constructeur
    Installation();

    //surcharge constructeur;
    Installation(std::TYPE_INSTALL type, int prix, int installation_x, int installation_y);

    //getters (pas de setters, on n'améliore pas les installatoins)
    int get_taille();
    int get_prix();
    int get_position_x();
    int get_position_y();

    //other methods
    void amelioration(TYPE_INSTALL type,Tower tour);


    //PARTIE SDL VISUEL à voir...

}

Installation* create_installation(int coord_x, int coord_y, TYPE_INSTALL type);