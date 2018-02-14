#include <cube.h>

// Inicializacion de variables estaticas
const GLdouble Cube::scale = 1.0L;
const GLdouble Cube::gap   = 0.0025L;
const double   Cube::PI_2  = 1.57079632679489661923;
const double   Cube::step  = Cube::PI_2 / (60.0 / 5.0);

Cube::Cube (const GLubyte &location, VAO *const cube_sd, VAO *const cube_hd, VAO *const sticker) : angle(0.0), vao_sd(cube_sd), vao_hd(cube_hd), face_x(NULL), face_y(NULL), face_z(NULL)
{
	// Ubicacion en el eje x
	GLubyte axis = location >> 4;
	switch (axis)
	{
		case 0: // Izquierda
			pos.x = -Cube::scale - Cube::gap;
			face_x = new Sticker(Sticker::LEFT, sticker);
			break;

		case 2: // Derecha
			pos.x = Cube::scale + Cube::gap;
			face_x = new Sticker(Sticker::RIGHT, sticker);
			break;

		default: // Ninguno
			face_x = new Sticker(Sticker::NONE, sticker);
			break;
	}

	// Ubicacion en el eje y
	axis = (location >> 2) & 3;
	switch (axis)
	{
		case 0: // Arriba
			pos.y = Cube::scale + Cube::gap;
			face_y = new Sticker(Sticker::UP, sticker);
			break;

		case 2: // Abajo
			pos.y = -Cube::scale - Cube::gap;
			face_y = new Sticker(Sticker::DOWN, sticker);
			break;

		default: // Ninguno
			face_y = new Sticker(Sticker::NONE, sticker);
			break;
	}

	// Ubicacion en el eje z
	axis = location & 3;
	switch (axis)
	{
		case 0: // Frente
			pos.z = Cube::scale + Cube::gap;
			face_z = new Sticker(Sticker::FRONT, sticker);
			break;

		case 2: // Atras
			pos.z = -Cube::scale - Cube::gap;
			face_z = new Sticker(Sticker::BACK, sticker);
			break;

		default: // Ninguno
			face_z = new Sticker(Sticker::NONE, sticker);
			break;
	}

	// Material
	color = glm::vec4(0.0F, 0.0F, 0.0F, 0.1F);
	ambient[0] = ambient[1] = ambient[2] = 0.0F; ambient[3] = 1.0F;
	diffuse[0] = diffuse[1] = diffuse[2] = 0.1F; diffuse[3] = 1.0F;
	specular[0] = specular[1] = specular[2] = 0.75F; specular[3] = 1.0F;
	shininess = 64.0L;
}

void Cube::draw() const
{
	// Cubo central no se dibuja
	if ((face_x->side == Sticker::NONE) && (face_y->side == Sticker::NONE) && (face_z->side == Sticker::NONE)) return;

	// Respaldo la matriz actual
	glPushMatrix();

	// Transformaciones
	glMultMatrixd(glm::value_ptr(glm::mat4_cast(rot_1)));
	glTranslated(pos.x, pos.y, pos.z);

	// Dibujar caras
	face_x->draw();
	face_y->draw();
	face_z->draw();

	// Material
	glColor3d(color.r, color.g, color.b);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	// Dibujar objeto
	vao_sd->draw();

	// Regresa a la matriz anterior
	glPopMatrix();
}

// Valida la direccion de caras visibles
bool Cube::face (const Sticker::FACE &side) const
{
	return (face_x->face() == side) || (face_y->face() == side) || (face_z->face() == side);
}

// Retorna el color de una cara
Sticker::COLOR Cube::tone (const Sticker::FACE &side) const
{
	if (face_x->side == side) return face_x->type;
	if (face_y->side == side) return face_y->type;
	if (face_z->side == side) return face_z->type;
	return Sticker::BLACK;
}

// Fijar rotacion
void Cube::turn (const Cube::AXIS &dir)
{
	// Rotar cubo
	switch (dir)
	{
		// Sentido de las agujas del reloj
		case Cube::X0: rot_1 = glm::angleAxis(Cube::PI_2, glm::dvec3(1.0, 0.0, 0.0)) * rot_0; break;
		case Cube::Y0: rot_1 = glm::angleAxis(Cube::PI_2, glm::dvec3(0.0, 1.0, 0.0)) * rot_0; break;
		case Cube::Z0: rot_1 = glm::angleAxis(Cube::PI_2, glm::dvec3(0.0, 0.0, 1.0)) * rot_0; break;

		// Sentido contrario a las agujas del reloj
		case Cube::X1: rot_1 = glm::angleAxis(-Cube::PI_2, glm::dvec3(1.0, 0.0, 0.0)) * rot_0; break;
		case Cube::Y1: rot_1 = glm::angleAxis(-Cube::PI_2, glm::dvec3(0.0, 1.0, 0.0)) * rot_0; break;
		case Cube::Z1: rot_1 = glm::angleAxis(-Cube::PI_2, glm::dvec3(0.0, 0.0, 1.0)) * rot_0; break;
	}

	// Respalda la rotacion y reinicia el angulo
	rot_0 = rot_1;
	angle = 0.0;
}

// Actualizar rotacion de las caras
void Cube::turnFaces (const Sticker::AXIS &dir)
{
	face_x->turn(dir);
	face_y->turn(dir);
	face_z->turn(dir);
}

// Animar cubo
bool Cube::animate (const Cube::AXIS &dir)
{
	// Ajusta la rotacion cuando se alcanza o superan pi / 2 radianes
	angle += Cube::step;
	if (angle >= Cube::PI_2)
	{
		turn(dir);
		return true;
	}

	// Rotar cubo
	switch (dir)
	{
		// Sentido de las agujas del reloj
		case Cube::X0: rot_1 = glm::angleAxis(angle, glm::dvec3(1.0, 0.0, 0.0)) * rot_0; return false;
		case Cube::Y0: rot_1 = glm::angleAxis(angle, glm::dvec3(0.0, 1.0, 0.0)) * rot_0; return false;
		case Cube::Z0: rot_1 = glm::angleAxis(angle, glm::dvec3(0.0, 0.0, 1.0)) * rot_0; return false;

		// Sentido contrario a las agujas del reloj
		case Cube::X1: rot_1 = glm::angleAxis(-angle, glm::dvec3(1.0, 0.0, 0.0)) * rot_0; return false;
		case Cube::Y1: rot_1 = glm::angleAxis(-angle, glm::dvec3(0.0, 1.0, 0.0)) * rot_0; return false;
		case Cube::Z1: rot_1 = glm::angleAxis(-angle, glm::dvec3(0.0, 0.0, 1.0)) * rot_0; return false;
	}

	return false;
}

// Destructor
Cube::~Cube()
{
	delete face_x;
	delete face_y;
	delete face_z;
}

