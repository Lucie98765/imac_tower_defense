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
    int nombre_noeuds = 0;
    int temp = 0;
    int indice_noeud = 0;

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
            

            // Verification des lignes 3 à 8
            if(numLigne>=3 && numLigne<=8){ //Il faut maintenant faire les vérifications pour chaque item
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
                        extension = strrchr(chaine, '.');
                        if((strncmp(extension, ".ppm", 4))!=0){
                            printf("L'extension de votre carte n'est pas bonne.\n");
                            return 0;
                        }

                        } else { //Si le nom de la carte n'a pas été renseigné
                            printf("Vous n'avez entré aucun nom de carte.\n");
                            return 0;
                        }
                        printf("Ligne carte valide.\n");
                } /*else if ((strncmp(chaine, "en", 2))==0){ //Vérification du paramètre énergie
                    char mot [20];
                    int nombre;
                    sscanf (chaine,"%s %d",mot,&nombre);
                    if (nombre>=1000 || nombre<0){
                        printf("Mauvaise valeur pour l'énergie, elle doit être comprise entre 0 et 1000.");
                    }
                } */ else { // pour toutes les autres lignes
                    char mot [20];
                    int nombre1, nombre2, nombre3;
                    sscanf (chaine,"%s %d %d %d",mot,&nombre1, &nombre2, &nombre3);
                    if (nombre1<0 || nombre1>255 || nombre2<0 || nombre2>255 || nombre3<0 || nombre3>255){
                        printf("Mauvaise(s) valeur(s) pour les couleurs de %s\n", mot);
                        return 0;
                    }
                printf("Ligne %s valide.\n", mot);
                }
            }
            
            //Vérification de la ligne annonçant le nombre de noeuds
            if(numLigne == 9){
                char * end;
                nombre_noeuds = strtol (chaine,&end,10);
                if (0 == nombre_noeuds){
                    printf("La ligne 9 est incorrecte. Elle doit être un chiffre ou un nombre strictement positif représentant le nombre de noeuds.\n");
                    return 0;
                } else {
                    temp = nombre_noeuds;
                    printf("Ligne nombre de noeuds valide.\n");
                }
            }

            //Vérification du format des noeuds annoncés au dessus
            if(numLigne>=10){
                int n1, n2, n3, n4;
                sscanf (chaine,"%d %d %d %d",&n1,&n2, &n3, &n4);
                if (n1!=indice_noeud){
                    printf("l'indice du %de noeud  est faux, il devrait valoir %d.\n",indice_noeud+1, indice_noeud );
                    return 0;
                }
                if (n2<=0 || n2>4){
                    printf("La nature du %de noeud est fausse. Elle peut valoir 1(zone d'entrée des monstres), 2(zone de sortie des monstres), 3(coude) ou 4(intersection de chemins).\n", indice_noeud+1);
                    return 0;
                }
                if (n3<0 || n3>800){
                    printf("La valeur de la première coordonnée du %de noeud est fausse, elle doit être comrpise entre 0 et 800.\n",indice_noeud-1 );
                    return 0;
                }


                indice_noeud++;
                temp--;
            }
        }

        if (temp!=0){
            printf("Le nombre de noeuds décrits ne correspond pas au nombre de noeuds prévus.\n");
            return 0;
        } else {
            printf("Nombre de noeuds en accord avec le chiffre entré en ligne 9.\n");
        }

        fclose(carteItd);
    }
    else {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s\n", nomFichier);
    }
    return 1;
}