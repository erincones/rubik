#include <scene.h>

// Constructor
Scene::Scene(const std::string &path, const glm::vec4 &sceneColor) : vao(NULL), texture(NULL), color(sceneColor)
{
	// Cargar modelo del escenario
	vao = new VAO(path + "/scene.obj");

	// Posicion
	pos = glm::dvec3(0.0L, 0.0L, -15.0L);
	rot = glm::angleAxis(M_PI, glm::dvec3(0.0, 0.0, 1.0));

	// Material
	scene_ambient[0] = scene_ambient[1] = scene_ambient[2] = 1.0F; scene_ambient[3] = 1.0F;
	scene_diffuse[0] = scene_diffuse[1] = scene_diffuse[2] = 1.0F; scene_diffuse[3] = 1.0F;
	scene_specular[0] = scene_specular[1] = scene_specular[2] = 0.0F; scene_specular[3] = 1.0F;
	scene_shininess = 0.0L;

	// Iluminacion
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	light_ambient[0] = light_ambient[1] = light_ambient[2] = 0.0F; light_ambient[3] = 1.0F;
	light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 1.0F; light_diffuse[3] = 1.0F;
	light_specular[0] = light_specular[1] = light_specular[2] = 1.0F; light_specular[3] = 1.0F;
	light_position[0] = 0.1F; light_position[1] = 0.15F; light_position[2] = 0.98F; light_position[3] = 0.0F;

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Texturas
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	// Back face culling, Z-Buffer y aliasing
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

// Asigna una textura
bool Scene::setTexture (const std::string &path)
{
	// Elimina la textura anterior
	if (texture != NULL) delete texture;

	// Crea la textura nueva
	texture = new Texture(path);

	return texture->valid();
}

// Dibujar
void Scene::draw () const
{
	// Respaldo la matriz actual y carga la identidad
	glPushMatrix();
	glLoadIdentity();

	// Transformaciones
	glTranslated(pos.x, pos.y, pos.z);
	glMultMatrixd(glm::value_ptr(glm::mat4_cast(rot)));

	// Material
	glColor3d(color.r, color.g, color.b);
	glMaterialfv(GL_FRONT, GL_AMBIENT, scene_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, scene_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, scene_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &scene_shininess);

	// Dibujar objeto
	texture->enable();
	vao->draw();
	texture->disable();

	// Regresa a la matriz anterior
	glPopMatrix();
}

// Animar escena
void Scene::animate()
{
	rot = glm::angleAxis(0.001, glm::dvec3(0.0, 1.0, 0.0)) * rot;
}

// Destructor
Scene::~Scene()
{
	delete vao;
	delete texture;
}

