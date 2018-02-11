#ifndef CUBE_H
#define CUBE_H

#include <sticker.h>
#include <vao.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Cube
{
	private:
		// Dimension y separacion entre cubos
		static const GLdouble scale;
		static const GLdouble gap;

		// Rotacion
		static const double PI_2;
		static const double step;
		double angle;

		// Vertex Array Object
		const VAO *vao;

		// Ubicacion y rotacion
		glm::dvec3 pos;
		glm::dquat rot_0;
		glm::dquat rot_1;

		// Material
		glm::vec4 color;
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat shininess;

		// Etiquetas de color
		Sticker *face_x;
		Sticker *face_y;
		Sticker *face_z;

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
		Cube (const VAO *const cube, const VAO *const sticker, const GLubyte &location, const glm::vec4 &colorRGBA);

		// Dibujar
		void draw () const;

		// Asigna el color
		void setColor (const GLfloat &r, const GLfloat &g, const GLfloat &b);

		// Valida la direccion de caras visibles
		bool face (const Sticker::FACE &side) const;

		// Obtiene el color de la cara
		Sticker::COLOR tone (const Sticker::FACE &side);

		// Rotar y animar cubo
		void turn (const Cube::AXIS &dir);
		bool animate(const Cube::AXIS &dir);
		void turnFaces (const Sticker::AXIS &dir);

		// Destructor
		~Cube ();
};

#endif // CUBE_H
