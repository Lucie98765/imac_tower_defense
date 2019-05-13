#include "../include/headers.h"
#include "../include/tower.h"
#include "../include/batiment.h"

int main() {
    Tower newtower(4,5,ROCKET,8.0,2.0,3.0,6);
    printf("%f",newtower.get_puissance());
    return 0;
}