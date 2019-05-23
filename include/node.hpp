#ifndef NODE_HPP
#define NODE_HPP
#define MAX_DEPENDENCES 5


#include "headers.h"


class Node {
	private : 
	  int pos_x;
	  int pos_y;
	  int type;

	  int dependences[MAX_DEPENDENCES];

	public:
		//constructor
		Node(int x, int y, int type);


		//getters
    	int get_pos_x();
    	int get_pos_y();
    	int get_type();



    	//setters
	    void set_pos_x(int new_x);
	    void set_pos_y(int new_y);
	    void set_type(int new_type);
    
  
} ;

#endif