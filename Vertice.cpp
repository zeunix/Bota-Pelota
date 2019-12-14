
#include "Vertice.h"

Vertice::Vertice()
{
	//ctor
}

Vertice::Vertice(float x_in, float y_in, float z_in)
{
	//ctor
	x = x_in;
	y = y_in;
	z = z_in;
}


Vertice::~Vertice()
{
	//dtor
}

vector<float> Vertice::getVertex() {
	vector<float> v;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	return v;
}

void Vertice::setV(arma::frowvec vertex) {
	x = vertex[0];
	y = vertex[1];
	z = vertex[2];
}

arma::fcolvec Vertice::homg() {
	arma::fcolvec p = { {x},{y},{z},{1.0} };
	return p;
}

float Vertice::getX() {
	return x;
}
void Vertice::setX(float val) {
	x = val;
}
float Vertice::getY() {
	return y;
}
void Vertice::setY(float val) {
	y = val;
}
float Vertice::getZ() {
	return z;
}
void Vertice::setZ(float val) {
	z = val;
}

