#ifndef FLATOBJECT_H
#define FLATOBJECT_H

#include <object.h>
#include <vao.h>
#include <texture.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class FlatObject : virtual public Object
{
	public:
		enum POSITION2D {UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};

	protected:
		// Posicion 2D
		FlatObject::POSITION2D origin;

		// Bandera
		bool active;


	public:
		// Constructores
		FlatObject (VAO *const vao = NULL, const std::string &tex_0 = "", const std::string &tex_1 = "");

		// Dibujar
		void draw () const;

		// Actualiza la posicion ortogonal
		void resize ();

		friend class GUI;
};

#endif // FLATOBJECT_H
