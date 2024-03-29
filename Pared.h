#pragma once
#include<vector>
#include <armadillo>
#include "Vertice.h"
#include "Caras.h"
#include "Transform.h"
#include <gl/glut.h>
#include <GLFW/glfw3.h>
class Pared
{
public:
	~Pared();

	vector<Caras> vectorCaras;
	vector<float> color;
	float S;
	int V;
	float angle;
	float t;
	float dt;
	float radio;
	float posicion[3];
	arma::fmat transf;

	Pared(arma::fmat trans, vector<Caras> caras, vector<float> colorV, float s, int v, arma::frowvec pos, float rad);
	vector<Caras> iluminacion(arma::frowvec DOP);
	vector<arma::frowvec> colorear(vector<Caras> colores);
	//void dibujarPared(arma::frowvec posicion, arma::frowvec DOP);
	//void colores(int cara);
	void movimiento(arma::fmat transform);
};

