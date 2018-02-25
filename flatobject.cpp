#include <flatobject.h>

// Constructores
FlatObject::FlatObject (VAO *const vao, const std::string &tex_0, const std::string &tex_1)
{
	// Inicia desactivado
	active = false;

	// Vertex Array Object y textura
	vao_0 = vao;
	texture_0 = (tex_0.empty() ? NULL : new Texture(path + tex_0));
	texture_1 = (tex_1.empty() ? NULL : new Texture(path + tex_1));

	// Color
	color = glm::vec4(1.0F);
}

void FlatObject::draw() const
{
	// Respaldo la matriz actual
	glPushMatrix();
	glLoadIdentity();

	// Transformaciones
	glColor4f(color.r, color.g, color.b, color.a);
	glTranslatef(pos_1.x, pos_1.y, 0.0F);
	glScalef(scale_1.x, scale_1.y, 0.0F);

	// Dibujar objeto
	active ? texture_1->enable() : texture_0->enable();
	vao_0->draw();
	texture_0->disable();

	// Regresa a la matriz anterior
	glPopMatrix();
}

// Actualiza la posicion ortogonal
void FlatObject::resize ()
{
	// Actualiza valores
	scale_1 = (GLfloat) Object::win_h * scale_0;
	offset_1 = (GLfloat) Object::win_h * offset_0;

	// Reubicacion
	const int ori = (int) origin;
	const glm::vec2 mid = scale_1 / 2.0F;
	pos_1.x = ((ori & 1) == 0 ? offset_1.x + mid.x : (GLfloat) Object::win_w - offset_1.x - mid.x);
	pos_1.y = ((ori & 2) == 2 ? offset_1.y + mid.y : (GLfloat) Object::win_h - offset_1.y - mid.y);
}
