#ifndef BATIMENT_H
#define BATIMENT_H

#include "headers.h"
#include "entity.h"
#include "tower.h"
#include "timer.h"


//To make the difference between installation
enum TYPE_INSTALL {
    RADAR,
    FACTORY_ARMAMENT,
    STOCK_MUNITIONS
};

//class installation

class Installation : public Entity
{
    private:
    TYPE_INSTALL type;
    int size;
    int price;
    float scope;

    public:

    //constructor
    Installation();

    //Overload1
    Installation(int installation_x, int installation_y);

    //Overload2
    Installation(int installation_x, int installation_y, TYPE_INSTALL type, int price);

    //destructor
    ~Installation();

    //getters (no need setters)
    int get_size();
    int get_price();
    int get_scope();

    //other methods
    void amelioration(TYPE_INSTALL type,Tower tower);


    //PARTIE SDL VISUEL à voir...

};


#endif