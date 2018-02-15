#ifndef MINICUBE_H
#define MINICUBE_H

#include <cube.h>
#include <sticker.h>
#include <texture.h>
#include <object.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Minicube : public Cube
{
	protected:
		// Textura de cada etiqueta
		Texture *sticker_texture[6];

		// Distancia de los bordes
		glm::vec2 offset;

	public:
		// Constructor
		Minicube (Object *parent);

		// Actualizar posicion
		void updatePosition ();

		// Dibujar
		void draw () const;

		// Destructor
		~Minicube ();
};

#endif // MINICUBE_H
