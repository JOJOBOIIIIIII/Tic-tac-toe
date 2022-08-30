#pragma once

#include "game.h"

struct Player {

	bool isPlaying;
	Shape shape[3][3];

	Player();

	~Player();

	void render(SDL_Renderer* ren);

	bool isWinning(); //Check if winning

};