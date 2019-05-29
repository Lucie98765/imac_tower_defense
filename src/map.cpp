#include "../include/map.h"
#define MAX_SIZE 1000
#define SIZE_COLOR_TAB 12

char path_color[SIZE_COLOR_TAB] = "";
char node_color[SIZE_COLOR_TAB] = "";
char construct_color[SIZE_COLOR_TAB] = "";
char in_color[SIZE_COLOR_TAB] = "";
char out_color[SIZE_COLOR_TAB] = "";


    Map::Map() {};
    
    unsigned int Map::get_width() {
      return width;
    };

    unsigned int Map::get_height(){
      return height;
    };

    vector<int> Map::get_data() {
      return data;
    };

    int Map::get_one_value_data (int i) {
      return data[i];
    }

   void Map::set_width(unsigned int newvalue) {
      width = newvalue;
    };
    
    void Map::set_height(unsigned int newvalue) {
      height = newvalue;
    };
     
    void Map::set_data(vector<int> newvalue) {
      data = newvalue;
    };

    void load_check_Map(const char* pathimage, Map* map) {
        ifstream fichier(pathimage);
        string line;
        vector<int> tmp_data;
         
        if (fichier)
        {  
          int numline=1;
          while (getline(fichier, line)) {
            if  (numline == 1) {
              if (line != "P3") {
                cout << "The ppm is not a P3 format";
                return;
              }
            }
            if ( numline == 2 ) {
              bool width = true;
              stringstream ss;
              ss << line;
              int convert;
              while (!ss.eof())
                {
                  ss >> convert;
                  if (width == true) {
                    map->set_width(convert);
                    width = false;
                  }
                  else {
                    map->set_height(convert);
                  }
                }
            }
            if  (numline == 3) {
              if (line != "255") {
                cout << "3rd line is not 255" << "\n";
                return;
              }
            }
            if (numline > 3 ) {
              stringstream ss;
              ss << line;
                  int convert;
                  while (!ss.eof())
                  {
                    ss >> convert;
                    tmp_data.push_back(convert);
                  }
              map->set_data(tmp_data);
            }
            numline++;
              //cout << map.get_width() << '\n';
              // cout << map.get_height() << '\n';
              // cout << map.get_one_value_data(32) << '\n';
          }
        }
        cout << map->get_one_value_data((800*232+383)*3-1) << "\n";
        cout <<"check\n";
        cout << map->get_one_value_data((800*232+383)*3) << "\n";
        cout <<"check\n";
        cout << map->get_one_value_data((800*232+383)*3+1) << "\n";
    };




int check_node_color(vector<Node>* node_vector, Map* map) {
	for (unsigned int i=0; i<node_vector->size(); i++)  {
        int width=map->get_width();
        int x=(*node_vector)[i].get_pos_x();
        int y=(*node_vector)[i].get_pos_y();
        int position_rgb = (width*(y-1) +(x-1))*3;
        int color_r = map->get_one_value_data(position_rgb + i);
        int color_g = map->get_one_value_data(position_rgb + i + 1);
        int color_b = map->get_one_value_data(position_rgb + i + 2);
        if ( (color_r!=0) && (color_g!=0) && (color_b!=0) ) {
            cout << "the node_color in ITD does not correspond to the map";
            return 1;
        }
   }
   return 0;
}

bool bressenham(Node *point1, Node *point2, vector<int> path_color[3], vector<Entity>* path) { 
    // unsigned x1 = point1->get_pos_x();
    // unsigned y1 = point1->get_pos_y();
    // unsigned x2 = point2->get_pos_x();
    // unsigned y2 = point2->get_pos_y();
    // vector<int> color[3] = path_color;
    // {
    //   int dx  = x2 - x1,
    //       dy  = y2 - y1,
    //       y   = y1,
    //       e = 0,5, //initial error value
    //       e_0_1 = dy /dx, // ratio between dy dx
    //       e_1_0= -1;
    //   for ( int x = x1; x <= x2; x++ )  {
    //     //tracer pixel
    //     if ( (e + e_1_0) >= 0 ) {
    //       y=y+1;
    //       e= e + e_0_1;
    //     }
    //     eps += dy;
    //     if ( (eps << 1) >= dx )  {
    //       y++;  eps -= dx;
    //     }
    //   }
    // }
    return true;
}

bool enter_exit(vector<Node>* nodeList) {
    bool map_enter=false;
    bool map_exit=false;
    for (unsigned int i=0; i<nodeList->size(); i++)  {
        if ((*nodeList)[i].get_type()==1) {
            map_enter = true;
        }
        if ((*nodeList)[i].get_type()==2) {
            map_exit = true;
        }
    }
    if ((map_enter==true) && (map_exit==true)) {
        return true;
    }
    else {
        return false;
    }
}



int check_itd(char const *nameFile, vector<Node> *TabNode){
    FILE* itdMap = NULL;
    char sentence[MAX_SIZE] = "";
    int numLine = 0;
    int nodeNumber = 0;
    int counter_node=0;
    vector<int> color_stock(3);
    bool EnterExit=false;
    // bool entrance = false, exit = false;

    itdMap = fopen(nameFile,"r+");

    printf("%s\n", nameFile);

    if (itdMap != NULL) //If the file has been openned
    {        
        while (fgets(sentence, MAX_SIZE, itdMap) != NULL) //We read the file until we have an error -. until the file ends (NULL)
        {
            numLine++;
            printf("%s", sentence); //We display the sentence we just read

            //Check of the first lign of the file
            if(numLine == 1){
                if ((strncmp(sentence, "@ITD ", 5))!=0){ //We check that the 5 first characters describe an itd file
                    printf("Error Line 1 : the first Line of your .itd file is not valid, the file doesn't seem to be an ITD format.\n");
                    fclose(itdMap);
                    return 0;
                }
                if (isdigit(sentence[5]) == false){ //We check the version number of the file
                    printf("Error lign 1 : bad version number.\n");
                    return 0;
                }
                //printf("Line 1 valid.\n");
            }

            
            //Check of the second lign of the file
            if(numLine == 2){
                if (sentence[0]!='#'){ //Checking it is a commentary lign
                    printf("The second lign of your itd file is not valid, it has to be a commentary.\n");
                    return 0;
                } 
                //printf("Line 2 valid.\n");
            }
            

            //Checking ligns 3 to 8
            if(numLine>=3 && numLine<=8){ //We now have to check every item
                /* Map lign */
                if ((strncmp(sentence, "ca", 2))==0){ //If it is the lign describing the map name
                        char const *nom_carte = NULL;
                        nom_carte = strchr(sentence, ' ');
                        if (nom_carte  != NULL) //If the map name is correctly written
                        {
                            int taille_nom = (int)strlen(nom_carte);
                            for (int i = 1; i<taille_nom; i++){
                                if(nom_carte[i] == ' '){ //Checking if there is no space in the map name
                                    printf("The map name cannot contain a space character.\n");
                                    return 0;
                                }
                            }
                        char const *extension = NULL;
                        extension = strrchr(sentence, '.');
                        if((strncmp(extension, ".ppm", 4))!=0){
                            printf("Your file extension has to be .ppm.\n");
                            return 0;
                        }

                        } else { //If the map name is not written 
                            printf("You have enter no name for your map.\n");
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
                            return 0;
                        }
                        if (numLine == 5) {
                            color_stock.push_back(number1);
                            color_stock.push_back(number2);
                            color_stock.push_back(number3);
                        }
                    }
                    
                //printf("%s Line valid.\n", word);
                
            }
            
            //Checking the Line telling the number of nodes
            if(numLine == 9){
                char * end;
                nodeNumber = strtol (sentence,&end,10);
                if (0 == nodeNumber){
                    printf("Ligne number 9 is not correct. It has to be a positiv number representing the number of nodes\n");
                    return 0;
                }
            }

            //Checking the format of the nodes announced before
            // if(numLine>=10){
            //     int n1, n2, n3, n4;
            //     sscanf (sentence,"%d %d %d %d",&n1,&n2, &n3, &n4);
            //     if (n1!=nodeIndex){
            //         printf("The index of the node number %d is wrong, it should be equal to %d.\n",nodeIndex+1, nodeIndex );
            //         return 0;
            //     }
            //     if (n2<=0 || n2>4){
            //         printf("The nature of the node number %d is wrong. It can be equal to 1(entrance of the monsters), 2(exit of the monsters), 3(angle in the path) or 4(path intersection).\n", nodeIndex+1);
            //         return 0;
            //     }
            //     if (n3<0 || n3>800){
            //         printf("The value of the first coordinate of the node number %d is false, it has to be between 0 and 800.\n",nodeIndex-1 );
            //         return 0;
            //     }
            //     if (n4<0 || n4>600){
            //         printf("The value of the second coordinate of the node number %d is false, it has to be between 0 and 600.\n",nodeIndex-1 );
            //         return 0;
            //     }

            //     if (n2==1) entrance =true;
            //     if (n2==2) exit =true;

            //     nodeIndex++;
            //     temp--;
            // }
            if (numLine >= 10) {
                Node* tmp_Node = new Node;
                tmp_Node->set_color_rgb(color_stock);
                *tmp_Node=collectNode(sentence,tmp_Node);
                TabNode->push_back(*tmp_Node);
                counter_node++;
            }
        }

        EnterExit=enter_exit(TabNode);
        if (EnterExit == false) {
            cout << "there is no enter or no exit found in ITD";
            return 0;
        }

        //Check if the number of described nodes in the itd is the same of the announced one
        if (counter_node!=nodeNumber){
            printf("The number of nodes actually described does not match the announced number of nodes.\n");
            return 0;
        }

        // if (!entrance){
        //     printf("You have to include at least one monstre entrance.\n");
        //     return 0;
        // }
        // if (!exit){
        //     printf("You have to include at least one monster exit.\n");
        //     return 0;
        // }
        printf("Itd map is valid.\n");
        
        fclose(itdMap);

    } else {
        //Error openning the file
        printf("File %s cannot be openned.\n", nameFile);
    }
    return 1;
}


