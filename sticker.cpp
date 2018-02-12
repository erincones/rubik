#include <sticker.h>

// Inicializa constantes estaticas
const GLdouble Sticker::scale = 0.5L;
const double Sticker::PI_2 = 1.57079632679489661923;
const double Sticker::PI   = 3.14159265358979323846;

// Geometria y material
VAO *Sticker::vao = NULL;
GLfloat Sticker::ambient[4]  = {0.50F, 0.50F, 0.50F, 1.0F};
GLfloat Sticker::specular[4] = {0.20F, 0.20F, 0.20F, 1.0F};
GLfloat Sticker::shininess   =  64.0F;


// Constructor
Sticker::Sticker (const FACE &dir) : side(dir)
{
	switch (side)
	{
		// Arriba    | Blanco
		case Sticker::UP:
			pos.y = Sticker::scale;

			type = Sticker::WHITE;
			setColor(0.8F, 0.8F, 0.8F);
			break;

		// Abajo     | Amarillo
		case Sticker::DOWN:
			pos.y = -Sticker::scale;
			rot = glm::angleAxis(Sticker::PI, glm::dvec3(1.0L, 0.0L, 0.0L));

			type = Sticker::YELLOW;
			setColor(0.8F, 0.8F, 0.0F);
			break;

		// Izquierda | Naranja
		case Sticker::LEFT:
			pos.x = -Sticker::scale;
			rot = glm::angleAxis(Sticker::PI_2, glm::dvec3(0.0L, 0.0L, 1.0L));

			type = Sticker::ORANGE;
			setColor(0.8F, 0.376F, 0.0F);
			break;

		// Derecha   | Rojo
		case Sticker::RIGHT:
			pos.x = Sticker::scale;
			rot = glm::angleAxis(-Sticker::PI_2, glm::dvec3(0.0L, 0.0L, 1.0L));

			type = Sticker::RED;
			setColor(0.8F, 0.0F, 0.0F);
			break;

		// Fente     | Verde
		case Sticker::FRONT:
			pos.z = Sticker::scale;
			rot = glm::angleAxis(Sticker::PI_2, glm::dvec3(1.0L, 0.0L, 0.0L));

			type = Sticker::GREEN;
			setColor(0.0F, 0.8F, 0.0F);
			break;

		// Atras     | Azul
		case Sticker::BACK:
			pos.z = -Sticker::scale;
			rot = glm::angleAxis(-Sticker::PI_2, glm::dvec3(1.0L, 0.0L, 0.0L));

			type = Sticker::BLUE;
			setColor(0.0F, 0.0F, 0.8F);
			break;

		// Ninguno
		case Sticker::NONE:
			type = Sticker::BLACK;
			setColor(0.0F, 0.0F, 0.0F);
			break;
	}
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
	vao->draw();

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

// Asigna el VAO
void Sticker::setVAO (VAO *const sticker)
{
	Sticker::vao = sticker;
}

// Asigna el color
void Sticker::setColor (const GLfloat &r, const GLfloat &g, const GLfloat &b)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 1.0F;

	// Material
	diffuse[0] = color.r;
	diffuse[1] = color.g;
	diffuse[2] = color.b;
	diffuse[3] = 1.0F;
}

