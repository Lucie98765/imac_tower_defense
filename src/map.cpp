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

    vector<unsigned int> Map::get_data() {
      return data;
    };

    vector<Entity> Map::get_path_pixel() {
      return path_pixel;
    }

    vector<unsigned int> Map::get_node_color() {
      return node_color;
    }

    vector<unsigned int> Map::get_in_node_color() {
      return in_node_color;
    }

    vector<unsigned int> Map::get_out_node_color() {
      return out_node_color;
    }

    vector<Node> Map::get_TabNode() {
      return TabNode;
    }

    Node Map::get_one_node_TabNode(int i) {
      return TabNode[i];
    }
    
    vector<unsigned int> Map::get_path_color() {
      return path_color;
    };

    vector<unsigned int> Map::get_construct_color() {
      return construct_field;
    };


    unsigned int Map::get_one_value_data (int i) {
      return data[i];
    }

   void Map::set_width(unsigned int newvalue) {
      width = newvalue;
    }
    
    void Map::set_height(unsigned int newvalue) {
      height = newvalue;
    }
     
    void Map::set_data(vector<unsigned int> newvalue) {
      data = newvalue;
    }

    void Map::set_path_pixel(vector<Entity> path) {
      path_pixel = path;
    }

    void Map::set_path_one_pixel(Entity pixel) {
      path_pixel.push_back(pixel);
    }

    void Map::set_node_color(vector<unsigned int> newvalue) {
      node_color = newvalue;
    }

    void Map::set_in_node_color( vector<unsigned int> newvalue) {
      in_node_color = newvalue;
    }

    void Map::set_out_node_color(vector<unsigned int> newvalue) {
      out_node_color = newvalue;
    }

    void Map::set_TabNode(vector<Node> newTab) {
      TabNode = newTab;
    }

    void Map::set_one_node_TabNode(Node newNode){
      TabNode.push_back(newNode);
    }

    void Map::set_path_color(vector<unsigned int> newvalue) {
      path_color = newvalue;
    };

    void Map::set_construct_color(vector<unsigned int> newvalue) {
      construct_field = newvalue;
    };


    void load_check_Map(const char* pathimage, Map* map) {
        int numline=1;
        ifstream fichier(pathimage);
        string line;
        vector<unsigned int> tmp_data;
         
        if (fichier)
        {
          while (getline(fichier, line)) {
            //check if format is P3
            if  (numline == 1) {
              if (line != "P3") {
                //cout << "The ppm is not a P3 format";
                return;
              }
            }
            //stock the width and the height
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
            //check if the 3rd line is 255
            if  (numline == 3) {
              if (line != "255") {
                //cout << "3rd line is not 255" << "\n";
                return;
              }
            }
            //stock all the rgb compenant
            if (numline > 3 ) {
              stringstream ss;
              ss << line;
                  unsigned int convert;
                  while (!ss.eof())
                  {
                    ss >> convert;
                    tmp_data.push_back(convert);
                  }
            }
            numline++;
          }
          map->set_data(tmp_data);
        }
    };



//Check the node color noticed in .itd and the real color of the map
int check_node_color(Node node, Map map) {
        int width=map.get_width();
        int x=node.get_pos_x();
        int y=node.get_pos_y();
        // Dans map.h, la classe map a un vecotr<int> data qui contient les composants RGB de la ppm, je suppose que le premier pixel se trouve à la position (1,1) (enfin j'esềre que c'est ça) 
        int position_rgb =(width*y + x)*3 ;
        unsigned int color_r = map.get_one_value_data(position_rgb);
        unsigned int color_g = map.get_one_value_data(position_rgb+1);
        unsigned int color_b = map.get_one_value_data(position_rgb+2);
        //cout << x << " " << y << "\n";
        //cout << color_r << " " << color_g << " " << color_b << "\n";
        if ( (color_r!=node.get_one_color_rgb(0)) &&
             (color_g!=node.get_one_color_rgb(1)) && 
             (color_b!=node.get_one_color_rgb(2)) ) {
            //cout << "the node_color in ITD does not correspond to the map";
            return 1;
        }
   
   return 0;
}

//check color of path (used in bressenham algorithm)
bool check_path_color(int x, int y, Map map) {
    int width=map.get_width();
        int position_rgb =(width*y + x)*3 ;
        unsigned int color_r = map.get_one_value_data(position_rgb);
        unsigned int color_g = map.get_one_value_data(position_rgb+1);
        unsigned int color_b = map.get_one_value_data(position_rgb+2);
        //cout << color_r << " " << color_g << " " << color_b << "\n";
        //cout << x << " " << y << "\n";
        if ( (color_r!=(map.get_path_color())[0]) &&
             (color_g!=(map.get_path_color())[1]) && 
             (color_b!=(map.get_path_color())[2]) ) {
            //cout << "the pixel does not correspond to the path of map \n";
            return false;
        }
   return true;
}

bool check_in_node_color(int x, int y, Map map) {
    int width=map.get_width();
        int position_rgb =(width*y + x)*3 ;
        unsigned int color_r = map.get_one_value_data(position_rgb);
        unsigned int color_g = map.get_one_value_data(position_rgb+1);
        unsigned int color_b = map.get_one_value_data(position_rgb+2);
        //cout << color_r << " " << color_g << " " << color_b << "\n";
        //cout << x << " " << y << "\n";
        if ( (color_r!=(map.get_in_node_color())[0]) &&
             (color_g!=(map.get_in_node_color())[1]) && 
             (color_b!=(map.get_in_node_color())[2]) ) {
            cout << "the pixel does not correspond to the path of map \n";
            return false;
        }
   return true;
}

bool check_node_color2(int x, int y, Map map) {
    int width=map.get_width();
        int position_rgb =(width*y + x)*3 ;
        unsigned int color_r = map.get_one_value_data(position_rgb);
        unsigned int color_g = map.get_one_value_data(position_rgb+1);
        unsigned int color_b = map.get_one_value_data(position_rgb+2);
        //cout << color_r << " " << color_g << " " << color_b << "\n";
        //cout << x << " " << y << "\n";
        if ( (color_r!=(map.get_node_color())[0]) &&
             (color_g!=(map.get_node_color())[1]) && 
             (color_b!=(map.get_node_color())[2]) ) {
            //cout << "the pixel does not correspond to the path of map \n";
            return false;
        }
   return true;
}


bool check_out_node_color(int x, int y, Map map) {
    int width=map.get_width();
        int position_rgb =(width*y + x)*3 ;
        unsigned int color_r = map.get_one_value_data(position_rgb);
        unsigned int color_g = map.get_one_value_data(position_rgb+1);
        unsigned int color_b = map.get_one_value_data(position_rgb+2);
        //cout << color_r << " " << color_g << " " << color_b << "\n";
        //cout << x << " " << y << "\n";
        if ( (color_r!=(map.get_out_node_color())[0]) &&
             (color_g!=(map.get_out_node_color())[1]) && 
             (color_b!=(map.get_out_node_color())[2]) ) {
            //cout << "the pixel does not correspond to the path of map \n";
            return false;
        }
   return true;
}


//we suppose, we just have horizontal and vertical movement
bool bressenham(Node point1, Node point2, Map* map) {
    Entity *pixel = new Entity;
    //cout << "yo";
    int x1 = point1.get_pos_x();
    //cout << x1;
    int y1 = point1.get_pos_y();
    //cout << y1;
    int x2 = point2.get_pos_x();
    int y2 = point2.get_pos_y();
    pixel->set_x(x1);
    pixel->set_y(y1);
    map->set_path_one_pixel(*pixel);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
        if ( dx <= 2 ) {
            //cout << dx << "\n";
            x1=x2;
            if (y1<y2) {
                while ( y1 < y2 ) {
                    y1=y1-1;
                    if ( check_path_color(x1,y1,*map)!=true &&
                          check_in_node_color(x1,y1,*map)!=true &&
                          check_out_node_color(x1,y1,*map)!=true &&
                          check_node_color2(x1,y1,*map)!=true ) {
                            //cout << "there is a problem";
                            return false;
                          }
                    else {
                      pixel->set_y(y1);
                      map->set_path_one_pixel(*pixel);
                    }
                }
            }
            else {
                while ( y1 > y2 ) {
                    y1=y1+1;
                    if ( check_path_color(x1,y1,*map)!=true &&
                          check_in_node_color(x1,y1,*map)!=true &&
                          check_out_node_color(x1,y1,*map)!=true &&
                          check_node_color2(x1,y1,*map)!=true ) {
                            //cout << "there is a problem";
                            return false;
                          }
                    else {
                      pixel->set_y(y1);
                      map->set_path_one_pixel(*pixel);
                    }
                }
              }
        }
        if( dy <= 2) {
            //cout << dy << "\n";
            y1=y2;
            if (x1<x2) {
                while ( x1 < x2 ) {
                    x1=x1+1;
                    if ( check_path_color(x1,y1,*map)!=true &&
                          check_in_node_color(x1,y1,*map)!=true &&
                          check_out_node_color(x1,y1,*map)!=true &&
                          check_node_color2(x1,y1,*map)!=true ) {
                            //cout << "there is a problem";
                            return false;
                          }
                    else {
                      pixel->set_y(x1);
                      map->set_path_one_pixel(*pixel);
                    }
                }
            }
            else {
              while ( x1 < x2 ) { 
                  x1=x1-1;
                  if ( check_path_color(x1,y1,*map)!=true &&
                        check_in_node_color(x1,y1,*map)!=true &&
                        check_out_node_color(x1,y1,*map)!=true &&
                        check_node_color2(x1,y1,*map)!=true ) {
                          //cout << "there is a problem";
                          return false;
                        }
                  else {
                    pixel->set_y(x1);
                    map->set_path_one_pixel(*pixel);
                  }
              }
            }
        }
    return true;
}

bool enter_exit(vector<Node> nodeList) {
    bool map_enter=false;
    bool map_exit=false;
    for (unsigned int i=0; i<nodeList.size(); i++)  {
        if (nodeList[i].get_type()==1) {
            map_enter = true;
        }
        if (nodeList[i].get_type()==2) {
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

int check_itd(char const *nameFile, Map *map){
    FILE* itdMap = NULL;
    char sentence[MAX_SIZE] = "";
    int numLine = 0;
    int nodeNumber = 0;
    int counter_node=0;
    vector<unsigned int> enter_color_stock;
    vector<unsigned int> exit_color_stock;
    vector<unsigned int> color_stock;
    vector<unsigned int> path_color_stock;
    bool EnterExit=false;
    // bool entrance = false, exit = false;

    itdMap = fopen(nameFile,"r+");

    printf("%s\n", nameFile);

    if (itdMap != NULL) //If the file has been openned
    {        
        while (fgets(sentence, MAX_SIZE, itdMap) != NULL) //We read the file until we have an error -. until the file ends (NULL)
        {
            numLine++;
            //printf("%s", sentence); //We display the sentence we just read

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
            if(numLine>=3 && numLine<=8){ //Now we have to check every item
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
                }
                else { // For all the other Lines
                        char word [20];
                        unsigned int number1, number2, number3;
                        sscanf (sentence,"%s %d %d %d",word,&number1, &number2, &number3);
                        if (number1<0 || number1>255 || number2<0 || number2>255 || number3<0 || number3>255){
                            printf("Bad value(s) the color of the  %s\n", word);
                            return 0;
                        }
                        //stock the rgb component of path
                        if (strcmp(word,"chemin") == 0) {
                            path_color_stock.push_back(number1);
                            path_color_stock.push_back(number2);
                            path_color_stock.push_back(number3);
                            map->set_path_color(path_color_stock);
                        }
                        //stock the rgb component of nodes
                        if (strcmp(word,"noeud")== 0) {
                            color_stock.push_back(number1);
                            color_stock.push_back(number2);
                            color_stock.push_back(number3);
                            //cout << "VIVE LES NOEUDS";
                            //cout << word;
                            //cout<< color_stock[0] << " " << color_stock[1] << " " << color_stock[3] << "\n";
                            map->set_node_color(color_stock);
                        }
                        //stock the rgb component of entry
                        if (strcmp(word,"in")== 0) {
                            enter_color_stock.push_back(number1);
                            enter_color_stock.push_back(number2);
                            enter_color_stock.push_back(number3);
                            //cout<< number1 << " " << number2 << " " << number3 << "\n";
                            map->set_in_node_color(enter_color_stock);
                        }
                        
                        //stock the rgb component of exit
                        if (strcmp(word,"out")== 0) {
                            exit_color_stock.push_back(number1);
                            exit_color_stock.push_back(number2);
                            exit_color_stock.push_back(number3);
                            map->set_in_node_color(enter_color_stock);
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
            if (numLine >= 10) {
                Node* tmp_Node = new Node;
                *tmp_Node=collectNode(sentence,tmp_Node);
                if (tmp_Node->get_number_node() == 1) {
                    tmp_Node->set_color_rgb(enter_color_stock);
                }
                if (tmp_Node->get_number_node() == 2) {
                    tmp_Node->set_color_rgb(exit_color_stock);
                }
                else {
                    tmp_Node->set_color_rgb(color_stock);
                    //cout << tmp_Node->get_one_color_rgb(0);
                }
                map->set_one_node_TabNode(*tmp_Node);
                counter_node++;
            }
        }

        EnterExit=enter_exit(map->get_TabNode());
        if (EnterExit == false) {
            //cout << "there is no enter or no exit found in ITD";
            return 0;
        }

        //Check if the number of described nodes in the itd is the same of the announced one
        if (counter_node!=nodeNumber){
            printf("The number of nodes actually described does not match the announced number of nodes.\n");
            return 0;
        }
        printf("Itd map is valid.\n");
        
        fclose(itdMap);

    } else {
        //Error openning the file
        printf("File %s cannot be openned.\n", nameFile);
    }
    return 1;
}