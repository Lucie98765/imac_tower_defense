#include "../include/monstre.hpp"
#include "../include/verifCarte.hpp"
#include "../include/tower.h"
#include "../include/batiment.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <cstdio>

int main(int argc, char const *argv[])
{
	char const *nom_carte_itd = "data/carte1.itd";
	char const *nom_carte_ppm = "images/carte1.ppm";


	int itd_ok = verifier_itd(nom_carte_itd);
	if (itd_ok == 0) return 0;


	verifier_ppm

	Tower newtower(4,5,ROCKET,8.0,2.0,3.0,6);
    printf("%f",newtower.get_puissance());






	return 1;
}
#include "../include/headers.h"
#include "../include/tower.h"
#include "../include/batiment.h"
