#include <minicube.h>

// Constructor
Minicube::Minicube (Object *parent, const FlatObject::POSITION2D &pos) : rot_ref(parent->rot())
{
	// Carga la textura
	texture_0 = new Texture(Object::path + "/minicube.png");

	// Escala y ubicacion
	origin = pos;
	scale_0 = glm::vec3(0.075F);
	offset_0 = glm::vec3(0.050F, 0.050F, 0.0F);

	// Color
	color = glm::vec4(1.0F, 1.0F, 1.0F, 1.0F);
	ambient   = glm::vec4(0.00F, 0.00F, 0.00F, 1.0F);
	diffuse   = glm::vec4(1.00F, 1.00F, 1.00F, 1.0F);
	specular  = glm::vec4(1.00F, 1.00F, 1.00F, 1.0F);
	shininess = 64.0F;
}


void Minicube::draw () const
{
	// Respaldo la matriz actual
	glPushMatrix();
	glLoadIdentity();

	// Transformaciones
	glColor4f(color.r, color.g, color.b, color.a);
	glTranslatef(pos_1.x, pos_1.y, 0.0F);
	glMultMatrixf(glm::value_ptr(glm::mat4_cast(rot_ref)));
	glScalef(scale_1.x, scale_1.y, scale_1.z);

	// Carga material y dibujar objeto
	loadMaterial();
	texture_0->enable();
	Cube::cube_0->draw();

	// Regresa a la matriz anterior
	glPopMatrix();
}

Minicube::~Minicube ()
{
	delete texture_0;
}

