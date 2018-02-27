#ifndef STICKER_H
#define STICKER_H

#include <vao.h>
#include <texture.h>
#include <object.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Sticker : public Object
{
	public:
		// Cara de la etiqueta
		/***
		 * UP:    Arriba      DOWN:  Abajo
		 * LEFT:  Izquierda	  RIGHT: Derecha
		 * FRONT: Frente      BACK:  Atras
		 */
		enum FACE {UP, DOWN, LEFT, RIGHT, FRONT, BACK, NONE};

		// Color de la etiqueta
		enum COLOR {WHITE, YELLOW, ORANGE, RED, GREEN, BLUE, BLACK};


		// Eje de rotacion
		/***
		 * X: Eje x    0: Sentido de las agujas del reloj
		 * Y: Eje y    1: Sentido contrario a las agujas del reloj
		 * Z: Eje z
		 */
		enum AXIS
		{
			X1, Y1, Z1,
			X0, Y0, Z0
		};

	protected:
		// Geometria estatica para etiquetas
		static VAO *sticker_sd;

		// Desplazamiento respecto del cubo
		static GLfloat offset;


		// Direccion y color
		Sticker::FACE side;
		Sticker::COLOR type;


	public:
		// Constructor
		Sticker (const Sticker::FACE &dir = Sticker::NONE, Texture *const img = NULL);

		// Dibujar
		void draw () const;

		// Direccion y color
		Sticker::FACE face () const;
		Sticker::COLOR tone () const;

		// Rotar cara
		void turn (const Sticker::AXIS &dir);



		// Clase amiga Cube, Rubik y Minicube
		friend class Cube;
		friend class Rubik;
		friend class Minicube;
};

#endif // STICKER_H
