#include "../include/money.h"

//initialization number of piece
//constructor
    Piece::Piece() : money(5) {};

//destrucot
    Piece::~Piece() {};

//getter
int Piece::get_money() {
    return money;
}

//setter
void Piece::set_money(int cash) {
    money = cash;
}

//destructor

void buy_tower(Tower *tower, Piece *pieces)
{
    if (pieces->get_money()<tower->get_price()) {
        cout << "you don't have enouch money";
        //Lucie Reine de la SDL fait moi un petit visuel :p
    }
    else {
        pieces->set_money( pieces->get_money() - tower->get_price());
    }
}

void pay_install(Installation *installation, Piece *pieces)
{
    if (pieces->get_money()<installation->get_price()) {
        cout << "you don't have enouch money";
        //Lucie Reine de la SDL fait moi un petit visuel :p
    }
    else {
        pieces->set_money( pieces->get_money() - installation->get_price());
    }
}

//bluid_tower Lucie

void earn_money(Monster *monster, Piece *pieces){
    switch (monster->get_type())
    {
        case MONSTER1:
        {
            pieces->set_money(pieces->get_money() + monster->get_gain());
            break;
        }

        case MONSTER2:
        {
            pieces->set_money(pieces->get_money() + monster->get_gain());
            break;
        }

        case BOSS:
        {
            pieces->set_money(pieces->get_money() + monster->get_gain());
            break;
        }
    }
}