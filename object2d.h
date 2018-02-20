#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <object.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Object2D : virtual public Object
{
	public:
		enum POSITION {UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};

	protected:
		// Posicion relativa a la pantalla
		Object2D::POSITION position;

		// Escala
		glm::vec2 scale_0;
		glm::vec2 scale_1;

		// Desplazamiento
		glm::vec2 offset_0;
		glm::vec2 offset_1;

	public:
		// Asignar desplazamiento
		void setOffset (const GLfloat &x, const GLfloat &y, const Object2D::POSITION &pos);

		// Asignar escala
		void setScale (const GLfloat &w, const GLfloat &h);

		// Actualizar posicion
		void updatePosition ();
};

#endif // OBJECT2D_H
