#include <scene.h>

// Constructor
Scene::Scene ()
{
	// Cargar modelo del escenario
	vao_0 = vao_1 = new VAO(path + "/scene.obj");
	texture_0 = texture_1 = new Texture(path + "/background.png");

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

	// Normalizacion, Back face culling, Z-Buffer y aliasing
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	texture_0->enable();
	vao_0->draw();


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
	delete vao_0;
	delete texture_0;
}

