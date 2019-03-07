#include "Brick.h"

#include <string>
#include <Core/Engine.h>

using namespace std;

void Brick::SetEdges(glm::vec3 corner)
{
	this->left.x1 = corner.x;
	this->left.y1 = corner.y;
	this->left.x2 = corner.x;
	this->left.y2 = corner.y + height;

	this->up.x1 = corner.x;
	this->up.y1 = corner.y + height;
	this->up.x2 = corner.x + width;
	this->up.y2 = corner.y + height;

	this->right.x1 = corner.x + width;
	this->right.y1 = corner.y + height;
	this->right.x2 = corner.x + width;
	this->right.y2 = corner.y;

	this->down.x1 = corner.x + width;
	this->down.y1 = corner.y;
	this->down.x2 = corner.x;
	this->down.y2 = corner.y;
}

Brick::Brick(float height, float width) {
	this->height = height;
	this->width = width;
}

Brick::~Brick() {
}

Mesh* Brick::CreateBrick(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	this->left.x1 = corner.x;
	this->left.y1 = corner.y;
	this->left.x2 = corner.x;
	this->left.y2 = corner.y + height;

	this->up.x1 = corner.x;
	this->up.y1 = corner.y + height;
	this->up.x2 = corner.x + width;
	this->up.y2 = corner.y + height;

	this->right.x1 = corner.x + width;
	this->right.y1 = corner.y + height;
	this->right.x2 = corner.x + width;
	this->right.y2 = corner.y;

	this->down.x1 = corner.x + width;
	this->down.y1 = corner.y;
	this->down.x2 = corner.x;
	this->down.y2 = corner.y;
	visible = true;
	inScale = false;


	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

void Brick::SetValues(float height, float width, string name) {
	this->height = height;
	this->width = width;
	this->name = name;
}