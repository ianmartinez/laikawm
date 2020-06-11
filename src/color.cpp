#include "include/color.hpp"

lk_color::lk_color() {
	this->r = 0.0;
	this->g = 0.0;
	this->b = 0.0;
	this->a = 0.0;
}

lk_color::lk_color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void lk_color::to_array(float *array) {
	array[0] = this->r;
	array[1] = this->g;
	array[2] = this->b;
	array[3] = this->a;
}
