#include "BrickBreaker.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Brick.h"
#include "Circle.h"
#include "Life.h"
#include "Thunder.h"
#include "Mushroom.h"

using namespace std;

BrickBreaker::BrickBreaker()
{
}

BrickBreaker::~BrickBreaker()
{
}

// BRICKS
Brick* wall1;
Brick* wall2;
Brick* wall3;
vector <Brick*> bricks(100);
vector <Mesh*> meshe(100);
int numVisible = 100;
vector <float> scale(100);

// PLATFORM
Brick* platform;
float platformX, platformY;

// CIRCLE
Circle* circle;
float circleX, circleY;
int speedBall = 300;
float angle = 0;

// THUNDER
vector <Thunder*> thunders(20);
vector <Mesh*> meshethunders(20);
int numThunder = 20;

// MUSHROOMS
vector <Mushroom*> mushrooms(20);
vector <Mesh*> meshemushrooms(20);
int numMushroom = 20;
float big = 1;
int mushMAX = 2;
int mush;

// LIFES
vector <Life*> lifes(3);
vector <Mesh*> mesheLifes(3);
int numLifes = 3;

struct Pair
{
	Brick* brick;
	float pond;
	int go;
	bool isHit;
};

Pair hitPlatform(Brick* wall) {
	Pair out;
	out.isHit = false;
	// hit up part
	if (wall->up.y1 - 2.5 >= circleY - circle->radius && 
		wall->up.x1 <= circleX + circle->radius && wall->up.x2 >= circleX - circle->radius) {
		out.isHit = true;
		out.brick = wall;

		float middle = ((wall->up.x2 - wall->up.x1) / 2) + wall->up.x1;
		float point = (circleX - middle);

		// calculate the angle of ball's direction
		out.pond = acos(point/ ((wall->up.x2 - wall->up.x1) / 2)) - (M_PI / 2);

	}

	return out;
}

Pair hitWalls(Brick* wall) {
	Pair out;
	out.isHit = false;
	// hit down part
	if (wall->down.y1 <= circleY + circle->radius &&
		 wall->down.x2 <= circleX + circle->radius && 
		wall->down.x1 >= circleX - circle->radius) {
		out.isHit = true;
		out.brick = wall;
	}

	// hit left or right part
	if (wall->left.x1 <= circleX + circle->radius && 
		wall->left.y1 <= circleY && 
		wall->width + wall->left.x1 > circleX + circle->radius) {
		out.isHit = true;
		out.brick = wall;
	}

	return out;
}

Pair hitBricks(Brick* brick) {
	Pair out;
	out.isHit = false;

	// hit down
	if (brick->down.y1 <= circleY + circle->radius &&
		brick->down.y1 + (brick->height/2) > circleY + circle->radius &&
		brick->down.x2 <= circleX + circle->radius && 
		brick->down.x1 >= circleX - circle->radius)
	{
		out.isHit = true;
		out.brick = brick;
		circle->goingUp = false;
		circle->goingDown = true;
	}

	// hit up
	if (brick->up.y1 >= circleY - circle->radius &&
		brick->up.y1 - (brick->height / 2) < circleY - circle->radius &&
		brick->up.x2 >= circleX - circle->radius &&
		brick->up.x1 <= circleX + circle->radius)
	{
		out.isHit = true;
		out.brick = brick;
		circle->goingDown = false;
		circle->goingUp = true;
	}

	// hit left
	if (brick->left.y1 <= circleY + circle->radius &&
		brick->left.x1 + (brick->width / 2) > circleX + circle->radius &&
		brick->left.y2 >= circleY - circle->radius &&
		brick->left.x1 <= circleX + circle->radius)
	{
		out.isHit = true;
		out.brick = brick;
		circle->goingLeft = true;
		circle->goingRight = false;
	}

	// hit right
	if (brick->right.y1 >= circleY - circle->radius &&
		brick->right.x1 - (brick->width / 2) < circleX - circle->radius &&
		brick->right.y2 <= circleY + circle->radius &&
		brick->right.x1 >= circleX - circle->radius)
	{
		out.isHit = true;
		out.brick = brick;
		circle->goingLeft = false;
		circle->goingRight = true;
	}
	return out;
}

void checkGoingFast(float deltaTimeSeconds) {
	if (circle->isGoingFast)
	{
		circle->timeThunder += deltaTimeSeconds;
		if (circle->timeThunder >= 10)
		{
			speedBall = 300;
			circle->isGoingFast = false;
		}
	}
}

void checkIsBig(float deltaTimeSeconds) {
	if (circle->isBigBig)
	{
		circle->timeMushroom += deltaTimeSeconds;
		if (circle->timeMushroom >= 10)
		{
			big = 1;
			circle->isBigBig = false;
			circle->radius /= 2 * mush;
			mush = 0;
		}
	}
}

void BrickBreaker::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// create walls
	float wallW = 25;
	float wallH = 620;

	wall1 = new Brick(wallH, wallW);
	wall2 = new Brick(wallW, 1280);
	wall3 = new Brick(wallH, wallW);
	glm::vec3 corner = glm::vec3(0, 100, 0);

	Mesh* w1 = wall1->CreateBrick("wall1", corner, glm::vec3(1, 0, 0), true);
	Mesh* w2 = wall2->CreateBrick("wall2", corner + glm::vec3(0, 595, 0), glm::vec3(1, 0, 0), true);
	Mesh* w3 = wall3->CreateBrick("wall3", corner + glm::vec3(1255, 0, 0), glm::vec3(1, 0, 0), true);
	AddMeshToList(w1);
	AddMeshToList(w2);
	AddMeshToList(w3);

	// create bricks
	int index = 0, even = 2;
	int width = 65, height = 30;
	int corner_start = (1280 - (2 * wallW + (10 + width) * 10)) / 2;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			glm::vec3 start = glm::vec3(wallW + corner_start + j * (width + 10), 650 - i * (height + 10), 0);
			// NAME Brick
			string name = "brick";
			string buf, buf1;
			buf = std::to_string(i);
			buf1 = std::to_string(j);
			name.append(buf);
			name.append(buf1);


			bricks[index] = new Brick(height, width);

			// Width & Height
			bricks[index]->SetValues(height, width, name);

			// Create mesh
			if (((index + 1) % even == 0 && i % even == 0) ||
				((index + 1) % even != 0 && i % even != 0))
			{
				meshe[index] = bricks[index]->CreateBrick(name, start, glm::vec3(1, 0, 0), true);
			}
			else {
				meshe[index] = bricks[index]->CreateBrick(name, start, glm::vec3(0, 1, 0), true);
			}

			// Add to list
			AddMeshToList(meshe[index]);
			index++;
			
		}
	}

	// create mesh for platform
	int platformW = 200, platformH = 20;
	platform = new Brick(platformH, platformW);
	platformY = 50;
	corner = glm::vec3(0, 50, 0);
	Mesh* plat1 = platform->CreateBrick("plat", corner, glm::vec3(1, 1, 1), true);
	AddMeshToList(plat1);

	// create mesh for ball
	float radius = 10;
	circleX = 0;
	circleY = platformY + platformH + radius + 5;
	circle = new Circle();
	circle->isOnPlatform = true;
	corner = glm::vec3(0, 0, 0);
	Mesh* circ = circle->CreateCircle("circ", corner, radius, glm::vec3(1, 1, 1), true);
	AddMeshToList(circ);

	// create mesh for lifes
	float lifeX = 30, lifeY = 40;
	float dim = 5;
	for (int i = 0; i < numLifes; i++)
	{
		glm::vec3 startL = glm::vec3(lifeX + (dim*4 + 5) * i, lifeY, 0);
		lifes[i] = new Life();
		// NAME life
		string name2 = "Life";
		string buf2;
		buf2 = std::to_string(i);
		name2.append(buf2);

		lifes[i]->name = name2;

		mesheLifes[i] = lifes[i]->CreateLife(name2, startL, dim, glm::vec3(1, 0, 0), true);
		AddMeshToList(mesheLifes[i]);
	}

	// create mesh for thunders
	float dimThunder = 5;
	glm::vec3 startM = glm::vec3(0, 0, 0);
	for (int i = 0; i < 20; i++)
	{
		thunders[i] = new Thunder();
		string name3 = "Thunder";
		string buf3;
		buf3 = std::to_string(i);
		name3.append(buf3);

		thunders[i]->name = name3;

		meshethunders[i] = thunders[i]->CreateThunder(name3, startM, dimThunder, glm::vec3(1, 1, 0), true);
		AddMeshToList(meshethunders[i]);
	}

	//create mesh for mushrooms
	float dimMushroom = 5;
	glm::vec3 startT = glm::vec3(0, 0, 0);
	for (int i = 0; i < 20; i++)
	{
		mushrooms[i] = new Mushroom();
		string name4 = "Mushroom";
		string buf4;
		buf4 = std::to_string(i);
		name4.append(buf4);

		mushrooms[i]->name = name4;

		meshemushrooms[i] = mushrooms[i]->CreateMushroom(name4, startT, dimThunder, glm::vec3(1, 0, 0), true);
		AddMeshToList(meshemushrooms[i]);
	}
	
	// Scale - used for thunder power up (the ball is getting bigger)
	for (int i = 0; i < 100; i++) {
		scale[i] = 1;
	}
}

void BrickBreaker::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void BrickBreaker::Update(float deltaTimeSeconds)
{
	checkGoingFast(deltaTimeSeconds);
	checkIsBig(deltaTimeSeconds);
	
	// draw WALL 1
	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["wall1"], shaders["VertexColor"], modelMatrix);

	// draw WALL 2
	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["wall2"], shaders["VertexColor"], modelMatrix);

	// draw WALL 3
	modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["wall3"], shaders["VertexColor"], modelMatrix);

	// draw BRICKS
	bool hitSmth = false;

	for (int i = 0; i < 100; i++) {
		modelMatrix = glm::mat3(1);
		// draw bricks that weren't hit
		if (bricks[i]->visible) {
			Pair hit = hitBricks(bricks[i]);
			if (hit.isHit) {
				bricks[i]->visible = false;
				bricks[i]->inScale = true;
				hitSmth = true;

				// put random powerup - move faster
				if (i % 7 == 0 && numThunder > 0)
				{
					float xt = bricks[i]->left.x1 + bricks[i]->width / 2;
					float yt = bricks[i]->left.y1 + bricks[i]->height / 2;
					thunders[numThunder - 1]->visible = true;
					thunders[numThunder - 1]->x = xt;
					thunders[numThunder - 1]->y = yt;
					numThunder--;
				}

				// put random powerup - getting bigger
				if (i % 9 == 0 && numMushroom > 0)
				{
					float xt = bricks[i]->left.x1 + bricks[i]->width / 2;
					float yt = bricks[i]->left.y1 + bricks[i]->height / 2;
					mushrooms[numMushroom - 1]->visible = true;
					mushrooms[numMushroom - 1]->smaller = true;
					mushrooms[numMushroom - 1]->x = xt;
					mushrooms[numMushroom - 1]->y = yt;
					numMushroom--;
				}
			}
		}

		// bricks that were hit need to get smaller until they disapear
		if (bricks[i]->inScale)
		{
			float xOld = bricks[i]->left.x1 + bricks[i]->width / 2;
			float yOld = bricks[i]->left.y1 + bricks[i]->height / 2;

			float xNew = -bricks[i]->left.x1 - bricks[i]->width / 2;
			float yNew = -bricks[i]->left.y1 - bricks[i]->height / 2;
			if (scale[i] <= 0) {
				bricks[i]->visible = false;
				bricks[i]->inScale = false;
				numVisible--;
			}
			scale[i] -= deltaTimeSeconds;
			modelMatrix *= Transform2D::Translate(xOld, yOld);
			modelMatrix *= Transform2D::Scale(scale[i], scale[i]);
			modelMatrix *= Transform2D::Translate(xNew, yNew);
			RenderMesh2D(meshes[bricks[i]->name], shaders["VertexColor"], modelMatrix);
		}
		
		
		if (bricks[i]->visible)
		{
			RenderMesh2D(meshes[bricks[i]->name], shaders["VertexColor"], modelMatrix);
		}
	}

	// PLATFORM
	modelMatrix = glm::mat3(1);
	if (platformX < 1080 && platformX > 0) {
		modelMatrix *= Transform2D::Translate(platformX, 0);
		platform->SetEdges(glm::vec3(platformX, platformY, 0));
	} else if (platformX < 0) {
		modelMatrix *= Transform2D::Translate(0 , 0);
		platform->SetEdges(glm::vec3(0, platformY, 0));
	} else {
		modelMatrix *= Transform2D::Translate(1080, 0);
		platform->SetEdges(glm::vec3(platformX, platformY, 0));
	}
	RenderMesh2D(meshes["plat"], shaders["VertexColor"], modelMatrix);

	// BALL
	modelMatrix = glm::mat3(1);
	if (circle->isOnPlatform) {
		if (platformX < 1080 && platformX > 0) {
			circleX = platformX + platform->width / 2;
		}
		else if (platformX < 0) {
			circleX = 0 + platform->width / 2;
		}
		else {
			circleX = 1080 + platform->width / 2;
		}
	}
	else {
		// hit walls ?
		float add = 0;
		Pair hitWall1 = hitWalls(wall2);
		Pair hitWall2 = hitWalls(wall1);
		Pair hitWall3 = hitWalls(wall3);

		// change direction of the ball in case it hit a wall
		if (hitWall1.isHit && !hitSmth) {
			circle->goingUp = false;
			circle->goingDown = true;
			hitSmth = true;
		}

		if (hitWall2.isHit && !hitSmth) {
			circle->goingLeft = false;
			circle->goingRight = true;
			hitSmth = true;
		}

		if (hitWall3.isHit && !hitSmth) {
			circle->goingRight = false;
			circle->goingLeft = true;
			hitSmth = true;
		}

		Pair hit = hitPlatform(platform);
		if (hit.isHit && !hitSmth)
		{
			circle->goingUp = !circle->goingUp;
			add = hit.pond;
			angle = add;
			hitSmth = true;
			if (hit.pond == 0) {
				circle->goingUp = true;
				circle->goingLeft = false;
				circle->goingRight = false;
				circle->goingDown = false;
			}

			if (hit.pond > 0) {
				circle->goingLeft = true;
				circle->goingUp = true;
				circle->goingRight = false;
				circle->goingDown = false;
			}

			if (hit.pond < 0) {
				circle->goingRight = true;
				circle->goingLeft = false;
				circle->goingUp = true;
				circle->goingDown = false;
				angle *= -1;
			}
		}
		
		if (circle->goingUp) {
			circleY += deltaTimeSeconds * speedBall;
		} 
		if (circle->goingLeft){
			circleX -= deltaTimeSeconds * speedBall * angle;
		} 
		if (circle->goingRight) {
			circleX += deltaTimeSeconds * speedBall * angle;
		}
		if (circle->goingDown) {
			circleY -= deltaTimeSeconds * speedBall;
		}
	}
	
	// Game over
	if (circleY < platformY  || numLifes == 0) {
		if (circle->isBigBig)
		{
			big = 1;
			circle->isBigBig = false;
			circle->radius /= 2 * mush;
			mush = 0;
		}
		if (circle->isGoingFast)
		{
			speedBall = 300;
			circle->isGoingFast = false;
		}
		circle->isOnPlatform = true;
		circleY = platformY + platform->height + circle->radius + 5;
		numLifes--;
	}
	else {
		modelMatrix *= Transform2D::Translate(circleX, circleY);
		modelMatrix *= Transform2D::Scale(big, big);
		RenderMesh2D(meshes["circ"], shaders["VertexColor"], modelMatrix);
	}
	
	
	// LIFES
	for (int i = 0; i < numLifes; i++)
	{
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes[lifes[i]->name], shaders["VertexColor"], modelMatrix);
	}

	// Thunders
	for (int i = 0; i < 20; i++)
	{
		if (thunders[i]->visible) {
			thunders[i]->angle += 2 * deltaTimeSeconds;
			thunders[i]->down -= deltaTimeSeconds * 100;
			modelMatrix = glm::mat3(1);

			modelMatrix *= Transform2D::Translate(0, thunders[i]->down);
			modelMatrix *= Transform2D::Translate(thunders[i]->x, thunders[i]->y);
			modelMatrix *= Transform2D::Rotate(thunders[i]->angle);
			modelMatrix *= Transform2D::Translate(-thunders[i]->x, -thunders[i]->y);
			modelMatrix *= Transform2D::Translate(-2*thunders[i]->dim, -3 * thunders[i]->dim - thunders[i]->dim / 2);
			modelMatrix *= Transform2D::Translate(thunders[i]->x, thunders[i]->y);
			RenderMesh2D(meshes[thunders[i]->name], shaders["VertexColor"], modelMatrix);

			float x = -2 * thunders[i]->dim + thunders[i]->x;
			float y = -(3 * thunders[i]->dim - thunders[i]->dim / 2) + thunders[i]->y + thunders[i]->down;

			if (y < platform->down.y1 + platform->height / 2 && 
				x >= platform->up.x1 && x <= platform->up.x2 && 
				y > platform->down.y1)
			{
				thunders[i]->visible = false;
				speedBall = 300 * 1.7;
				circle->isGoingFast = true;
				circle->timeThunder = 0;
			}

		}
		
	}

	// Mushrooms
	for (int i = 0; i < 20; i++)
	{
		if (mushrooms[i]->visible) {
			mushrooms[i]->angle += 2 * deltaTimeSeconds;
			mushrooms[i]->down -= deltaTimeSeconds * 100;
			modelMatrix = glm::mat3(1);
			if (mushrooms[i]->bigger)
			{
				mushrooms[i]->smaller = false;
				mushrooms[i]->scale +=  deltaTimeSeconds/2;
				if (mushrooms[i]->scale >= 1)
				{
					mushrooms[i]->smaller = true;
					mushrooms[i]->bigger = false;
				}
			}
			else if (mushrooms[i]->smaller) {
				mushrooms[i]->bigger = false;
				mushrooms[i]->scale -=  deltaTimeSeconds/2;
				if (mushrooms[i]->scale <= 0.5)
				{
					mushrooms[i]->smaller = false;
					mushrooms[i]->bigger = true;
				}
			}
			
			modelMatrix *= Transform2D::Translate(0, mushrooms[i]->down);
			modelMatrix *= Transform2D::Translate(mushrooms[i]->x, mushrooms[i]->y);
			modelMatrix *= Transform2D::Rotate(mushrooms[i]->angle);
			modelMatrix *= Transform2D::Scale(mushrooms[i]->scale, mushrooms[i]->scale);
			modelMatrix *= Transform2D::Translate(-mushrooms[i]->dim, -5 * mushrooms[i]->dim);
			RenderMesh2D(meshes[mushrooms[i]->name], shaders["VertexColor"], modelMatrix);

			float x = -mushrooms[i]->dim + mushrooms[i]->x;
			float y = -5 * mushrooms[i]->dim + mushrooms[i]->y + mushrooms[i]->down;

			if (y < platform->down.y1 + platform->height / 2 && 
				x >= platform->up.x1 && x <= platform->up.x2 && 
				y > platform->down.y1 &&
				mush < mushMAX)
			{
				mushrooms[i]->visible = false;
				circle->radius *= 2;
				big *= 2;
				mush++;
				circle->isBigBig = true;
				circle->timeMushroom = 0;
			}

		}

	}

	// The game is over or no more lifes
	if (numLifes == 0 || numVisible == 0)
	{
		// Reset all
		for (int i = 0; i < 100; i++)
		{
			bricks[i]->visible = true;
			bricks[i]->inScale = false;
			scale[i] = 1;
		}
		for (int i = 0; i < 20; i++)
		{
			thunders[i]->visible = false;
			mushrooms[i]->visible = false;
		}
		numLifes = 3;
		numVisible = 100;
		circle->isOnPlatform = true;
		circleY = platformY + platform->height + circle->radius + 5;
	}
}

void BrickBreaker::FrameEnd()
{

}

void BrickBreaker::OnInputUpdate(float deltaTime, int mods)
{
	
}

void BrickBreaker::OnKeyPress(int key, int mods)
{
	// add key press event
}

void BrickBreaker::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void BrickBreaker::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	platformX = (float) mouseX - 100;
}

void BrickBreaker::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	circle->isOnPlatform = false;
	//circle->goingUp = !circle->goingUp;
}

void BrickBreaker::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void BrickBreaker::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void BrickBreaker::OnWindowResize(int width, int height)
{
}
