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
        return type;
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

//void Monster::seDeplacer(int move_x, int move_y) {
    //tant que le noeud n'est pas atteint, avancé soit en x sans en y
    //calculer la fonction affine en fonction des noeuds
    //jusqu'à atteindre le noeuf

    //Intelligence des monstres
    //calculer le chemin le plus court en distance et en temps
    //choisir en conséquence

    void Monster::move(int xAct, int yAct) {

    };
	
    void Monster::gauge_Pv() {
        //Partie DSL 

        //Howmany pixel represent
        int subdiv = get_Pv();
    };


void create_monster(int coord_x, int coord_y, TYPE_MONSTER type, Monster new_monster, int level) {
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
    
    printf("swtich Monster");
}