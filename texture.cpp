#include <texture.h>

// Construye la textura
void Texture::build (GLubyte *const image)
{
	// Textura
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Asignacion de datos
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	// Mipmap y parametros
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Desactiva la textura y libera memoria
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}

// Constructor
Texture::Texture (const std::string &path) : texture(0)
{
	// Lee la textura
	GLubyte *const image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	// Si se lee correctamente se construye
	if (image != NULL) build(image);
}

// Habilita la textura
void Texture::enable () const
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

// Desabilita la textura
void Texture::disable () const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Destructor
Texture::~Texture()
{
	// Destruye la textura
	glDeleteTextures(1, &texture);

	// Resetea valores por defecto
	texture = 0;
}


