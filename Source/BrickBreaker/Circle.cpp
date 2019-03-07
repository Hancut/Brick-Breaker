#include "Circle.h"

#include <Core/Engine.h>
#include <math.h>

using namespace std;

Circle::Circle(){

}

Circle::~Circle() {

}
Mesh* Circle::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
	this->goingUp = true;
	this->goingRight = false;
	this->goingLeft = false;
	this->goingDown = false;
	this->center.x = center.x;
	this->center.y = center.y;
	this->radius = radius;
	this->isBigBig = false;
	this->isGoingFast = false;

	std::vector <VertexFormat> vertices;
	VertexFormat a = VertexFormat(center, color);
	vertices.push_back(a);

	for (int i = 0; i < 1000; i++)
	{
		double angle = 2 * M_PI * i / 700;
		double x = radius * cos(angle);
		double y = radius * sin(angle);
		VertexFormat a = VertexFormat(center + glm::vec3(x, y, 0), color);
		vertices.push_back(a);
	}

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices;
	for (int i = 0; i < 700; i++) {
		indices.push_back(i);
	}
	
	square->SetDrawMode(GL_TRIANGLE_FAN);
	
	square->InitFromData(vertices, indices);
	return square;
}