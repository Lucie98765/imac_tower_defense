#include "../include/batiment.h"

//constructor

Installation::Installation() : Entity() {};

//overload1
Installation::Installation(int installation_x, int installation_y) :
    Entity(installation_x, installation_y)
{};

//overload2
Installation::Installation(int installation_x, int installation_y, TYPE_INSTALL type, int price) : 
    Entity(installation_x, installation_y),
    type(type),
    price(price),
    size(20){
};

//destructor
Installation::~Installation() {}


//getters (no need setters)
TYPE_INSTALL Installation::get_type() {
    return type;
}

int Installation::get_size()
{
    return size;
}

int Installation::get_price()
{
    return price;
}

int Installation::get_scope()
{
    return scope;
}

// int Installation::get_position_x()
// {
//     return installation_x;
// }

// int Installation::get_position_y()
// {
//     return installation_y;
// }


//methods
void Installation::amelioration(TYPE_INSTALL type, Tower *tower)
{
    switch (type)
    {
    case RADAR:
    {
        //25% increasement of the scope of tower 
        float new_value = 1.25 * tower->get_scope();
        tower->set_scope(new_value);
        break;
    }

    case FACTORY_ARMAMENT:
    {
        //25% increasement of the power of tower 
        float new_value = 1.25 * tower->get_power();
        tower->set_power(new_value);
        break;
    }

    case STOCK_MUNITIONS:
    {
        //25% increasement of the cadence of tower 
        float new_value = 1.25 * tower->get_cadence();
        tower->set_cadence(new_value);
        break;
    }

    default:
        break;
    }
}
void create_installation(int coord_x, int coord_y, TYPE_INSTALL type, Installation new_install) {

    switch (type)
    {
        case RADAR:
        {
            new_install = Installation(coord_x,coord_y,type,15);
            break;
        }
        case FACTORY_ARMAMENT:
        {
            new_install = Installation(coord_x,coord_y,type,20);
            break;
        }

        case STOCK_MUNITIONS:
        {
            new_install = Installation(coord_x,coord_y,type,18);
            break;
        }

        default:
            break;
    }
    
    printf("swtich install");
}

void apply_effect_to_tower(Installation * installation, Tower * tower) {
    {
    int scope_x_inf = installation->get_x() - (int)installation->get_scope();
    int scope_x_sup = installation->get_x() + (int)installation->get_scope();
    int scope_y_inf = installation->get_y() - (int)installation->get_scope();
    int scope_y_sup = installation->get_y() + (int)installation->get_scope();
    if ( (tower->get_x() < scope_x_sup) && (tower->get_x() > scope_x_inf)
        && (tower->get_y() < scope_y_sup) && (tower->get_y() > scope_y_inf) )
    {
        switch (installation->get_type())
        {
            case RADAR:
            {      
                installation->amelioration(installation->get_type(), tower);
                break;
            }
            
            case FACTORY_ARMAMENT:
            {   
                installation->amelioration(installation->get_type(), tower);
                break;
            }
            case STOCK_MUNITIONS:
            {   
                installation->amelioration(installation->get_type(), tower);
                break;
            }
            default:
            break;
            }
        }
    }
}