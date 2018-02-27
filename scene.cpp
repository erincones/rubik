#include <scene.h>

// Constructor
Scene::Scene ()
{
	// Cargar modelo del escenario
	vao_sd = vao_hd = new VAO(path + "/scene.obj");
	texture_sd = texture_hd = new Texture(path + "/background.png");

	// Posicion
	pos_1 = glm::vec3(0.0L, 0.0L, -10.5);

	// Ajuste de animacion
	speed = 1.0F / 1000.0F;
	step  = Object::PI * speed / Object::fps;
	rot_0 = glm::angleAxis(step, glm::vec3(0.0F, 1.0F, 0.0F));


	// Material
	color     = glm::vec4(0.7F, 0.7F, 0.8F, 0.1F);
	ambient   = glm::vec4(1.0F, 1.0F, 1.0F, 1.0F);
	diffuse   = glm::vec4(1.0F, 1.0F, 1.0F, 1.0F);
	specular  = glm::vec4(0.0F, 0.0F, 0.0F, 1.0F);
	shininess = 0.0F;


	// Texturas
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	// Normalizacion, Back face culling, Z-Buffer y aliasing
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

// Dibujar
void Scene::draw () const
{
	// Respaldo la matriz actual y carga la identidad
	glPushMatrix();
	glLoadIdentity();

	// Transformaciones
	glTranslatef(pos_1.x, pos_1.y, pos_1.z);
	glMultMatrixf(glm::value_ptr(glm::mat4_cast(rot_1)));

	// Material
	loadMaterial();

	// Dibujar escena con textura
	texture_sd->enable();
	vao_sd->draw();
	texture_sd->disable();

	// Regresa a la matriz anterior
	glPopMatrix();


	// Limpia el Z-Buffer
	glClear(GL_DEPTH_BUFFER_BIT);
}

// Animar escena
void Scene::animate ()
{
	rot_1 = rot_0 * rot_1;
}

// Destructor
Scene::~Scene()
{
	delete vao_sd;
	delete texture_sd;
}

