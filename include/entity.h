#pragma once
#include "headers.h"
#include "timer.h"

class Entity {
    private:
        int coord_x;
        int coord_y;
    
    public:
    //constructeur
        Entity();

        Entity(float x,float y);

    //destructeur
        ~Entity();
    
    //getters
        int get_x();
        int get_y();

    //setters
        void set_X(int x);
        void set_Y(int y);

    //lol
        void update();
};
