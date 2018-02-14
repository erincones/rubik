#ifndef OBJECT_H
#define OBJECT_H

#include <vao.h>
#include <texture.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Object
{
	protected:
		// Constantes estaticas matematicas
		static const GLfloat PI;
		static const GLfloat PI_2;
		static const GLfloat SIN45;
		static const GLfloat SQRT2;

		// Variables estaticas de ventana
		static GLint win_w;
		static GLint win_h;

		// Variables estaticas de proyeccion
		static const GLfloat fov_factor;
		static GLfloat proy_fovy;
		static GLfloat proy_zFar;
		static GLfloat proy_zNear;
		static GLfloat proy_w;
		static GLfloat proy_h;
		static GLfloat proy_aspect;

		// Tipos
		bool hd;
		bool d2;

		// Vertex Array Object
		VAO *vao_sd;
		VAO *vao_hd;

		// Textura
		Texture *texture_sd;
		Texture *texture_hd;

		// Posicion
		GLfloat z_max;
		GLfloat z_min;
		glm::vec3 pos_0;
		glm::vec3 pos_1;
		glm::vec3 *pos_parent;

		// Rotacion
		glm::quat rot_0;
		glm::quat rot_1;
		glm::vec3 point_0;
		glm::vec3 point_1;
		glm::quat *rot_parent;
		GLfloat trackball_size;

		// Escala
		glm::vec3 scale_0;
		glm::vec3 scale_1;
		glm::vec3 *scale_parent;

		// Material
		glm::vec4 color;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		GLfloat shininess;

		// Proyecta punto en virtual trackball
		glm::vec3 projectToSphere (const glm::vec2 &point);


	public:
		Object();

		// Proyeccion ortogonal
		static void pushOrtho ();
		static void popOrtho ();

		// Actualiza las propiedades de la ventana
		void setWindow (const GLfloat &w, const GLfloat &h, const GLfloat &fovy, const GLfloat &zNear, const GLfloat &zFar);

		// Click-and-drag
		void dragBegin (const int &x, const int &y);
		void dragEnd (const int &x, const int &y);

		// Rotacion
		void rotateBegin (const int &x, const int &y);
		void rotateEnd (const int &x, const int &y);

		// Zoom
		void zoomIn ();
		void zoomOut ();


		// Metodo virtual dibujar
		virtual void draw () const;


		// Desctructor virtual puro
		virtual ~Object () = 0;

};

#endif // OBJECT_H
