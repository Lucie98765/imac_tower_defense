#include "../include/verifCarte.hpp"
#include <stdlib.h>
#include <stdio.h>
#define TAILLE_MAX 1000


void ouvrirCarte(char const *nomFichier){
    FILE* carteItd = NULL;
    char chaine[TAILLE_MAX] = "";

    carteItd = fopen(nomFichier,"r+");

    printf("%s\n", nomFichier);

    if (carteItd != NULL)
    {        
        while (fgets(chaine, TAILLE_MAX, carteItd) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
        }

        fclose(carteItd);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s\n", nomFichier);
    }

}