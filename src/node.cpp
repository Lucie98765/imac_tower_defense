#include "../include/node.h"

    //constructor
    Node::Node() {};

    Node::Node(int number, int x, int y, int type) : 
    number_node(number), pos_x(x), pos_y(y), type(type)
    {}

    //getters
    int Node::get_number_node() {
        return number_node;
    }

    int Node::get_pos_x() {
        return pos_x;
    }

    int Node::get_pos_y() {
        return pos_y;
    }

    int Node::get_type() {
        return type;
    }

    vector<unsigned int> Node::get_color_rgb() {
        return color_rgb;
    };

    unsigned int Node::get_one_color_rgb(int i) {
        return color_rgb[i];
    }

    vector<int> Node::get_linked_points() {
        return linked_points;
    }

    //setters
    void Node::set_number_node(int new_number) {
        number_node = new_number;
    }

    void Node::set_pos_x(int new_x) {
        pos_x = new_x;
    }

    void Node::set_pos_y(int new_y) {
        pos_y = new_y;
    }

    void Node::set_type(int new_type) {
        type = new_type;
    }

    void Node::set_color_rgb(vector<unsigned int> color) {
        color_rgb = color;
    }

    void Node::set_linked_points(vector<int> points) {
        linked_points = points;
    }

    void Node::set_one_linked_point(int point) {
        linked_points.push_back(point);
    }

    Node collectNode(char *sentence ,Node* node) {
                int data_node = 0;
                stringstream ss;
                string line(sentence);
                ss << line;
                int convert;
                while (!ss.eof()) {
                    data_node++;
                    ss >> convert;
                    if (data_node == 1){
                        node->set_number_node(convert);
                    }
                    if (data_node == 2) {
                        node->set_type(convert);
                    }
                    if (data_node == 3){
                       node->set_pos_x(convert);
                    }
                    if (data_node == 4){
                        node->set_pos_y(convert);
                    }
                    else {
                        node->set_one_linked_point(convert);
                    }
                }
            return *node;
    }
