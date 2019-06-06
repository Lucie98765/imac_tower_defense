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
    vector<unsigned int> data;
    vector<Entity> path_pixel;
    vector<unsigned int> path_color;
    vector<unsigned int> node_color;
    vector<unsigned int> in_node_color;
    vector<unsigned int> out_node_color;
    vector<Node> TabNode;
    vector<unsigned int> construct_field;
  
  public:
      Map();
    
      //getter
      unsigned int get_width();

      unsigned int get_height();

      vector<unsigned int> get_data();
      unsigned int get_one_value_data(int i);

      vector<Entity> get_path_pixel();

      vector<unsigned int> get_node_color();

      vector<unsigned int> get_in_node_color();

      vector<unsigned int> get_out_node_color();

      vector<unsigned int> get_path_color();

      vector<unsigned int> get_construct_color();

      vector<Node> get_TabNode();
      Node get_one_node_TabNode(int i);

      //setter
      void set_width(unsigned int newvalue);

      void set_height(unsigned int newvalue);

      void set_data(vector<int> newvalue);

      void set_data(vector<unsigned int> newvalue);

      void set_path_pixel(vector<Entity> path);
      void set_path_one_pixel(Entity pixel);

      void set_node_color(vector<unsigned int> newvalue);

      void set_in_node_color(vector<unsigned int> newvalue);

      void set_out_node_color(vector<unsigned int> newvalue);

      void set_TabNode(vector<Node> newTab);
      void set_one_node_TabNode(Node newNode);

      void set_one_value_TabNode(vector<Node> newTab);

      void set_path_color(vector<unsigned int> newvalue);
      
      void set_construct_color(vector<unsigned int> newvalue);

      //other methods
};

void load_check_Map(char const *pathimage, Map* map);


int check_node_color(Node node, Map map);
bool check_path_color(int x, int y, Map map);
bool enter_exit(vector<Node> nodeList);
bool check_in_node_color(int x, int y, Map map);
bool check_out_node_color(int x, int y, Map map);
bool check_node_color2(int x, int y, Map map);

int check_itd(char const *nameFile, Map * map);

bool bressenham(Node point1, Node point2, Map* map);




#endif