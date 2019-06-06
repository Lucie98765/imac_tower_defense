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
void Tower::shot(Monster* monster, TYPE_TOWER type, int tower_react) {
    int scope_x_inf = this->get_x() - (int)this->get_scope();
    int scope_x_sup = this->get_x() + (int)this->get_scope();
    int scope_y_inf = this->get_y() - (int)this->get_scope();
    int scope_y_sup = this->get_y() + (int)this->get_scope();
    if ( (monster->get_x() < scope_x_sup) && (monster->get_x() > scope_x_inf)
        && (monster->get_y() < scope_y_sup) && (monster->get_y() > scope_y_inf) )
    {
        switch (this->get_type_tower())
        {
            case ROCKET:
            {   
                if (tower_react % (int)this->get_cadence() == 0) { 
                    float degat =monster->get_resistance_tr() * this->get_power();
                    float result_degats = monster->get_Pv() - degat;
                    if (result_degats>0) {
                        monster->set_Pv(result_degats);
                    }
                    else {
                        monster->set_Pv(0.0);
                        }
                    break;
                    }
            }
            
            case LASER:
            {   
                if (tower_react % (int)this->get_cadence() == 0) {
                    float degat =monster->get_resistance_tr() * this->get_power();
                    float result_degats = monster->get_Pv() - degat;
                    if (result_degats>0) {
                        monster->set_Pv(result_degats);
                    }
                    else {
                        monster->set_Pv(0.0);
                        }
                    break;
                }
            }
            
            case MACHINEGUN:
            {   
                if (tower_react % (int)this->get_cadence() == 0) {
                    float degat =monster->get_resistance_tr() * this->get_power();
                    //cout << degat;
                    float result_degats = monster->get_Pv() - degat;
                    //cout << "result dégats =" << result_degats << "\n";
                    if (result_degats>0) {
                        monster->set_Pv(result_degats);
                        //cout <<"le monstre a : " << monster->get_Pv() << "pv \n";
                    }
                    else {
                        monster->set_Pv(0.0);
                        }
                    break;
                }
            }

            case HYBRID:
            {   
                if (tower_react % (int)this->get_cadence() == 0) {
                    float degat =monster->get_resistance_tr() * this->get_power();
                    //cout << degat;
                    float result_degats = monster->get_Pv() - degat;
                    //cout << "result dégats =" << result_degats << "\n";
                    if (result_degats>0) {
                        monster->set_Pv(result_degats);
                        //cout <<"le monstre a : " << monster->get_Pv() << "pv \n";
                    }
                    else {
                        monster->set_Pv(0.0);
                        }
                    break;
                }
            }
        }
    }
}
            


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

void shot_kill_monster(vector<Monster>* wave, vector<Tower>* towers, int tower_react) {
    int monster_index = 0;
    int distance=0;
    for (int i=0; i < towers->size(); i++)  {

        int x_monster = (*wave)[0].get_x();
        int y_monster = (*wave)[0].get_y();

        int x_tower= (*towers)[i].get_x();
        int y_tower= (*towers)[i].get_y();

        int dx = abs(x_monster - x_tower);
        int dy = abs(y_monster - y_tower);

        int min_distance = sqrt( (dx^2) + (dy^2) );

        for (int j=1; j < wave->size() ; j++) {

            x_monster = (*wave)[j].get_x();
            y_monster = (*wave)[j].get_y();

            dx = abs(x_monster - x_tower);
            dy = abs(y_monster - y_tower);

            distance= sqrt( (dx^2) + (dy^2) );

            if (distance < min_distance) {
                min_distance = distance;
                monster_index = j;
            }
        }
        (*towers)[i].shot( &(*wave)[monster_index] , (*towers)[i].get_type_tower(), tower_react);
    }

}