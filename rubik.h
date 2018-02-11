#ifndef RUBIK_H
#define RUBIK_H

#include <sticker.h>
#include <cube.h>
#include <vao.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <queue>

#include <iostream>

class Rubik
{
	public:
		// Pasos
		/***
		* Nomenclatura Singmaster
		* U: Arriba       M: Meridiano | Entre L y R
		* D: Abajo        E: Ecuador   | Entre U y D
		* L: Izquierda    S: Centro    | Entre F y B
		* R: Derecha
		* F: Frente       0: Sentido de las agujas del reloj
		* B: Atras        1: Sentido contrario a las agujas del reloj
		*/
		enum STEP
		{
			U0, D0, L0, R0, F0, B0,
			U1, D1, L1, R1, F1, B1
		};

	private:
		// Constantes matematicas
		static const GLdouble fov_factor;
		static const GLdouble PI_2;

		// Posicion
		glm::dvec3 pos_0;
		glm::dvec3 pos_1;

		// Rotacion
		glm::dquat rot;
		glm::dvec3 point_0;
		glm::dvec3 point_1;

		// Campo visual
		GLdouble fov;

		// Datos
		unsigned int dim;
		Cube *cube[27];

		// Vertex Array Objects
		VAO *cube_vao;
		VAO *sticker_vao;

		// Cola de rotaciones
		std::queue<Cube::AXIS> move;
		std::queue<std::vector<Cube *> > target;


		// Proyectar punto en esfera
		static glm::dvec3 projectToSphere (const int &x, const int &y);



	public:
		// Constructor
		Rubik (const std::string &path, const GLdouble &fov = 45.0L);

		// Dibujar
		void draw () const;

		// Animar cubo
		void animate ();

		// Imprimir estado
		void print () const;

		// Traslacion
		void drag_0 (const int &x, const int &y);
		void drag_1 (const int &x, const int &y);

		// Rotacion
		void rotate_0 (const int &x, const int &y);
		void rotate_1 (const int &x, const int &y);

		// Zoom
		void zoom (const bool &dir);

		// Jugar
		void play (const Rubik::STEP &step);
		bool win () const;

		// Destructor
		~Rubik ();
};

#endif // RUBIK_H