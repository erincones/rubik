#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
#include <iostream>


class Texture
{
	private:
		// Identificador y detalles de textura
		GLuint texture;
		GLsizei width;
		GLsizei height;

		// Construye la textura
		void build (GLubyte *const image);

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
