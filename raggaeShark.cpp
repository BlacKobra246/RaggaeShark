#include "raggaeShark.h"

Color deepBlack = { 20, 20, 20, 255 }; // Very dark grey (close to black)

RaggaeShark::RaggaeShark()
{
	//Loads the regular face of the player.
	chill_L = LoadTexture("assets/Raggae_Shark_L.png");
	chill_R = LoadTexture("assets/Raggae_Shark_R.png");
	chill_U = LoadTexture("assets/Raggae_Shark_U.png");
	chill_D = LoadTexture("assets/Raggae_Shark_D.png");

	//Loads the eating "animation" of the player.
	eat_L = LoadTexture("assets/Raggae_Eats_L.png");
	eat_R = LoadTexture("assets/Raggae_Eats_R.png");
	eat_U = LoadTexture("assets/Raggae_Eats_U.png");
	eat_D = LoadTexture("assets/Raggae_Eats_D.png");

	facingDir = 'R';
}

RaggaeShark::~RaggaeShark()
{
	UnloadTexture(chill_L);
	UnloadTexture(chill_R);
	UnloadTexture(chill_D);
	UnloadTexture(chill_U);

	UnloadTexture(eat_L);
	UnloadTexture(eat_R);
	UnloadTexture(eat_U);
	UnloadTexture(eat_D);
}

void RaggaeShark::draw(bool eating)
{
	int i;
	float x = 0, y = 0; // Declare x, y outside the loop

	for (i = 1; i <= body.size(); i++)
	{
		// This is the HEAD (we draw it last to avoid overlap in tail texture)
		if (i == body.size())
		{
			x = body[0].x;
			y = body[0].y;
		}
		//We handle tail.
		else
		{
			x = body[i].x;
			y = body[i].y;

			float center_x, center_y;
			centerTail(&center_x, &center_y);
			Rectangle segment = Rectangle{((x + center_x) * (float)Cell_Size),((y + center_y) * (float)Cell_Size),Cell_Size,Cell_Size};
			DrawRectangleRounded(segment, 0.6, 0.6, deepBlack);
		}

		// If this is the head, draw it *after* the rest
		if (i == body.size())
		{
			// Determine texture based on direction and eating state
			Texture2D textureToDraw;
			switch (facingDir)
			{
			case 'U': textureToDraw = eating ? eat_U : chill_U; break;
			case 'D': textureToDraw = eating ? eat_D : chill_D; break;
			case 'L': textureToDraw = eating ? eat_L : chill_L; break;
			case 'R': textureToDraw = eating ? eat_R : chill_R; break;
			}

			DrawTextureEx(textureToDraw,Vector2{ (x * (float)Cell_Size), (y * (float)Cell_Size) },0.0f, 1.0f, WHITE);
		}
	}
}


void RaggaeShark::update(bool eating)
{
	if (!eating)
	{
		body.pop_back();
	}
	body.push_front(Vector2Add(body[0], dir));
}


void RaggaeShark::setFacing(char facing)
{
	facingDir = facing;
}

char RaggaeShark::getFacing() const
{
	return facingDir;
}

void RaggaeShark::centerTail(float* x, float* y) const
{
	// No tail to adjust if only the head exists
	if (body.size() < 2)
	{
		return; 
	}

	Vector2 tail = body.back();                       // Last segment (tail)
	Vector2 beforeTail = body[body.size() - 2];       // Segment before tail
	Vector2 diff = Vector2Subtract(tail, beforeTail); // Tail movement direction

	// Check where the tail is relative to the previous segment (to center it)
		// Tail moving right:
	if (diff.x > 0)
	{
		*x = 0.25;
		*y = 0.5;
	}
		// Tail moving left
	else if (diff.x < 0)
	{
		*x = 0.75;
		*y = 0.5;
	}
		// Tail moving down
	else if (diff.y > 0)
	{ 
		*x = 0.5;
		*y = 0.25;
	}
		// Tail moving up
	else if (diff.y < 0) 
	{
		*x = 0.5;
		*y = 0.75;
	} 
}


Vector2 RaggaeShark::getLocation() const
{
	return body[0];
}

bool RaggaeShark::hitHimself() const
{
	int i;

	//check for a collosion of the head with the rest of the body.
	for (i = 1; i < body.size(); i++)
	{
		float x = body[i].x;
		float y = body[i].y;

		if ((body[0].x == body[i].x) && body[0].y == body[i].y)
		{
			return true;
		}
	}
	return false;
}