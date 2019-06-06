#include "../include/monster.h"


//constructor
    Monster::Monster() : Entity() {}

// Overload
    Monster::Monster(int monster_x, int monster_y, TYPE_MONSTER type, int level, float pv,
		float speed, int gain, float resistance_tr, float resistance_tg, float resistance_ty, float resistance_tb):
        Entity(monster_x,monster_y),
        type(type),
        level(level),
        pv(pv),
        speed(speed),
        gain(gain),
		resistance_tr(resistance_tr),
		resistance_tg(resistance_tg),
		resistance_ty(resistance_ty),
		resistance_tb(resistance_tb)
        {}

//destructor
	Monster::~Monster() {}

//getters
    TYPE_MONSTER Monster::get_type() {
        return this->type;
    }

    int Monster::get_level() {
        return level;
    }

    float Monster::get_Pv(){
        return pv;
    }

    float Monster::get_speed(){
        return speed;
    }

    int Monster::get_gain() {
        return gain;
    }

    float Monster::get_resistance_tr() {
        return resistance_tr;
    }

    float Monster::get_resistance_tg() {
        return resistance_tg;
    };

    float Monster::get_resistance_ty() {
        return resistance_ty;
    }

    float Monster::get_resistance_tb() {
        return resistance_tb;
    }

    int Monster::get_walk_counter() {
        return walk_counter;
    }


//setters
    void Monster::set_type(TYPE_MONSTER nwtype) {
        type = nwtype;
    }

    void Monster::set_level(int nwlevel) {
        level = nwlevel;
    }

    void Monster::set_Pv(float nwPv) {
        pv = nwPv;
    }

    void Monster::set_speed(float nwspeed) {
        speed = nwspeed;
    }

    void Monster::set_gain(int nwgain) {
        gain = nwgain;
    }

    void Monster::set_resistance_tr(float nwResistance) {
        resistance_tr = nwResistance;
    }

    void Monster::set_resistance_tg(float nwResistance) {
        resistance_tg = nwResistance;
    }

    void Monster::set_resistance_ty(float nwResistance) {
        resistance_ty = nwResistance;
    }

    void Monster::set_resistance_tb(float nwResistance) {
        resistance_tb = nwResistance;
    }

    void Monster::set_walk_counter(int i) {
        walk_counter=i;
    }

   void Monster::move(int x1, int y1, int x2, int y2) {
        //cout << "houston we have a pb\n";
        if ( abs(x1 - x2) <= 2 ) {
            //cout << abs(x1 - x2) << "\n";
            x1=x2;
            if (y1<y2)
                while ( y1 <= y2 ) {
                    sleep(this->get_speed());
                    y1=y1+1;
                    set_y(y1);
                    //cout << "( " << this->get_x() << "," <<  this->get_y() << "\n";
                }
            else {
                while ( y1>=y2 ) {
                    sleep(this->get_speed());
                    y1=y1-1;
                    set_y(y1);
                    //cout << "( " << this->get_x() << "," <<  this->get_y() << " )\n";
                }
            }
        }
        if( abs(y1-y2) <= 2) {
            //cout << abs(y1 - y2) << "\n";
            y1=y2;
            if (x1<x2)
                while ( x1 <= x2 ) {
                    x1=x1+1;
                    sleep(this->get_speed());
                    set_x(x1);
                    //cout << "( " << this->get_x() << "," <<  this->get_y() << " )\n";
                }
            else {
                while ( x1 >= x2 ) {
                    sleep(this->get_speed());
                    x1=x1-1;
                    set_x(x1);
                    //cout << "( " << this->get_x() << "," <<  this->get_y() << " )\n";
                }
            }
        }
    }


//move2
    void Monster::move2(int monster_x, int monster_y, int x2, int y2) {
        int dx= abs(monster_x-x2);
        int dy= abs(monster_y-y2);
        if ( dx <= 2) {
            this->set_x(x2);
            if (monster_y<y2) {
                    monster_y++;
                    this->set_y(monster_y);
                }
            else {
                    monster_y--;
                    this->set_y(monster_y);
                }
        }
        if ( dy <= 2) {
            this->set_y(y2);
            if (monster_x<x2) {
                monster_x++;
                set_x(monster_x);
                }
            else {
                monster_x--;
                set_x(monster_x);
            }
        }
    }


Monster create_monster(int coord_x, int coord_y, TYPE_MONSTER type, Monster new_monster, int level) {
    //initiazition monster according to chosen parameters 
    switch (type)
    {
        case MONSTER1:
        {
            new_monster = Monster(coord_x,coord_y,type,level,15+level,0.7-(level/100),5,0.75,1,1,1.25);
            break;
        }
        case MONSTER2:
        {
            new_monster = Monster(coord_x,coord_y,type,level,20+level,1.2-(level/100),5,1.25,0.8,1,0.8);
            break;
        }

        case BOSS:
        {
            new_monster = Monster(coord_x,coord_y,type,51,1500,1.5,1000,1,1.5,0.7,0.8);
            break;
        }

        default:
            break;
    }
    return new_monster;
    printf("swtich Monster");
}

void wave_monster(vector<Monster>* wave,int init_x, int init_y, int level) {
    int percent = level/100;
    for (int i=0; i<10; i++){
            Monster monster1(init_x-30*i,init_y,MONSTER1,level,30+level*10,2,5,0.75-percent,1-percent,1-percent,1.25-percent);
            Monster monster2(init_x-30*i,init_y,MONSTER2,level,40+level*10,2,5,1.25-percent,0.8-percent,1-percent,0.8-percent);
        if (i<5) {
            wave->push_back(monster1);
        }
        else {
            wave->push_back(monster2);
        }
    }
}

int wave_generate(vector<Monster>* wave, vector<Node> Go_node, int monster1_react, int monster2_react) {
            for (int i=0; i<wave->size();i++) {
            TYPE_MONSTER type = (*wave)[i].get_type();
            if (type == MONSTER1) {
                int counter_node=(*wave)[i].get_walk_counter();
                if ( monster1_react % int((*wave)[i].get_speed()) == 0) {
                    if ((*wave)[i].get_x() == Go_node[counter_node].get_pos_x() &&
                        (*wave)[i].get_y() == Go_node[counter_node].get_pos_y()) {
                            counter_node++;
                            (*wave)[i].set_walk_counter(counter_node);
                            if (counter_node == Go_node.size()) {
                                cout << "GAME OVER";
                                return 0;
                            }
                        }
                        (*wave)[i].move2((*wave)[i].get_x(), (*wave)[i].get_y(), Go_node[counter_node].get_pos_x(), Go_node[counter_node].get_pos_y());
                }
            }
            if (type == MONSTER2) {
                int counter_node=(*wave)[i].get_walk_counter();
                if ( monster2_react % int((*wave)[i].get_speed()) == 0) {
                    if ((*wave)[i].get_x() == Go_node[counter_node].get_pos_x() &&
                        (*wave)[i].get_y() == Go_node[counter_node].get_pos_y()) {
                            counter_node++;
                            (*wave)[i].set_walk_counter(counter_node);
                            if (counter_node == Go_node.size()) {
                                cout << "GAME OVER";
                                return 0;
                            }
                        }
                        (*wave)[i].move2((*wave)[i].get_x(), (*wave)[i].get_y(), Go_node[counter_node].get_pos_x(), Go_node[counter_node].get_pos_y());
                }
            }
        }
    return 1;
}

void kill_monster(vector<Monster>* monster){
    for (int i=0; i < monster->size() ; i++) {
        if ( (*monster)[i].get_Pv() == 0) {
            monster->erase(monster->begin() + i);
            i=0;
        }
    }
}