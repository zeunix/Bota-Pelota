#pragma once
///Clase parcial para declarar un punto de la trayectoria de la pelora
class Point {
public:
	float x, y, z;
	void setxyz(float x2, float y2, float z2) { x = x2; y = y2; z = z2; }
	const Point& operator=(const Point& rPoint) {
		x = rPoint.x;
		y = rPoint.y;
		z = rPoint.z;
		return *this;
	}
};

