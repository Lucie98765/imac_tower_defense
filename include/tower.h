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
    float puissance;
    float portee;
    float cadence;
    int prix;
    int rayon;
    GLuint texture;
    //Monster cible;

  public:
    //construteur
    Tower();

    //surcharge
    Tower(int tower_x, int tower_y);

    //destructeur
    ~Tower();

    //surcharge constructeur
    Tower(int tower_x, int tower_y, TYPE_TOWER type, float puissance, float portee, float cadence, int prix);

    //getter
    TYPE_TOWER get_type_tower();
    float get_puissance();
    float get_cadence();
    float get_portee();
    int get_prix();
    int get_rayon();

    //setter
    void set_puissance(float value);
    void set_cadence(float value);
    void set_portee(float value);
    void set_prix(int value);
    void set_position(int value_x, int value_y);

    //other method
    void tirer(int puissance, Monster monster, TYPE_TOWER type);

    //PARTIE SDL VISUELLE à voir...

    
};

void create_tower(int coord_x, int coord_y, Tower *new_tower);

#endif
