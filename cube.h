#ifndef CUBE_H
#define CUBE_H

#include <sticker.h>
#include <vao.h>
#include <texture.h>
#include <object.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Cube : virtual public Object
{
	protected:
		// Geometria estatica para los cubos
		static VAO *cube_sd;
		static VAO *cube_hd;

		// Dimension y separacion entre cubos
		static GLfloat size;
		static GLfloat gap;

		// Angulo acumulado en animacion
		GLfloat angle;

		// Etiquetas de color por cara
		Sticker *sticker[6];
		Sticker *visible[3];

		// Opciones de dibujado
		bool drawable;


	public:
		// Eje de rotacion
		/***
		 * X: Eje x    0: Sentido de las agujas del reloj
		 * Y: Eje y    1: Sentido contrario a las agujas del reloj
		 * Z: Eje z
		 */
		enum AXIS
		{
			X0, Y0, Z0,
			X1, Y1, Z1
		};

		// Constructor
		Cube (const GLubyte &location = 0x15);

		// Dibujar
		void draw () const;

		// Valida la direccion de caras visibles
		bool face (const Sticker::FACE &side) const;

		// Obtiene el color de la cara
		Sticker::COLOR tone (const Sticker::FACE &side) const;

		// Rotar y animar cubo
		void turn (const Cube::AXIS &dir);
		bool animate(const Cube::AXIS &dir);
		void turnFaces (const Sticker::AXIS &dir);

		// Destructor
		~Cube ();

		// Clase amiga Rubik
		friend class Rubik;
};

#endif // CUBE_H
