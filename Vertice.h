#ifndef VERTICE_H
#define VERTICE_H
#include <iostream>
#include<vector>
#include <armadillo>

using namespace std;

class Vertice
{
public:
	
	Vertice();
	Vertice(float x_in, float y_in, float z_in);
	virtual ~Vertice();
	void inline print() { cout << x << "," << y << "," << z << endl; }
	arma::fcolvec homg();
	vector<float> getVertex();
	void setV(arma::frowvec);

	float getX();
	void setX(float val);
	float getY();
	void setY(float val);
	float getZ();
	void setZ(float val);

protected:

private:
	float x;
	float y;
	float z;

};

#endif // VERTICE_H
