#ifndef MINICUBE_H
#define MINICUBE_H

#include <cube.h>
#include <sticker.h>
#include <flatobject.h>
#include <object.h>
#include <texture.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


class Minicube : public Cube, public FlatObject
{
	protected:
		// Referencia de rotacion
		const glm::quat &rot_ref;

		// Textura de cada etiqueta
		Texture *sticker_texture[6];


	public:
		// Constructor
		Minicube (Object *parent, const FlatObject::POSITION2D &pos);

		// Dibujar
		void draw () const;

		// Destructor
		~Minicube ();
};

#endif // MINICUBE_H
