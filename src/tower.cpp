#include "../include/tower.h"
#include "../include/monster.h"



//constructeur

Tower::Tower() : Entity(){};

Tower::Tower(int tower_x, int tower_y) : Entity(tower_x, tower_y) {
}

//surcharge constructeur
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

    
//getters

TYPE_TOWER Tower::get_type_tower() {
    return type;
}

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


//destructeur
Tower::~Tower(){};

//methodes
void Tower::tirer(int puissance, Monster monster, TYPE_TOWER type) {
    int portee_x_inf = Tower::get_x() - (int)Tower::get_portee();
    int portee_x_sup = Tower::get_x() + (int)Tower::get_portee();
    int portee_y_inf = Tower::get_y() - (int)Tower::get_portee();
    int portee_y_sup = Tower::get_y() + (int)Tower::get_portee();
    if ( (monster.get_x() < portee_x_sup) && (monster.get_x() > portee_x_inf)
        && (monster.get_y() < portee_y_sup) && (monster.get_y() > portee_y_sup) )
    {
        switch (type)
        {
            case ROCKET:
            {      
                float result_degats = monster.get_Pv() - monster.get_resistance_tr() * Tower::get_puissance();
                if (result_degats>0) {
                    monster.set_Pv(result_degats);
                }
                else {
                    monster.set_Pv(0.0);
                    }
                break;
            }
            
            case LASER:
            {   
                float result_degats = monster.get_Pv() - monster.get_resistance_tv() * Tower::get_puissance();
                if (result_degats>0) {
                    monster.set_Pv(result_degats);
                }
                else {
                    monster.set_Pv(0.0);
                    }
                break;
            }
            
            case MACHINEGUN:
            {   
                float result_degats = monster.get_Pv() - monster.get_resistance_tj() * Tower::get_puissance();
                if (result_degats>0) {
                    monster.set_Pv(result_degats);
                }
                else {
                    monster.set_Pv(0.0);
                    }
                break;
            }

            case HYBRID:
            {   
                float result_degats = monster.get_Pv() - monster.get_resistance_tb() * Tower::get_puissance();
                if (result_degats>0) {
                    monster.set_Pv(result_degats);
                }
                else {
                    monster.set_Pv(0.0);
                    }
                break;
            }
        }
    }
};
            


void create_tower(int coord_x, int coord_y, TYPE_TOWER type, Tower new_tower) {

    switch (type)
    {
        case ROCKET:
        {
            new_tower = Tower(coord_x,coord_y,type,8.0,2.0,2.0,5);
            break;
        }
        case LASER:
        {
            new_tower = Tower(coord_x,coord_y,type,5.0,1.0,8.0,5);
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