#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

using namespace std;
struct Edge
{
	float x1, x2;
	float y1, y2;
};

class Brick
{
public:
	void SetEdges(glm::vec3 corner);
	float height, width;
	bool visible;
	bool inScale;
	Edge left, right, up, down;
	string name;
	Brick(float height, float width);
	~Brick();
	
	Mesh* CreateBrick(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color, bool fill = false);
	void SetValues(float height, float width, string name);
};

