#include <minicube.h>

// Constructor
Minicube::Minicube (Object *parent, const FlatObject::POSITION2D &pos) : Cube(), rot_ref(parent->rot())
{
	// Debe dibujarse
	drawable = true;

	// Escala y ubicacion
	origin = pos;
	scale_0 = glm::vec3(0.075F);
	offset_0 = glm::vec3(0.050F, 0.050F, 0.0F);

	// Crea cada calcomania con las texturas
	for (GLubyte i = 0; i < 6; i++)
	{
		const Sticker::FACE dir = (Sticker::FACE) i;

		sticker_texture[dir] = new Texture(path + "/minicube_" + std::string(1, i + '0') + ".png");

		sticker[dir]->side = dir;
		sticker[dir]->color = glm::vec4(1.0F);
		sticker[dir]->diffuse = glm::vec4(1.0F);
		sticker[dir]->texture_0 = sticker_texture[i];
	}

	// Color
	color = glm::vec4(0.08F, 0.08F, 0.08F, 1.0F);
}


void Minicube::draw() const
{
	// Respaldo la matriz actual
	glPushMatrix();
	glLoadIdentity();

	// Transformaciones
	glColor4f(color.r, color.g, color.b, color.a);
	glTranslatef(pos_1.x, pos_1.y, 0.0F);
	glMultMatrixf(glm::value_ptr(glm::mat4_cast(rot_ref)));
	glScalef(scale_1.x, scale_1.y, scale_1.z);

	// Dibujar caras
	for (GLubyte i = 0; i < 6; i++)
	{
		sticker[i]->draw();
	}

	// Carga material y dibujar objeto
	loadMaterial();
	Texture::disable();
	Cube::cube_0->draw();

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

