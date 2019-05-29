#ifndef DEF_MONSTRE_H
#define DEF_MONSTRE_H

#include "headers.h"
#include "entity.h"
#include "node.h"
#include "timer.h"
//#include "map.h"

//To make difference between monsters
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
		float speed;
		float resistance_tr;
		float resistance_tg;
		float resistance_ty;
		float resistance_tb;

/* La résistance des monstre est le pourcentage de réception des attaques des tours en question.
Si r = 100 : reçoit 100% de l'attaque : pas résistant du tout */

	public:

//constructor
	Monster();

//overload
    Monster(int x, int y);

//destructor
	~Monster();

//getters
    int get_level();
	float get_Pv();
    float get_speed();
	float get_resistance_tr();
	float get_resistance_tg();
	float get_resistance_ty();
	float get_resistance_tb();


//setters
    void set_level(int nwlevel);
	void set_Pv(float nwPv);
    void set_speed(float nwpeed);
    void set_resistance_tr(float nwResistance);
	void set_resistance_tg(float nwResistance);
	void set_resistance_ty(float nwResistance);
	void set_resistance_tb(float nwResistance);


//autres
		void move(int xAct, int yAct);
		void jauge_Pv();

};

#endif