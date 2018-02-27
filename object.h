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

		// Variables estaticas de ventana
		static GLint win_w;
		static GLint win_h;

		// Variables estaticas de proyeccion
		static const GLfloat fovy_factor;
		static GLfloat proj_fovy;
		static GLfloat proj_zFar;
		static GLfloat proj_zNear;
		static GLfloat proj_aspect;
		static GLfloat proj_w;
		static GLfloat proj_h;


		// Directorio de busqueda de archivos
		static std::string path;

		// Variables estaticas de animacion
		static GLint fps;
		GLfloat speed;
		GLfloat step;

		// Tipo de modelo
		bool ortho;
		bool hd;

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

		// Rotacion
		glm::quat rot_0;
		glm::quat rot_1;
		glm::vec3 point_0;
		glm::vec3 point_1;
		glm::quat *rot_ref;

		// Escala
		glm::vec3 scale_0;
		glm::vec3 scale_1;

		// Material
		glm::vec4 color;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		GLfloat shininess;


		// Proyecta punto en virtual trackball
		glm::vec3 projectToSphere (const int &x, const int &y);


	public:
		// Manejo de proyecciones
		static void perspective ();
		static void orthogonal ();

		// Actualiza las propiedades de la ventana
		static void setWindow (const GLfloat &w, const GLfloat &h, const GLfloat &fovy, const GLfloat &zNear, const GLfloat &zFar);

		// Asigna la cantidad de cuadros por segundo
		static void setFPS (const GLint &fraps);

		// Click-and-drag
		void dragBegin (const int &x, const int &y);
		void dragEnd (const int &x, const int &y);

		// Rotacion
		void rotateBegin (const int &x, const int &y);
		void rotateEnd (const int &x, const int &y);

		// Zoom
		void zoomIn ();
		void zoomOut ();

		// Asigna el directorio de archivos
		static void setPath (const std::string &dir);


		// Retorna apuntador a rotacion
		glm::quat *rotPointer ();


		// Metodo virtual puro dibujar
		virtual void draw () const = 0;

		// Carga el material
		void loadMaterial () const;


		// Desctructor virtual puro
		virtual ~Object () = 0;

};

#endif // OBJECT_H
