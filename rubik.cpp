#include <rubik.h>

// Constructor
Rubik::Rubik ()
{
	// Carga modelos
	Cube::cube_sd = new VAO(path + "/roundedcube_flat.obj");
	Cube::cube_hd = new VAO(path + "/roundedcube_smooth.obj");
	Sticker::sticker_sd = new VAO(path + "/sticker.obj");

	// Posicion y rotacion inicial
	pos_1 = glm::vec3( 0.00F,  0.00F, -12.5F);
	rot_1 = glm::quat(-0.96F, -0.21F,  0.17F, 0.04F);

	// Minimo y maximo zoom
	z_min = -19.00F;
	z_max =  -4.25F;

	// Dimensiones
	dim = 3;

	// Construye los cubos
	for (GLubyte i = 0, x = 0, y = 0, z = 0, location = 0; i < 27; i++)
	{
		// Localizacion
		location = (x << 4) | (y << 2) | z;
		if (++x == dim) {x = 0; if (++y == dim) {y = 0; z++;}}

		cube[i] = new Cube(location);
	}
}

// Dibujar modelo
void Rubik::draw () const
{
	// Respaldo la matriz actual y carga la identidad
	glPushMatrix();
	glLoadIdentity();

	// Transformaciones
	glTranslatef(pos_1.x, pos_1.y, pos_1.z);
	glMultMatrixf(glm::value_ptr(glm::mat4_cast(rot_1)));

	// Dibujar cada cubo
	for (unsigned char i = 0; i < 27; i++) cube[i]->draw();

	// Regresa a la matriz anterior
	glPopMatrix();
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

// Imprimir estado
void Rubik::print () const
{
	std::cout << "Estado: " << (win() ? "armado" : "desarmado") << std::endl;
}


// Destructor
Rubik::~Rubik()
{
	delete Cube::cube_sd;
	delete Cube::cube_hd;
	delete Sticker::sticker_sd;

	for (int i = 0; i < 26; i++) delete cube[i];
}

