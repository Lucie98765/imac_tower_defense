#ifndef BATIMENT_H
#define BATIMENT_H

#include "headers.h"
#include "entity.h"
#include "tower.h"
#include "timer.h"


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
    float portee;

    public:

    //constructeur
    Installation();

    //surcharge
    Installation(int installation_x, int installation_y);

    //surcharge constructeur;
    Installation(int installation_x, int installation_y, TYPE_INSTALL type, int prix);

    //destructeur
    ~Installation();

    //getters (pas de setters, on n'améliore pas les installatoins)
    int get_taille();
    int get_prix();
    int get_portee();

    //other methods
    void amelioration(TYPE_INSTALL type,Tower tour);


    //PARTIE SDL VISUEL à voir...

};


#endif