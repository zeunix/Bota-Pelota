#pragma once
#include<vector>
#include <armadillo>
#include "Vertex.h"
#include "Face.h"
#include "Transform.h"
#include "Point.h"

class Esfera
{
public:
	~Esfera();

	vector<Face> vectorCaras;
	vector<float> color;
	float S;
	int V;
	float angle;
	float t;
	float dt;
	float radio;
	float posicion[3];
	float aumento;
	//Se declaran dos arreglos de puntos para las dos trayectorias
	Point izq[4];
	Point der[4];
	double tBezier = 0.0;

	arma::fmat transf;

	vector<Vertex> dibujaBezier(arma::fmat trans, arma::frowvec pos);
	Esfera(arma::fmat trans, vector<Face> caras, vector<float> colorV, float s, int v, arma::frowvec pos, float rad);
	vector<Face> iluminacion(arma::frowvec DOP);
	vector<arma::frowvec> colorear(vector<Face> colores);
	void movimiento(arma::fmat transform);
	void setTrayectoriaIZQ();
	void setTrayectoriaDER();
	Point Bezier(Point A, Point B, Point C, Point D, double t);
};
