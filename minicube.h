#ifndef MINICUBE_H
#define MINICUBE_H

#include <sticker.h>
#include <vao.h>
#include <texture.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Minicube
{
	private:
		// Constantes matematicas
		static const GLdouble fov_factor;
		static const GLdouble PI_2;

		// Vertex Array Object
		VAO *vao_sd;
		VAO *vao_hd;

		// Caracas y texturas
		Sticker *face[6];
		Texture *texture[6];

		// Escala, posicion y rotacion
		GLint offset;
		glm::dvec3 pos;
		glm::dquat *const rot;

		// Material
		glm::vec4 color;
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat shininess;

		// Informacion de pantalla
		GLint width;
		GLint height;
		GLdouble fov;
		GLdouble far;
		GLdouble near;
		GLdouble aspect;

		// Cambia la proyeccion
		void enable_ortho  () const;
		void disable_ortho () const;


	public:
		// Constructor
		Minicube (const std::string &path, glm::dquat *const parent_rot, VAO *const cube_sd = NULL, VAO *const cube_hd = NULL, VAO *const sticker = NULL);

		// Asigna informacion de la pantalla
		void setScreenInfo (const GLint &screen_width, const GLint &screen_height, const GLdouble &fovy, const GLdouble &zNear, const GLdouble &zFar);

		// Dibujar
		void draw () const;

		// Destructor
		~Minicube ();

		// Clase amiga Rubik
		friend class Rubik;
};

#endif // MINICUBE_H
