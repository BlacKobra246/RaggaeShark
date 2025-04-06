#include "munchies.h"

Munchies::Munchies()
{
	munchies = LoadTexture("assets/Munchies.png");
	pos = generateRandomPos();
}

Munchies::~Munchies()
{
	UnloadTexture(munchies);
}

void Munchies::draw()
{
	DrawTextureEx(munchies, Vector2{ (pos.x * (float)Cell_Size), (pos.y * (float)Cell_Size) }, 0.0f, 1.0f, WHITE);
}

Vector2 Munchies::generateRandomPos() const{
		float x = GetRandomValue(2, Cell_Count - 2);
		float y = GetRandomValue(2, Cell_Count - 2);

		return Vector2{(x),(y)};
}

Vector2 Munchies::getPos() const
{
	return pos;
}

void Munchies::setNewPos()
{
	pos = generateRandomPos();
}
