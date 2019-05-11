#include "../include/tower.h"


//getters
float Tower::get_puissance() {
    return puissance;
}

float Tower::get_cadence() {
    return cadence;
}

float Tower::get_portee() {
    return portee;
}

int Tower::get_prix() {
    return prix;
}

int Tower::get_rayon() {
     return rayon;
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

void Tower::set_prix(int value) {
    prix = value;
}


//constructeur

Tower::Tower(int tower_x, int tower_y) : Entity(tower_x, tower_y) {
}

Tower::Tower(int tower_x, int tower_y, TYPE_TOWER type, float puissance, float portee, float cadence, int prix): 
    Entity(tower_x, tower_y),
    type(type),
    puissance(puissance),
    portee(portee),
    cadence(cadence),
    prix(prix),
    rayon(20)
    {

    }


void create_tower(int coord_x, int coord_y, TYPE_TOWER type, Tower new_tower) {

    switch (type)
    {
        case ROCKET:
        {
            new_tower = Tower(coord_x,coord_y,type,8.0,4.0,2.0,5);
            break;
        }
        case LASER:
        {
            new_tower = Tower(coord_x,coord_y,type,5.0,2.0,8.0,5);
            break;
        }
        
        case MACHINEGUN:
        {
            new_tower = Tower(coord_x,coord_y,type,2.0,2.0,4.0,3);
            break;
        }
        case HYBRID:
        {
            new_tower = Tower(coord_x,coord_y,type,3.0,8.0,6.0,6);
            break;
        }
            
        default:
            break;
    }
    
    printf("swtich");


}