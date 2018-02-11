#ifndef VAO_H
#define VAO_H

#include <SOIL.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>


#include <vector>

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cctype>


// Macro auxiliar de OpenGL
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(i) ((const void *) (i))
#endif

class VAO
{
	private:
		// Indentificadores
		GLuint vao;
		GLuint vbo;

		// Dimensiones
		GLsizei vertices;

		// Cargar datos
		void load (const std::vector<glm::vec3> &vertex, const std::vector<glm::vec3> &normal, const std::vector<glm::vec2> &texture);


	public:
		// Constructor
		VAO (const std::string &path);

		// Dibujar
		void draw () const;

		// Destructor
		~VAO ();
};

#endif // VAO_H
