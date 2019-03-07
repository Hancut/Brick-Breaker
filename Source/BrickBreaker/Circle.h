#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

using namespace std;
struct Point
{
	float x, y;
};
class Circle
{
public:
	Point center;
	float radius;
	bool goingUp;
	bool goingDown;
	bool goingLeft;
	bool goingRight;
	bool isOnPlatform;
	bool isGoingFast;
	bool isBigBig;
	float timeThunder;
	float timeMushroom;
	Circle::Circle();
	Circle::~Circle();
	// Create square with given bottom left corner, length and color
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);

};

