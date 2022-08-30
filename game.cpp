#include "game.h"

SDL_Window* window;
SDL_Renderer* renderer;

//SelectionGrid<10,10>* grid = new SelectionGrid<10, 10>(0,0);     //long and repetitive

auto Grid = new SelectionGrid<3, 3>(0, 0); //This is way cleaner with the auto key word!  <columns, rows>(positionX,positionY)
Player players[2]; //List of players 
int p=0; //to get which player (0th or 1st player in the array)

Game::Game() {}; 
Game::~Game() {}; 


int Game::init(const char* title, int w, int h, bool fullscreen) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,w,h, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 120, 0, 200, 255); //Also the color of renderClear()
	
	//Center the whole gride
	Grid->xPos = (w/2) - Grid->columns*100/2;  
	Grid->yPos = (h/2) - Grid->rows*100/2;

	std::cout<< "Enter each player's color (red,green,blue)" << std::endl;
	std::string color1;
	std::cin >> color1;
	std::string color2;
	std::cin >> color2;

	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			players[0].shape[i][j].color = color1;
			players[1].shape[i][j].color = color2;
		}
	}
	

	return true;
};

void Game::handleEvents() {
	int LMBy;
	int LMBx;

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			//std::cout << "---Left pressed---" << std::endl;
			LMBx = event.button.x;
			LMBy = event.button.y;
			for (int r = 0;r < 3;r++) {
				for (int c = 0;c < 3;c++) {
					if (LMBx > Grid->grid[c][r].rect.x
						&& LMBx<Grid->grid[c][r].rect.x + Grid->grid[c][r].rect.w
						&& LMBy>Grid->grid[c][r].rect.y
						&& LMBy < Grid->grid[c][r].rect.y + Grid->grid[c][r].rect.h) {

						//std::cout << c << " "<<r<<std::endl;

						if (players[0].shape[c][r].placed == false && players[1].shape[c][r].placed == false) {
							players[p].shape[c][r].placed = true;
							std::cout << "PLACED (Player" << p+1 << ")" << std::endl;
							p = !p; //0 becomes 1 or 1 becomes 0 :)
						}
					}
				}
			}
		}
	case SDL_MOUSEMOTION:
		LMBx = event.button.x;
		LMBy = event.button.y;
		for (int r = 0;r < 3;r++) {
			for (int c = 0;c < 3;c++) {
				if (LMBx > Grid->grid[c][r].rect.x
					&& LMBx<Grid->grid[c][r].rect.x + Grid->grid[c][r].rect.w
					&& LMBy>Grid->grid[c][r].rect.y
					&& LMBy < Grid->grid[c][r].rect.y + Grid->grid[c][r].rect.h) {

					Grid->grid[c][r].glow = true;
				}
				else Grid->grid[c][r].glow = false;
			}
		}


	default:
		break;
	}
};

void Game::update() {
	Grid->update();
	if (players[0].isWinning()) { 
		std::cout << "Player 1 won!" << std::endl;
		isRunning = false;
	}
	if (players[1].isWinning()) { 
		std::cout << "Player 2 won!" << std::endl;
		isRunning = false;
	}
	
};

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);

	Grid->render(renderer);
	players[0].render(renderer);
	players[1].render(renderer);

	SDL_RenderPresent(renderer);
};

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
};