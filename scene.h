#ifndef SCENE_H
#define SCENE_H

#include <object.h>
#include <vao.h>
#include <texture.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>


class Scene : public Object
{
	protected:
		// Luces
		GLfloat light_ambient[4];
		GLfloat light_diffuse[4];
		GLfloat light_specular[4];
		GLfloat light_position[4];

	public:
		// Constructor
		Scene ();

		// Dibujar
		void draw () const;

		// Animar escena
		void animate ();

		// Destructor
		~Scene ();
};

#endif // SCENE_H
