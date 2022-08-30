#pragma once
#include "SDL.h"
#include <iostream>
#include "SDL_image.h"


struct Shape {
	bool placed;
	std::string color;
	std::string type;
	void render(SDL_Renderer* ren,int c,int r);

	Shape();
	Shape(std::string color, std::string type);
	~Shape();
};

