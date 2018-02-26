#ifndef RUBIK_H
#define RUBIK_H

#include <minicube.h>
#include <sticker.h>
#include <cube.h>
#include <object.h>
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
#include <fmodp.h>

class Rubik : public Object
{
	public:
		//sistema de sonido
		fmodp *sound = NULL;
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

	protected:
		// Datos
		GLsizei dim;
		Cube *cube[27];

		// Cola de rotaciones
		std::queue<Cube::AXIS> move;
		std::queue<std::vector<Cube *> > target;


	public:
		// Constructor
		Rubik ();

		// Dibujar
		void draw () const;

		// Animar cubo
		void animate ();

		// Jugar
		void play (const Rubik::STEP &step);
		bool win () const;

		// Imprimir estado
		void print () const;

		// Destructor
		~Rubik ();
};

#endif // RUBIK_H
