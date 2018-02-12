#include <rubik.h>
#include <scene.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cmath>
#include <cstdlib>


// Macros para scroll
#ifndef GLUT_WHEEL_DOWN
#define GLUT_WHEEL_DOWN 0x0003
#endif

#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP   0x0004
#endif

// Constantes matematicas
const GLdouble fov_factor = 3.141592653589793238462643383279502884L / 360.0L;


// Campo de vision
GLdouble fov = 45.0L;

// Objetos
Rubik *cube = NULL;
Scene *scene = NULL;

// Controlador de loop
const GLint tick = 1000 / 60;
const GLint skip = 10;
GLint game_ms = 0;
GLint loop = 0;

// Contador de fps
GLint fps_ms = 0;
GLint fraps = 0;


// Banderas de eventos del mouse
bool move = false;
bool rotate = false;


// Funciones auxiliares
// Proyeccion perspectiva
void perspective (const GLdouble &fovy, const GLdouble &aspect, const GLdouble &zNear, const GLdouble &zFar)
{
	//height = tan((fovy / 2) * (pi / 180)) * zNear;
	const GLdouble h = std::tan(fovy * fov_factor) * zNear;
	const GLdouble w = h * aspect;

	glFrustum(-w, w, -h, h, zNear, zFar);
}


// Callbacks de GLUT
// Redimensionar ventana
void reshape (int w, int h)
{
	// Ajusta el viewport a las dimensiones de la ventana
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	// Reestablece la patriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective(fov, (GLdouble) w / (GLdouble) h, 1.0L, 150.0L);

	// Regresa a la matriz del modelo
	glMatrixMode(GL_MODELVIEW);
}

// Dibujar escena
void display ()
{
	// Limpiar buffers
	glClearColor(0.25F, 0.25F, 0.25F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Dibujar escenario
	scene->draw();

	// Dibujar objeto
	cube->draw();

	// Refrescar
	glutSwapBuffers();
}

// Animaciones
void idle ()
{
	// Actualizar juego
	loop = 0;
	if ((glutGet(GLUT_ELAPSED_TIME) >= game_ms) && (loop < skip))
	{
		scene->animate();
		cube->animate();

		loop = 0;
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
	// Rueda del mouse
	if (((button == GLUT_WHEEL_UP) || (button == GLUT_WHEEL_DOWN)) && (state == GLUT_DOWN))
	{
		cube->zoom(button == GLUT_WHEEL_UP);
		return;
	}

	// Click izquierdo
	if ((button == GLUT_LEFT_BUTTON))
	{
		rotate = (state == GLUT_DOWN);
		if (rotate) cube->rotate_0(x, y);
		return;
	}

	// Boton derecho
	if (button == GLUT_RIGHT_BUTTON)
	{
		move = (state == GLUT_DOWN);
		if (move) cube->drag_0(x, y);
	}
}

// Arrastrar o rotar
void motion (int x, int y)
{
	// Arrastrar
	if (move) cube->drag_1(x, y);

	// Rotar
	if (rotate) cube->rotate_1(x, y);
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
		case 'q': case 'Q': cube->play(Rubik::U0); return;
		case 'w': case 'W': cube->play(Rubik::D0); return;
		case 'e': case 'E': cube->play(Rubik::L0); return;
		case 'r': case 'R': cube->play(Rubik::R0); return;
		case 't': case 'T': cube->play(Rubik::F0); return;
		case 'y': case 'Y': cube->play(Rubik::B0); return;

		// Sentido opuesto a las agujas del reloj
		case 'a': case 'A': cube->play(Rubik::U1); return;
		case 's': case 'S': cube->play(Rubik::D1); return;
		case 'd': case 'D': cube->play(Rubik::L1); return;
		case 'f': case 'F': cube->play(Rubik::R1); return;
		case 'g': case 'G': cube->play(Rubik::F1); return;
		case 'h': case 'H': cube->play(Rubik::B1); return;
	}
}

// Al finalizar la aplicacion
void close ()
{
	delete cube;
	delete scene;
}

int main(int argc, char **argv)
{
	// Inicializar GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 800) >> 1, (glutGet(GLUT_SCREEN_HEIGHT) - 600) >> 1);
	glutInitWindowSize(800, 600);
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

	// Construir cubo y escenario
	cube = new Rubik(path, fov);
	scene = new Scene(path, glm::dvec4(0.70L, 0.70L, 0.8L, 0.1L));
	scene->setTexture(path + "/background.png");

	// Loop principal de GLUT
	glutMainLoop();
	return 0;
}
