#ifndef GUI_H
#define GUI_H

#include <flatobject.h>
#include <object.h>
#include <vao.h>
#include <texture.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class GUI : public Object
{
	protected:
		// Distancia entre botones y borde
		static GLfloat gap;
		static GLfloat border;

		// Botones y paneles
		FlatObject *help;
		FlatObject *conf;
		FlatObject *sound;
		FlatObject *window;
		FlatObject *quit;
		FlatObject *mix;
		FlatObject *solve;

	public:
		// COnstructor
		GUI ();

		// Redimensionar
		void resize ();

		// Dibujar
		void draw () const;

		// Destructor
		~GUI ();
};

#endif // GUI_H
