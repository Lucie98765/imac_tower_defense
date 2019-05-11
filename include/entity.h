#pragma once

class Entity {
    private:
        int coord_x;
        int coord_y;
    
    public:
        Entity(float x,float y);

        int get_x();
        int get_y();

        void set_X(int x);
        void set_Y(int y);

        void update();
};
