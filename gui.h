#ifndef GUI_H
#define GUI_H

#include <object.h>

#include <vao.h>
#include <texture.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class GUI
{
	protected:
		static VAO *square;


	public:
		GUI();
};

#endif // GUI_H
