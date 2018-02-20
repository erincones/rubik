#include <light.h>

// Variables estaticas
bool Light::globalState = false;


// Constructor
Light::Light (const TYPE &light)
{
	// Asigna el tipo
	type = light;
	id = GL_LIGHT0;
	state = false;

	// Propiedades
	ambient  = glm::vec4(0.00F, 0.00F, 0.00F, 1.0F);
	diffuse  = glm::vec4(1.00F, 1.00F, 1.00F, 1.0F);
	specular = glm::vec4(1.00F, 1.00F, 1.00F, 1.0F);
	position = glm::vec4(0.10F, 0.15F, 0.98F, 0.0F);

	// Configura las propiedades
	glLightfv(id, GL_AMBIENT, glm::value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, glm::value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, glm::value_ptr(specular));
	glLightfv(id, GL_POSITION, glm::value_ptr(position));

	// Enciende la luz
	turnOn();
}


// Activa la iluminacion
void Light::globalTurnOn ()
{
	glEnable(GL_LIGHTING);
	Light::globalState = true;
}

// Desactiva la iluminacion
void Light::globalTurnOff ()
{
	glDisable(GL_LIGHTING);
	Light::globalState = true;
}


// Enciende la luz
void Light::turnOn ()
{
	glEnable(id);
	state = true;
}

// Apaga la luz
void Light::turnOff ()
{
	glDisable(id);
	state = false;
}
