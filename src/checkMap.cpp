#include "../include/checkMap.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <ctype.h>
#define MAX_SIZE 1000
#define SIZE_COLOR_TAB 12

char path_color[SIZE_COLOR_TAB] = "";
char node_color[SIZE_COLOR_TAB] = "";
char construct_color[SIZE_COLOR_TAB] = "";
char in_color[SIZE_COLOR_TAB] = "";
char out_color[SIZE_COLOR_TAB] = "";


int check_itd(char const *nameFile){
    FILE* itdMap = NULL;
    char sentence[MAX_SIZE] = "";
    int numLine = 0;
    int nodeNumber = 0;
    int temp = 0;
    int nodeIndex = 0;
    bool entrance = false, exit = false;

    itdMap = fopen(nameFile,"r+");

    printf("%s\n", nameFile);

    if (itdMap != NULL) //If the file has been openned
    {        
        while (fgets(sentence, MAX_SIZE, itdMap) != NULL) //We read the file until we have an error --> until the file ends (NULL)
        {
            numLine++;
            printf("%s", sentence); //We display the sentence we just read

            //Check of the first Line of the file
            if(numLine == 1){
                if ((strncmp(sentence, "@ITD ", 5))!=0){ //We check that the 5 first characters describe an itd file
                    printf("Error Line 1 : the first Line of your .itd file is not valid, the file doesn't seem to be an ITD format.\n");
                    fclose(itdMap);
                    return 0;
                }
                if (isdigit(sentence[5]) == false){ //We check the version number of the file
                    printf("Error Line 1 : bad version number.\n");
                    fclose(itdMap);
                    return 0;
                }
                //printf("Line 1 valid.\n");
            }

            
            //Check of the second Line of the file
            if(numLine == 2){
                if (sentence[0]!='#'){ //Checking it is a commentary Line
                    printf("The second Line of your itd file is not valid, it has to be a commentary.\n");
                    fclose(itdMap);
                    return 0;
                } 
                //printf("Line 2 valid.\n");
            }
            

            //Checking Lines 3 to 8
            if(numLine>=3 && numLine<=8){ //We now have to check every item
                /* Map Line */
                if ((strncmp(sentence, "ca", 2))==0){ //If it is the Line describing the map name
                        char const *mapName = NULL;
                        mapName = strchr(sentence, ' ');
                        if (mapName  != NULL) //If the map name is correctly written
                        {
                            int taille_nom = (int)strlen(mapName);
                            for (int i = 1; i<taille_nom; i++){
                                if(mapName[i] == ' '){ //Checking if there is no space in the map name
                                    printf("The map name cannot contain a space character.\n");
                                    fclose(itdMap);
                                    return 0;
                                }
                            }
                        char const *extension = NULL;
                        extension = strrchr(sentence, '.');
                        if((strncmp(extension, ".ppm", 4))!=0){
                            printf("Your file extension has to be .ppm.\n");
                            fclose(itdMap);
                            return 0;
                        }

                        } else { //If the map name is not written 
                            printf("You have enter no name for your map.\n");
                            fclose(itdMap);
                            return 0;
                        }
                        //printf("Map Line valid.\n");
                } /*else if ((strncmp(sentence, "en", 2))==0){ //Checking the energy parameter
                    char word [20];
                    int number;
                    sscanf (sentence,"%s %d",word,&number);
                    if (number>=1000 || number<0){
                        printf("Mauvaise valeur pour l'énergie, elle doit être comprise entre 0 et 1000.");
                    }
                } */ else { // For all the other Lines
                    char word [20];
                    int number1, number2, number3;
                    sscanf (sentence,"%s %d %d %d",word,&number1, &number2, &number3);
                    if (number1<0 || number1>255 || number2<0 || number2>255 || number3<0 || number3>255){
                        printf("Bad value(s) the color of the  %s\n", word);
                        fclose(itdMap);
                        return 0;
                    }
                    //revoir ça 
                    if ((strncmp(sentence, "ch", 2))==0){
                        char* chainelol = sprintf(chainelol, "%d %d %d", number1, number2, number3);
                        strcat(path_color, chainelol);
                        printf("%s\n", path_color);
                    }
                //printf("%s Line valid.\n", word);
                }
            }
            
            //Checking the Line telling the number of nodes
            if(numLine == 9){
                char * end;
                nodeNumber = strtol (sentence,&end,10);
                if (0 == nodeNumber){
                    printf("Linee number 9 is not correct. It has to be a positiv number representing the number of nodes\n");
                    fclose(itdMap);
                    return 0;
                } else {
                    temp = nodeNumber;
                    //printf("Number of nodes Line valid.\n");
                }
            }

            //Checking the format of the nodes announced before
            if(numLine>=10){
                int n1, n2, n3, n4;
                sscanf (sentence,"%d %d %d %d",&n1,&n2, &n3, &n4);
                if (n1!=nodeIndex){
                    printf("The index of the node number %d is wrong, it should be equal to %d.\n",nodeIndex+1, nodeIndex );
                    fclose(itdMap);
                    return 0;
                }
                if (n2<=0 || n2>4){
                    printf("The nature of the node number %d is wrong. It can be equal to 1(entrance of the monsters), 2(exit of the monsters), 3(angle in the path) or 4(path intersection).\n", nodeIndex+1);
                    fclose(itdMap);
                    return 0;
                }
                if (n3<0 || n3>800){
                    printf("The value of the first coordinate of the node number %d is false, it has to be between 0 and 800.\n",nodeIndex-1 );
                    fclose(itdMap);
                    return 0;
                }
                if (n4<0 || n4>600){
                    printf("The value of the second coordinate of the node number %d is false, it has to be between 0 and 600.\n",nodeIndex-1 );
                    fclose(itdMap);
                    return 0;
                }

                if (n2==1) entrance =true;
                if (n2==2) exit =true;


                nodeIndex++;
                temp--;
            }
        }


        if (temp!=0){
            printf("The number of nodes actually described does not match the announced number of nodes.\n");
            fclose(itdMap);
            return 0;
        } else {
            //printf("Number of nodes described equal to announced number of node (Line 9).\n");
        }

        if (!entrance){
            printf("You have to include at least one monstre entrance.\n");
            fclose(itdMap);
            return 0;
        }
        if (!exit){
            printf("You have to include at least one monster exit.\n");
            fclose(itdMap);
            return 0;
        }


        printf("\nItd map is valid.\n");
        
        fclose(itdMap);

    } else {
        //Error openning the file
        printf("File %s cannot be openned.\n", nameFile);
    }
    return 1;
}


int check_ppm(char const *ppmName){


    return 1;
}

void enregistrer_noeud(int x, int y, int type){

}