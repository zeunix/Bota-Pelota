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
arma::frowvec pos3 = { 0,0,0 };

float posicion = 0;
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

	std::vector< Face > pared1Caras = pared1.faces;
	std::vector< Face > pared2Caras = pared2.faces;
	std::vector< Face > EsferaCaras = EsferaO.faces;

	Transform Tr = Transform();
	float radio;
	

	//Paredes	
	
	arma::fmat transformacion = Tr.S(0.3, 0.3, 0.3) * Tr.R(0, 1, 0, -90.0) * Tr.T(pos1[0], pos1[1], pos1[2]);
	//Transformacion, caras, colores, S, V
	radio = pared1.biggestOne;
	Pared paredObj1 = Pared(transformacion, pared1Caras, { 1.0, 1.0, 0.0 }, 0.7, 0, pos1, radio);
	paredObj1.mueve(transformacion);
	
	arma::fmat transformacion2 = Tr.S(0.3, 0.3, 0.3) * Tr.R(0, 1, 0, -90.0) * Tr.T(pos2[0], pos2[1], pos2[2]);
	//Transformacion, caras, colores, S, V
	radio = pared2.biggestOne;
	Pared paredObj2 = Pared(transformacion2, pared2Caras, { 0.0, 1.0, 1.0 }, 0.7, 0, pos2, radio);
	paredObj2.mueve(transformacion2);

	arma::fmat transformacion3 = Tr.S(0.1, 0.1, 0.1) * Tr.R(0, 1, 0, -90.0) * Tr.T(pos3[0], pos3[1], pos3[2]);
	//Transformacion, caras, colores, S, V
	radio = EsferaO.biggestOne;
	Esfera EsferaObj = Esfera(transformacion3, EsferaCaras, { 0.0, 1.0, 0.0 }, 0.7, 0, pos3, radio);
	EsferaObj.mueve(transformacion3);


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


	//  Proyecci�n en perspectiva
	//glFrustum(-ar, ar, -ar, ar, 0.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	do {
			
		//Mueve camara
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
		
		

		gluLookAt(eye[0], eye[1], eye[2],
			camera[0], camera[1], camera[2],
			0.0, 1.0, 0.0);
		
	
		// Dibujar el pokemon

		vector<Face> carasIluminadas = paredObj1.iluminacion(DOP);
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


		vector<Face> carasIluminadas2 = paredObj2.iluminacion(DOP);
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



		vector<Face> carasIluminadas3 = EsferaObj.iluminacion(DOP);
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

	
		// paredObj2.dibujarPared(pos2, DOP);
		

		/*
		// Dibujar la pokebola[0].vertices[0].getVertex();
		posicion_pokemon = pokemon.faces[200].vertices[0].getVertex();
		std::vector< Vertex > pokebola_vertices = pokebola.lanza(transf, pokemon.radio, posicion_pokemon);

		glColor3f(pokebola.color[0], pokebola.color[1], pokebola.color[2]);
		glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < pokebola_vertices.size(); i++) {
			arma::frowvec vert = pokebola_vertices[i].getVertex();
			glVertex3f(vert[0], vert[1], vert[2]);
		}
		glEnd();
		// Fin dibujado de la pokebola

		*/

		 /*
			//Checa si lo atrapo
		if (pokebola.atrapa)
		{
			std::cout << "ATRAPADO" << endl;

			/*glfwTerminate();
			fflush(stdin);
			getchar();

			return 0;
		}*/


		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);



	glfwTerminate();

	return 0;
}