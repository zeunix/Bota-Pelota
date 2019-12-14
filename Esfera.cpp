#include "Esfera.h"
#include "Transform.h"


Esfera::Esfera(arma::fmat trans, vector<Caras> caras, vector<float> colorV, float s, int v, arma::frowvec pos, float radio_in)
{
	transf = trans;
	vectorCaras = caras;	
	S = s;
	V = v;
	color = colorV;
	aumento = 0.0;
	posicion[0] = pos[0];
	posicion[1] = pos[1];
	posicion[2] = pos[2];
	radio = radio_in;
	dt = 0.05 * (V + 1);
}

Esfera::~Esfera()
{
}
/*
void Pared::dibujarPared(arma::frowvec posicion, arma::frowvec DOP) {
	vector<Face> carasIluminadas = iluminacion(DOP);
	int cara = 0;
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < carasIluminadas.size(); i++) {

		colores(cara);
		for (int j = 0; j < 3; j++) {
			arma::frowvec vert = carasIluminadas[i].vertices[j].getVertex();
			glVertex3f(vert[0], vert[1], vert[2]);
		}
		cara++;
	}
	glEnd();
}

*/



//variable para el aumento de velocidad en el movimiento


///Seccion donde se colocan los puntos especificos de la trayectoria para el movimiento de la pelota
void Esfera::setTrayectoriaIZQ() {
	izq[0].setxyz(9, 0.2, 0);
	izq[1].setxyz(5.1, 5,0);
	izq[2].setxyz(-5, 3.5, 0);
	izq[3].setxyz(-9, 0.2,0);
}
void Esfera:: setTrayectoriaDER() {
	der[3].setxyz(-9,-0.2, 0);
	der[2].setxyz(-5.3, -5, 0);
	der[1].setxyz(5, -3, 0);
	der[0].setxyz(9, 0.2, 0);
}



Point Esfera::Bezier(Point A, Point B, Point C, Point D, double t) {
	Point P;
	P.x = pow((1 - t), 3) * A.x + 3 * t * pow((1 - t), 2) * B.x + 3 * (1 - t) * pow(t, 2) * C.x + pow(t, 3) * D.x;
	P.y = pow((1 - t), 3) * A.y + 3 * t * pow((1 - t), 2) * B.y + 3 * (1 - t) * pow(t, 2) * C.y + pow(t, 3) * D.y;
	P.z = pow((1 - t), 3) * A.z + 3 * t * pow((1 - t), 2) * B.z + 3 * (1 - t) * pow(t, 2) * C.z + pow(t, 3) * D.z;
	return P;
}

void Esfera::movimiento(arma::fmat transform)
{
	Transform Tr = Transform();
	transf = transf;
	vector<Vertice> vertices;
	for (unsigned int i = 0; i < vectorCaras.size(); i++) {
		arma::fcolvec v = vectorCaras[i].vertices[0].homg();
		arma::fcolvec vp = transf * v;
		Vertice rv = Vertice();
		rv.setV(arma::trans(vp));
		vectorCaras[i].vertices[0] = rv;

		v = vectorCaras[i].vertices[1].homg();
		vp = transf * v;
		rv = Vertice();
		rv.setV(arma::trans(vp));
		vectorCaras[i].vertices[1] = rv;

		v = vectorCaras[i].vertices[2].homg();
		vp = transf * v;
		rv = Vertice();
		rv.setV(arma::trans(vp));
		vectorCaras[i].vertices[2] = rv;
	}
}

vector<Caras> Esfera::iluminacion(arma::frowvec DOP)
{
	vector<Caras> carasListas;
	for (int i = 0; i < vectorCaras.size(); i++)
	{
		Caras f = vectorCaras[i];
		//Sacar normales
		arma::fcolvec v0 = { {f.vertices[0].getX()}, {f.vertices[0].getY()}, f.vertices[0].getZ() };
		arma::fcolvec v1 = { {f.vertices[1].getX()}, {f.vertices[1].getY()}, f.vertices[1].getZ() };
		arma::fcolvec v2 = { {f.vertices[2].getX()}, {f.vertices[2].getY()}, f.vertices[2].getZ() };
		arma::fcolvec N = arma::cross((v1 - v0), (v2 - v0));
		N = arma::normalise(N);
		float seve = arma::dot(DOP, N);
		if (seve > 0) {
			carasListas.push_back(f);
		}

	}
	return carasListas;
}

vector<arma::frowvec> Esfera::colorear(vector<Caras> visibles) {
	vector<arma::frowvec> colores;

	float Ia = 0.95;
	float Ka = 0.85;
	float Ip = 0.8;
	float Kd = 0.75;

	arma::fcolvec F = { -8.0, 8.0, -8.0 };
	for (int i = 0; i < visibles.size(); i++)
	{
		//Normales normalizadas
		Caras f = visibles[i];
		//Sacar normales
		arma::frowvec v0 = { f.vertices[0].getX(), f.vertices[0].getY(), f.vertices[0].getZ() };
		arma::frowvec v1 = { f.vertices[1].getX(), f.vertices[1].getY(), f.vertices[1].getZ() };
		arma::frowvec v2 = { f.vertices[2].getX(), f.vertices[2].getY(), f.vertices[2].getZ() };
		arma::frowvec N = arma::cross((v1 - v0), (v2 - v0));
		N = arma::normalise(N);

		//Obtener L normalizada
		arma::fcolvec v0t = { {f.vertices[0].getX()}, {f.vertices[0].getY()}, {f.vertices[0].getZ() } };
		arma::fcolvec L = arma::normalise(F - v0t);

		float I = Ia * Ka + Ip * Kd * arma::dot(N, L);
		arma::frowvec c;
		c = { I * color[0], I * color[1], I * color[2] };
		colores.push_back(c);

	}


	return colores;
}