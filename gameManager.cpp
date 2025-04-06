#include "gameManager.h"
#include "munchies.h"
#include "seaweed.h"
#include <thread>
#include <chrono>

using namespace std::chrono;      //For the game pace ! 
using namespace std::this_thread;

Color blueish = { 180, 205, 250, 255 }; // Thats a kind of purple blue. VERY NICE!
Color darkGray = { 45, 45, 45, 255 }; // Elegant dark gray, VERY NICE!
Color midnightBlue = { 50, 80, 130, 255 }; // Very deep and mysterious
Color steelBlue = { 70, 110, 160, 255 }; // Slightly brighter but cool and calm
Color softGold = { 255, 223, 96, 255 }; // Light gold, soft and elegant
Color deepGold = { 204, 168, 48, 255 }; // Rich gold, deep and classy
Color softCrimson = { 200, 50, 50, 255 }; // A softer, more muted red


Game::Game()
{
	menuStart = LoadTexture("assets/Start_A_Game.png");
	menuExit = LoadTexture("assets/Exit.png");
	displayFont = LoadFontEx("assets/Howdy.ttf", Font_Size, 0, 0);
	gameOverFont = LoadFontEx("assets/Howdy2.ttf", Game_Over_Font_Size, 0, 0);
	eatingSound = LoadSound("assets/Chomp.wav");
	boarderCollision = LoadSound("assets/Boarder_Collision.wav");
	backgroundMusic = LoadSound("assets/Background_Music.wav");
	score = 0;

	scoreTxt = new char[(Score_Len)];
}

Game::~Game()
{
	UnloadFont(displayFont);
	UnloadSound(eatingSound);
	UnloadSound(boarderCollision);
	UnloadSound(backgroundMusic);
	UnloadTexture(menuExit);
	UnloadTexture(menuStart);
	delete[]scoreTxt;
}

void Game::mainMenu()
{
	bool viewingExit = false;

	while (true)
	{
		// Handle key input to switch menu state
		if (IsKeyPressed(KEY_S))
		{
			viewingExit = true;
		}
		if (IsKeyPressed(KEY_W))
		{
			viewingExit = false;
		}

		// Start frame
		BeginDrawing();
		ClearBackground(BLACK);

		if (viewingExit)
		{
			DrawTextureEx(menuExit, Vector2{ 0, 0 }, 0, 1.0f, WHITE);
			if (IsKeyPressed(KEY_ENTER))
			{
				break;
			}
		}
		else
		{
			DrawTextureEx(menuStart, Vector2{ 0, 0 }, 0, 1.0f, WHITE);
			if (IsKeyPressed(KEY_ENTER))
			{
				score = 0;
				runGame();
			}
		}

		Vector2 textPosition = { 35, 450 }; // Adjust the position as needed
		DrawRectangle(10, 440, 566, 85, BLACK); // Black square
		DrawText("This game was made for educational purposes only.\n credit to The Key of Awesome YouTube channel. \nimages were taken from the 'Reggae Shark' song.",
			textPosition.x, textPosition.y, 20, WHITE);

		EndDrawing();
		StopSound(backgroundMusic);
		sleep_for(milliseconds(10)); // Keeps CPU cool
	}
}

void Game::runGame()
{
	Munchies food;
	RaggaeShark player;
	Seaweed animationObj[Seaweed_Amount];
	bool eating = false;
	int speedUp = 0;

	//Main game loop.
	while (!WindowShouldClose())
	{
		//Sets up the background music.
		if (!IsSoundPlaying(backgroundMusic))
		{
			PlaySound(backgroundMusic);
		}

		BeginDrawing();
		handleInput(player);

		//"Collision" with food
		if (Vector2Distance(food.getPos(), player.getLocation()) < 2.0f)
		{
			PlaySound(eatingSound);
			food.setNewPos();
			eating = true;
			incScore();
			//Manage game speed ! to a limit !
			if (speedUp <= (Game_Pace / 2))
			{
				speedUp += Food_Pace_Boost;
			}
		}

		//Player is out_of_bounds (?)
		if (player.body[0].x == Cell_Count - 1|| player.body[0].x == 1)
		{
			PlaySound(boarderCollision);
			gameOver();
			break;
		}
		if (player.body[0].y == Cell_Count - 1 || player.body[0].y == 1)
		{
			PlaySound(boarderCollision);
			gameOver();
			break;
		}
		if (player.hitHimself())
		{
			PlaySound(boarderCollision);
			gameOver();
			break;
		}

		handleInput(player);
		player.update(eating);
		loadScreen(player, food, animationObj, eating, speedUp);
		DrawTextEx(displayFont, "Raggae Shark", Vector2{Cell_Size + Boarder_Thickness , Y_Zero }, Font_Size, 2, BLACK);
		EndDrawing();

		eating = false;
		sleep_for(milliseconds(Game_Pace - speedUp));
	}
}

//Collects user's input, and adjust facing direction.
void Game::handleInput(RaggaeShark& player)	
{
	if (IsKeyPressed(KEY_W) && player.getFacing() != 'D')
	{
		player.dir = { 0, -1 };
		player.setFacing('U');
	}
	else if (IsKeyPressed(KEY_S) && player.getFacing() != 'U')
	{
		player.dir = { 0 , 1 };
		player.setFacing('D');
	}
	else if (IsKeyPressed(KEY_A) && player.getFacing() != 'R')
	{
		player.dir = { -1, 0 };
		player.setFacing('L');
	}
	else if (IsKeyPressed(KEY_D) && player.getFacing() != 'L')
	{
		player.dir = { 1,0 };
		player.setFacing('R');
	}
}

//Loads the whole screen, including the player and the food.
void Game::loadScreen(RaggaeShark& player, Munchies& food, Seaweed animationObj[Seaweed_Amount], bool eating, int speedUp)
{
	int i;

	//Outside color
	ClearBackground(steelBlue);

	// Draw game area background
	DrawRectangle((Cell_Size + (Cell_Count / 2)), (Cell_Size + (Cell_Count / 2)),(Cell_Size * (Cell_Count)), (Cell_Size * Cell_Count),blueish);

	//Panic not. below there is the drawing of the boarder!
	DrawRectangleLinesEx(Rectangle{ Boarder_Pos ,Boarder_Pos ,float((Cell_Size * Cell_Count)), float((Cell_Size * Cell_Count)) }, float(Boarder_Thickness), darkGray);
	food.draw();
	player.draw(eating);

	for (i = 0; i < Seaweed_Amount; i++)
	{
		animationObj[i].draw();
		animationObj[i].Animation(speedUp);
	}
	displayScore();
}

void Game::incScore()
{
	++score;
}

void Game::displayScore() const
{
	sprintf(scoreTxt, "Score: %d", score);
	DrawTextEx(displayFont, scoreTxt, Vector2({(Score_X_Location),Y_Zero}), Font_Size, 0 , softGold);
}

void Game::gameOver()
{
	BeginDrawing();
	DrawTextEx(gameOverFont, "Game Over.", Vector2({ ((Cell_Count*Cell_Count) / 5),((Cell_Count * Cell_Count) / 3) }), (Game_Over_Font_Size), 0, softCrimson);
	DrawTextEx(displayFont, scoreTxt, Vector2({ ((Cell_Count * Cell_Count) / 5),((Cell_Count * Cell_Count) / 2) }), (Font_Size), 0, deepGold);
	EndDrawing();
	sleep_for(seconds(4));
}