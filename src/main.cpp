#include "../include/monstre.hpp"
#include "../include/verifCarte.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char const *nom_carte_itd = "data/carte1.itd";
	char const *nom_carte_ppm = "images/carte1.ppm";


	int itd_ok = verifier_itd(nom_carte_itd);
	if (itd_ok == 0) return 0;


	verifier_ppm

	return 1;
}