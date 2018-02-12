#ifndef STICKER_H
#define STICKER_H

#include <vao.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Sticker
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

	private:
		// Constantes matematicas
		static const GLdouble scale;
		static const double PI_2;
		static const double PI;

		// Vertex Array Object
		static VAO *vao;

		// Color, ubicacion y rotacion
		glm::dvec3 pos;
		glm::dquat rot;

		// Material
			   glm::vec4 color;
		static GLfloat ambient[4];
			   GLfloat diffuse[4];
		static GLfloat specular[4];
		static GLfloat shininess;

		// Direccion y color
		Sticker::FACE side;
		Sticker::COLOR type;

	public:
		// Constructor
		Sticker (const Sticker::FACE &dir = Sticker::NONE);

		// Dibujar
		void draw () const;

		// Direccion y color
		Sticker::FACE face () const;
		Sticker::COLOR tone () const;

		// Rotar cara
		void turn (const Sticker::AXIS &dir);

		// Asigna el VAO
		static void setVAO (VAO *const sticker);

		// Asigna el color
		void setColor (const GLfloat &r, const GLfloat &g, const GLfloat &b);
};

#endif // STICKER_H
