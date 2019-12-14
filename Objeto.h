#ifndef OBJETO_H
#define OBJETO_H
#include "Vertice.h"
#include "Arista.h"
#include "Caras.h"
#include <vector>
#include <string>

using namespace std;


class Objeto
{
public:
	Objeto();
	Objeto(vector<Vertice> vertices_in, vector<Arista> edges_in, vector<Caras> faces_in);
	void scale();
	virtual ~Objeto();
	vector<Vertice> vertices;
	vector<Arista> edges;
	vector<Caras> faces;
	string name;
	float punto;

protected:

private:

};

#endif // OBJETO_H
