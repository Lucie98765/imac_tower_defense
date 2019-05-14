#include "../include/batiment.h"

//constructor

Installation::Installation() : Entity() {};

//overload1
Installation::Installation(int installation_x, int installation_y) :
    Entity(installation_x, installation_y)
{};

//overload2
Installation::Installation(int installation_x, int installation_y, TYPE_INSTALL type, int price) : 
    Entity(installation_x, installation_y),
    type(type),
    price(price),
    size(20){
};

//destructor
Installation::~Installation() {};


//getters (no need setters)
int Installation::get_size()
{
    return size;
}

int Installation::get_price()
{
    return price;
}

int Installation::get_scope()
{
    return scope;
}

// int Installation::get_position_x()
// {
//     return installation_x;
// }

// int Installation::get_position_y()
// {
//     return installation_y;
// }


//methods
void Installation::amelioration(TYPE_INSTALL type, Tower tower)
{
    switch (type)
    {
    case RADAR:
    {
        float new_value = 1.25 * tower.get_scope();
        tower.set_scope(new_value);
        break;
    }

    case FACTORY_ARMAMENT:
    {
        float new_value = 1.25 * tower.get_power();
        tower.set_power(new_value);
        break;
    }

    case STOCK_MUNITIONS:
    {
        float new_value = 1.25 * tower.get_cadence();
        tower.set_cadence(new_value);
        break;
    }

    default:
        break;
    }
}