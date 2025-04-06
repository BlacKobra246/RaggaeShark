#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "utillities.h"
#include "raggaeShark.h"
#include "munchies.h"
#include "seaweed.h"

class Game
{
	Font displayFont, gameOverFont;
	unsigned int score;
	char* scoreTxt = nullptr;
	Sound eatingSound, boarderCollision, backgroundMusic;
	Texture2D menuStart, menuExit;

	public:
		Game();
		~Game();
		void mainMenu();
		void runGame();
		void handleInput(RaggaeShark& player);
		void loadScreen(RaggaeShark& player, Munchies& food, Seaweed animationObj[Seaweed_Amount], bool eating, int speedUp);
		void incScore();	
		void displayScore() const;
		void gameOver();
};

#endif  // GAME_MANAGER_H
