#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
#include <iostream>


class Texture
{
	protected:
		// Identificador y detalles de textura
		GLuint texture;

		// Construye la textura
		void build (GLubyte *const image, const GLsizei &width, const GLsizei &height);


	public:
		// Constructor
		Texture (const std::string &path = "");

		// Habilita y desabilita la textura
		void enable () const;
		void disable () const;

		// Destructor
		~Texture ();
};

#endif // TEXTURE_H
