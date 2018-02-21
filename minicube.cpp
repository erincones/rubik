#include <minicube.h>

// Constructor
Minicube::Minicube (Object *parent, const Object::POSITION2D &pos) : Cube()
{
	// Se usa proyeccion ortogonal
	ortho = true;

	// Rotacion y ubicacion
	pos_2d = pos;
	scale_0 = glm::vec2(0.075F);
	offset_0 = glm::vec2(0.050F);
	rot_ref = parent->rotPointer();
	updateOrthoPosition();

	// Crea cada calcomania con las texturas
	for (GLubyte i = 0; i < 6; i++)
	{
		const Sticker::FACE dir = (Sticker::FACE) i;

		sticker_texture[dir] = new Texture(path + "/minicube_" + std::string(1, i + '0') + ".png");

		sticker[dir]->side = dir;
		sticker[dir]->color = glm::vec4(1.0F);
		sticker[dir]->diffuse = glm::vec4(1.0F);
		sticker[dir]->texture_sd = sticker_texture[i];
	}

	// Debe dibujarse
	drawable = true;
}


void Minicube::draw() const
{
	// Respaldo la matriz actual
	glPushMatrix();
	glLoadIdentity();

	// Transformaciones
	glTranslatef(pos_1.x, pos_1.y, 0.0F);
	glMultMatrixf(glm::value_ptr(glm::mat4_cast(*rot_ref)));
	glScalef(scale_1.x, scale_1.y, scale_1.y);

	// Dibujar caras
	for (GLubyte i = 0; i < 6; i++)
	{
		sticker[i]->draw();
	}

	// Carga material y dibujar objeto
	loadMaterial();
	Cube::cube_sd->draw();

	// Regresa a la matriz anterior
	glPopMatrix();
}

// Destructor
Minicube::~Minicube()
{
	for (GLubyte i = 0; i < 6; i++)
	{
		delete sticker_texture[i];
	}
}

