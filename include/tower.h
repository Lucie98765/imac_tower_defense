#ifndef TOWER_H
#define TOWER_H

#include "headers.h"
#include "entity.h"
#include "monster.h"
#include "timer.h"

// void *operator new(size_t size) { return malloc(size); }
// void operator delete(void *ptr)
// {
//     if (ptr)
//         free(ptr);
// }

enum TYPE_TOWER
{
    ROCKET,
    LASER,
    MACHINEGUN,
    HYBRID
};

class Tower : public Entity
{
  private:
    TYPE_TOWER type;
    float power;
    float scope;
    float cadence;
    int price;
    int rayon;
    GLuint texture;
    //Monster cible;

  public:
    //constructor
    Tower();

    //overload
    Tower(int tower_x, int tower_y);

    //destructor
    ~Tower();

    //overload constructor
    Tower(int tower_x, int tower_y, TYPE_TOWER type, float power, float scope, float cadence, int price);

    //getter
    TYPE_TOWER get_type_tower();
    float get_power();
    float get_cadence();
    float get_scope();
    int get_price();
    int get_rayon();

    //setter
    void set_power(float value);
    void set_cadence(float value);
    void set_scope(float value);
    void set_price(int value);
    void set_position(int value_x, int value_y);

    //other method
    void tirer(int power, Monster monster, TYPE_TOWER type);

    //PARTIE SDL VISUELLE à voir...

    
};

void create_tower(int coord_x, int coord_y, Tower new_tower);

#endif
