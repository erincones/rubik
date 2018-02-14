#include <minicube.h>

// Inicializa variabes estaticas
const GLdouble  Minicube::fov_factor = 3.141592653589793238462643383279502884L / 360.0L;
const GLdouble  Minicube::PI_2       = 1.570796326794896619231321691639751442L;

// Activa la proyeccion ortogonal
void Minicube::enable_ortho () const
{
	// Cambia a la matriz de proyeccion, guarda el estado y crea una nueva matriz
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// Calculo de la proyeccion ortogonal
	glOrtho(-width, width, -height, height, near, far);

	// Regresa a la matriz de modelo y vista
	glMatrixMode(GL_MODELVIEW);
}

// Desactiva la proyeccion ortogonal
void Minicube::disable_ortho () const
{
	// Cambia a la matriz de proyeccion y recupera el estado anterior
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Regresa a la matriz de modelo y vista
	glMatrixMode(GL_MODELVIEW);
}

// Constructor
Minicube::Minicube (const std::string &path, glm::dquat *const parent_rot, VAO *const cube_sd, VAO *const cube_hd, VAO *const sticker) : vao_sd(cube_sd), vao_hd(cube_hd), rot(parent_rot)
{
	// Escala y posicion
	offset = 1.0L;
	pos    = glm::dvec3(0.0, 0.0, -12.5);

	// Crea cada calcomania con las texturas
	for (GLubyte i = 0; i < 6; i++)
	{
		const Sticker::FACE dir = (Sticker::FACE) i;

		texture[i] = new Texture(path + "/minicube_" + std::string(1, i + '0') + ".png");
		face[i]    = new Sticker(dir, sticker, texture[i]);
	}

	// Material
	color = glm::vec4(0.0F, 0.0F, 0.0F, 0.1F);
	ambient[0] = ambient[1] = ambient[2] = 0.0F; ambient[3] = 1.0F;
	diffuse[0] = diffuse[1] = diffuse[2] = 0.1F; diffuse[3] = 1.0F;
	specular[0] = specular[1] = specular[2] = 0.75F; specular[3] = 1.0F;
	shininess = 64.0L;
}

// Asigna la informacion de la pantalla
void Minicube::setScreenInfo (const GLint &screen_width, const GLint &screen_height, const GLdouble &fovy, const GLdouble &zNear, const GLdouble &zFar)
{
	fov    = fovy;
	far    = zFar;
	near   = zNear;

	// Calculo de la proyeccion ortogonal
	aspect = (GLdouble) screen_width / (GLdouble) screen_height;
	height = std::tan(fov * fov_factor) * (-pos.z);
	width  = height * aspect;

	// Actualiza la posicion
	pos.x = width  - offset;
	pos.y = offset - height;
}

// Dibujar
void Minicube::draw() const
{
	// Habilita la proyeccion ortogonal
	enable_ortho();


	// Transformaciones
	glPushMatrix();
	glTranslated(pos.x, pos.y, pos.z);
	glMultMatrixd(glm::value_ptr(glm::mat4_cast(*rot)));

	// Dibuja cada calcomania
	for (GLubyte i = 0; i < 6; i++) face[i]->draw();

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


	// Desactiva la proyeccion ortogonal
	disable_ortho();
}

// Destructor
Minicube::~Minicube()
{
	for (GLubyte i = 0; i < 6; i++)
	{
		delete face[i];
		delete texture[i];
	}
}

