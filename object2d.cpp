#include <object2d.h>

// Asigna el desplazamiento
void Object2D::setOffset (const GLfloat &x, const GLfloat &y, const Object2D::POSITION &pos)
{
	offset_0.x = x;
	offset_0.y = y;
	position = pos;
}

// Asigna escala
void Object2D::setScale (const GLfloat &w, const GLfloat &h)
{
	scale_0.x = w;
	scale_0.y = h;
}

// Acutlizar posicion
void Object2D::updatePosition ()
{
	// Actualiza valores
	offset_1 = (GLfloat) Object::win_h * offset_0;
	scale_1 = (GLfloat) Object::win_h * scale_0;

	// Reubicacion
	const int pos = (int) position;
	const glm::vec2 mid = scale_1 / 2.0F;
	pos_1.x = ((pos & 1) == 0 ? offset_1.x + mid.x : (GLfloat) Object::win_w - offset_1.x - mid.x);
	pos_1.y = ((pos & 2) == 2 ? offset_1.y + mid.y : (GLfloat) Object::win_h - offset_1.y - mid.y);
}
