#include "../include/monster.h"


//constructeur
    Monster::Monster(int x, int y): Entity(x,y){};

//getters
int Monster::get_level() {
    return level;
}

int Monster::get_Pv(){
	return pv;
}

float Monster::get_vitesse(){
    return vitesse;
}

float Monster::get_resistance_tr() {
    return resistance_tr;
}

float Monster::get_resistance_tv() {
    return resistance_tv;
};

float Monster::get_resistance_tb() {
    return resistance_tb;
}

float Monster::get_resistance_tj() {
    return resistance_tj;
}


//setters
void Monster::set_level(int nvlevel) {
    level = nvlevel;
}

void Monster::set_Pv(int nvxPv) {
    pv = nvxPv;
}

void Monster::set_vitesse(float nvlvitesse) {
    vitesse = nvlvitesse;
}

void Monster::set_resistance_tr(float nvlResistance) {
    resistance_tr = nvlResistance;
}

void Monster::set_resistance_tv(float nvlResistance) {
    resistance_tv = nvlResistance;
}

void Monster::set_resistance_tb(float nvlResistance) {
    resistance_tb = nvlResistance;
}

void Monster::set_resistance_tj(float nvlResistance) {
    resistance_tj = nvlResistance;
}

//void Monster::seDeplacer(int move_x, int move_y) {
    //tant que le noeud n'est pas atteint, avancé soit en x sans en y
    //calculer la fonction affine en fonction des noeuds
    //jusqu'à atteindre le noeuf

    //Intelligence des monstres
    //calculer le chemin le plus court en distance et en temps
    //choisir en conséquence

//};