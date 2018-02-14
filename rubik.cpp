#include <rubik.h>

// Inicializa variabes estaticas
const GLdouble  Rubik::fov_factor = 3.141592653589793238462643383279502884L / 360.0L;
const GLdouble  Rubik::PI_2       = 1.570796326794896619231321691639751442L;


// Proyectar vector en esfera
glm::dvec3 Rubik::projectToSphere (const GLdouble &x, const GLdouble &y)
{
	const GLdouble w = (GLdouble) width;
	const GLdouble h = (GLdouble) height;

	// Ubicacion en el plano
	const GLdouble sph_x = (2.0L * x - w) / w;
	const GLdouble sph_y = (h - 2.0L * y) / h;

	// Magnitud del vector
	const GLdouble d = glm::length(glm::dvec2(sph_x, sph_y));

	// Altura
	const GLdouble sph_z = glm::cos(Rubik::PI_2 * (d < 1.0L ? d : 1.0L));

	// Magnitud
	return glm::normalize(glm::dvec3(sph_x, sph_y, sph_z));
}


// Constructor
Rubik::Rubik (const std::string &path) : dim(3), sticker_vao(NULL), cube_flat_vao(NULL), cube_smooth_vao(NULL)
{
	// Posicion y rotacion inicial
	pos_1 = glm::dvec3( 0.00,  0.00, -12.5);
	rot   = glm::dquat(-0.96, -0.21,  0.17, 0.04);

	// Cargar modelos de los cubos y las etiquetas
	sticker_vao     = new VAO(path + "/sticker.obj");
	cube_flat_vao   = new VAO(path + "/roundedcube_flat.obj");
	cube_smooth_vao = new VAO(path + "/roundedcube_smooth.obj");

	// Construye el minicubo
	minicube = new Minicube(path, &rot, cube_flat_vao, cube_smooth_vao, sticker_vao);

	// Construye los cubos
	for (GLubyte i = 0, x = 0, y = 0, z = 0, location = 0; i < 27; i++)
	{
		// Localizacion
		location = (x << 4) | (y << 2) | z;
		if (++x == dim) {x = 0; if (++y == dim) {y = 0; z++;}}

		cube[i] = new Cube(location, cube_flat_vao, cube_smooth_vao, sticker_vao);
	}
}

// Asigna la informacion de la pantalla
void Rubik::setScreenInfo (const GLint &screen_width, const GLint &screen_height, const GLdouble &fovy, const GLdouble &zNear, const GLdouble &zFar)
{
	fov    = fovy;
	width  = screen_width;
	height = screen_height;

	minicube->setScreenInfo(screen_width, screen_height, fovy, zNear, zFar);
}

// Dibujar modelo
void Rubik::draw () const
{
	// Respaldo la matriz actual y carga la identidad
	glPushMatrix();
	glLoadIdentity();

	// Transformaciones
	glTranslated(pos_1.x, pos_1.y, pos_1.z);
	glMultMatrixd(glm::value_ptr(glm::mat4_cast(rot)));

	// Dibujar cada cubo
	for (unsigned char i = 0; i < 27; i++) cube[i]->draw();

	// Regresa a la matriz anterior
	glPopMatrix();


	// Dibuja el minicubo
	minicube->draw();
}

// Animar rotacion
void Rubik::animate ()
{
	// Valida si hay rotaciones pendiente
	if (move.empty()) return;

	// Anima los cubos
	bool ready = true;
	for (std::size_t i = 0; i < target.front().size(); i++)
	{
		ready &= target.front()[i]->animate(move.front());
	}

	// La animacion ha terminado
	if (ready)
	{
		move.pop();
		target.pop();
	}
}

// Imprimir estado
void Rubik::print () const
{
	std::cout << "Estado: " << (win() ? "armado" : "desarmado") << std::endl;
}

// Click inicial al arrastrar
void Rubik::drag_0 (const int &x, const int &y)
{
	pos_0.x = (GLdouble) x;
	pos_0.y = (GLdouble) y;
}

// Actualizar posicion al arrastrar
void Rubik::drag_1 (const int &x, const int &y)
{
	// Desplazamiento del mouse y plano
	const GLdouble scale = (GLdouble) glm::min(width, height) / 2.0L;
	const GLdouble dx = (GLdouble) (x - pos_0.x) / scale;
	const GLdouble dy = (GLdouble) (y - pos_0.y) / scale;
	const GLdouble dz = glm::tan(fov * Rubik::fov_factor) * (pos_1.z == 0.0L ? 0.01L : glm::abs(pos_1.z));

	// Desplazamiento del modelo
	pos_1.x += dx * dz;
	pos_1.y -= dy * dz;

	// Actualiza la posicion inicial
	pos_0.x = (GLdouble) x;
	pos_0.y = (GLdouble) y;
}

// Click inicial al rotar
void Rubik::rotate_0 (const int &x, const int &y)
{
	point_0 = projectToSphere((GLdouble) x, (GLdouble) y);
}

// Actualizar rotacion al arrastrar
void Rubik::rotate_1 (const int &x, const int &y)
{
	// Vector final
	point_1 = projectToSphere((GLdouble) x, (GLdouble) y);

	// Angulo
	double angle = glm::length(point_1 - point_0);
		 if (angle ==   0.0) angle = 1E8;
	else if (angle >  0.008) angle = 0.008;

	// Acumular rotacion
	rot = glm::normalize(glm::dquat(glm::dquat(0.01 / angle, glm::cross(point_0, point_1)) * rot));

	// Actualiza el vector inicial
	point_0 = point_1;
}

// Zoom
void Rubik::zoom (const bool &dir)
{
	pos_1.z -= pos_1.z * (dir ? -0.05 : 0.05);

	if (pos_1.z > -4.0L) pos_1.z = -4.0L;
	if (pos_1.z < -17.5L) pos_1.z = -17.5L;
}

// Jugar
void Rubik::play (const Rubik::STEP &step)
{
	// Variables temporales
	Cube::AXIS next_move = Cube::X0;
	Sticker::FACE face = Sticker::UP;
	std::vector<Cube *> selection;

	switch (step)
	{
		// Sentido de las agujas del reloj
		case Rubik::U0: next_move = Cube::Y1; face = Sticker::UP;    break;
		case Rubik::D0: next_move = Cube::Y0; face = Sticker::DOWN;  break;
		case Rubik::L0: next_move = Cube::X0; face = Sticker::LEFT;  break;
		case Rubik::R0: next_move = Cube::X1; face = Sticker::RIGHT; break;
		case Rubik::F0: next_move = Cube::Z1; face = Sticker::FRONT; break;
		case Rubik::B0: next_move = Cube::Z0; face = Sticker::BACK;  break;

		// Sentido contrario a las agujas del reloj
		case Rubik::U1: next_move = Cube::Y0; face = Sticker::UP;    break;
		case Rubik::D1: next_move = Cube::Y1; face = Sticker::DOWN;  break;
		case Rubik::L1: next_move = Cube::X1; face = Sticker::LEFT;  break;
		case Rubik::R1: next_move = Cube::X0; face = Sticker::RIGHT; break;
		case Rubik::F1: next_move = Cube::Z0; face = Sticker::FRONT; break;
		case Rubik::B1: next_move = Cube::Z1; face = Sticker::BACK;  break;
	}

	// Obtiene los cubos a rotar y actualiza las caras
	for (GLubyte i = 0; i < 27; i++)
	{
		if (cube[i]->face(face))
		{
			cube[i]->turnFaces((Sticker::AXIS) next_move);
			selection.push_back(cube[i]);
		}
	}

	// Encola el movimiento
	move.push(next_move);
	target.push(selection);

	// Imprime el estado
	print();
}

// Cubo armado
bool Rubik::win () const
{
	// Nueve colores por seis caras
	Sticker::COLOR color[6][9] = {Sticker::WHITE};
	GLubyte ind[6] = {0};

	// Para cada cubo
	for (GLubyte i = 0; i < 27; i++)
	{
		// Identifica las caras
		for (GLubyte j = 0; j < 6; j++)
		{
			const Sticker::FACE face = (Sticker::FACE) j;
			if (cube[i]->face(face))
			{
				// Almacena el color en la cara
				color[j][ind[j]] = cube[i]->tone(face);
				ind[j]++;

				// Verifica si es del mismo color que los otros cubos de la cara
				if ((ind[j] > 1) && (color[j][ind[j] - 2] != color[j][ind[j] - 1])) return false;
			}
		}
	}

	return true;
}

// Destructor
Rubik::~Rubik()
{
	delete cube_flat_vao;
	delete sticker_vao;

	for (int i = 0; i < 26; i++) delete cube[i];
}

