// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <gl/glut.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "Lector.h"
#include "Objeto.h"
#include "Transform.h"
#include "Pared.h"
#include "Esfera.h"

arma::frowvec eye = { -10.0, 0.5, 0.0 };
arma::frowvec camera = { 0.0, 0.0, 0.0 };
arma::frowvec DOP = arma::normalise(camera - eye);


arma::frowvec pos1 = { -3,0,0};
arma::frowvec pos2 = { 3,0,0 };
arma::frowvec pos3 = { 3,0,0 };

float posicion = 0;
float t = 0;
float aumento = 0.005;
bool bandWall = false;

using namespace std;



 int main(void)
 {
	float angley = 0.0;

	GLFWwindow* window;

	Lector LectorPared = Lector("pared.obj");
	Lector LectorPared2 = Lector("pared.obj");
	Lector LectorEsfera = Lector("pelota.obj");

	LectorPared.read();
	LectorPared2.read();
	LectorEsfera.read();

	Objeto pared1 = LectorPared.objetos[0];
	Objeto pared2 = LectorPared2.objetos[0];
	Objeto EsferaO = LectorEsfera.objetos[0];

	std::vector< Caras > pared1Caras = pared1.faces;
	std::vector< Caras > pared2Caras = pared2.faces;
	std::vector< Caras > EsferaCaras = EsferaO.faces;

	Transform Tr = Transform();
	float radio;
	

	//Paredes	
	
	arma::fmat transformacion = Tr.S(0.3, 0.3, 0.3) * Tr.R(0, 1, 0, -90.0) * Tr.T(pos1[0], pos1[1], pos1[2]);
	//Transformacion de la pared
	radio = pared1.punto;
	Pared paredObj1 = Pared(transformacion, pared1Caras, { 1.0, 1.0, 0.0 }, 0.7, 0, pos1, radio);
	paredObj1.movimiento(transformacion);
	
	arma::fmat transformacion2 = Tr.S(0.3, 0.3, 0.3) * Tr.R(0, 1, 0, -90.0) * Tr.T(pos2[0], pos2[1], pos2[2]);

	radio = pared2.punto;
	Pared paredObj2 = Pared(transformacion2, pared2Caras, { 0.0, 1.0, 1.0 }, 0.7, 0, pos2, radio);
	paredObj2.movimiento(transformacion2);

	//Transformacion de la pelota
	arma::fmat transformacion3 = Tr.S(0.1, 0.1, 0.1) * Tr.R(0, 1, 0, -90.0) * Tr.T(pos3[0] += 0.1, pos3[1], pos3[2]);

	if (!glfwInit())
	{
		fprintf(stderr, "Fallo al inicializar GLFW\n");
		getchar();
		return -1;
	}

	window = glfwCreateWindow(1024, 768, "Bota Pelota", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Fallo al abrir la ventana de GLFW.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

	//  Proyecciones
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	float ar = width / height;

	//  Proyecci�n en paralelo
	glViewport(0, 0, width, height);
	glOrtho(-ar, ar, -1.0, 1.0, -40.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	do {
			
		//Velocidad de la pelota
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			aumento += 0.001;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			if (aumento > 0) {
				aumento -= 0.001;
			}
			else {
				aumento += 0.001;
			}
		}
		//Manejo de la camara
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		{
			arma::fcolvec transeye = { {eye[0]}, {eye[1]}, {eye[2]} ,{1.0} };
			arma::fmat rotarcamara = Tr.R(0.0, 1.0, 0.0, -5.0);
			arma::fcolvec res = rotarcamara * transeye;
			eye = { res[0], res[1], res[2] };
			DOP = arma::normalise(camera - eye);


		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			arma::fcolvec transeye = { {eye[0]}, {eye[1]}, {eye[2]} ,{1.0} };
			arma::fmat rotarcamara = Tr.R(0.0, 1.0, 0.0, 5.0);
			arma::fcolvec res = rotarcamara * transeye;
			eye = { res[0], res[1], res[2] };
			DOP = arma::normalise(camera - eye);


		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			arma::fcolvec transeye = { {eye[0]}, {eye[1]}, {eye[2]} ,{1.0} };
			float angle = 2.0;
			if (angley >= 76.0) {
				angle = 0.0;
			}
			angley += angle;
			arma::fmat rotarcamara = Tr.R(0.0, 0.0, 1.0, angle);
			arma::fcolvec res = rotarcamara * transeye;
			eye = { res[0], res[1], res[2] };
			DOP = arma::normalise(camera - eye);


		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		{
			arma::fcolvec transeye = { {eye[0]}, {eye[1]}, {eye[2]} ,{1.0} };
			float angle = -2.0;
			if (angley <= -50.0) {

				angle = 0.0;
			}
			angley += angle;
			arma::fmat rotarcamara = Tr.R(0.0, 0.0, 1.0, angle);
			arma::fcolvec res = rotarcamara * transeye;
			eye = { res[0], res[1], res[2] };
			DOP = arma::normalise(camera - eye);

			 
		}
		

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		gluLookAt(eye[0], eye[1], eye[2],camera[0], camera[1], camera[2],0.0, 1.0, 0.0);
		
		//Dibujando las paredes
		//Pared 1
		vector<Caras> carasIluminadas = paredObj1.iluminacion(DOP);
		vector<arma::frowvec> color = paredObj1.colorear(carasIluminadas);

		
		glBegin(GL_TRIANGLES);
	
		for (unsigned int i = 0; i < carasIluminadas.size(); i++) {
			glColor3f(color[i][0], color[i][1], color[i][2]);
			for (int j = 0; j < 3; j++) {
				arma::frowvec vert = carasIluminadas[i].vertices[j].getVertex();
				glVertex3f(vert[0], vert[1], vert[2]);
			}
			
		}
		glEnd();

		//Pared 2
		vector<Caras> carasIluminadas2 = paredObj2.iluminacion(DOP);
		vector<arma::frowvec> color2 = paredObj2.colorear(carasIluminadas2);
		
		glBegin(GL_TRIANGLES);

		for (unsigned int i = 0; i < carasIluminadas2.size(); i++) {
			glColor3f(color2[i][0], color2[i][1], color2[i][2]);
			for (int j = 0; j < 3; j++) {
				arma::frowvec vert = carasIluminadas2[i].vertices[j].getVertex();
				glVertex3f(vert[0], vert[1], vert[2]);
			}
			
		}
		glEnd();

		//Dibujando la pelota
		radio = EsferaO.punto;
		Esfera EsferaObj = Esfera(transformacion3, EsferaCaras, { 0.0, 1.0, 0.0 }, 0.7, 0, pos3, radio);
		EsferaObj.movimiento(transformacion3);
		EsferaObj.setTrayectoriaIZQ();
		EsferaObj.setTrayectoriaDER();

		vector<Caras> carasIluminadas3 = EsferaObj.iluminacion(DOP);		
		vector<arma::frowvec> color3 = EsferaObj.colorear(carasIluminadas3);

		glBegin(GL_TRIANGLES);

		for (unsigned int i = 0; i < carasIluminadas3.size(); i++) {
			glColor3f(color3[i][0], color3[i][1], color3[i][2]);
			for (int j = 0; j < 3; j++) {
				arma::frowvec vert = carasIluminadas3[i].vertices[j].getVertex();
				glVertex3f(vert[0], vert[1], vert[2]);
			}
		}
		glEnd();

		float xB,yB,zB;//nueva posicion de la pelota en la trayectoria
		
		if (!bandWall) {//trayectoria IZQ
			if (t <= 1.0) {

				Point P = EsferaObj.Bezier(EsferaObj.izq[0], EsferaObj.izq[1], EsferaObj.izq[2], EsferaObj.izq[3], t);
				xB = P.x;
				yB = P.y;
				zB = P.z;			
				transformacion3 = Tr.S(0.1, 0.1, 0.1) * Tr.R(0, 1, 0, -90.0) * Tr.T(xB, yB, zB);
			}
			else {
				bandWall = true;				
				t = 0.0;
			}
		}
		else {//Trayectoria Der
			if (t <= 1.0) {
				Point P = EsferaObj.Bezier(EsferaObj.der[3], EsferaObj.der[2], EsferaObj.der[1], EsferaObj.der[0], t);
				xB = P.x;
				yB = P.y;
				zB = P.z;				
				transformacion3 = Tr.S(0.1, 0.1, 0.1) * Tr.R(0, 1, 0, -90.0) * Tr.T(xB, yB, zB);
			}
			else {
				bandWall = false;				
				t = 0.0;
			}
		}
		t +=aumento;

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);



	glfwTerminate();

	return 0;
}