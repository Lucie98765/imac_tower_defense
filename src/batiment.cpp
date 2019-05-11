#include "../include/batiment.h"

Installation::Installation(int installation_x, int installation_y) :
    Entity(installation_x, installation_y)
{};

Installation::Installation(int installation_x, int installation_y, TYPE_INSTALL type, int prix) : 
    Entity(installation_x, installation_y),
    type(type),
    prix(prix),
    taille(20){
};

int Installation::get_taille()
{
    return taille;
}

int Installation::get_prix()
{
    return prix;
}

// int Installation::get_position_x()
// {
//     return installation_x;
// }

// int Installation::get_position_y()
// {
//     return installation_y;
// }

void Installation::amelioration(TYPE_INSTALL type, Tower tour)
{
    switch (type)
    {
    case RADAR:
    {
        float new_value = 1.25 * tour.get_portee();
        tour.set_portee(new_value);
        break;
    }

    case USINE_ARMEMENT:
    {
        float new_value = 1.25 * tour.get_puissance();
        tour.set_puissance(new_value);
        break;
    }

    case STOCK_MUNITIONS:
    {
        float new_value = 1.25 * tour.get_cadence();
        tour.set_cadence(new_value);
        break;
    }

    default:
        break;
    }
}