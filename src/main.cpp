#include "../include/monstre.hpp"
#include "../include/verifCarte.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char const *nomCarte = "data/carte1.itd";
	verifier_itd(nomCarte);

	return 0;
}