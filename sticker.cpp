#include <sticker.h>

// Inicializa constantes estaticas
VAO *Sticker::sticker_sd;

GLfloat Sticker::offset = 0.5L;


// Constructor
Sticker::Sticker (const FACE &dir, Texture *const img)
{
	// Asigna direccion y textura
	side = dir;
	texture_sd = img;

	// Construye la etiqueta indicada
	switch (side)
	{
		// Arriba
		case Sticker::UP:
			pos_1.y = Sticker::offset;

			// Blanco
			type = Sticker::WHITE;
			color = glm::vec4(0.8F, 0.8F, 0.8F, 1.0F);
			break;

		// Abajo
		case Sticker::DOWN:
			pos_1.y = -Sticker::offset;
			rot_1 = glm::angleAxis(Object::PI, glm::vec3(1.0F, 0.0F, 0.0F));

			// Amarillo
			type = Sticker::YELLOW;
			color = glm::vec4(0.8F, 0.8F, 0.0F, 1.0F);
			break;

		// Izquierda
		case Sticker::LEFT:
			pos_1.x = -Sticker::offset;
			rot_1 = glm::angleAxis(Object::PI_2, glm::vec3(0.0F, 0.0F, 1.0F));

			// Naranja
			type = Sticker::ORANGE;
			color = glm::vec4(0.8F, 0.376F, 0.0F, 1.0F);
			break;

		// Derecha
		case Sticker::RIGHT:
			pos_1.x = Sticker::offset;
			rot_1 = glm::angleAxis(-Object::PI_2, glm::vec3(0.0F, 0.0F, 1.0F));

			// Rojo
			type = Sticker::RED;
			color = glm::vec4(0.8F, 0.0F, 0.0F, 1.0F);
			break;

		// Fente
		case Sticker::FRONT:
			pos_1.z = Sticker::offset;
			rot_1 = glm::angleAxis(Object::PI_2, glm::vec3(1.0F, 0.0F, 0.0F));

			// Verde
			type = Sticker::GREEN;
			color = glm::vec4(0.0F, 0.8F, 0.0F, 1.0F);
			break;

		// Atras
		case Sticker::BACK:
			pos_1.z = -Sticker::offset;
			rot_1 = glm::angleAxis(-Object::PI_2, glm::vec3(1.0F, 0.0F, 0.0F));

			// Azul
			type = Sticker::BLUE;
			color = glm::vec4(0.0F, 0.0F, 0.8F, 1.0F);
			break;

		// Ninguno
		case Sticker::NONE:
			type = Sticker::BLACK;
			color = glm::vec4(0.0F, 0.0F, 0.0F, 1.0F);
			break;
	}

	// Material
	ambient   = glm::vec4(0.5F, 0.5F, 0.5F, 1.0F);
	diffuse   = color;
	specular  = glm::vec4(0.2F, 0.2F, 0.2F, 1.0F);
	shininess = 64.0F;
}

// Dibujar
void Sticker::draw () const
{
	// Copio la matriz actual
	glPushMatrix();

	// Transformaciones
	glTranslatef(pos_1.x, pos_1.y, pos_1.z);
	glMultMatrixf(glm::value_ptr(glm::mat4_cast(rot_1)));

	// Material
	loadMaterial();

	// Dibujar objeto
	if (texture_sd != NULL) texture_sd->enable();
	sticker_sd->draw();
	if (texture_sd != NULL) texture_sd->disable();

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

