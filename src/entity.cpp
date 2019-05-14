#include "../include/entity.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <cstdio>
#include "../include/entity.h"


//contructeur

	Entity::Entity() {};

//surcharge
	Entity::Entity(float x, float y):coord_x(x), coord_y(y) 
		{
	};

//destructeur
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
	void Entity::set_X(int x) {
		coord_x = x;
	};

	void Entity::set_Y(int y) {
		coord_y=y;
	};

