#pragma once
#include<vector>
#include <armadillo>
#include "Vertex.h"
#include "Face.h"
#include "Transform.h"
#include <gl/glut.h>
#include <GLFW/glfw3.h>
class Pared
{
public:
	~Pared();

	vector<Face> vectorCaras;
	vector<float> color;
	float S;
	int V;
	float angle;
	float t;
	float dt;
	float radio;
	float posicion[3];
	arma::fmat transf;

	Pared(arma::fmat trans, vector<Face> caras, vector<float> colorV, float s, int v, arma::frowvec pos, float rad);
	vector<Face> iluminacion(arma::frowvec DOP);
	vector<arma::frowvec> colorear(vector<Face> colores);
	//void dibujarPared(arma::frowvec posicion, arma::frowvec DOP);
	//void colores(int cara);
	void movimiento(arma::fmat transform);
};

