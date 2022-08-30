#include "Shape.h"


Shape::Shape() {
	placed = false;
	type = "square";
	color = "green";
};
Shape::Shape(std::string color, std::string type) {
	placed = false;
	type = color;
	color = type;
};

Shape::~Shape() {};

void Shape::render(SDL_Renderer* ren,int col,int row) {
	int red = 0, green = 0, blue = 0;
	if (color == "blue") {
		blue = 255;
	}
	else if (color == "red") {
		red = 255;
	}
	else if (color == "green") {
		green = 255;
	}

	
	SDL_SetRenderDrawColor(ren, red, green, blue, 255);
	SDL_Rect r = {275+col*100,195+row*100,50,50};
	SDL_RenderDrawRect(ren, &r);

};

