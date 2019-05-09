#include "../include/verifCarte.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <ctype.h>
#define TAILLE_MAX 1000


int verifier_itd(char const *nomFichier){
    FILE* carteItd = NULL;
    char chaine[TAILLE_MAX] = "";
    int numLigne = 0;

    carteItd = fopen(nomFichier,"r+");

    printf("%s\n", nomFichier);

    if (carteItd != NULL) //Si le fichier a pu être ouvert
    {        
        while (fgets(chaine, TAILLE_MAX, carteItd) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur --> tant qu'on n'est pas à la fin (NULL)
        {
            numLigne++;
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire

            // Verification de la première ligne du fichier
            if(numLigne == 1){
                char debut_ligne[6];
                strncpy(debut_ligne, chaine, 5); //On récupère la première partie de la première ligne
                if ((strcmp(debut_ligne, "@ITD "))!=0){ //On vérifie que les premiers caractères décrivent bien un fichier itd
                    printf("Erreur ligne 1 : la première ligne de votre fichier .itd n'est pas valide, le fichier ne semble pas être au format @ITD\n");
                    return 0;
                }
                if (isdigit(chaine[5]) == false){ //On vérifie le numéro de version du fichier.
                    printf("Erreur ligne 1 : mauvais numero de version.\n");
                    return 0;
                }
                printf("Ligne 1 valide.\n");
            }

            
            // Verification de la deuxieme ligne du fichier
            if(numLigne == 2){
                if (chaine[0]!='#'){ //On vérifie que c'est bien une ligne de commentaire
                    printf("La deuxième ligne de votre fichier .itd n'est pas valide, elle doit être en commentaire.\n");
                    return 0;
                } 
                printf("Ligne 2 valide.\n");
            }
            

            // Verification des lignes 3 à 9
            if(numLigne>=3 && numLigne<=9){ //Il faut maintenant faire les vérifications pour chaque item
                /* Ligne carte */
                if ((strncmp(chaine, "ca", 2))==0){ //S'il s'agit de la ligne décrivant le nom de la carte
                        char const *nom_carte = NULL;
                        nom_carte = strchr(chaine, ' ');
                        if (nom_carte  != NULL) //Si le nom de la carte a bien été renseigné
                        {
                            int taille_nom = (int)strlen(nom_carte);
                            for (int i = 1; i<taille_nom; i++){
                                if(nom_carte[i] == ' '){ //On vérifie qu'il n'y a pas d'espace dans le nom de la carte
                                    printf("Le nom de la carte ne doit pas contenir d'espace.\n");
                                    return 0;
                                }
                            }
                        char const *extension = NULL;
                        extension = strchr(chaine, '.');
                        if((strncmp(extension, ".ppm", 4))!=0){
                            printf("L'extension de votre carte n'est pas bonne.\n");
                            return 0;
                        }

                        } else { //Si le nom de la carte n'a pas été renseigné
                            printf("Vous n'avez entré aucun nom de carte.\n");
                            return 0;
                        }
                        printf("Ligne carte valide.\n");
                }
                /* Ligne chemin */
                if ((strncmp(chaine, "ch", 2))==0){
                    printf("chemin ok\n");
                }
                if ((strncmp(chaine, "no", 2))==0){
                    printf("noeud ok\n");
                }
                if ((strncmp(chaine, "co", 2))==0){
                    printf("construct ok\n");
                }
                if ((strncmp(chaine, "in", 2))==0){
                    printf("in ok\n");
                }
                if ((strncmp(chaine, "ou", 2))==0){
                    printf("out ok\n");
                }
                if ((strncmp(chaine, "en", 2))==0){
                    printf("energie ok\n");
                }
            }

            
        }

        fclose(carteItd);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s\n", nomFichier);
    }
    return 1;
}