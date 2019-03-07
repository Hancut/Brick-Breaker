#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

using namespace std;

class Mushroom
{
public:
	bool visible;
	float dim;
	float x, y;
	float angle;
	float down;
	float scale;
	bool bigger;
	bool smaller;
	string name;
	Mushroom();
	~Mushroom();
	Mesh* CreateMushroom(std::string name, glm::vec3 left, float dim, glm::vec3 color, bool fill);
};

