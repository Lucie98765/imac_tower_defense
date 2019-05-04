#include "../include/verifCarte.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#define TAILLE_MAX 1000


void ouvrirCarte(char const *nomFichier){
    FILE* carteItd = NULL;
    char chaine[TAILLE_MAX] = "";
    int numLigne = 1;
    bool valide = true;

    carteItd = fopen(nomFichier,"r+");

    printf("%s\n", nomFichier);

    if (carteItd != NULL) //Si le fichier a pu être ouvert
    {        
        while (fgets(chaine, TAILLE_MAX, carteItd) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur --> tant qu'on n'est pas à la fin (NULL)
        {
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire

            if(numLigne == 1){
                if ((strcmp(chaine, "@ITD 1\n"))!=0){
                    printf("La première ligne de votre fichier .itd n'est pas valide.\n");
                    valide = false;
                } 
            }
            printf("ligne 1 fait\n");

            if(numLigne == 2){
                if (chaine[0]!='#'){
                    printf("La deuxième ligne de votre fichier .itd n'est pas valide.\n");
                    valide = false;
                } 
            }
            printf("ligne 2 fait\n");

            if(numLigne == 3){
                if (chaine[0]!='#'){
                    printf("La troisieme ligne de votre fichier .itd n'est pas valide.\n");
                    valide = false;
                } 
            }
            printf("ligne 3 fait\n");


            numLigne++;
        }

        fclose(carteItd);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s\n", nomFichier);
    }

}
