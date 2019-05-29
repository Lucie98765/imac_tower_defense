#include "../include/monster.h"


//constructor
    Monster::Monster() : Entity() {
    };

// Overload
    Monster::Monster(int x, int y): Entity(x,y){};

//destructor
	Monster::~Monster() {};

//getters
    int Monster::get_level() {
        return level;
    }

    float Monster::get_Pv(){
        return pv;
    }

    float Monster::get_speed(){
        return speed;
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
    void Monster::set_level(int nwlevel) {
        level = nwlevel;
    }

    void Monster::set_Pv(float nwPv) {
        pv = nwPv;
    }

    void Monster::set_speed(float nwspeed) {
        speed = nwspeed;
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
	
    void Monster::jauge_Pv() {
        int subdiv = get_Pv();
    };
//};