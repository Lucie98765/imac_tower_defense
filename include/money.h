#ifndef MONEY_H
#define MONEY_H

#include "headers.h"
#include "tower.h"
#include "monster.h"
#include "batiment.h"

class Piece{
    private:
        int money;
        //image pièce;
    
    public:
        //constructor
        Piece();

        //destctructor
        ~Piece();

        //getter
        int get_money();
    
        //setter
        void set_money(int cash);

};

void pay_entity(Entity element, Piece pieces);
void earn_money(Monster *monster, Piece *pieces);

#endif