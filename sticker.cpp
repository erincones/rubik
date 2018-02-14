#include <sticker.h>

// Inicializa constantes estaticas
const GLdouble Sticker::scale = 0.5L;
const double Sticker::PI_2 = 1.57079632679489661923;
const double Sticker::PI   = 3.14159265358979323846;

// Constructor
Sticker::Sticker (const FACE &dir, VAO *const sticker, Texture *const img) : vao(sticker), texture(img), side(dir)
{
	switch (side)
	{
		// Arriba
		case Sticker::UP:
			pos.y = Sticker::scale;

			// Blanco
			type = Sticker::WHITE;
			color = glm::dvec4(0.8L, 0.8L, 0.8L, 1.0L);
			break;

		// Abajo
		case Sticker::DOWN:
			pos.y = -Sticker::scale;
			rot = glm::angleAxis(Sticker::PI, glm::dvec3(1.0L, 0.0L, 0.0L));

			// Amarillo
			type = Sticker::YELLOW;
			color = glm::dvec4(0.8L, 0.8L, 0.0L, 1.0L);
			break;

		// Izquierda
		case Sticker::LEFT:
			pos.x = -Sticker::scale;
			rot = glm::angleAxis(Sticker::PI_2, glm::dvec3(0.0L, 0.0L, 1.0L));

			// Naranja
			type = Sticker::ORANGE;
			color = glm::dvec4(0.8L, 0.376L, 0.0L, 1.0L);
			break;

		// Derecha
		case Sticker::RIGHT:
			pos.x = Sticker::scale;
			rot = glm::angleAxis(-Sticker::PI_2, glm::dvec3(0.0L, 0.0L, 1.0L));

			// Rojo
			type = Sticker::RED;
			color = glm::dvec4(0.8L, 0.0L, 0.0L, 1.0L);
			break;

		// Fente
		case Sticker::FRONT:
			pos.z = Sticker::scale;
			rot = glm::angleAxis(Sticker::PI_2, glm::dvec3(1.0L, 0.0L, 0.0L));

			// Verde
			type = Sticker::GREEN;
			color = glm::dvec4(0.0L, 0.8L, 0.0L, 1.0L);
			break;

		// Atras
		case Sticker::BACK:
			pos.z = -Sticker::scale;
			rot = glm::angleAxis(-Sticker::PI_2, glm::dvec3(1.0L, 0.0L, 0.0L));

			// Azul
			type = Sticker::BLUE;
			color = glm::dvec4(0.0L, 0.0L, 0.8L, 1.0L);
			break;

		// Ninguno
		case Sticker::NONE:
			type = Sticker::BLACK;
			color = glm::dvec4(0.0L, 0.0L, 0.0L, 1.0L);
			break;
	}

	// Material
	ambient[0] = ambient[1] = ambient[2] = 0.5F; ambient[3] = 1.0F;
	diffuse[0] = color.r; diffuse[1] = color.g; diffuse[2] = color.b; diffuse[3] = 1.0F;
	specular[0] = specular[1] = specular[2] = 0.2F; specular[3] = 1.0F;
	shininess = 64.0L;
}

// Dibujar
void Sticker::draw () const
{
	if (side == Sticker::NONE) return;

	// Copio la matriz actual
	glPushMatrix();

	// Transformaciones
	glTranslated(pos.x, pos.y, pos.z);
	glMultMatrixd(glm::value_ptr(glm::mat4_cast(rot)));

	// Material
	glColor3d(color.r, color.g, color.b);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	// Dibujar objeto
	if (texture != NULL) texture->enable();
	vao->draw();
	if (texture != NULL) texture->disable();

	// Regresa a la matriz anterior
	glPopMatrix();
}


// Obtiene el lado de la cara
Sticker::FACE Sticker::face () const
{
	return side;
}

// Obtiene el tono de color
Sticker::COLOR Sticker::tone () const
{
	return type;
}

// Rotar cara
void Sticker::turn(const Sticker::AXIS &dir)
{

	if ((dir == Sticker::X0 && side == Sticker::FRONT) ||
		(dir == Sticker::Z0 && side == Sticker::LEFT ) ||
		(dir == Sticker::X1 && side == Sticker::BACK ) ||
		(dir == Sticker::Z1 && side == Sticker::RIGHT)) {side = Sticker::UP;    return;}

	if ((dir == Sticker::X0 && side == Sticker::BACK ) ||
		(dir == Sticker::Z0 && side == Sticker::RIGHT) ||
		(dir == Sticker::X1 && side == Sticker::FRONT) ||
		(dir == Sticker::Z1 && side == Sticker::LEFT))  {side = Sticker::DOWN;  return;}

	if ((dir == Sticker::Y0 && side == Sticker::FRONT) ||
		(dir == Sticker::Z0 && side == Sticker::DOWN ) ||
		(dir == Sticker::Y1 && side == Sticker::BACK ) ||
		(dir == Sticker::Z1 && side == Sticker::UP   )) {side = Sticker::LEFT;  return;}

	if ((dir == Sticker::Y0 && side == Sticker::BACK ) ||
		(dir == Sticker::Z0 && side == Sticker::UP   ) ||
		(dir == Sticker::Y1 && side == Sticker::FRONT) ||
		(dir == Sticker::Z1 && side == Sticker::DOWN )) {side = Sticker::RIGHT; return;}

	if ((dir == Sticker::X0 && side == Sticker::DOWN ) ||
		(dir == Sticker::Y0 && side == Sticker::RIGHT) ||
		(dir == Sticker::X1 && side == Sticker::UP   ) ||
		(dir == Sticker::Y1 && side == Sticker::LEFT )) {side = Sticker::FRONT; return;}

	if ((dir == Sticker::X0 && side == Sticker::UP   ) ||
		(dir == Sticker::Y0 && side == Sticker::LEFT ) ||
		(dir == Sticker::X1 && side == Sticker::DOWN ) ||
		(dir == Sticker::Y1 && side == Sticker::RIGHT)) {side = Sticker::BACK;  return;}
}

// Asigna el color
void Sticker::setColor(const glm::vec4 &tone)
{
	color = tone;
	diffuse[0] = color.r; diffuse[1] = color.g; diffuse[2] = color.b; diffuse[3] = 1.0F;
}

