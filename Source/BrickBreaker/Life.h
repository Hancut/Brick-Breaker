#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

using namespace std;

class Life
{
public:
	float height, width;
	string name;
	Life();
	~Life();
	Mesh* CreateLife(std::string name, glm::vec3 left, float dim, glm::vec3 color, bool fill);
};

