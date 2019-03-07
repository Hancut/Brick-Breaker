#include "Life.h"

#include <string>
#include <Core/Engine.h>

using namespace std;

Life::Life() {
}

Life::~Life() {
}

Mesh* Life::CreateLife(std::string name, glm::vec3 leftCorner, float dim, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(dim, dim, 0), color),
		VertexFormat(corner + glm::vec3(dim * 2, 0, 0), color),
		VertexFormat(corner + glm::vec3(dim * 2, 0, 0), color),
		VertexFormat(corner + glm::vec3(dim *3, dim, 0), color),
		VertexFormat(corner + glm::vec3(dim *4, 0, 0), color),
		VertexFormat(corner + glm::vec3(dim * 4, 0, 0), color),
		VertexFormat(corner + glm::vec3(dim * 2, -dim*2, 0), color),
		VertexFormat(corner, color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
	
	if (fill)
	{
		square->SetDrawMode(GL_TRIANGLES);
	}
	
	
	square->InitFromData(vertices, indices);
	return square;
}

