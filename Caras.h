#ifndef CARAS_H
#define CARAS_H
#include "Arista.h"
#include <vector>

using namespace std;
class Caras
{
public:
	Caras();
	Caras(vector<Arista> edges_in);
	vector<Vertice> vertices;
	vector<Arista> edges;

	virtual ~Caras();

protected:

private:

};

#endif // CARAS_H
