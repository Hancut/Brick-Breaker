#include "Thunder.h"

#include <string>
#include <Core/Engine.h>

using namespace std;

Thunder::Thunder() {
}

Thunder::~Thunder() {
}

Mesh* Thunder::CreateThunder(std::string name, glm::vec3 leftCorner, float dim, glm::vec3 color, bool fill)
{
	this->visible = false;
	this->dim = dim;
	this->angle = 0;
	this->down = 0;
	glm::vec3 corner = leftCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color), // 0
		VertexFormat(corner + glm::vec3(2 * dim, 3 * dim, 0), color), // 1
		VertexFormat(corner + glm::vec3(3 * dim, 3 * dim, 0), color), // 2
		VertexFormat(corner + glm::vec3(3 * dim, 3 * dim, 0), color), // 2
		VertexFormat(corner + glm::vec3(4 * dim, 4 * dim, 0), color), // 3
		VertexFormat(corner + glm::vec3(0, 3 * dim, 0), color), // 4
		VertexFormat(corner + glm::vec3(4 * dim, 4 * dim, 0), color), // 3
		VertexFormat(corner + glm::vec3(0, 3 * dim, 0), color), // 4
		VertexFormat(corner + glm::vec3(0, 4 * dim, 0), color), // 5
		VertexFormat(corner + glm::vec3(0, 4 * dim, 0), color), // 5
		VertexFormat(corner + glm::vec3(2 * dim, 4 * dim, 0), color), // 6
		VertexFormat(corner + glm::vec3(3 * dim, 6 * dim, 0), color), // 7
		VertexFormat(corner + glm::vec3(3 * dim, 6 * dim, 0), color), // 7
		VertexFormat(corner + glm::vec3(0, 4 * dim, 0), color), // 5
		VertexFormat(corner + glm::vec3(dim, 6 * dim, 0), color), // 8
		VertexFormat(corner + glm::vec3(0, 3 * dim, 0), color), // 4
		VertexFormat(corner + glm::vec3(0, 4 * dim, 0), color), // 5
		VertexFormat(corner + glm::vec3(-dim / 2, 3 * dim, 0), color), // 9
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices;
	
	for (int i = 0; i < 18; i++)
	{
		indices.push_back(i);
	}

	if (fill)
	{
		square->SetDrawMode(GL_TRIANGLES);
	}
	
	
	square->InitFromData(vertices, indices);
	return square;
}

