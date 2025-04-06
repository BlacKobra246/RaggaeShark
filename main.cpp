#include "gameManager.h"
#include "Munchies.h"

void main()
{

	cout << "Starting the game";
	InitWindow(((Boarder_Width) + Cell_Size * Cell_Count), (Boarder_Width) + (Cell_Size * Cell_Count), "Raggae Shark - Ben Vann");
	InitAudioDevice();
	SetTargetFPS(60);

	Game game;
	game.mainMenu();
	CloseWindow();	
}