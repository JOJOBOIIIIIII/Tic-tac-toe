#include "player.h"

Player::Player() {}
Player::~Player() {};

void Player::render(SDL_Renderer* ren) {
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			if (shape[i][j].placed == 1) { //Render the player's shape if they were placed
				shape[i][j].render(ren,i,j);
			}
		}
	}
}

bool Player::isWinning() {

	bool win = false;
	for (int i = 0;i < 4;i++) {
		//std::cout << i << std::endl;
		if (win) return true; //will exit the loop if true
		if (shape[i][0].placed == 1 && shape[i][1].placed == 1 && shape[i][2].placed == 1) win =true; //check columns
		if (shape[0][i].placed == 1 && shape[1][i].placed == 1 && shape[2][i].placed == 1) win=true; //check rows
	} 
	if (shape[0][0].placed == 1 && shape[1][1].placed == 1 && shape[2][2].placed == 1) return true;
	if (shape[2][0].placed == 1 && shape[1][1].placed == 1 && shape[0][2].placed == 1) return true;


	return false;
}