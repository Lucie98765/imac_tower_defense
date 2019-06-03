#pragma once
#include "headers.h"
#include "timer.h"

//Class (parent)
class Entity {
    private:
        int coord_x;
        int coord_y;
    
    public:
    //constructor
        Entity();

        Entity(float x,float y);

    //destructor
        ~Entity();
    
    //getters
        int get_x();
        int get_y();

    //setters
        void set_x(int x);
        void set_y(int y);

    //lol
        void update();
};
