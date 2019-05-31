#include "../include/tower.h"
#include "../include/monster.h"



//constructor

Tower::Tower() : Entity(){};

Tower::Tower(int tower_x, int tower_y) : Entity(tower_x, tower_y) {
}

//overload constructor
Tower::Tower(int tower_x, int tower_y, TYPE_TOWER type, float power, float scope, float cadence, int price): 
    Entity(tower_x, tower_y),
    type(type),
    power(power),
    scope(scope),
    cadence(cadence),
    price(price),
    rayon(20)
    {

    }

    
//getters

TYPE_TOWER Tower::get_type_tower() {
    return type;
}

float Tower::get_power() {
    return power;
}

float Tower::get_cadence() {
    return cadence;
}

float Tower::get_scope() {
    return scope;
}

int Tower::get_price() {
    return price;
}

int Tower::get_rayon() {
     return rayon;
}

//setters
void Tower::set_power(float value) {
    power = value;
}

void Tower::set_cadence(float value) {
    cadence = value;
}

void Tower::set_scope(float value) {
    scope = value;
}

void Tower::set_price(int value) {
    price = value;
}


//destructor
Tower::~Tower(){};

//methodes
void Tower::shot(int power, Monster monster, TYPE_TOWER type) {
    int scope_x_inf = Tower::get_x() - (int)Tower::get_scope();
    int scope_x_sup = Tower::get_x() + (int)Tower::get_scope();
    int scope_y_inf = Tower::get_y() - (int)Tower::get_scope();
    int scope_y_sup = Tower::get_y() + (int)Tower::get_scope();
    if ( (monster.get_x() < scope_x_sup) && (monster.get_x() > scope_x_inf)
        && (monster.get_y() < scope_y_sup) && (monster.get_y() > scope_y_inf) )
    {
        switch (Tower::get_type_tower())
        {
            case ROCKET:
            {      
                float result_degats = monster.get_Pv() - monster.get_resistance_tr() * Tower::get_power();
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
                float result_degats = monster.get_Pv() - monster.get_resistance_tg() * Tower::get_power();
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
                float result_degats = monster.get_Pv() - monster.get_resistance_ty() * Tower::get_power();
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
                float result_degats = monster.get_Pv() - monster.get_resistance_tb() * Tower::get_power();
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