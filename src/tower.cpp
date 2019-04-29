#include "../include/tower.hpp"


//getters
float Tower::get_puissance() {
    return puissance;
}

float Tower::get_cadence() const {
    return cadence;
}

float Tower::get_portee() const {
    return portee;
}

int Tower::get_prix() const {
    return prix;
}

int Tower::get_rayon() const {
     return rayon;
}

int Tower::get_position_x() const {
    return tower_x;
}

int Tower::get_position_y() const {
    return tower_y;
}

//setters
void Tower::set_puissance(float value) {
    puissance = value;
}

void Tower::set_cadence(float value) {
    cadence = value;
}

void Tower::set_portee(float value) {
    portee = value;
}

void Tower::set_prixt(int value) {
    prix = value;
}

void Tower::set_position(int value_x, int value_y) {
    tower_x = value_x;
    tower_y = value_y;
}

Tower::Tower() {};

Tower::Tower(TYPE_TOWER type, float puissance, float portee, float cadence, int tower_x, int tower_y, int prix): 
    type(type),
    puissance(puissance),
    portee(portee),
    cadence(cadence),
    tower_x(tower_x),
    tower_y(tower_y),
    prix(prix),
    rayon(20) 
    {

    }
;

Tower* create_tower(int coord_x, int coord_y, TYPE_TOWER type, Tower* new_tower) {

    switch (type)
    {
        case ROCKET:
            *Tower new_tower(type,8,4,2,coord_x,coord_y,5);
            break;

        case LASER:
            *Tower new_tower(type,5,2,8,coord_x,coord_y,5);
            break;
        
        case MACHINEGUN:
            *Tower new_tower(type,2,2,4,coord_x,coord_y,3);
            break;
        
        case HYBRID:
            *Tower new_tower(type,3,8,6,coord_x,coord_y,6);
            break;
            
        default:
            break;
    }
}