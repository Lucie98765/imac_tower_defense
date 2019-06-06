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
    MONSTER2,
	BOSS
};

class Monster : public Entity
{
	private: 
		TYPE_MONSTER type;
        int level;
		float pv;
		float speed;
		int gain;
		float resistance_tr;
		float resistance_tg;
		float resistance_ty;
		float resistance_tb;
		int walk_counter=1;

/* La résistance des monstre est le pourcentage de réception des attaques des tours en question.
Si r = 100 : reçoit 100% de l'attaque : pas résistant du tout */

	public:

//constructor
	Monster();

//overload
    Monster(int monster_x, int monster_y, TYPE_MONSTER type, int level,
		float pv,
		float speed,
		int gain,
		float resistance_tr,
		float resistance_tg,
		float resistance_ty,
		float resistance_tb)
		;

//destructor
	~Monster();

//getters
	TYPE_MONSTER get_type();
    int get_level();
	float get_Pv();
    float get_speed();
	int get_gain();
	float get_resistance_tr();
	float get_resistance_tg();
	float get_resistance_ty();
	float get_resistance_tb();
	int get_walk_counter();


//setters
	void set_type(TYPE_MONSTER nwtype);
    void set_level(int nwlevel);
	void set_Pv(float nwPv);
    void set_speed(float nwpeed);
	void set_gain(int gain);
    void set_resistance_tr(float nwResistance);
	void set_resistance_tg(float nwResistance);
	void set_resistance_ty(float nwResistance);
	void set_resistance_tb(float nwResistance);
	void set_walk_counter(int i);


//other methods

		//we considere that the path bewteen two nodes is vertical or horizontal
		void move(int x1, int y1, int x2, int y2);
		void move2(int monster_x, int monster_y, int x2, int y2);

		//represent the PV barre
		void gauge_Pv();

};

//create one wave of monster
void wave_monster(vector<Monster>* wave,int init_x, int init_y, int level);

//manage the wave movement
int wave_generate(vector<Monster>* wave, vector<Node> Go_node, int monster1_react, int monster2_react);

//delete monster if their Pv=0
void kill_monster(vector<Monster>* monster);
#endif