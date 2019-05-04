#include "../include/verifCarte.hpp"
#include <stdlib.h>
#include <stdio.h>


void ouvrirCarte(char const *nomFichier){
    FILE* carteItd = NULL;
    int caractereActuel = 0;

    carteItd = fopen(nomFichier,"r+");

    printf("%s\n", nomFichier);

    if (carteItd != NULL)
    {
        printf("fichier ouvert\n");
        
        // Boucle de lecture des caractères un à un
        do
        {
            caractereActuel = fgetc(carteItd); // On lit le caractère
            printf("%c", caractereActuel); // On l'affiche
        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
               
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier\n");
    }

}