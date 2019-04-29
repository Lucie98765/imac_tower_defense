#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <tower.h>

int main() {
    Tower newtower(8,2,3,4,5,6);
    cprintf(newtower.get_puissance());
    return 0;
}