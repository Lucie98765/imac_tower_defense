#ifndef DEF_MONSTRE_H
#define DEF_MONSTRE_H

#include "headers.h"
#include "entity.h"
#include "timer.h"
//#include "map.h"

enum TYPE_MONSTER {
    MONSTER1,
    MONSTER2
};

class Monster : public Entity
{
	private: 
		TYPE_MONSTER type;
        int level;
		float pv;
		float vitesse;
		float resistance_tr;
		float resistance_tv;
		float resistance_tb;
		float resistance_tj;

/* La résistance des monstre est le pourcentage de réception des attaques des tours en question.
Si r = 100 : reçoit 100% de l'attaque : pas résistant du tout */


/* manque le constructeur et le destructeur */

	public:

//constructeur
	Monster();

//surcharge
    Monster(int x, int y);

//destructeur
	~Monster();

//getters
    int get_level();
	float get_Pv();
    float get_vitesse();
	float get_resistance_tr();
	float get_resistance_tv();
	float get_resistance_tb();
	float get_resistance_tj();


//setters
    void set_level(int nvlevel);
	void set_Pv(float nvxPv);
    void set_vitesse(float nvlvistesse);
    void set_resistance_tr(float nvlResistance);
	void set_resistance_tv(float nvlResistance);
	void set_resistance_tb(float nvlResistance);
	void set_resistance_tj(float nvlResistance);


//autres
		void seDeplacer(int xAct, int yAct);
		void jauge_Pv();

};

#endif