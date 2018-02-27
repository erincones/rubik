#ifndef LIGHT_H
#define LIGHT_H

#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>


class Light
{
	public:
		// Tipo de luz
		enum TYPE {DIRECTIONAL, POSITIONAL};

	protected:
		// Contador de luces
		//static std::map<GLuint, bool> counter;

		// Identificacion
		GLuint id;
		Light::TYPE type;

		// Propiedades
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::vec4 position;
		glm::vec4 direction;

		// Estado
		static bool globalState;
		bool state;


	public:
		// Costructor
		Light (const Light::TYPE &light = Light::DIRECTIONAL);

		// Encender y apagar iluminacion
		static void globalTurnOn ();
		static void globalTurnOff ();

		// Encender y apagar
		void turnOn ();
		void turnOff ();
};

#endif // LIGHT_H
