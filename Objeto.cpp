#include "Objeto.h"
#include <algorithm>
using namespace std;

Objeto::Objeto()
{
	//ctor
}

Objeto::Objeto(vector<Vertice> vertices_in, vector<Arista> edges_in, vector<Caras> faces_in)
{
	//ctor
	vertices = vertices_in;
	edges = edges_in;
	faces = faces_in;
}

//Funcion para escalar los valores 
void Objeto::scale()
{
	while (punto > 0.3)
	{
		punto = punto / 10;
		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].setX(vertices[i].getX() / 2);
			vertices[i].setY(vertices[i].getY() / 2);
			vertices[i].setZ(vertices[i].getZ() / 2);
		}
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].vertices[0].setX(faces[i].vertices[0].getX() / 2);
			faces[i].vertices[0].setY(faces[i].vertices[0].getY() / 2);
			faces[i].vertices[0].setZ(faces[i].vertices[0].getZ() / 2);

			faces[i].vertices[1].setX(faces[i].vertices[1].getX() / 2);
			faces[i].vertices[1].setY(faces[i].vertices[1].getY() / 2);
			faces[i].vertices[1].setZ(faces[i].vertices[1].getZ() / 2);

			faces[i].vertices[2].setX(faces[i].vertices[2].getX() / 2);
			faces[i].vertices[2].setY(faces[i].vertices[2].getY() / 2);
			faces[i].vertices[2].setZ(faces[i].vertices[2].getZ() / 2);
		}

		for (int i = 0; i < edges.size(); i++)
		{
			edges[i].v1.setX(edges[i].v1.getX() / 2);
			edges[i].v1.setY(edges[i].v1.getY() / 2);
			edges[i].v1.setZ(edges[i].v1.getZ() / 2);

			edges[i].v2.setX(edges[i].v2.getX() / 2);
			edges[i].v2.setY(edges[i].v2.getY() / 2);
			edges[i].v2.setZ(edges[i].v2.getZ() / 2);

		}
	}

}

Objeto::~Objeto()
{
	//dtor
}
