#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

using namespace std;

class Thunder
{
public:
	bool visible;
	float dim;
	float x, y;
	float angle;
	float down;
	string name;
	Thunder();
	~Thunder();
	Mesh* CreateThunder(std::string name, glm::vec3 left, float dim, glm::vec3 color, bool fill);
};

