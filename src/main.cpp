#include "../include/checkMap.hpp"
#include "../include/tower.h"
#include "../include/batiment.h"
#include "../include/headers.h"
#include "../include/batiment.h"

int main(int argc, char const *argv[])
{
	char const *itd_map_name = "data/carte1.itd";
	char const *ppm_map_name = "images/carte1.ppm";


	int itd_ok = check_itd(itd_map_name);
	if (itd_ok == 0) return 0;


	//verifier_ppm

	Tower newtower(4,5,ROCKET,8.0,2.0,3.0,6);
    printf("%f",newtower.get_puissance());




	return 1;
}
