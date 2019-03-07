#include "Mushroom.h"

#include <string>
#include <Core/Engine.h>

using namespace std;

Mushroom::Mushroom() {
}

Mushroom::~Mushroom() {
}

Mesh* Mushroom::CreateMushroom(std::string name, glm::vec3 leftCorner, float dim, glm::vec3 color, bool fill)
{
	this->visible = false;
	this->dim = dim;
	this->angle = 0;
	this->down = 0;
	this->scale = 1;
	glm::vec3 corner = leftCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(-1 * dim, 0, 0), glm::vec3(0.941f, 0.917f, 0.839f)), // 0
		VertexFormat(corner + glm::vec3(3 * dim, 0 * dim, 0), glm::vec3(0.941f, 0.917f, 0.839f)), // 1
		VertexFormat(corner + glm::vec3(2 * dim, 3 * dim, 0), glm::vec3(0.941f, 0.917f, 0.839f)), // 2

		VertexFormat(corner + glm::vec3(-1 * dim, 0, 0), glm::vec3(0.941f, 0.917f, 0.839f)), // 0
		VertexFormat(corner + glm::vec3(2 * dim, 3 * dim, 0), glm::vec3(0.941f, 0.917f, 0.839f)), // 2
		VertexFormat(corner + glm::vec3(0 * dim, 3 * dim, 0), glm::vec3(0.941f, 0.917f, 0.839f)), // 3

		VertexFormat(corner + glm::vec3(-2 * dim, 3 * dim, 0), color), // 4
		VertexFormat(corner + glm::vec3(-2 * dim, 5 * dim, 0), color), // 5
		VertexFormat(corner + glm::vec3(4 * dim, 5 * dim, 0), color), // 6

		VertexFormat(corner + glm::vec3(-2 * dim, 3 * dim, 0), color), // 4
		VertexFormat(corner + glm::vec3(4 * dim, 5 * dim, 0), color), // 6
		VertexFormat(corner + glm::vec3(4 * dim, 3 * dim, 0), color), // 7

		VertexFormat(corner + glm::vec3(4 * dim, 5 * dim, 0), glm::vec3(1, 1, 1)), // 6
		VertexFormat(corner + glm::vec3(4 * dim, 3 * dim, 0), glm::vec3(1, 1, 1)), // 7
		VertexFormat(corner + glm::vec3(5 * dim, 4 * dim, 0), glm::vec3(1, 1, 1)), // 8

		VertexFormat(corner + glm::vec3(-2 * dim, 3 * dim, 0), color), // 4
		VertexFormat(corner + glm::vec3(-2 * dim, 5 * dim, 0), color), // 5
		VertexFormat(corner + glm::vec3(-3 * dim, 4 * dim, 0), color), // 9

		VertexFormat(corner + glm::vec3(-2 * dim, 5 * dim, 0), glm::vec3(1, 1, 1)), // 5
		VertexFormat(corner + glm::vec3(1 * dim, 5 * dim, 0), glm::vec3(1, 1, 1)), // 10
		VertexFormat(corner + glm::vec3(0 * dim, 8 * dim, 0), glm::vec3(1, 1, 1)), // 11

		VertexFormat(corner + glm::vec3(1 * dim, 5 * dim, 0), color), // 10
		VertexFormat(corner + glm::vec3(0 * dim, 8 * dim, 0), color), // 11
		VertexFormat(corner + glm::vec3(2 * dim, 8 * dim, 0), color), // 12

		VertexFormat(corner + glm::vec3(1 * dim, 5 * dim, 0), color), // 10
		VertexFormat(corner + glm::vec3(2 * dim, 8 * dim, 0), color), // 12
		VertexFormat(corner + glm::vec3(4 * dim, 5 * dim, 0), color), // 6
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices;
	
	for (int i = 0; i < 27; i++)
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

