#include <texture.h>

// Construye la textura
void Texture::build (GLubyte *const image)
{
	// Textura
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Asignacion de datos
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Mipmap y parametros
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Desactiva la textura
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Constructor
Texture::Texture (const std::string &path) : texture(0)
{
	// Lee la textura
	GLubyte *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	// Validacion de la lectura del archivo
	if (image == NULL) std::cerr << "Error: no se puede abrir `" << path << "'." << std::endl;

	// Se construye la textura
	else build(image);

	// Libera memoria
	SOIL_free_image_data(image);
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

// Obtiene el ID de la textura
bool Texture::valid () const
{
	return texture != 0;
}

// Destructor
Texture::~Texture()
{
	// Destruye la textura
	glDeleteTextures(1, &texture);

	// Resetea valores por defecto
	texture = 0;
}

