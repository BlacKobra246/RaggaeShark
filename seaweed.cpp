#include "seaweed.h"

Seaweed::Seaweed()
{
	firstAnimation = LoadTexture("assets/seaweed_1.png");
	secondAnimation = LoadTexture("assets/seaweed_2.png");
	animationState = GetRandomValue(0, 1);
	Random_X_Cords = GetRandomValue(Beg_Ocean_Width, End_Ocean_Width);
	ticks = 0;
}

Seaweed::~Seaweed()
{
	UnloadTexture(firstAnimation);
	UnloadTexture(secondAnimation);
}

void Seaweed::draw() const
{
	if (animationState == 0)
	{
		DrawTexture(firstAnimation, Random_X_Cords, Ocean_Bottom, WHITE);
	}
	else
	{
		DrawTexture(secondAnimation, Random_X_Cords, Ocean_Bottom, WHITE);
	}
}

void Seaweed::Animation(int speedUp)
{
	//Calculates a fixed time for the animation, independent from the game_pace that keeps changing.
	ticks += ((Game_Pace) - speedUp);

	if (ticks > Seaweed_Animation_Rate)
	{
		ticks = 0;
		if (animationState == 0)
		{
			animationState = 1;
			DrawTexture(secondAnimation, Random_X_Cords, Ocean_Bottom, WHITE);
		}
		else
		{
			animationState = 0;
			DrawTexture(firstAnimation, Random_X_Cords, Ocean_Bottom, WHITE);
		}
	}
}