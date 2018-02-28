#include <gui.h>

// Variables estaticas
GLfloat GUI::gap    = 0.0100F;
GLfloat GUI::border = 0.0125F;

// Constructor
GUI::GUI ()
{
	// Vertex Array Object
	vao_0 = new VAO(path + "/square.obj");

	// Inicializa los botones
	help   = new FlatObject(vao_0, "/help.png", "/help_press.png");
	conf   = new FlatObject(vao_0, "/settings.png", "/settings_press.png");
	sound  = new FlatObject(vao_0, "/sound_on.png", "/sound_off.png");
	window = new FlatObject(vao_0, "/maximize.png", "/minimize.png");
	quit   = new FlatObject(vao_0, "/quit.png");
	mix    = new FlatObject(vao_0, "/mix.png");
	solve  = new FlatObject(vao_0, "/solve.png");

	// Escalas
	const glm::vec3 scale(0.075F);
	help->scale_0   = scale;
	conf->scale_0   = scale;
	sound->scale_0  = scale;
	window->scale_0 = scale;
	quit->scale_0   = scale;
	mix->scale_0    = scale;
	solve->scale_0  = scale;

	// Ubicaciones
	const GLfloat offset = GUI::gap + scale.x;
	help->offset_0   = glm::vec3(GUI::border                , GUI::border, 0.0F);
	conf->offset_0   = glm::vec3(GUI::border + offset       , GUI::border, 0.0F);
	sound->offset_0  = glm::vec3(GUI::border + offset * 2.0F, GUI::border, 0.0F);
	window->offset_0 = glm::vec3(GUI::border + offset       , GUI::border, 0.0F);
	quit->offset_0   = glm::vec3(GUI::border                , GUI::border, 0.0F);
	mix->offset_0    = glm::vec3(GUI::border                ,      0.500F, 0.0F);
	solve->offset_0  = glm::vec3(GUI::border + offset       ,      0.500F, 0.0F);

	// Puntos de referencia
	help->origin   = FlatObject::UPLEFT;
	conf->origin   = FlatObject::UPLEFT;
	sound->origin  = FlatObject::UPLEFT;
	window->origin = FlatObject::UPRIGHT;
	quit->origin   = FlatObject::UPRIGHT;
	mix->origin    = FlatObject::UPRIGHT;
	solve->origin  = FlatObject::UPRIGHT;
}

void GUI::resize ()
{
	help->resize();
	conf->resize();
	sound->resize();
	window->resize();
	quit->resize();
	mix->resize();
	solve->resize();
}

// Dibujar
void GUI::draw () const
{
	// Habilita transparencia y texturas
	glEnable(GL_BLEND);

	// Dibuja botones y paneles
	help->draw();
	//conf->draw();
	sound->draw();
	window->draw();
	quit->draw();
	mix->draw();
	//solve->draw();

	// Deshabilita transparencia y texturas
	glDisable(GL_BLEND);
}

// Destructor
GUI::~GUI ()
{
	// Destruye botones y paneles
	delete mix;
	delete solve;
	delete sound;
	delete window;
	delete conf;
	delete help;
	delete quit;

	// Destruye Vertex Array Object
	delete vao_0;
}

