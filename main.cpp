#include <rubik.h>
#include <scene.h>
#include <object.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cmath>
#include <cstdlib>

#include <string>


// Macros para scroll
#ifndef GLUT_WHEEL_DOWN
#define GLUT_WHEEL_DOWN 0x0003
#endif

#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP   0x0004
#endif


// Objetos
Scene *scene = NULL;
Rubik *rubik = NULL;
Minicube *minicube = NULL;


// Informacion de pantalla
GLint width = 800;
GLint height = 600;
GLfloat fov = 45.0L;
GLfloat far = 100.0L;
GLfloat near = 1.0L;


// Controlador de loop
const GLint tick = 1000 / 60;
const GLint skip = 10;
GLint game_ms = 0;
GLint loops = 0;

// Contador de fps
GLint fps_ms = 0;
GLint fraps = 0;


// Banderas de eventos del mouse
bool move = false;
bool rotate = false;



// Callbacks de GLUT
// Redimensionar ventana
void reshape (int w, int h)
{
	// Actualiza las dimensiones de la pantalla
	width = w;
	height = h;

	// Ajusta el viewport a las dimensiones de la ventana
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	// Actualiza la informacion de la pantalla de los objetos
	Object::setWindow((GLfloat) w, (GLfloat) h, fov, near, far);
	minicube->updatePosition();
}

// Dibujar escena
void display ()
{
	// Limpiar buffers
	glClearColor(0.25F, 0.25F, 0.25F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Objetos 3D usan proyeccion perspectiva
	Object::perspective();

	// Escenario y cubo
	scene->draw();
	rubik->draw();


	// Objectos 2D usan proyeccion ortogonal
	Object::orthogonal();

	// Minicubo guia
	minicube->draw();


	// Intercamiar buffers
	glutSwapBuffers();
}

// Animaciones
void idle ()
{
	// Actualizar juego
	loops = 0;
	if ((glutGet(GLUT_ELAPSED_TIME) >= game_ms) && (loops < skip))
	{
		scene->animate();
		rubik->animate();

		loops = 0;
		game_ms += tick;
	}

	// Contador de FPS
	fraps++;
	if ((glutGet(GLUT_ELAPSED_TIME) - fps_ms) >= 1000)
	{
		std::clog << "FPS: " << fraps << std::endl;
		fraps = 0;
		fps_ms += 1000;
	}

	// Dibujar
	glutPostRedisplay();
}

// Eventos del mouse
// Click y scroll
void mouse (int button, int state, int x, int y)
{
	// Scroll hacia arriba
	if ((button == GLUT_WHEEL_UP) && (state == GLUT_DOWN))
	{
		rubik->zoomOut();
		return;
	}

	// Scrool hacia abajo
	if ((button == GLUT_WHEEL_DOWN) && (state == GLUT_DOWN))
	{
		rubik->zoomIn();
		return;
	}

	// Click izquierdo
	if (button == GLUT_LEFT_BUTTON)
	{
		rotate = (state == GLUT_DOWN);
		if (rotate) rubik->rotateBegin(x, y);
		return;
	}

	// Click derecho
	if (button == GLUT_RIGHT_BUTTON)
	{
		move = (state == GLUT_DOWN);
		if (move) rubik->dragBegin(x, y);
	}
}

// Arrastrar o rotar
void motion (int x, int y)
{
	// Arrastrar
	if (move) rubik->dragEnd(x, y);

	// Rotar
	if (rotate) rubik->rotateEnd(x, y);
}

// Teclado
void keyboard (unsigned char key, int, int)
{
	// Captura ALT
	const bool alt = (GLUT_ACTIVE_ALT == glutGetModifiers());

	switch (key)
	{
		// Ctrl + Enter alterna el modo pantalla completa
		case 13: if (alt) glutFullScreenToggle(); return;

		// Jugar
		// Sentido de las agujas del reloj
		case 'q': case 'Q': rubik->play(Rubik::U0); return;
		case 'w': case 'W': rubik->play(Rubik::D0); return;
		case 'e': case 'E': rubik->play(Rubik::L0); return;
		case 'r': case 'R': rubik->play(Rubik::R0); return;
		case 't': case 'T': rubik->play(Rubik::F0); return;
		case 'y': case 'Y': rubik->play(Rubik::B0); return;

		// Sentido opuesto a las agujas del reloj
		case 'a': case 'A': rubik->play(Rubik::U1); return;
		case 's': case 'S': rubik->play(Rubik::D1); return;
		case 'd': case 'D': rubik->play(Rubik::L1); return;
		case 'f': case 'F': rubik->play(Rubik::R1); return;
		case 'g': case 'G': rubik->play(Rubik::F1); return;
		case 'h': case 'H': rubik->play(Rubik::B1); return;
	}
}

// Al finalizar la aplicacion
void close ()
{
	delete rubik;
	delete scene;
}

int main(int argc, char **argv)
{
	// Inicializar GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) >> 1, (glutGet(GLUT_SCREEN_HEIGHT) - height) >> 1);
	glutInitWindowSize(width, height);
	glutCreateWindow("Rubik");
	glutCreateMenu(NULL);


	// Inicializar GLEW
	glewInit();


	// Callbacks de GLUT
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutCloseFunc(close);


	// Obtiene directorio de archivos
	std::string path = argv[0];
	path.erase(path.find_last_of("/\\"));
	path.erase(path.find_last_of("/\\"));
	path += "/Files";
	Object::setPath(path);


	// Informa velocidad de animacion
	Object::setFPS(tick);

	// Construir objetos
	scene = new Scene();
	rubik = new Rubik();
	minicube = new Minicube(rubik);




	// Loop principal de GLUT
	glutMainLoop();
	return 0;
}
