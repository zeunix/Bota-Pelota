#ifndef ARISTA_H
#define ARISTA_H
#include "Vertice.h"


class Arista
{
public:
	Arista();
	Arista(Vertice v1_in, Vertice v2_in);
	virtual ~Arista();
	Vertice v1;
	Vertice v2;

protected:

private:

};

#endif // ARISTA_H
