#ifndef SCENE_H
#define SCENE_H

#include <vao.h>
#include <texture.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>


class Scene
{
	private:
		// Modelo del escenario
		VAO *vao;
		Texture *texture;

		// Posicion y rotacion
		glm::dvec3 pos;
		glm::dquat rot;

		// Material
		glm::vec4 color;
		GLfloat scene_ambient[4];
		GLfloat scene_diffuse[4];
		GLfloat scene_specular[4];
		GLfloat scene_shininess;

		// Luces
		GLfloat light_ambient[4];
		GLfloat light_diffuse[4];
		GLfloat light_specular[4];
		GLfloat light_position[4];

	public:
		// Constructor
		Scene (const std::string &path);

		// Asignar textura
		bool setTexture (const std::string &path);

		// Dibujar
		void draw () const;

		// Animar escena
		void animate ();

		// Destructor
		~Scene ();
};

#endif // SCENE_H
