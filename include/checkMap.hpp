#ifndef CHECKMAP_HPP
#define CHECKMAP_HPP


typedef struct Noeud{ /* faire une classe, reprendre classe node c++ */
  int pos_x;
  int pos_y;
  int type;
  Noeud *suivant;
} Noeud;


int check_itd(char const *nameFile);
int check_ppm(char const *ppmName);



#endif