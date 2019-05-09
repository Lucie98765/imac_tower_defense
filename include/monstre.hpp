#ifndef MONSTRE_HPP
#define MONSTRE_HPP


class Monstre {
	private: 

		int pv;
		int vitesse;
		int resistance_tr;
		int resistance_tv;
		int resistance_tb;
		int resistance_tj;

/* La résistance des monstre est le pourcentage de réception des attaques des tours en question.
Si r = 100 : reçoit 100% de l'attaque : pas résistant du tout */


/* manque le constructeur et le destructeur */

	public:

		void seDeplacer(int xAct, int yAct);
		int getPv();
		void setPv(int nvxPv);

		int getresistance_tr();
		void setresistance_tr(int nvlResistance);
		int getresistance_tv();
		void setresistance_tv(int nvlResistance);
		int getresistance_tb();
		void setresistance_tb(int nvlResistance);
		int getresistance_tj();
		void setresistance_tj(int nvlResistance);


};

#endif