#ifndef DEF_MONSTRE_H
#define DEF_MONSTRE_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstdlib>
#include "entity.h"
#include "tower.h"
//#include "map.h"
#include <new>

enum TYPE_MONSTER {
    MONSTER1,
    MONSTER2
};

class Monster : public Entity
{
	private: 
        int level;
		int pv;
		int vitesse;
		int resistance_tr;
		int resistance_tv;
		int resistance_tb;
		int resistance_tj;

/* La résistance des monstre est le pourcentage de réception des attaques des tours en question.
Si r = 100 : reçoit 100% de l'attaque : pas résistant du tout */


/* manque le constructeur et le destructeur */

	public:

//constructeur
    Monster(int x, int y);


//getters
    int get_level();
	int get_Pv();
    float get_vitesse();
	float get_resistance_tr();
	float get_resistance_tv();
	float get_resistance_tb();
	float get_resistance_tj();

//setters
    void set_level(int nvlevel);
	void set_Pv(int nvxPv);
    void set_vitesse(float nvlvistesse);
    void set_resistance_tr(float nvlResistance);
	void set_resistance_tv(float nvlResistance);
	void set_resistance_tb(float nvlResistance);
	void set_resistance_tj(float nvlResistance);

//autres
		//void seDeplacer(int xAct, int yAct);

//destructeur
};

#endif