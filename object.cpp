#include <object.h>

// Constantes estaticas matematicas
const GLfloat Object::PI = 3.14159265358979323846F;
const GLfloat Object::PI_2 = 1.57079632679489661923F;

// Variables estaticas de pantalla
GLint Object::win_w = 0;
GLint Object::win_h = 0;

// Variables estaticas de proyeccion
const GLfloat Object::fovy_factor = Object::PI / 360.0F;
GLfloat Object::proj_fovy = 0.0F;
GLfloat Object::proj_zFar = 0.0F;
GLfloat Object::proj_zNear = 0.0F;
GLfloat Object::proj_aspect = 0.0F;
GLfloat Object::proj_w = 0.0F;
GLfloat Object::proj_h = 0.0F;

// Directorio de archivos
std::string Object::path;

// Variables estaticas de animacion
GLint Object::fps = 0;



// Proyecta punto en virtual trackball
glm::vec3 Object::projectToSphere (const int &x, const int &y)
{
	// Normalizacion de coordenadas en el intervalo [-1.0, 1.0]
	glm::vec3 sphere;
	sphere.x = (GLfloat) (2 * x - Object::win_w) / (GLfloat) Object::win_w;
	sphere.y = (GLfloat) (Object::win_h - 2 * y) / (GLfloat) Object::win_h;
	sphere.z = (sphere.x * sphere.x) + (sphere.y * sphere.y);

	// Proyeccion sobre esfera
	if (sphere.z <= 0.5F)
	{
		sphere.z = glm::sqrt(1.0F - sphere.z);
	}

	// Proyeccion sobre hiperbola
	else
	{
		sphere.z = 1.0F / (2.0F * glm::sqrt(sphere.z));
	}

	return sphere;
}


// Cambia a proyeccion perspectiva
void Object::perspective ()
{
	// Apila la matriz de proyeccion y cambia a perspectiva
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-Object::proj_w, Object::proj_w, -Object::proj_h, Object::proj_h, Object::proj_zNear, Object::proj_zFar);

	// Cambia a la matriz de modelo y vista
	glMatrixMode(GL_MODELVIEW);
}

// Cambia a proyeccion ortogonal
void Object::orthogonal ()
{
	// Apila la matriz de proyeccion y cambia a ortogonal
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0F, (GLfloat) Object::win_w, 0.0F, (GLfloat) Object::win_h, -50.0F, 50.0F);

	// Cambia a la matriz de modelo y vista
	glMatrixMode(GL_MODELVIEW);
}


// Actualiza las propiedades de la ventana
void Object::setWindow (const GLfloat &w, const GLfloat &h, const GLfloat &fovy, const GLfloat &zNear, const GLfloat &zFar)
{
	// Dimensiones
	Object::win_w = (GLint) w;
	Object::win_h = (GLint) h;

	// Proyeccion
	Object::proj_fovy = fovy;
	Object::proj_zFar = zFar;
	Object::proj_zNear = zNear;
	Object::proj_aspect = w / h;

	// Proyeccion perspectiva
	Object::proj_h = std::tan(Object::proj_fovy * Object::fovy_factor) * proj_zNear;
	Object::proj_w = Object::proj_h * Object::proj_aspect;
}


// Asigna la cantiadd de cuadros por segundo
void Object::setFPS(const GLint &fraps)
{
	fps = fraps;
}

// Asigna el directorio de archivos
void Object::setPath(const std::string &dir)
{
	path = dir;
}


// Iniciar click-and-drag
void Object::dragBegin (const int &x, const int &y)
{
	pos_0.x = (GLfloat) x;
	pos_0.y = (GLfloat) y;
}

// Terminar click-and-drag
void Object::dragEnd (const int &x, const int &y)
{
	// Desplazamiento del mouse y plano
	const GLfloat scale = (GLfloat) glm::min(Object::win_w, Object::win_h) / 2.0F;
	const GLfloat dx = (GLfloat) (x - pos_0.x) / scale;
	const GLfloat dy = (GLfloat) (y - pos_0.y) / scale;
	const GLfloat dz = glm::tan(proj_fovy * Object::fovy_factor) * (pos_1.z != 0.0F ? glm::abs(pos_1.z) : 0.01F);

	// Desplazamiento del modelo
	pos_1.x += dx * dz;
	pos_1.y -= dy * dz;

	// Actualiza la posicion inicial
	pos_0.x = (GLfloat) x;
	pos_0.y = (GLfloat) y;
}


// Iniciar rotacion
void Object::rotateBegin (const int &x, const int &y)
{
	// Proyecta el punto en la esfera
	point_0 = projectToSphere(x, y);
}

// Termina rotacion
void Object::rotateEnd (const int &x, const int &y)
{
	// Proyecta el punto en la esfera
	point_1 = projectToSphere(x, y);

	// Direccion y angulo de rotacion
	const glm::vec3 dir = glm::cross(point_0, point_1);
	const GLfloat angle = Object::PI_2 * pos_1.z / z_min;

	// Acumula la rotacion
	rot_1 = glm::normalize(glm::angleAxis(angle, dir) * rot_1);

	// Actualiza el punto inicial
	point_0 = point_1;
}


// Acerca el objeto
void Object::zoomIn ()
{
	if (pos_1.z <= z_max) pos_1.z -= pos_1.z * 0.05F;
}

// Aleja el objecto
void Object::zoomOut ()
{
	if (pos_1.z >= z_min) pos_1.z += pos_1.z * 0.05F;
}


// Retorna apuntador a rotacion
glm::quat *Object::rotPointer ()
{
	return &rot_1;
}


// Carga el material
void Object::loadMaterial() const
{
	glColor3d(color.r, color.g, color.b);
	glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(specular));
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
}


// Destructor virtual
Object::~Object ()
{

}
