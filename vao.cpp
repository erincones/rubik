#include <vao.h>

// Inicializar
void VAO::load (const std::vector<glm::vec3> &vertex, const std::vector<glm::vec3> &normal, const std::vector<glm::vec2> &texture)
{
	// Dimensiones
	vertices = (GLsizei) vertex.size();
	std::size_t vertex_size = vertex.size() * sizeof(glm::vec3);
	std::size_t normal_size = normal.size() * sizeof(glm::vec3);
	std::size_t texture_size = texture.size() * sizeof(glm::vec2);

	// Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Asignacion de datos
	glBufferData(GL_ARRAY_BUFFER, vertex_size + normal_size + texture_size, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_size, &vertex[0][0]);
	glBufferSubData(GL_ARRAY_BUFFER, vertex_size, normal_size, &normal[0][0]);
	glBufferSubData(GL_ARRAY_BUFFER, vertex_size + normal_size, texture_size, &texture[0][0]);
	
	// Paso de atributos
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glNormalPointer(GL_FLOAT, 0, BUFFER_OFFSET(vertex_size));
	glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(vertex_size + normal_size));

	// Desactiva los array objects
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// Constructor
VAO::VAO (const std::string &path)
{
	// Valida el archivo
	std::ifstream file(path.c_str());
	if(!file.is_open())
	{
		std::cerr << "Error: no se puede abrir `" << path << "'." << std::endl;
		exit(1);
	}

	// Datos del modelo
	std::vector<glm::vec3> vertexRAW;
	std::vector<glm::vec3> normalRAW;
	std::vector<glm::vec2> textureRAW;

	// Indices de caras
	std::vector<glm::vec3> vertex;
	std::vector<glm::vec3> normal;
	std::vector<glm::vec2> texture;


	// Lee cada linea
	GLint vind[3] = {0};
	GLint nind[3] = {0};
	GLint tind[3] = {0};
	glm::vec3 data;
	std::string line;
	std::string token;
	while (!file.eof())
	{
		std::getline(file, line);

		// Ignora comentarios
		if (line.empty() || line[0] == '#') continue;

		// Elimina espacios finales
		while (std::isspace(line[line.size() - 1])) line.resize(line.size() - 1);

		// Obtiene el primer token
		std::istringstream stream(line);
		stream >> token;

		// Lee un vertice
		if (token == "v")
		{
			stream >> data.x >> data.y >> data.z;
			vertexRAW.push_back(data);
		}

		// Lee un vector normal
		else if (token == "vn")
		{
			stream >> data.x >> data.y >> data.z;
			normalRAW.push_back(data);
		}

		// Lee una coordenada de textura
		else if (token == "vt")
		{
			stream >> data.x >> data.y;
			textureRAW.push_back(glm::vec2(data.x, data.y));
		}

		// Lee una cara
		else if (token == "f")
		{
			//f 50//1 1//2 15//3
			std::sscanf(line.c_str(), "%*s %d/%d/%d %d/%d/%d %d/%d/%d\n", &vind[0], &tind[0], &nind[0], &vind[1], &tind[1], &nind[1], &vind[2], &tind[2], &nind[2]);

			// Vertices
			vertex.push_back(vertexRAW[vind[0] - 1]);
			vertex.push_back(vertexRAW[vind[1] - 1]);
			vertex.push_back(vertexRAW[vind[2] - 1]);

			// Normales
			normal.push_back(normalRAW[nind[0] - 1]);
			normal.push_back(normalRAW[nind[1] - 1]);
			normal.push_back(normalRAW[nind[2] - 1]);

			// Textura
			texture.push_back(normalRAW[tind[0] - 1]);
			texture.push_back(normalRAW[tind[1] - 1]);
			texture.push_back(normalRAW[tind[2] - 1]);
		}
	}

	// Limpia memoria
	vertexRAW.clear();
	normalRAW.clear();

	load(vertex, normal, texture);
}

// Dibujar
void VAO::draw () const
{
	// Activar Vertex Array Object
	glBindVertexArray(vao);

	// Habilita los estados del cliente
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Dibujar triangulos
	glDrawArrays(GL_TRIANGLES, 0, vertices);

	// Deshabilita los estados del cliente
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Desactiva Vertex Array Object
	glBindVertexArray(0);

}

// Destructor
VAO::~VAO ()
{
	// Libera los Vertex Buffer Object
	glDeleteBuffers(1, &vbo);

	// Libera el Vertex Array Object
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);

	vertices = 0;

	vao = 0;
	vbo = 0;
}
