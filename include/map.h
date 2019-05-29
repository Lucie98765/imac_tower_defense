#ifndef CHECKMAP_HPP
#define CHECKMAP_HPP

#include "headers.h"
#include "node.h"
#include "entity.h"

// typedef struct Noeud{ /* faire une classe, reprendre classe node c++ */
//   int pos_x;
//   int pos_y;
//   int type;
//   Noeud *suivant;
// } Noeud;

class Map{

  private:
    unsigned int width;
    unsigned int height;
    vector<int> data;
  
  public:
      Map();
    
      //getter
      unsigned int get_width();
      unsigned int get_height();
      vector<int> get_data();
      int get_one_value_data (int i);

      //setter
      void set_width(unsigned int newvalue);
      void set_height(unsigned int newvalue);
      void set_data(vector<int> newvalue);

      //other methods
};

void load_check_Map(char const *pathimage, Map* map);


int check_node_color(vector<Node>* node_vector, Map* map);
bool enter_exit(vector<Node>* nodeList);

int check_itd(char const *nameFile, vector<Node> *TabNode);

bool bressenham(Node pointA, Node pointB, vector<int> path_color);



#endif