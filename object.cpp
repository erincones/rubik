#include <object.h>

// Constantes estaticas matematicas
const GLfloat Object::PI   = 3.14159265358979323846F;
const GLfloat Object::PI_2 = 1.57079632679489661923F;
const GLfloat Object::SIN45 = 0.70710678118654752440F;
const GLfloat Object::SQRT2 = 1.41421356237309504880F;

// Variables estaticas de pantalla
GLint Object::win_w = 0;
GLint Object::win_h = 0;

// Variables estaticas de proyeccion
const GLfloat Object::fov_factor = Object::PI / 360.0F;
GLfloat Object::proy_fovy = 0.0F;
GLfloat Object::proy_zFar = 0.0F;
GLfloat Object::proy_zNear = 0.0F;
GLfloat Object::proy_w = 0.0F;
GLfloat Object::proy_h = 0.0F;
GLfloat Object::proy_aspect = 0.0F;


// Proyecta punto en virtual trackball
glm::vec3 Object::projectToSphere (const glm::vec2 &point)
{
	// Punto proyectado
	glm::vec3 proy(point, 0.0F);

	// Longitud del vector
	const GLfloat length = glm::length(point);

	// Proyeccion
	if (length < trackball_size * Object::SIN45)
	{
		// En la esfera
		proy.z = glm::sqrt((trackball_size * trackball_size) - (length * length));
	}
	else
	{
		// En la elipse
		const GLfloat t = trackball_size / Object::SQRT2;
		proy.z = (t * t) / length;
	}

	// Retorna el vector
	return proy;
}


// Constructor
Object::Object()
{

}


// Actualiza las propiedades de la ventana
void Object::setWindow (const GLfloat &w, const GLfloat &h, const GLfloat &fovy, const GLfloat &zNear, const GLfloat &zFar)
{
	// Dimensiones
	Object::win_w = w;
	Object::win_h = h;

	// Proyeccion
	Object::proy_fovy  = fovy;
	Object::proy_zNear = zNear;
	Object::proy_zFar  = zFar;

	Object::proy_aspect = (GLfloat) w / (GLfloat) h;
	Object::proy_h = std::tan(Object::proy_fovy * Object::fov_factor) * (pos_1.z != 0.0F ? glm::abs(pos_1.z) : 0.01F);
	Object::proy_w = Object::proy_h * Object::proy_aspect;
}


// Cambia a proyeccion ortogonal
void Object::pushOrtho ()
{
	// Apila la matriz de proyeccion y cambia a ortogonal
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(-Object::proy_w, Object::proy_w, -Object::proy_h, Object::proy_h, Object::proy_zNear, Object::proy_zFar);

	// Cambia a la matriz de modelo y vista
	glMatrixMode(GL_MODELVIEW);
}

// Deshace proyeccion ortogonal
void Object::popOrtho ()
{
	// Desapila la matriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Cambia a la matriz de modelo y vista
	glMatrixMode(GL_MODELVIEW);
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
	const GLfloat dz = glm::tan(proy_fovy * Object::fov_factor) * (pos_1.z != 0.0F ? glm::abs(pos_1.z) : 0.01F);

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
	point_0 = projectToSphere(glm::vec2((GLfloat) x, (GLfloat) y));
}

// Termina rotacion
void Object::rotateEnd (const int &x, const int &y)
{
	// Proyecta el punto en la esfera
	point_1 = projectToSphere(glm::vec2((GLfloat) x, (GLfloat) y));

	// No hay rotacion
	if (point_0 == point_1)
	{
		rot_1 = glm::quat();
		return;
	}


	// Direccion de la rotacion
	const glm::vec3 dir = glm::cross(point_1, point_0);

	// Cuanto ha rotado
	GLfloat dt = glm::length(point_0 - point_1) / (2.0F * trackball_size);

		 if (dt >  1.0F) dt =  1.0F;
	else if (dt < -1.0F) dt = -1.0F;

	// Angulo de rotacion<=
	const GLfloat phi = 2.0F * glm::asin(dt);


	// Acumula la rotacion
	rot_1 = glm::normalize(glm::quat(phi, dir) * rot_1);

	// Actualiza el punto inicial
	point_0 = point_1;
}


// Acerca el objeto
void Object::zoomIn ()
{
	if (pos_1.z <= z_max) pos_1.z += 0.05;
}

// Aleja el objecto
void Object::zoomOut ()
{
	if (pos_1.z >= z_min) pos_1.z -= 0.05;
}


// Dibujar
void Object::draw () const
{
	// Si es 2D cambia a ortogonal
	if (d2) Object::pushOrtho();


	// Transformaciones
	glPushMatrix();
	glTranslatef(pos_1.x, pos_1.y, pos_1.z);
	glMultMatrixf(glm::value_ptr(glm::mat4_cast(rot_1)));

	// Material
	glColor3d(color.r, color.g, color.b);
	glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(specular));
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	// Dibujar objeto con textura
	if (hd)
	{
		texture_hd->enable();
		vao_hd->draw();
		texture_hd->disable();
	}
	else
	{
		texture_sd->enable();
		vao_sd->draw();
		texture_sd->disable();
	}

	// Regresa a la matriz de vista y modelo anterior
	glPopMatrix();


	// Regresa a la matriz de proyeccion anterior
	if (d2) Object::popOrtho();
}


// Destructor virtual
Object::~Object ()
{

}
