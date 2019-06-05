#include "../include/entity.h"
#include "../include/headers.h"


//contructor

	Entity::Entity() {};

//overload
	Entity::Entity(float x, float y):coord_x(x), coord_y(y) 
		{
	};

//destructorr
	Entity::~Entity() {};

/* void Entity::update() {
	glColor4f(255, 0, 0, 1);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		glVertex2f(m_x, m_y);
	glEnd();
	glPointSize(1.0f);
} */

//getters
	int Entity::get_x() {
		return coord_x;
	};

	int Entity::get_y() {
		return coord_y;
	};

//setters
	void Entity::set_x(int x) {
		this->coord_x = x;
	};

	void Entity::set_y(int y) {
		this->coord_y=y;
	};

