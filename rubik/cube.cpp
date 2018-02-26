#include <cube.h>

// Inicializacion de variables estaticas
VAO *Cube::cube_sd;
VAO *Cube::cube_hd;

GLfloat Cube::size = 1.0F;
GLfloat Cube::gap   = 0.0025F;


// Constructor
Cube::Cube (const GLubyte &location)
{
	// Inicializa angulo y visibilidad
	angle = 0.0F;
	drawable = false;

	// Ajusta la animacion
	speed = 3.0F;
	step  = Object::PI_2 * speed / Object::fps;

	// Construye las etiquetas
	for (GLubyte i = 0; i < 6; i++)
	{
		const Sticker::FACE dir = (Sticker::FACE) i;

		sticker[dir] = new Sticker(dir);
		sticker[dir]->side = Sticker::NONE;
	}


	// Ubicacion
	const GLfloat offset = Cube::size + Cube::gap;

	// Etiquetas
	glm::ivec3 axis;
	axis.x =  location >> 0x04;
	axis.y = (location >> 0x02) & 0x03;
	axis.z =  location &  0x03;

	switch (axis.x)
	{
		case 0: pos_1.x = -offset; sticker[Sticker::LEFT ]->side = Sticker::LEFT;  break; // Izquierda
		case 2: pos_1.x =  offset; sticker[Sticker::RIGHT]->side = Sticker::RIGHT; break; // Derecha
	}

	switch (axis.y)
	{
		case 0: pos_1.y =  offset; sticker[Sticker::UP  ]->side = Sticker::UP;   break; // Arriba
		case 2: pos_1.y = -offset; sticker[Sticker::DOWN]->side = Sticker::DOWN; break; // Abajo
	}

	switch (axis.z)
	{
		case 0: pos_1.z =  offset; sticker[Sticker::FRONT]->side = Sticker::FRONT; break; // Frente
		case 2: pos_1.z = -offset; sticker[Sticker::BACK ]->side = Sticker::BACK;  break; // Atras
	}

	// Valida si es dibujable
	drawable |= (axis.x != 1) || (axis.y != 1) || (axis.z != 1);


	// Material
	color     = glm::vec4(0.00F, 0.00F, 0.00F, 0.1F);
	ambient   = glm::vec4(0.00F, 0.00F, 0.00F, 1.0F);
	diffuse   = glm::vec4(0.10F, 0.10F, 0.10F, 1.0F);
	specular  = glm::vec4(0.75F, 0.75F, 0.75F, 1.0F);
	shininess = 64.0F;
}


void Cube::draw() const
{
	// Valida si se debe dibujar el cubo
	if (!drawable) return;

	// Respaldo la matriz actual
	glPushMatrix();

	// Transformaciones
	glMultMatrixf(glm::value_ptr(glm::mat4_cast(rot_1)));
	glTranslatef(pos_1.x, pos_1.y, pos_1.z);

	// Dibujar caras
	for (GLubyte i = 0; i < 6; i++)
	{
		if (sticker[i]->side != Sticker::NONE)
		{
			sticker[i]->draw();
		}
	}

	// Carga material y dibujar objeto
	loadMaterial();
	Cube::cube_sd->draw();

	// Regresa a la matriz anterior
	glPopMatrix();
}

// Valida la direccion de caras visibles
bool Cube::face (const Sticker::FACE &side) const
{
	for (GLubyte i = 0; i < 6; i++)
	{
		if (sticker[i]->side == side)
		{
			return true;
		}
	}

	// Si ninguna cara coincide retorna falso
	return false;
}

// Retorna el color de una cara
Sticker::COLOR Cube::tone (const Sticker::FACE &side) const
{
	for (GLubyte i = 0; i < 6; i++)
	{
		if (sticker[i]->side == side)
		{
			return sticker[i]->type;
		}
	}

	// Si no existe la cara no retorna ningun color
	return Sticker::BLACK;
}

// Fijar rotacion
void Cube::turn (const Cube::AXIS &dir)
{
	// Rotar cubo
	switch (dir)
	{
		// Sentido de las agujas del reloj
		case Cube::X0: rot_1 = glm::angleAxis(Cube::PI_2, glm::vec3(1.0, 0.0, 0.0)) * rot_0; break;
		case Cube::Y0: rot_1 = glm::angleAxis(Cube::PI_2, glm::vec3(0.0, 1.0, 0.0)) * rot_0; break;
		case Cube::Z0: rot_1 = glm::angleAxis(Cube::PI_2, glm::vec3(0.0, 0.0, 1.0)) * rot_0; break;

		// Sentido contrario a las agujas del reloj
		case Cube::X1: rot_1 = glm::angleAxis(-Cube::PI_2, glm::vec3(1.0, 0.0, 0.0)) * rot_0; break;
		case Cube::Y1: rot_1 = glm::angleAxis(-Cube::PI_2, glm::vec3(0.0, 1.0, 0.0)) * rot_0; break;
		case Cube::Z1: rot_1 = glm::angleAxis(-Cube::PI_2, glm::vec3(0.0, 0.0, 1.0)) * rot_0; break;
	}

	// Respalda la rotacion y reinicia el angulo
	rot_0 = rot_1;
	angle = 0.0;
}

// Actualizar rotacion de las caras
void Cube::turnFaces (const Sticker::AXIS &dir)
{
	for (GLubyte i = 0; i < 6; i++)
	{
		sticker[i]->turn(dir);
	}
}

// Animar cubo
bool Cube::animate (const Cube::AXIS &dir)
{
	// Ajusta la rotacion cuando se alcanza o superan pi / 2 radianes
	angle += step;
	if (angle >= Cube::PI_2)
	{
		turn(dir);
		return true;
	}

	// Rotar cubo
	switch (dir)
	{
		// Sentido de las agujas del reloj
		case Cube::X0: rot_1 = glm::angleAxis(angle, glm::vec3(1.0, 0.0, 0.0)) * rot_0; return false;
		case Cube::Y0: rot_1 = glm::angleAxis(angle, glm::vec3(0.0, 1.0, 0.0)) * rot_0; return false;
		case Cube::Z0: rot_1 = glm::angleAxis(angle, glm::vec3(0.0, 0.0, 1.0)) * rot_0; return false;

		// Sentido contrario a las agujas del reloj
		case Cube::X1: rot_1 = glm::angleAxis(-angle, glm::vec3(1.0, 0.0, 0.0)) * rot_0; return false;
		case Cube::Y1: rot_1 = glm::angleAxis(-angle, glm::vec3(0.0, 1.0, 0.0)) * rot_0; return false;
		case Cube::Z1: rot_1 = glm::angleAxis(-angle, glm::vec3(0.0, 0.0, 1.0)) * rot_0; return false;
	}

	return false;
}

// Destructor
Cube::~Cube()
{
	for (GLubyte i = 0; i < 6; i++)
	{
		delete sticker[i];
	}
}

