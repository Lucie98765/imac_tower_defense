#ifndef NODE_H
#define NODE_H


#include "headers.h"


class Node {
	private:
		int number_node;
		int pos_x;
		int pos_y;
		int type;
		vector<int> color_rgb;
		vector <int> linked_points;

	public:
		//constructor

		Node();

		//overload constructor
		Node(int number, int x, int y, int type);


		//getters
			int get_number_node();
			int get_pos_x();
			int get_pos_y();
			int get_type();
			vector<int> get_color_rgb();
			int get_one_color_rgb(int i);
			vector<int> get_linked_points();



    	//setters
			void set_number_node(int new_number);
			void set_pos_x(int new_x);
			void set_pos_y(int new_y);
			void set_type(int new_type);
			void set_color_rgb(vector<int> color);
			void set_linked_points(vector<int> points);
			void set_one_linked_point(int point);
		
		//other methods
		
} ;

	Node collectNode(char* sentence,Node* node);
#endif

