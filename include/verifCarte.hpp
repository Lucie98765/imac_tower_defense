#ifndef VERIFCARTE_HPP
#define VERIFCARTE_HPP


typedef struct Noeud{ /* faire une classe, reprendre classe node c++ */
  int pos_x;
  int pos_y;
  int type;
  Noeud *suivant;
} Noeud;


int verifier_itd(char const *nomFichier);
int verifier_ppm(char const *nom_ppm);



#endif