#include "Text.h"
#include "log.h"

Text::Text() {
	//Initialize
    font = NULL;
	texture = NULL;
	width = 0;
	height = 0;
}

bool Text::openFont(int size) {
	if(font != NULL) {
		TTF_CloseFont(font);
	}

	TTF_Font* newFont = NULL;
	newFont = TTF_OpenFont("assets/fonts/Digital7.ttf", size);
	if(newFont == NULL) {
		LogTTF("TTF_OpenFont");
	}
	font = newFont;
	return font != NULL;
}

bool Text::loadText(const std::string &text) {
	//Free texture if it exists
	if(texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}

	SDL_Color textColor = {255, 255, 255};

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if(textSurface == NULL) {
		LogTTF("TTF_RenderText");
	} else {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if(texture == NULL) {
			LogSDL("CreateTextureFromSurface");
		} else {
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	return texture != NULL;
}

void Text::renderText(int x, int y, SDL_Rect* rect) {
	if(x == -1 || y == -1) {
		//Center position
		int centerX, centerY;

		if(rect != NULL) {
			centerX = rect->x + ((rect->w - width) / 2);
			centerY = rect->y + ((rect->h - height) / 2); 
		} else {
			int windowWidth, windowHeight;
			SDL_GetWindowSize(window, &windowWidth, &windowHeight);
			centerX = (windowWidth - width) / 2;
			centerY = (windowHeight - height) / 2;
		}

		x = (x == -1) ? centerX : x;
		y = (y == -1) ? centerY : y;
	}

	//Set rendering space and render to screen
	SDL_Rect newRect = {x, y, width, height};

	//Render to screen
	SDL_RenderCopy(renderer, texture, NULL, &newRect);
}